/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"
#include "scope.h"
#include "errors.h"
#include "codegen.h"


Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

void Program::Check() {
    nodeScope = new Scope();
    decls->DeclareAll(nodeScope);
    decls->CheckAll();
}
void Program::Emit() {
    /* pp4: here is where the code generation is kicked off.
     *      The general idea is perform a tree traversal of the
     *      entire program, generating instructions as you go.
     *      Each node can have its own way of translating itself,
     *      which makes for a great use of inheritance and
     *      polymorphism in the node classes.
     */
    bool found = false;
    for (int i = 0; i < decls-> NumElements(); i++) {
        Decl* d = decls-> Nth(i);
        if (!strcmp(d-> GetName(), "main") && d-> IsFnDecl()) {
            found = true;
            break;
        }
    }
    if (!found) {
        ReportError::NoMainFound();
    }
    CodeGenerator *cg = new CodeGenerator();
    decls-> EmitAll(cg);
    if (ReportError::NumErrors() == 0) {
        cg-> DoFinalCodeGen();
    }
}

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}

void StmtBlock::Check() {
    nodeScope = new Scope();
    decls->DeclareAll(nodeScope);
    decls->CheckAll();
    stmts->CheckAll();
}

Location *StmtBlock::Emit(CodeGenerator *cg) {
    decls-> EmitAll(cg);
    stmts-> EmitAll(cg);
    return NULL;
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) { 
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this); 
    (body=b)->SetParent(this);
}

void ConditionalStmt::Check() {
    if (!test->CheckAndComputeResultType()->IsCompatibleWith(Type::boolType))
	ReportError::TestNotBoolean(test);
    body->Check();
}


ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

Location *ForStmt::Emit(CodeGenerator *cg) {
    char *L_Before = cg-> NewLabel();
    char *L_After = cg-> NewLabel();
    L_End = L_After;
    init-> Emit(cg);
    cg-> GenLabel(L_Before);
    Location *t = test-> Emit(cg);
    cg-> GenIfZ(t, L_After);
    body-> Emit(cg);
    step-> Emit(cg);
    cg-> GenGoto(L_Before);
    cg-> GenLabel(L_After);
    return NULL;
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}

void IfStmt::Check() {
    ConditionalStmt::Check();
    if (elseBody) elseBody->Check();
}

Location *IfStmt::Emit(CodeGenerator *cg) {
    char *L_AfterIf = cg-> NewLabel();
    char *L_AfterElse;
    if (elseBody) {
        L_AfterElse = cg-> NewLabel();
    }
    Location *t = test-> Emit(cg);
    cg-> GenIfZ(t, L_AfterIf);
    body-> Emit(cg);
    if (elseBody) {
        cg-> GenGoto(L_AfterElse);
    }
    cg-> GenLabel(L_AfterIf);
    if (elseBody) {
        elseBody-> Emit(cg);
        cg-> GenLabel(L_AfterElse);
    }
    return NULL;
}

Location *WhileStmt::Emit(CodeGenerator *cg) {
    char *L_Before = cg-> NewLabel();
    char *L_After = cg-> NewLabel();
    L_End = L_After;
    cg-> GenLabel(L_Before);
    Location *t = test-> Emit(cg);
    cg-> GenIfZ(t, L_After);
    body-> Emit(cg);
    cg-> GenGoto(L_Before);
    cg-> GenLabel(L_After);
    return NULL;
}

void BreakStmt::Check() {
    if (!FindSpecificParent<LoopStmt>())
        ReportError::BreakOutsideLoop(this);
}

Location *BreakStmt::Emit(CodeGenerator *cg) {
    Node *p = parent;
    while (p) {
        if (dynamic_cast<LoopStmt *>(p)) {
            break;
        }
        p = p-> GetParent();
    }
    char *endLabel = dynamic_cast<LoopStmt *>(p)-> GetEndLabel();
    cg-> GenGoto(endLabel);
    return NULL;
}

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}

void ReturnStmt::Check() {
    Type *got = expr->CheckAndComputeResultType();
    Type *expected =  FindSpecificParent<FnDecl>()->GetReturnType();
    if (!got->IsCompatibleWith(expected))
	ReportError::ReturnMismatch(this, got, expected);
}

Location *ReturnStmt::Emit(CodeGenerator *cg) {
    Location *t = expr-> Emit(cg);
    cg-> GenReturn(t);
    return NULL;
}

PrintStmt::PrintStmt(List<Expr*> *a) {    
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}

void PrintStmt::Check() {
    for (int i = 0; i < args->NumElements();i++) {
	Type *t = args->Nth(i)->CheckAndComputeResultType();
	if (t->IsEquivalentTo(Type::errorType)) continue;
	if (!(t->IsEquivalentTo(Type::intType) || t->IsEquivalentTo(Type::stringType) || t->IsEquivalentTo(Type::boolType)))
	  ReportError::PrintArgMismatch(args->Nth(i),i + 1, t);
    }
}

Location *PrintStmt::Emit(CodeGenerator *cg) {
    for (int i = 0; i < args-> NumElements(); i++) {
        Expr *currArg = args-> Nth(i);
        Location *t = currArg-> Emit(cg);
        BuiltIn builtIn;
        if (currArg-> CheckAndComputeResultType()-> IsEquivalentTo(Type::intType)) {
            builtIn = BuiltIn::PrintInt;
        }
        if (currArg-> CheckAndComputeResultType()-> IsEquivalentTo(Type::stringType)) {
            builtIn = BuiltIn::PrintString;
        }
        if (currArg-> CheckAndComputeResultType()-> IsEquivalentTo(Type::boolType)) {
            builtIn = BuiltIn::PrintBool;
        }
        cg-> GenBuiltInCall(builtIn, t, NULL);
    }
    return NULL;
}
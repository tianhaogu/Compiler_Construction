/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"
#include "codegen.h"
#include "errors.h"
#include "scope.h"


Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

void Program::Check() {
    /* You can use your pp3 semantic analysis or leave it out if
     * you want to avoid the clutter.  We won't test pp4 against 
     * semantically-invalid programs.
     */
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
        if (!strcmp(d-> GetName(), "main") && d-> isFunct()) {
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

void StmtBlock::Emit(CodeGenerator *cg) {
    decls-> EmitAll(cg);
    stmts-> EmitAll(cg);
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) { 
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this); 
    (body=b)->SetParent(this);
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

void ForStmt::Emit(CodeGenerator *cg) {
    char *L_Before = cg-> NewLabel();
    char *L_After = cg-> NewLabel();
    cg-> GenLabel(L_Before);
    init-> Emit(cg);
    Location *t = test-> Emit(cg);
    cg-> GenIfZ(t, L_After);
    body-> Emit(cg);
    step-> Emit(cg);
    cg-> GenGoto(L_Before);
    cg-> GenLabel(L_After);
    L_End = L_After;
}

void WhileStmt::Emit(CodeGenerator *cg) {
    char *L_Before = cg-> NewLabel();
    char *L_After = cg-> NewLabel();
    cg-> GenLabel(L_Before);
    Location *t = test-> Emit(cg);
    cg-> GenIfZ(t, L_After);
    body-> Emit(cg);
    cg-> GenGoto(L_Before);
    cg-> GenLabel(L_After);
    L_End = L_After;
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}

// Not sure here...
void IfStmt::Emit(CodeGenerator *cg) {
    char *L_AfterIf = cg-> NewLabel();
    char *L_AfterElse = cg-> NewLabel();
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
}

void BreakStmt::Emit(CodeGenerator *cg) {
    Node *p = parent;
    while (p) {
        if (dynamic_cast<LoopStmt *>(p)) {
            break;
        }
        p = p-> GetParent();
    }
    char *endLabel = dynamic_cast<LoopStmt *>(p)-> GetEndLabel();
    cg-> GenGoto(endLabel);
}

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}

void ReturnStmt::Emit(CodeGenerator *cg) {
    Location *t = expr-> Emit(cg);
    cg-> GenReturn(t);
}
  
PrintStmt::PrintStmt(List<Expr*> *a) {    
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}

void PrintStmt::Emit(CodeGenerator *cg) {
    for (int i = 0; i < args-> NumElements(); i++) {
        Expr *currArg = args-> Nth(i);
        Location *t = currArg-> Emit(cg);
        BuiltIn builtIn;
        if (currArg-> CheckType()-> IsEquivalentTo(Type::intType)) {
            builtIn = BuiltIn::PrintInt;
        }
        if (currArg-> CheckType()-> IsEquivalentTo(Type::stringType)) {
            builtIn = BuiltIn::PrintString;
        }
        if (currArg-> CheckType()-> IsEquivalentTo(Type::boolType)) {
            builtIn = BuiltIn::PrintBool;
        }
        cg-> GenBuiltInCall(builtIn, t, NULL);
    }
}

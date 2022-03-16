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

Program::Program(List<Decl *> *d)
{
    Assert(d != NULL);
    (decls = d)->SetParentAll(this);
}

void Program::Check()
{
    /* pp3: here is where the semantic analyzer is kicked off.
     *      The general idea is perform a tree traversal of the
     *      entire program, examining all constructs for compliance
     *      with the semantic rules.  Each node can have its own way of
     *      checking itself, which makes for a great use of inheritance
     *      and polymorphism in the node classes.
     */
    scope = new Scope();
    decls->DeclareAll(scope);
    decls->CheckAll();
}

StmtBlock::StmtBlock(List<VarDecl *> *d, List<Stmt *> *s)
{
    Assert(d != NULL && s != NULL);
    (decls = d)->SetParentAll(this);
    (stmts = s)->SetParentAll(this);
}

void StmtBlock::Check()
{
    scope = new Scope();
    decls->DeclareAll(scope);
    decls->CheckAll();
    stmts->CheckAll();
}

IntConst::IntConst(yyltype loc, int val) : Stmt(loc)
{
    value = val;
}

CaseExpr::CaseExpr(IntConst *t, List<Stmt *> *s)
{
    Assert(t != NULL && s != NULL);
    (test = t)->SetParent(this);
    (stmts = s)->SetParentAll(this);
}

void CaseExpr::Check()
{
    scope = new Scope();
    stmts->CheckAll();
}

DefaultBlock::DefaultBlock(List<Stmt *> *s)
{
    Assert(s != NULL);
    (stmts = s)->SetParentAll(this);
}

void DefaultBlock::Check()
{
    scope = new Scope();
    stmts->CheckAll();
}

SwitchStmt::SwitchStmt(Expr *t, List<CaseExpr *> *s, DefaultBlock *d)
{
    Assert(t != NULL && s != NULL);
    (test = t)->SetParent(this);
    (stmts = s)->SetParentAll(this);
    if (d != NULL)
    {
        (defaultBody = d)->SetParent(this);
    }
    else
    {
        defaultBody = NULL;
    }
}

void SwitchStmt::Check()
{
    scope = new Scope();
    Type *t = test->CheckType();
    if (!t->IsEquivalentTo(Type::intType))
    {
        ReportError::TestNotBoolean(test);
    }
    stmts->CheckAll();
    defaultBody->Check();
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b)
{
    Assert(t != NULL && b != NULL);
    (test = t)->SetParent(this);
    (body = b)->SetParent(this);
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b) : LoopStmt(t, b)
{
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init = i)->SetParent(this);
    (step = s)->SetParent(this);
}

void ForStmt::Check()
{
    scope = new Scope();
    init->Check();
    Type *t = test->CheckType();
    if (!t->IsEquivalentTo(Type::boolType) &&
        !t->IsEquivalentTo(Type::errorType))
    {
        ReportError::TestNotBoolean(test);
    }
    step->Check();
    body->Check();
}

void WhileStmt::Check()
{
    scope = new Scope();
    Type *t = test->CheckType();
    if (!t->IsEquivalentTo(Type::boolType) &&
        !t->IsEquivalentTo(Type::errorType))
    {
        ReportError::TestNotBoolean(test);
    }
    body->Check();
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb) : ConditionalStmt(t, tb)
{
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody)
        elseBody->SetParent(this);
}

void IfStmt::Check()
{
    scope = new Scope();
    Type *t = test->CheckType();
    if (!t->IsEquivalentTo(Type::boolType) &&
        !t->IsEquivalentTo(Type::errorType))
    {
        ReportError::TestNotBoolean(test);
    }
    body->Check();
    if (elseBody)
    {
        elseBody->Check();
    }
}

void BreakStmt::Check()
{
    scope = new Scope();
    Node *p = parent;
    while (p)
    {
        if (dynamic_cast<LoopStmt *>(p))
        {
            return;
        }
        p = p->GetParent();
    }
    ReportError::BreakOutsideLoop(this);
}

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc)
{
    Assert(e != NULL);
    (expr = e)->SetParent(this);
}

void ReturnStmt::Check()
{
    scope = new Scope();
    Type *t = expr->CheckType();
    Node *p = parent;
    while (p)
    {
        if (dynamic_cast<FnDecl *>(p))
        {
            Type *returnType = dynamic_cast<FnDecl *>(p)->getReturnType();
            if (!t->IsEquivalentTo(returnType) &&
                !(t->IsEquivalentTo(Type::nullType) && returnType->IsEquivalentTo(Type::voidType)) &&
                !t->IsEquivalentTo(Type::errorType))
            {
                ReportError::ReturnMismatch(this, t, returnType);
            }
            break;
        }
        p = p->GetParent();
    }
}

PrintStmt::PrintStmt(List<Expr *> *a)
{
    Assert(a != NULL);
    (args = a)->SetParentAll(this);
}

void PrintStmt::Check()
{
    scope = new Scope();
    for (int i = 0; i < args->NumElements(); ++i)
    {
        Type *t = args->Nth(i)->CheckType();
        if (!t->IsEquivalentTo(Type::intType) &&
            !t->IsEquivalentTo(Type::boolType) &&
            !t->IsEquivalentTo(Type::stringType) &&
            !t->IsEquivalentTo(Type::errorType))
        {
            ReportError::PrintArgMismatch(args->Nth(i), i+1, t);
        }
    }
}

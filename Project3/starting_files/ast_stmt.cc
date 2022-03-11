/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"
#include "scope.h"

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
    s = new Scope();
    decls->DeclareAll(s);
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

DefaultBrack::DefaultBrack(List<Stmt *> *s)
{
    Assert(s != NULL);
    (stmts = s)->SetParentAll(this);
}

SwitchStmt::SwitchStmt(Expr *t, List<CaseExpr *> *s, DefaultBrack *d)
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

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb) : ConditionalStmt(t, tb)
{
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody)
        elseBody->SetParent(this);
}

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc)
{
    Assert(e != NULL);
    (expr = e)->SetParent(this);
}

ReturnStmt::Check() {
    expr-> Check();

    Type *given = expr-> CheckType();
    Type *expected = NULL;
    Decl *d = NULL;
    while (d-> GetParent() != NULL) {
        d = d-> GetParent();
        if (d-> isFunct()) {
            break;
        }
    }
    if (d-> isFunct()) {
        expected = d-> GetType();
    }
    if (expected != NULL && (!given-> IsEquivalentTo(expected))) {
        ReportError::ReturnMismatch(this, given, expected);
    }
}

PrintStmt::PrintStmt(List<Expr *> *a)
{
    Assert(a != NULL);
    (args = a)->SetParentAll(this);
}

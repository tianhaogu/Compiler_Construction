/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
#include "errors.h"

Decl::Decl(Identifier *n) : Node(*n->GetLocation())
{
    Assert(n != NULL);
    (id = n)->SetParent(this);
}

// bool Decl::ConflictsWithPrevious(Decl *prev)
// {
//     if (prev == NULL || prev == this)
//         return false;
//     ReportError::DeclConflict(this, prev);
//     return true;
// }

VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n)
{
    Assert(n != NULL && t != NULL);
    (type = t)->SetParent(this);
}

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType *> *imp, List<Decl *> *m) : Decl(n)
{
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);
    extends = ex;
    if (extends)
        extends->SetParent(this);
    (implements = imp)->SetParentAll(this);
    (members = m)->SetParentAll(this);
    t = new NamedType(n);
    t->SetParent(this);
    inters = NULL;
}

void ClassDecl::Check() 
{
    if (extends)
    {   
        if (!(extends->getDecl() && extends->getDecl()->isClass()))
        {
            ReportError::IdentifierNotDeclared(extends->getID(), LookingForClass);
            extends = NULL;
        }
    }
    for (int i = 0; i < implements->NumElements(); ++i) 
    {
        NamedType *n = implements->Nth(i);
        if (!(n && n->getDecl() && n->getDecl()->isFunct())) 
        {
            ReportError::IdentifierNotDeclared(n->getID(), LookingForInterface);
            implements->RemoveAt(i);
            --i;
        }
    }
    GetScope();
    for (int i = 0; i < members->NumElements(); ++i) 
    {
        Decl *d = members->Nth(i);
        for (int j = 0; j < inters->NumElements(); ++j) 
        {
            inters->Nth(j)->Remove(d);
        }
    }
    for (int i = 0; i < inters->NumElements(); ++i) 
    {
        if (inters->Nth(i)->NumEntries() > 0) 
        {
            ReportError::InterfaceNotImplemented(this, implements->Nth(i));
        }
    }
    members->CheckAll();
}

Scope *ClassDecl::GetScope() 
{
    if (scope != NULL) {
        return scope;
    } else {
        scope = new Scope();
    }
    if (extends)
    {
        scope->Copy(extends->GetScope());
    }
    inters = new List<Scope *>;
    for (int i = 0; i < implements->NumElements(); ++i) {
        inters->Append(new Scope());
        inters->Nth(i)->Copy(implements->Nth(i)->GetScope());
        scope->Copy(implements->Nth(i)->GetScope());
    }
    members->DeclareAll(scope);
    return scope;
}

InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl *> *m) : Decl(n)
{
    Assert(n != NULL && m != NULL);
    (members = m)->SetParentAll(this);
}

void InterfaceDecl::Check()
{
    GetScope();
    members->CheckAll();
}

Scope *InterfaceDecl::GetScope()
{
    if (scope)
    {
        return scope;
    }
    scope = new Scope();
    members->DeclareAll(scope);
    return scope;
}

FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl *> *d) : Decl(n)
{
    Assert(n != NULL && r != NULL && d != NULL);
    (returnType = r)->SetParent(this);
    (formals = d)->SetParentAll(this);
    body = NULL;
}

void FnDecl::SetFunctionBody(Stmt *b)
{
    (body = b)->SetParent(this);
}

bool FnDecl::IsEquivalentTo(FnDecl *fn)
{
    if (!returnType->IsEquivalentTo(fn->returnType) ||
        formals->NumElements() != fn->formals->NumElements())
    {
        return false;
    }
    for (int i = 0; i < formals->NumElements(); ++i)
    {
        if (!formals->Nth(i)->GetType()->IsEquivalentTo(fn->formals->Nth(i)->GetType()))
        {
            return false;
        }
    }
    return true;
}

void FnDecl::Check()
{
    returnType->Check();
    scope = new Scope();
    formals->DeclareAll(scope);
    formals->CheckAll();
    if (body != NULL)
    {
        body->Check();
    }
}

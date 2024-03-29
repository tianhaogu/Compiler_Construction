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
    scope = NULL;
    parents = new Hashtable<const char *>;
}

void ClassDecl::Check()
{
    if (extends)
    {
        Decl *d = parent->FindDecl(extends->getID());
        if (!(d && d->isClass()))
        {
            ReportError::IdentifierNotDeclared(extends->getID(), LookingForClass);
            extends = NULL;
        }
        if (extends)
        {
            ClassDecl *cd = dynamic_cast<ClassDecl *>(d);
            Iterator<const char *> i = cd->parents->GetIterator();
            const char *tempC = i.GetNextValue();
            while (tempC)
            {
                parents->Enter(tempC, tempC);
                tempC = i.GetNextValue();
            }
            parents->Enter(extends->GetTypeName(), extends->GetTypeName());
        }
    }
    for (int i = 0; i < implements->NumElements(); ++i)
    {
        NamedType *n = implements->Nth(i);
        Decl *d = parent->FindDecl(n->getID());
        if (!(n && d && d->isInter()))
        {
            ReportError::IdentifierNotDeclared(n->getID(), LookingForInterface);
            implements->RemoveAt(i);
            --i;
        }
        else
        {
            parents->Enter(d->GetName(), d->GetName());
        }
    }
    GetScope();
    for (int i = 0; i < members->NumElements(); ++i)
    {
        Decl *d = members->Nth(i);
        for (int j = 0; j < inters->NumElements(); ++j)
        {
            // Decl *d_old = inters->Nth(j)->Find(d->getID());
            // if (dynamic_cast<FnDecl *>(d) && 
            //     dynamic_cast<FnDecl *>(d_old) && 
            //     !dynamic_cast<FnDecl *>(d)->IsEquivalentTo(dynamic_cast<FnDecl *>(d_old)))
            // {
            //     ReportError::OverrideMismatch(d);
            // }
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
    Hashtable<const char *> *flag = new Hashtable<const char *>;
    Iterator<Decl *> i = scope->GetIter();
    Decl *tempDecl = i.GetNextValue();
    const char *tempC = tempDecl ? tempDecl->GetName() : NULL;
    while (tempC)
    {
        flag->Enter(tempC, tempC);
        tempDecl = i.GetNextValue();
        tempC = tempDecl ? tempDecl->GetName() : NULL;
    }
    members->DeclareAll(scope, flag);
    members->CheckAll();
}

Scope *ClassDecl::GetScope()
{
    if (scope != NULL)
    {
        return scope;
    }
    else
    {
        scope = new Scope();
    }
    if (extends)
    {
        Decl *d = parent->FindDecl(extends->getID());
        scope->Copy(d->GetScope());
    }
    inters = new List<Scope *>;
    for (int i = 0; i < implements->NumElements(); ++i)
    {
        inters->Append(new Scope());
        NamedType *n = implements->Nth(i);
        Decl *d = parent->FindDecl(n->getID());
        inters->Nth(i)->Copy(d->GetScope());
        scope->Copy(d->GetScope());
    }
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
        VarDecl *formal = formals->Nth(i);
        VarDecl *fn_formal = fn->formals->Nth(i);
        if (!formal->GetType()->IsEquivalentTo(fn_formal->GetType())
            // || !(strcmp(formal->GetName(), fn_formal->GetName()) == 0)
            )
        {
            return false;
        }
    }
    return true;
}

void FnDecl::Check()
{
    scope = new Scope();
    returnType->Check();
    formals->DeclareAll(scope);
    formals->CheckAll();
    if (body != NULL)
    {
        body->Check();
    }
}

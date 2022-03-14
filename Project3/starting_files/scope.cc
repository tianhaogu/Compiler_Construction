#include "scope.h"
#include "list.h"
#include "ast.h"
#include "ast_decl.h"
#include "errors.h"

Decl *Scope::Find(Identifier *id)
{
    const char *c = id->GetName();

    return t->Lookup(id->GetName());
}

void Scope::Remove(Decl *d)
{
    t->Remove(d->GetName(), t->Lookup(d->GetName()));
}

bool Scope::Declare(Decl *d, bool flag)
{
    Decl *d_old = t->Lookup(d->GetName());
    if (d_old)
    {
        if ((dynamic_cast<ClassDecl *>(d->GetParent()) != NULL ||
             dynamic_cast<InterfaceDecl *>(d->GetParent()) != NULL) &&
            (dynamic_cast<ClassDecl *>(d_old->GetParent()) != NULL ||
             dynamic_cast<InterfaceDecl *>(d_old->GetParent()) != NULL) &&
            (d->GetParent() != d_old->GetParent() || flag))
        {
            FnDecl *fn = dynamic_cast<FnDecl *>(d);
            FnDecl *fn_old = dynamic_cast<FnDecl *>(d_old);
            if (fn->IsEquivalentTo(fn_old))
            {
                if (flag)
                {
                    t->Remove(d->GetName(), t->Lookup(d->GetName()));
                }
                t->Enter(d->GetName(), d);
                return true;
            }
            else
            {
                ReportError::OverrideMismatch(fn);
                return false;
            }
        }
        else
        {
            ReportError::DeclConflict(d, d_old);
            return false;
        }
    }
    t->Enter(d->GetName(), d);
    return true;
}

void Scope::Copy(Scope *s)
{
    Iterator<Decl *> i = s->t->GetIterator();
    for (Decl *d = i.GetNextValue(); d != NULL; d = i.GetNextValue())
    {
        t->Enter(d->GetName(), d);
    }
}

int Scope::NumEntries()
{
    return t->NumEntries();
}

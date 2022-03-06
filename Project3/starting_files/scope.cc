#include "scope.h"
#include "list.h"
#include "ast.h"
#include "ast_decl.h"

Decl *Scope::Find(Identifier *id) {
    return t.Lookup(id->GetName());
}

bool Scope::Declare(Decl *d) {




    t.Enter(d->GetName(), d);
    return true;
}

void Scope::Copy(Scope *s) {
    Iterator<Decl *> i = s->t.GetIterator();
    for (Decl *d = i.GetNextValue(); d != NULL; d = i.GetNextValue()) {
        t.Enter(d->GetName(), d);
    }
}

/* File: ast.cc
 * ------------
 */

#include "ast.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h> // strdup
#include <stdio.h>  // printf

Node::Node(yyltype loc)
{
    location = new yyltype(loc);
    parent = NULL;
    scope = NULL;
}

Node::Node()
{
    location = NULL;
    parent = NULL;
    scope = NULL;
}

Decl *Node::FindDecl(Identifier *id)
{
    scope = (scope == NULL) ? GetScope() : scope;
    Decl *d = scope->Find(id);
    if (d)
    {
        return d;
    }
    else if (parent)
    {
        return parent->FindDecl(id);
    }
    else
    {
        return NULL;
    }
}

Identifier::Identifier(yyltype loc, const char *n) : Node(loc)
{
    name = strdup(n);
}

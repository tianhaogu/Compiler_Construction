/* File: ast_type.cc
 * -----------------
 * Implementation of type node classes.
 */
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>
#include "errors.h"

/* Class constants
 * ---------------
 * These are public constants for the built-in base types (int, double, etc.)
 * They can be accessed with the syntax Type::intType. This allows you to
 * directly access them and share the built-in types where needed rather that
 * creates lots of copies.
 */

Type *Type::intType = new Type("int");
Type *Type::doubleType = new Type("double");
Type *Type::voidType = new Type("void");
Type *Type::boolType = new Type("bool");
Type *Type::nullType = new Type("null");
Type *Type::stringType = new Type("string");
Type *Type::errorType = new Type("error");

Type::Type(const char *n)
{
    Assert(n);
    typeName = strdup(n);
}

NamedType::NamedType(Identifier *i) : Type(*i->GetLocation())
{
    Assert(i != NULL);
    (id = i)->SetParent(this);
    d = NULL;
    error = false;
}

bool NamedType::isAssignableTo(Type *other)
{
    if (!error)
    {
        if (!d)
        {
            Decl *tempD = FindDecl(id);
            if (tempD && (tempD->isClass() || tempD->isInter()))
            {
                d = tempD;
            }
            ClassDecl *cDecl = dynamic_cast<ClassDecl *>(d);
            if (d && d->isClass() && cDecl)
            {
                if (cDecl->isParent(other->GetTypeName()))
                {
                    return true;
                }
            }
        }
        else
        {
            ClassDecl *cDecl = dynamic_cast<ClassDecl *>(d);
            if (d && d->isClass() && cDecl)
            {
                if (cDecl->isParent(other->GetTypeName()))
                {
                    return true;
                }
            }
        }
    }
    return IsEquivalentTo(other);
}

void NamedType::Check(bool c)
{
    if (!d && ((error < 1) || (c && (error < 2))))
    {
        Decl *tempD = FindDecl(id);
        if (tempD && (tempD->isClass() || tempD->isInter()))
        {
            d = tempD;
        }
        else
        {
            if (c)
            {
                ReportError::IdentifierNotDeclared(id, LookingForType);
                error = 2;
            }
            else
            {
                error = 1;
            }
        }
    }
}

ArrayType::ArrayType(yyltype loc, Type *et) : Type(loc)
{
    Assert(et != NULL);
    (elemType = et)->SetParent(this);
    error = false;
}

bool ArrayType::IsEquivalentTo(Type *t)
{
    if (strcmp(t->GetTypeName(), "[]"))
    {
        return false;
    }
    else
    {
        return elemType->IsEquivalentTo(dynamic_cast<ArrayType *>(t)->getElementType());
    }
}

void ArrayType::Check(bool c)
{
    elemType->Check(c);
}

/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>
#include "errors.h"

IntConstant::IntConstant(yyltype loc, int val) : Expr(loc)
{
    value = val;
    t = Type::intType;
}

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc)
{
    value = val;
    t = Type::doubleType;
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc)
{
    value = val;
    t = Type::boolType;
}

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc)
{
    Assert(val != NULL);
    value = strdup(val);
    t = Type::stringType;
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc)
{
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
}

CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r)
    : Expr(Join(l->GetLocation(), r->GetLocation()))
{
    Assert(l != NULL && o != NULL && r != NULL);
    (op = o)->SetParent(this);
    (left = l)->SetParent(this);
    (right = r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r)
    : Expr(Join(o->GetLocation(), r->GetLocation()))
{
    Assert(o != NULL && r != NULL);
    left = NULL;
    (op = o)->SetParent(this);
    (right = r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Expr *l, Operator *o)
    : Expr(Join(l->GetLocation(), o->GetLocation()))
{
    Assert(l != NULL && o != NULL);
    left = NULL;
    (op = o)->SetParent(this);
    (left = l)->SetParent(this);
}

Type *ArithmeticExpr::CheckType()
{
    if (t)
    {
        return t;
    }
    Type *l = NULL;
    Type *r = NULL;
    if (left)
    {
        l = left->CheckType();
    }
    r = right->CheckType();
    if (l && r)
    {
        if (!(r->IsEquivalentTo(Type::intType) ||
              r->IsEquivalentTo(Type::doubleType) ||
              r->IsEquivalentTo(Type::errorType)) ||
            !(l->IsEquivalentTo(Type::intType) ||
              l->IsEquivalentTo(Type::doubleType) ||
              l->IsEquivalentTo(Type::errorType)) ||
            !(r->IsEquivalentTo(l) ||
              r->IsEquivalentTo(Type::errorType) ||
              l->IsEquivalentTo(Type::errorType)))
        {
            ReportError::IncompatibleOperands(op, l, r);
            t = Type::errorType;
            return Type::errorType;
        }
    }
    else if (r)
    {
        if (!(r->IsEquivalentTo(Type::intType) ||
              r->IsEquivalentTo(Type::doubleType) ||
              r->IsEquivalentTo(Type::errorType)))
        {
            ReportError::IncompatibleOperand(op, r);
            t = Type::errorType;
            return Type::errorType;
        }
    }
    t = r;
    return r;
}

Type *PostfixExpr::CheckType()
{
    if (t)
    {
        return t;
    }
    Type *l = NULL;
    if (left)
    {
        l = left->CheckType();
    }
    if (!(l->IsEquivalentTo(Type::intType) ||
          l->IsEquivalentTo(Type::errorType)))
    {
        ReportError::IncompatibleOperand(op, l);
    }
    t = Type::intType;
    return Type::intType;
}

Type *RelationalExpr::CheckType()
{
    if (t)
    {
        return t;
    }
    Type *l = left->CheckType();
    Type *r = right->CheckType();
    if (!(r->IsEquivalentTo(Type::intType) ||
          r->IsEquivalentTo(Type::doubleType) ||
          r->IsEquivalentTo(Type::errorType)) ||
        !(l->IsEquivalentTo(Type::intType) ||
          l->IsEquivalentTo(Type::doubleType) ||
          l->IsEquivalentTo(Type::errorType)) ||
        !(r->IsEquivalentTo(l) ||
          r->IsEquivalentTo(Type::errorType) ||
          l->IsEquivalentTo(Type::errorType)))
    {
        ReportError::IncompatibleOperands(op, l, r);
    }
    t = Type::boolType;
    return Type::boolType;
}

Type *EqualityExpr::CheckType()
{
    if (t)
    {
        return t;
    }
    Type *l = left->CheckType();
    Type *r = right->CheckType();
    if (!r->IsEquivalentTo(l) && 
        !l->IsEquivalentTo(r) && 
        !l->IsEquivalentTo(Type::errorType) && 
        !r->IsEquivalentTo(Type::errorType) &&
        !(dynamic_cast<NamedType *>(r) && l->IsEquivalentTo(Type::nullType)) &&
        !(dynamic_cast<NamedType *>(l) && r->IsEquivalentTo(Type::nullType)))
    {
        ReportError::IncompatibleOperands(op, l, r);
    }
    t = Type::boolType;
    return Type::boolType;
}

Type *LogicalExpr::CheckType()
{
    if (t)
    {
        return t;
    }
    Type *l = NULL;
    Type *r = NULL;
    if (left)
    {
        l = left->CheckType();
    }
    r = right->CheckType();
    if (l && r)
    {
        if (!(r->IsEquivalentTo(Type::boolType) ||
              r->IsEquivalentTo(Type::errorType)) ||
            !(l->IsEquivalentTo(Type::boolType) ||
              l->IsEquivalentTo(Type::errorType)))
        {
            ReportError::IncompatibleOperands(op, l, r);
        }
    }
    else if (r)
    {
        if (!(r->IsEquivalentTo(Type::boolType) ||
              r->IsEquivalentTo(Type::errorType)))
        {
            ReportError::IncompatibleOperand(op, r);
        }
    }
    t = Type::boolType;
    return Type::boolType;
}

Type *AssignExpr::CheckType()
{
    if (t)
    {
        return t;
    }
    Type *l = left->CheckType();
    Type *r = right->CheckType();
    if (!(r->IsEquivalentTo(l) ||
          r->IsEquivalentTo(Type::errorType) ||
          l->IsEquivalentTo(Type::errorType)))
    {
        ReportError::IncompatibleOperands(op, l, r);
        t = Type::errorType;
        return Type::errorType;
    }
    if (l->IsEquivalentTo(Type::errorType))
    {
        t = r;
        return r;
    }
    t = l;
    return t;
}

Type *This::CheckType()
{
    if (t)
    {
        return t;
    }
    Node *p = parent;
    while (p)
    {
        if (dynamic_cast<ClassDecl *>(p))
        {
            t = dynamic_cast<ClassDecl *>(p)->GetType();
            return t;
        }
        p = p->GetParent();
    }
    ReportError::ThisOutsideClassScope(this);
    t = Type::errorType;
    return Type::errorType;
}

ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc)
{
    (base = b)->SetParent(this);
    (subscript = s)->SetParent(this);
}

Type *ArrayAccess::CheckType()
{
    if (t)
    {
        return t;
    }
    Type *tempType;
    tempType = base->CheckType();
    if (dynamic_cast<ArrayType *>(tempType) == NULL)
    {
        ReportError::BracketsOnNonArray(base);
    }
    tempType = subscript->CheckType();
    if (!tempType->IsEquivalentTo(Type::intType) &&
        !tempType->IsEquivalentTo(Type::errorType))
    {
        ReportError::SubscriptNotInteger(subscript);
    }
    tempType = base->CheckType();
    if (dynamic_cast<ArrayType *>(tempType) == NULL)
    {
        t = Type::errorType;
    }
    else
    {
        t = dynamic_cast<ArrayType *>(tempType)->getElementType();
    }
    return t;
}

FieldAccess::FieldAccess(Expr *b, Identifier *f)
    : LValue(b ? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation())
{
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base)
        base->SetParent(this);
    (field = f)->SetParent(this);
}

Type *FieldAccess::CheckType()
{
    if (t)
    {
        return t;
    }
    Decl *d = NULL;
    Type *cType = NULL;
    if (base)
    {
        cType = base->CheckType();
        if (cType->IsEquivalentTo(Type::errorType))
        {
            t = Type::errorType;
            return t;
        }
        NamedType *nType = dynamic_cast<NamedType *>(cType);
        if (nType != NULL)
        {
            d = FindDecl(nType->getID());
        }
        if (nType != NULL && d == NULL)
        {
            ReportError::IdentifierNotDeclared(nType->getID(), LookingForClass);
            t = Type::errorType;
            return t;
        }
        if (d == NULL || d->FindDecl(field) == NULL)
        {
            ReportError::FieldNotFoundInBase(field, cType);
            t = Type::errorType;
            return t;
        }
        bool inClass = false;
        Node *p = parent;
        while (p)
        {
            if (dynamic_cast<ClassDecl *>(p))
            {
                inClass = true;
                break;
            }
            p = p->GetParent();
        }
        if (!inClass)
        {
            ReportError::InaccessibleField(field, cType);
            t = Type::errorType;
            return t;
        }
    }
    else
    {
        bool inClass = false;
        Node *p = parent;
        while (p)
        {
            if (dynamic_cast<ClassDecl *>(p))
            {
                inClass = true;
                break;
            }
            p = p->GetParent();
        }
        if (inClass)
        {
            cType = dynamic_cast<ClassDecl *>(p)->GetType();
            d = FindDecl(field);
            if (d == NULL)
            {
                ReportError::FieldNotFoundInBase(field, cType);
                t = Type::errorType;
                return t;
            }
        }
        else 
        {
            const char *w = field->GetName();
            d = FindDecl(field);
            if (d == NULL)
            {
                ReportError::IdentifierNotDeclared(field, LookingForVariable);
                t = Type::errorType;
                return t;
            }
        }
    }

    if (dynamic_cast<VarDecl *>(d) == NULL)
    {
        ReportError::IdentifierNotDeclared(field, LookingForVariable);
        t = Type::errorType;
    }
    else
    {
        t = dynamic_cast<VarDecl *>(d)->GetType();
    }
    return t;
}

Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr *> *a) : Expr(loc)
{
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base)
        base->SetParent(this);
    (field = f)->SetParent(this);
    (actuals = a)->SetParentAll(this);
}

Type *Call::CheckType()
{
    if (t)
    {
        return t;
    }
    Decl *d = NULL;
    Type *cType = NULL;
    if (base)
    {
        cType = base->CheckType();
        if (cType->IsEquivalentTo(Type::errorType))
        {
            for (int i = 0; i < actuals->NumElements(); ++i)
            {
                actuals->Nth(i)->Check();
            }
            t = Type::errorType;
            return t;
        }
        NamedType *nType = dynamic_cast<NamedType *>(cType);
        if (nType != NULL)
        {
            d = FindDecl(nType->getID());
        }
        if (nType != NULL && d == NULL)
        {
            ReportError::IdentifierNotDeclared(nType->getID(), LookingForClass);
            for (int i = 0; i < actuals->NumElements(); ++i)
            {
                actuals->Nth(i)->Check();
            }
            t = Type::errorType;
            return t;
        }
        if (d == NULL || d->FindDecl(field) == NULL)
        {
            ReportError::FieldNotFoundInBase(field, cType);
            for (int i = 0; i < actuals->NumElements(); ++i)
            {
                actuals->Nth(i)->Check();
            }
            t = Type::errorType;
            return t;
        }
        d = d->FindDecl(field);





        // cType = base->CheckType();
        // if (cType->IsEquivalentTo(Type::errorType))
        // {
        //     for (int i = 0; i < actuals->NumElements(); ++i)
        //     {
        //         actuals->Nth(i)->Check();
        //     }
        //     t = Type::errorType;
        //     return t;
        // }
        // NamedType *nType = dynamic_cast<NamedType *>(cType);
        // if (nType != NULL)
        // {
        //     d = FindDecl(nType->getID());
        // }
        // if (d == NULL)
        // {
        //     ReportError::IdentifierNotDeclared(nType->getID(), LookingForClass);
        //     for (int i = 0; i < actuals->NumElements(); ++i)
        //     {
        //         actuals->Nth(i)->Check();
        //     }
        //     t = Type::errorType;
        //     return t;
        // }
        // d = d->FindDecl(field);
        // if (d == NULL)
        // {
        //     ReportError::FieldNotFoundInBase(field, cType);
        //     t = Type::errorType;
        //     return t;
        // }
    }
    else
    {
        // bool inClass = false;
        // Node *p = parent;
        // while (p)
        // {
        //     if (dynamic_cast<ClassDecl *>(p))
        //     {
        //         // inClass = true;
        //         break;
        //     }
        //     p = p->GetParent();
        // }
        // if (inClass)
        // {
        //     cType = dynamic_cast<ClassDecl *>(p)->GetType();
        //     d = FindDecl(field);
        //     if (d == NULL)
        //     {
        //         ReportError::FieldNotFoundInBase(field, cType);
        //         t = Type::errorType;
        //         return t;
        //     }
        // }
        // else
        // {
        d = FindDecl(field);
        if (d == NULL)
        {
            ReportError::IdentifierNotDeclared(field, LookingForFunction);
            t = Type::errorType;
            return t;
        }
        // }
    }

    if (dynamic_cast<FnDecl *>(d) == NULL)
    {
        ReportError::IdentifierNotDeclared(field, LookingForFunction);
        t = Type::errorType;
    }
    else
    {
        FnDecl *f = dynamic_cast<FnDecl *>(d);
        t = f->getReturnType();
        List<VarDecl *> *f_formals = f->getFormals();
        int num_actual = actuals->NumElements();
        int num_expect = f_formals->NumElements();
        if (num_actual != num_expect)
        {
            ReportError::NumArgsMismatch(field, num_expect, num_actual);
        }
        int num_comp = num_actual > num_expect ? num_expect : num_actual;
        for (int i = 0; i < num_comp; ++i)
        {
            Type *t_actual = actuals->Nth(i)->CheckType();
            Type *t_expect = f_formals->Nth(i)->GetType();
            if (!t_actual->IsEquivalentTo(Type::errorType) &&
                !t_expect->IsEquivalentTo(Type::errorType) &&
                !t_expect->IsEquivalentTo(t_actual))
            {
                ReportError::ArgMismatch(actuals->Nth(i), i+1, t_actual, t_expect);
            }
        }
        for (int i = num_comp; i < num_actual; ++i)
        {
            actuals->Nth(i)->Check();
        }
    }
    return t;
}

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc)
{
    Assert(c != NULL);
    (cType = c)->SetParent(this);
}

Type *NewExpr::CheckType()
{
    if (t)
    {
        return t;
    }
    Decl *d = FindDecl(cType->getID());
    if (d == NULL || !d->isClass())
    {
        ReportError::IdentifierNotDeclared(cType->getID(), LookingForClass);
        t = Type::errorType;
    }
    else
    {
        t = cType;
    }
    return t;
}

NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc)
{
    Assert(sz != NULL && et != NULL);
    (size = sz)->SetParent(this);
    (elemType = et)->SetParent(this);
}

Type *NewArrayExpr::CheckType()
{
    if (t)
    {
        return t;
    }
    Type *st = size->CheckType();
    if (st && !st->IsEquivalentTo(Type::intType) && !st->IsEquivalentTo(Type::errorType))
    {
        ReportError::NewArraySizeNotInteger(size);
    }
    elemType->Check();
    if (elemType->isError())
    {
        t = Type::errorType;
    }
    else
    {
        t = new ArrayType(*GetLocation(), elemType);
    }
    return t;
}

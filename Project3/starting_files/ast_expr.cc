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

Type *ArithmeticExpr::CheckType(bool c)
{
    if (t && !c)
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
            t = Type::errorType;
            if (c)
            {
                ReportError::IncompatibleOperands(op, l, r);
                if (left)
                {
                    left->Check();
                }
                right->Check();
            }
            return t;
        }
    }
    else if (r)
    {
        if (!(r->IsEquivalentTo(Type::intType) ||
              r->IsEquivalentTo(Type::doubleType) ||
              r->IsEquivalentTo(Type::errorType)))
        {
            t = Type::errorType;
            if (c)
            {
                ReportError::IncompatibleOperand(op, r);
                if (left)
                {
                    left->Check();
                }
                right->Check();
            }
            return t;
        }
    }
    t = r;
    if (c)
    {
        if (left)
        {
            left->Check();
        }
        right->Check();
    }
    return r;
}

Type *PostfixExpr::CheckType(bool c)
{
    if (t && !c)
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
        if (c)
        {
            ReportError::IncompatibleOperand(op, l);
        }
    }
    t = Type::intType;
    if (c)
    {
        if (left)
        {
            left->Check();
        }
    }
    return t;
}

Type *RelationalExpr::CheckType(bool c)
{
    if (t && !c)
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
        if (c)
        {
            ReportError::IncompatibleOperands(op, l, r);
        }
    }
    t = Type::boolType;
    if (c)
    {
        left->Check();
        right->Check();
    }
    return t;
}

Type *EqualityExpr::CheckType(bool c)
{
    if (t && !c)
    {
        return t;
    }
    Type *l = left->CheckType();
    Type *r = right->CheckType();
    if (!r->isAssignableTo(l) && 
        !l->isAssignableTo(r) && 
        !l->IsEquivalentTo(Type::errorType) && 
        !r->IsEquivalentTo(Type::errorType) &&
        !(dynamic_cast<NamedType *>(r) && l->IsEquivalentTo(Type::nullType)) &&
        !(dynamic_cast<NamedType *>(l) && r->IsEquivalentTo(Type::nullType)))
    {
        if (c)
        {
            ReportError::IncompatibleOperands(op, l, r);
        }
    }
    t = Type::boolType;
    if (c)
    {
        left->Check();
        right->Check();
    }
    return t;
}

Type *LogicalExpr::CheckType(bool c)
{
    if (t && !c)
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
            if (c)
            {
                ReportError::IncompatibleOperands(op, l, r);
            }
        }
    }
    else if (r)
    {
        if (!(r->IsEquivalentTo(Type::boolType) ||
              r->IsEquivalentTo(Type::errorType)))
        {
            if (c)
            {
                ReportError::IncompatibleOperand(op, r);
            }
        }
    }
    t = Type::boolType;
    if (c)
    {
        if (left)
        {
            left->Check();
        }
        right->Check();
    }
    return t;
}

Type *AssignExpr::CheckType(bool c)
{
    if (t && !c)
    {
        return t;
    }
    Type *l = left->CheckType();
    Type *r = right->CheckType();
    if (!r->isAssignableTo(l) &&
        !(r->IsEquivalentTo(Type::nullType) && dynamic_cast<NamedType *>(l)) &&
        !r->IsEquivalentTo(Type::errorType) &&
        !l->IsEquivalentTo(Type::errorType))
    {
        t = Type::errorType;
        if (c)
        {
            ReportError::IncompatibleOperands(op, l, r);
            left->Check();
            right->Check();
        }
        return t;
    }
    if (l->IsEquivalentTo(Type::errorType))
    {
        t = r;
    }
    else
    {
        t = l;
    }
    if (c)
    {
        left->Check();
        right->Check();
    }
    return t;
}

Type *This::CheckType(bool c)
{
    if (t && !c)
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
    if (c)
    {
        ReportError::ThisOutsideClassScope(this);
    }
    t = Type::errorType;
    return t;
}

ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc)
{
    (base = b)->SetParent(this);
    (subscript = s)->SetParent(this);
}

Type *ArrayAccess::CheckType(bool c)
{
    if (t && !c)
    {
        return t;
    }
    Type *tempType;
    tempType = base->CheckType();
    if (dynamic_cast<ArrayType *>(tempType) == NULL &&
        !tempType->IsEquivalentTo(Type::errorType))
    {
        if (c)
        {
            ReportError::BracketsOnNonArray(base);
        }
    }
    tempType = subscript->CheckType();
    if (!tempType->IsEquivalentTo(Type::intType) &&
        !tempType->IsEquivalentTo(Type::errorType))
    {
        if (c)
        {
            ReportError::SubscriptNotInteger(subscript);
        }
    }
    tempType = base->CheckType();
    if (dynamic_cast<ArrayType *>(tempType) == NULL || 
        tempType->IsEquivalentTo(Type::errorType))
    {
        t = Type::errorType;
    }
    else
    {
        t = dynamic_cast<ArrayType *>(tempType)->getElementType();
    }
    if (c)
    {
        base->Check();
        subscript->Check();
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

Type *FieldAccess::CheckType(bool c)
{
    if (t && !c)
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
            if (c)
            {
                base->Check();
            }
            return t;
        }
        NamedType *nType = dynamic_cast<NamedType *>(cType);
        if (nType != NULL)
        {
            d = FindDecl(nType->getID());
        }
        if (nType != NULL && d == NULL)
        {
            t = Type::errorType;
            if (c)
            {
                ReportError::IdentifierNotDeclared(nType->getID(), LookingForClass);
                base->Check();
            }
            return t;
        }
        if (d == NULL || d->FindDecl(field) == NULL)
        {
            t = Type::errorType;
            if (c)
            {
                ReportError::FieldNotFoundInBase(field, cType);
                base->Check();
            }
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
            t = Type::errorType;
            if (c)
            {
                ReportError::InaccessibleField(field, cType);
                base->Check();
            }
            return t;
        }
        d = d->FindDecl(field, true);
        if (d == NULL || dynamic_cast<VarDecl *>(d) == NULL)
        {
            t = Type::errorType;
            if (c)
            {
                ReportError::FieldNotFoundInBase(field, cType);
                base->Check();
            }
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
                t = Type::errorType;
                if (c)
                {
                    ReportError::FieldNotFoundInBase(field, cType);
                }
                return t;
            }
        }
        else 
        {
            const char *w = field->GetName();
            d = FindDecl(field);
            if (d == NULL)
            {
                t = Type::errorType;
                if (c)
                {
                    ReportError::IdentifierNotDeclared(field, LookingForVariable);
                }
                return t;
            }
        }
        if (dynamic_cast<VarDecl *>(d) == NULL)
        {
            t = Type::errorType;
            if (c)
            {
                ReportError::IdentifierNotDeclared(field, LookingForVariable);
            }
            return t;
        }
    }
    t = dynamic_cast<VarDecl *>(d)->GetType();
    if (c)
    {
        if (base)
        {
            base->Check();
        }
        dynamic_cast<VarDecl *>(d)->Check();
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

Type *Call::CheckType(bool c)
{
    if (t && !c)
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
            if (c)
            {
                base->Check();
                for (int i = 0; i < actuals->NumElements(); ++i)
                {
                    actuals->Nth(i)->Check();
                }
            }
            t = Type::errorType;
            return t;
        }
        if (dynamic_cast<ArrayType *>(cType) && strcmp(field->GetName(), "length") == 0)
        {
            t = Type::intType;

            int num_actual = actuals->NumElements();
            if (num_actual != 0)
            {
                if (c)
                {
                    ReportError::NumArgsMismatch(field, 0, num_actual);
                }
            }
            if (c)
            {
                base->Check();
                for (int i = 0; i < num_actual; ++i)
                {
                    actuals->Nth(i)->Check();
                }
            }
            return t;
        }
        NamedType *nType = dynamic_cast<NamedType *>(cType);
        if (nType != NULL)
        {
            d = FindDecl(nType->getID());
        }
        if (nType != NULL && d == NULL)
        {
            if (c)
            {
                ReportError::IdentifierNotDeclared(nType->getID(), LookingForClass);
                base->Check();
                for (int i = 0; i < actuals->NumElements(); ++i)
                {
                    actuals->Nth(i)->Check();
                }
            }
            t = Type::errorType;
            return t;
        }
        if (d == NULL || d->FindDecl(field) == NULL)
        {
            if (c)
            {
                ReportError::FieldNotFoundInBase(field, cType);
                base->Check();
                for (int i = 0; i < actuals->NumElements(); ++i)
                {
                    actuals->Nth(i)->Check();
                }
            }
            t = Type::errorType;
            return t;
        }

        d = d->FindDecl(field, true);
        if (d == NULL || dynamic_cast<FnDecl *>(d) == NULL)
        {
            if (c)
            {
                ReportError::FieldNotFoundInBase(field, cType);
                base->Check();
                for (int i = 0; i < actuals->NumElements(); ++i)
                {
                    actuals->Nth(i)->Check();
                }
            }
            t = Type::errorType;
            return t;
        }
    }
    else
    {
        d = FindDecl(field);
        if (d == NULL || dynamic_cast<FnDecl *>(d) == NULL)
        {
            if (c)
            {
                ReportError::IdentifierNotDeclared(field, LookingForFunction);
                for (int i = 0; i < actuals->NumElements(); ++i)
                {
                    actuals->Nth(i)->Check();
                }
            }
            t = Type::errorType;
            return t;
        }
    }

    FnDecl *f = dynamic_cast<FnDecl *>(d);
    t = f->getReturnType();
    List<VarDecl *> *f_formals = f->getFormals();
    int num_actual = actuals->NumElements();
    int num_expect = f_formals->NumElements();
    if (num_actual != num_expect)
    {
        if (c)
        {
            ReportError::NumArgsMismatch(field, num_expect, num_actual);
        }
    }
    int num_comp = num_actual > num_expect ? num_expect : num_actual;
    for (int i = 0; i < num_comp; ++i)
    {
        Type *t_actual = actuals->Nth(i)->CheckType();
        Type *t_expect = f_formals->Nth(i)->GetType();
        if (!t_actual->IsEquivalentTo(Type::errorType) &&
            !t_expect->IsEquivalentTo(Type::errorType) &&
            !(t_actual->IsEquivalentTo(Type::nullType) && dynamic_cast<NamedType *>(t_expect)) &&
            !t_actual->isAssignableTo(t_expect))
        {
            if (c)
            {
                ReportError::ArgMismatch(actuals->Nth(i), i+1, t_actual, t_expect);
            }
        }
    }
    if (c)
    {
        if (base)
        {
            base->Check();
        }
        for (int i = 0; i < num_actual; ++i)
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

Type *NewExpr::CheckType(bool c)
{
    if (t && !c)
    {
        return t;
    }
    Decl *d = FindDecl(cType->getID());
    if (d == NULL || !d->isClass())
    {
        if (c)
        {
            ReportError::IdentifierNotDeclared(cType->getID(), LookingForClass);
        }
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

Type *NewArrayExpr::CheckType(bool c)
{
    if (t && !c)
    {
        return t;
    }
    Type *st = size->CheckType();
    if (st && 
        !st->IsEquivalentTo(Type::intType) && 
        !st->IsEquivalentTo(Type::errorType))
    {
        if (c)
        {
            ReportError::NewArraySizeNotInteger(size);
        }
    }
    
    elemType->Check(false);
    if (elemType->isError())
    {
        t = Type::errorType;
    }
    else
    {
        t = new ArrayType(*GetLocation(), elemType);
    }
    if (c)
    {
        size->Check();
        elemType->Check();
    }
    return t;
}

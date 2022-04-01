/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>


IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;
}

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    value = strdup(val);
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
}
CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r) 
  : Expr(Join(l->GetLocation(), r->GetLocation())) {
    Assert(l != NULL && o != NULL && r != NULL);
    (op=o)->SetParent(this);
    (left=l)->SetParent(this); 
    (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r) 
  : Expr(Join(o->GetLocation(), r->GetLocation())) {
    Assert(o != NULL && r != NULL);
    left = NULL; 
    (op=o)->SetParent(this);
    (right=r)->SetParent(this);
}

Location *ArithmeticExpr::Emit(CodeGenerator *cg) {
    Location *L_left = NULL;
    if (left != NULL) {
        L_left = left-> Emit(cg);
    }
    else {
        L_left = cg-> GenLoadConstant(0);
    }
    Location *L_right = right-> Emit(cg);
    return cg-> GenBinaryOp(op->GetOpName(), L_left, L_right);
}

// A lot to do...
Location *RelationalExpr::Emit(CodeGenerator *cg) {
    Location *L_left = left-> Emit(cg);
    Location *L_right = right-> Emit(cg);
    return cg-> GenBinaryOp(op-> GetOpName(), L_left, L_right);
}

// A lot to do...
Location *EqualityExpr::Emit(CodeGenerator *cg) {
    Location *L_left = left-> Emit(cg);
    Location *L_right = right-> Emit(cg);
    return cg-> GenBinaryOp(op-> GetOpName(), L_left, L_right);
}

// Something to do...
Location *LogicalExpr::Emit(CodeGenerator *cg) {
    Location *L_left = NULL;
    Location *L_right = right-> Emit(cg);
    if (left != NULL) {
        L_left = left-> Emit(cg);
        return cg-> GenBinaryOp(op-> GetOpName(), L_left, L_right);
    }
    else {
        // TODO
    }
}

Location *AssignExpr::Emit(CodeGenerator *cg) {
    Location *L_left = left-> Emit(cg);
    Location *L_right = right-> Emit(cg);
    LValue *lvalue = dynamic_cast<LValue *>(left);
    if (lvalue != NULL) {
        if (dynamic_cast<ArrayAccess *>(lvalue)) {
            cg-> GenStore(L_left, L_right);
        }
        else if (dynamic_cast<FieldAccess *>(lvalue)) {
            cg-> GenStore(L_left, L_right, /*non-zero offset, need to fix*/);
        }
        else {
            cg-> GenAssign(L_left, L_right);
        }
    }
    return L_left;
}

ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
}
     
FieldAccess::FieldAccess(Expr *b, Identifier *f) 
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b; 
    if (base) base->SetParent(this); 
    (field=f)->SetParent(this);
}


Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}
 

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) { 
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}


NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this); 
    (elemType=et)->SetParent(this);
}

       

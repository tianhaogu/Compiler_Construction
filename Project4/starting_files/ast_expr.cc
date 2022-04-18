/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>
#include "errors.h"
#include "codegen.h"

Type *EmptyExpr::CheckAndComputeResultType() { return Type::voidType; } 

IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;
}
Type *IntConstant::CheckAndComputeResultType() { 
    return Type::intType;
}
DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}

Type *DoubleConstant::CheckAndComputeResultType() { 
    return Type::doubleType;
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}

Type *BoolConstant::CheckAndComputeResultType() { 
    return Type::boolType;
}

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    value = strdup(val);
}

Type *StringConstant::CheckAndComputeResultType() {
    return Type::stringType;
}

Type *NullConstant::CheckAndComputeResultType() { 
    return Type::nullType;
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

void CompoundExpr::ReportErrorForIncompatibleOperands(Type *lhs, Type *rhs) {
    if (!lhs) { //unary op
        ReportError::IncompatibleOperand(op, rhs);
    } else { // binary op
        ReportError::IncompatibleOperands(op, lhs, rhs);
    }
}

bool CompoundExpr::CanDoArithmetic(Type *lhs, Type *rhs) {
    if (lhs && lhs != Type::errorType && rhs != Type::errorType)
	return rhs->IsNumeric() && rhs->IsEquivalentTo(lhs);
    if (!lhs || lhs == Type::errorType)
	return rhs->IsNumeric() || rhs == Type::errorType;
    return rhs != Type::errorType || lhs->IsNumeric();
}


Type *GetResultType(Type *lhs, Type *rhs) {
    Type *lesser = rhs;
    if (lhs) lesser = lesser->LesserType(lhs);
    if (!lesser || !lesser->IsNumeric())
	return Type::errorType;
    return lesser;
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

Type*ArithmeticExpr::CheckAndComputeResultType() {
    Type *lType = left?left->CheckAndComputeResultType():NULL, *rType = right->CheckAndComputeResultType();
    if (!CanDoArithmetic(lType, rType))
	ReportErrorForIncompatibleOperands(lType, rType);
    return GetResultType(lType, rType);
}

Location *RelationalExpr::Emit(CodeGenerator *cg) {
    Location *L_left = left-> Emit(cg);
    Location *L_right = right-> Emit(cg);
    if (strcmp(op-> GetOpName(), "<") == 0) {
        return cg-> GenBinaryOp(op-> GetOpName(), L_left, L_right);
    }
    else if (strcmp(op-> GetOpName(), "<=") == 0) {
        Location *L_less = cg-> GenBinaryOp("<", L_left, L_right);
        Location *L_equal = cg-> GenBinaryOp("==", L_left, L_right);
        return cg-> GenBinaryOp("||", L_less, L_equal);
    }
    else if (strcmp(op-> GetOpName(), ">") == 0) {
        return cg-> GenBinaryOp("<", L_right, L_left);
    }
    else if (strcmp(op-> GetOpName(), ">=") == 0) {
        Location *L_less = cg-> GenBinaryOp("<", L_right, L_left);
        Location *L_equal = cg-> GenBinaryOp("==", L_right, L_left);
        return cg-> GenBinaryOp("||", L_less, L_equal);
    }
    return NULL;
}

Type* RelationalExpr::CheckAndComputeResultType() {
    Type*lhs = left->CheckAndComputeResultType(), *rhs = right->CheckAndComputeResultType();
    if (!CanDoArithmetic(lhs, rhs))
	ReportErrorForIncompatibleOperands(lhs, rhs);
    return Type::boolType;
}

Location *EqualityExpr::Emit(CodeGenerator *cg) {
    Location *L_left = left-> Emit(cg);
    Location *L_right = right-> Emit(cg);
    if (strcmp(op-> GetOpName(), "==") == 0) {
        if (left-> CheckAndComputeResultType()-> IsEquivalentTo(Type::stringType)) {
            return cg-> GenBuiltInCall(BuiltIn::StringEqual, L_left, L_right);
        }
        else {
            return cg-> GenBinaryOp(op-> GetOpName(), L_left, L_right);
        }
    }
    else {
        Location *L_zero = cg-> GenLoadConstant(0);
        Location *L_equal = (left-> CheckAndComputeResultType()-> IsEquivalentTo(Type::stringType)) ? \
                cg-> GenBuiltInCall(BuiltIn::StringEqual, L_left, L_right) : \
                cg-> GenBinaryOp("==", L_left, L_right);
        return cg-> GenBinaryOp("==", L_equal, L_zero);
    }
    return NULL;
}

Type* EqualityExpr::CheckAndComputeResultType() {
   Type*lhs = left->CheckAndComputeResultType(), *rhs = right->CheckAndComputeResultType();
    if (!lhs->IsCompatibleWith(rhs) && !rhs->IsCompatibleWith(lhs))
	ReportErrorForIncompatibleOperands(lhs, rhs);
    return Type::boolType;
}

Location *LogicalExpr::Emit(CodeGenerator *cg) {
    Location *L_left = NULL;
    Location *L_right = right-> Emit(cg);
    if (left != NULL) {
        L_left = left-> Emit(cg);
        return cg-> GenBinaryOp(op-> GetOpName(), L_left, L_right);
    }
    else {
        L_left = cg-> GenLoadConstant(0);
        return cg-> GenBinaryOp("==", L_right, L_left);
    }
    return NULL;
}

Type* LogicalExpr::CheckAndComputeResultType() {
    Type *lhs = left ?left->CheckAndComputeResultType() :NULL, *rhs = right->CheckAndComputeResultType();
    if ((lhs && !lhs->IsCompatibleWith(Type::boolType)) ||
	  (!rhs->IsCompatibleWith(Type::boolType)))
	ReportErrorForIncompatibleOperands(lhs, rhs);
    return Type::boolType;
}

Location *AssignExpr::Emit(CodeGenerator *cg) {
    Location *L_right = right-> Emit(cg);
    LValue *lvalue = dynamic_cast<LValue *>(left);
    Location *L_left;
    if (lvalue != NULL) {
        if (dynamic_cast<ArrayAccess *>(lvalue)) {
            L_left = dynamic_cast<ArrayAccess *>(lvalue)->EmitStore(cg);
            cg-> GenStore(L_left, L_right);
        }
        else if (dynamic_cast<FieldAccess *>(lvalue)) {
            L_left = dynamic_cast<FieldAccess *>(lvalue)->FieldAssign(cg, L_right);
            // cg-> GenStore(L_left, L_right, dynamic_cast<FieldAccess *>(lvalue)->GetFieldOffset());
        }
        else {
            L_left = left-> Emit(cg);
            cg-> GenAssign(L_left, L_right);
        }
    } else {
        L_left = left-> Emit(cg);
        cg-> GenAssign(L_left, L_right);
    }
    return L_left;
}

Type *AssignExpr::CheckAndComputeResultType() {
    Type *lhs = left->CheckAndComputeResultType(), *rhs = right->CheckAndComputeResultType();
    if (!rhs->IsCompatibleWith(lhs)) {
        ReportErrorForIncompatibleOperands(lhs, rhs);
        return Type::errorType;
    }
    return lhs;
}

Type* This::CheckAndComputeResultType() {
    if (!enclosingClass) enclosingClass = FindSpecificParent<ClassDecl>();
   if (!enclosingClass)  
       ReportError::ThisOutsideClassScope(this);
   if (!enclosingClass) return Type::errorType;
   return enclosingClass->GetDeclaredType();
 }

Location *This::Emit(CodeGenerator *cg) {
    Location *L_this = new Location(Segment::fpRelative, CodeGenerator::OffsetToFirstParam, "this");
    return L_this;
}

ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
}

Type *ArrayAccess::CheckAndComputeResultType() {
    Type *baseT = base->CheckAndComputeResultType();
    if ((baseT != Type::errorType) && !baseT->IsArrayType()) 
        ReportError::BracketsOnNonArray(base);
    if (!subscript->CheckAndComputeResultType()->IsCompatibleWith(Type::intType))
	ReportError::SubscriptNotInteger(subscript);
    return baseT->IsArrayType() ? dynamic_cast<ArrayType*>(baseT)->GetArrayElemType() : Type::errorType;
}

Location *ArrayAccess::EmitStore(CodeGenerator *cg) {
    Location* L_base = base-> Emit(cg);
    Location* L_subscript = subscript-> Emit(cg);
    return cg-> GenSubscript(L_base, L_subscript);
}

Location *ArrayAccess::Emit(CodeGenerator *cg) {
    Location* L_base = base-> Emit(cg);
    Location* L_subscript = subscript-> Emit(cg);
    return cg->GenLoad(cg-> GenSubscript(L_base, L_subscript));
}

FieldAccess::FieldAccess(Expr *b, Identifier *f) 
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b; 
    if (base) base->SetParent(this); 
    (field=f)->SetParent(this);
}

Type* FieldAccess::CheckAndComputeResultType() {
    Type *baseType = base ? base->CheckAndComputeResultType() : NULL;
    Decl *ivar = field->GetDeclRelativeToBase(baseType);
    if (ivar && ivar->IsIvarDecl() && !base) { // add implicit "this"
        base = new This(*field->GetLocation());
        base->SetParent(this);
        baseType = base->CheckAndComputeResultType();
    }
    if (base) {
        if (baseType == Type::errorType)
            return Type::errorType;
        else if (!ivar || !ivar->IsVarDecl()) {
            ReportError::FieldNotFoundInBase(field, baseType);
            return Type::errorType;
        } else {
            ClassDecl *enclosingClass = FindSpecificParent<ClassDecl>(); // check cur scope for compatibility
            Type *withinClass = (enclosingClass? enclosingClass->GetDeclaredType() : NULL);
            if (ivar && (!withinClass|| !withinClass->IsCompatibleWith(baseType))) {
                ReportError::InaccessibleField(field, baseType);
                return Type::errorType;
            } 
        }
    } else if (!ivar || !ivar->IsVarDecl()) {
        ReportError::IdentifierNotDeclared(field, LookingForVariable);
        return Type::errorType;
    }
    return ivar ? (dynamic_cast<VarDecl *>(ivar))->GetDeclaredType() : Type::errorType;
}

// A lot more to do...
Location *FieldAccess::Emit(CodeGenerator *cg) {
    // Location *L_base = NULL;
    // if (base != NULL) {
    //     L_base = base-> Emit(cg);
    // }

    VarDecl *ivar = GetFieldVarDecl();
    FieldAccess *F_base = dynamic_cast<FieldAccess *>(base);

    if (F_base == NULL) {
        if (ivar->rtLoc != NULL) {
            return ivar->rtLoc;
        } else {
            Location *L_this = new Location(Segment::fpRelative, CodeGenerator::OffsetToFirstParam, "this");
            return cg->GenLoad(L_this, ivar->GetOffset());
        }
    } else {
        VarDecl *V_base = F_base->GetFieldVarDecl();
        return cg->GenLoad(V_base->rtLoc, ivar->GetOffset());
    }
}

Location *FieldAccess::FieldAssign(CodeGenerator *cg, Location *L_right) {
    VarDecl *ivar = GetFieldVarDecl();
    FieldAccess *F_base = dynamic_cast<FieldAccess *>(base);

    if (F_base == NULL) {
        if (ivar->rtLoc != NULL) {
            cg->GenAssign(ivar->rtLoc, L_right);
            return ivar->rtLoc;
        } else {
            Location *L_this = new Location(Segment::fpRelative, CodeGenerator::OffsetToFirstParam, "this");
            cg->GenStore(L_this, L_right, ivar->GetOffset());
            return L_this;
        }
    } else {
        VarDecl *V_base = F_base->GetFieldVarDecl();
        cg->GenStore(V_base->rtLoc, L_right, ivar->GetOffset());
        return V_base->rtLoc;
    }
}

VarDecl *FieldAccess::GetFieldVarDecl() {
    Type *baseType = base ? base->CheckAndComputeResultType() : NULL;
    Decl *ivar = field->GetDeclRelativeToBase(baseType);
    return dynamic_cast<VarDecl *>(ivar);
}

Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}

// special-case code for length() on arrays
Type* Call::CheckAndComputeResultType() {
    Type *baseType = base ? base->CheckAndComputeResultType() : NULL;
    FnDecl *fd = dynamic_cast<FnDecl *>(field->GetDeclRelativeToBase(baseType));
    if (fd && fd->IsMethodDecl() && !base) { // add implicit "this"
        base = new This(*field->GetLocation());
        base->SetParent(this);
        baseType = base->CheckAndComputeResultType();
   }
   List<Type*> aTypes;
    for (int i = 0; i < actuals->NumElements(); i++) 
        aTypes.Append(actuals->Nth(i)->CheckAndComputeResultType());
// cascade, above loop checks actuals before function confirmed.
// what about excess actuals? what if function doesn't exist at all?
    if (baseType && baseType->IsArrayType() && strcmp(field->GetName(), "length") == 0) {
	if (actuals->NumElements() != 0) 
            ReportError::NumArgsMismatch(field, 0, actuals->NumElements());
	return Type::intType;
    }
    if (baseType == Type::errorType) {
	return Type::errorType;
    }
    if (baseType && !fd) { // had receiver, but no field in receiver (not class, wrong name, etc.)
	ReportError::FieldNotFoundInBase(field, baseType);
        return Type::errorType;
    } else if (!fd) { // no base, bad function
	ReportError::IdentifierNotDeclared(field, LookingForFunction);
        return Type::errorType;
    }  

    List<VarDecl*> *formals = fd->GetFormals();
    if (formals->NumElements() != actuals->NumElements()) {
	ReportError::NumArgsMismatch(field, formals->NumElements(), actuals->NumElements());
    }
    for (int i = 0; i < formals->NumElements(); i++) {
	if (i >= actuals->NumElements()) break;
        Type *at = aTypes.Nth(i);
        if (!at->IsCompatibleWith(formals->Nth(i)->GetDeclaredType()))
            ReportError::ArgMismatch(actuals->Nth(i), i+1, at,
                                    formals->Nth(i)->GetDeclaredType());
    }
    return fd->GetReturnType();
} 

Location *Call::Emit(CodeGenerator *cg) {
    if (base != NULL) { // need to check array type
        if (dynamic_cast<ArrayType *>(base->CheckAndComputeResultType()) && strcmp(field->GetName(), "length") == 0)
        {
            Location *L_array = base-> Emit(cg);
            return cg-> GenLoad(L_array, -4);
        }
    }
    List<Location *> *args = new List<Location *>();
    for (int i = 0; i < actuals-> NumElements(); i++) {
        Location* loc = actuals-> Nth(i)-> Emit(cg);
        args-> Append(loc);
    }

    if (base == NULL) {
        FnDecl *fndecl = dynamic_cast<FnDecl *>(field->GetDeclRelativeToBase(NULL)); // need to convert to fndecl from identifier
        bool hasReturnValue = !(fndecl-> GetType()->IsEquivalentTo(Type::voidType));
        return cg-> GenFunctionCall(fndecl-> GetFunctionLabel(), args, hasReturnValue);
    } else {
        FnDecl *fndecl = dynamic_cast<FnDecl *>(field->GetDeclRelativeToBase(base->CheckAndComputeResultType())); // need to convert to fndecl from identifier
        bool hasReturnValue = !(fndecl-> GetType()->IsEquivalentTo(Type::voidType));
        Location * loc = base-> Emit(cg);
        return cg-> GenDynamicDispatch(loc, fndecl-> GetOffset(), args, hasReturnValue);
    }
    return NULL;
}

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) { 
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}

Location *NewExpr::Emit(CodeGenerator *cg) {
    const char *className = cType-> GetTypeName();
    Decl *decl = FindDecl(cType-> GetId());
    ClassDecl *clsdecl = dynamic_cast<ClassDecl *>(decl);
    int class_size = clsdecl-> GetClassSize();
    Location *class_size_loc = cg-> GenLoadConstant(class_size);
    Location *L_call = cg-> GenBuiltInCall(BuiltIn::Alloc, class_size_loc);
    Location *L_vtable = cg-> GenLoadLabel(className);
    cg-> GenStore(L_call, L_vtable);
    return L_call;
}

Type* NewExpr::CheckAndComputeResultType() {
    if (!cType->IsClass()) {
        ReportError::IdentifierNotDeclared(cType->GetId(), LookingForClass);
        return Type::errorType;
    }
    return cType; 
} 

NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this); 
    (elemType=et)->SetParent(this);
}

Location *NewArrayExpr::Emit(CodeGenerator *cg) {
    Location *L_size = size-> Emit(cg);
    return cg-> GenNewArray(L_size);
}

Type *NewArrayExpr::CheckAndComputeResultType() {
    Type *st = size->CheckAndComputeResultType();
    if (!st->IsCompatibleWith(Type::intType))
	ReportError::NewArraySizeNotInteger(size);
    elemType->Check();
    if (elemType->IsError())
	return Type::errorType;
    yyltype none;
    return new ArrayType(none, elemType);
}   

Location *ReadIntegerExpr::Emit(CodeGenerator *cg) {
    return cg-> GenBuiltInCall(BuiltIn::ReadInteger);
}

Type *ReadIntegerExpr::CheckAndComputeResultType() {
    return Type::intType;
}

Location *ReadLineExpr::Emit(CodeGenerator *cg) {
    return cg-> GenBuiltInCall(BuiltIn::ReadLine);
}

Type *ReadLineExpr::CheckAndComputeResultType() {
    return Type::stringType;
}
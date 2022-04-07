/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
        
         
Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
    Assert(n != NULL);
    (id=n)->SetParent(this); 
}


VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
}
  

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);     
    extends = ex;
    if (extends) extends->SetParent(this);
    (implements=imp)->SetParentAll(this);
    (members=m)->SetParentAll(this);
}


InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
    Assert(n != NULL && m != NULL);
    (members=m)->SetParentAll(this);
}

	
FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r!= NULL && d != NULL);
    (returnType=r)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
}

void FnDecl::SetFunctionBody(Stmt *b) { 
    (body=b)->SetParent(this);
}

Location *FnDecl::Emit(CodeGenerator *cg) {
    cg-> GenLabel(/*need to get the function label in char* type.*/);
    BeginFunc *bgfunc = cg-> GenBeginFunc();
    int offset_param = CodeGenerator::OffsetToFirstParam;
    for (int i = 0; i < formals-> NumElements(); i++) {
        VarDecl *vardecl = formals-> Nth(i);
        Location *L_param = new Location(Segment::fpRelative, offset_param, vardecl-> GetName());
        offset_param += CodeGenerator::VarSize;
    }
    if (body != NULL) {
        body-> Emit(cg);
    }
    int offset_local = CodeGenerator::OffsetToFirstLocal;
    bgfunc-> SetFrameSize(offset_local); // need to get number of variables according to calculation within body.
    cg-> GenEndFunc();
    return NULL;
}


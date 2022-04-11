/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
#include <string>
        
         
Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
    Assert(n != NULL);
    (id=n)->SetParent(this); 
}


VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
}

Location *VarDecl::Emit(CodeGenerator *cg) {
    if (loc == NULL)
    {
        if (dynamic_cast<Program *>(parent))
        {
            loc = cg-> GenGlobalVariable(GetName());
        }
        else if (dynamic_cast<FnDecl *>(parent))
        {
            loc = cg-> GenLocalVariable(GetName());
        }
    }
    return loc;
}
  

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);     
    extends = ex;
    if (extends) extends->SetParent(this);
    (implements=imp)->SetParentAll(this);
    (members=m)->SetParentAll(this);
}

void ClassDecl::BuildClass() {
    if (extends != NULL) {}
    for (int i = 0; i < members-> NumElements(); i++) {
        if (dynamic_cast<VarDecl *>(members-> Nth(i))) {
            lastVarOffset -= CodeGenerator::VarSize;
        }
        if (dynamic_cast<FnDecl *>(members-> Nth(i))) {
            lastMethodOffset += CodeGenerator::VarSize;
            FnDecl *fndecl = dynamic_cast<FnDecl *>(members-> Nth(i));
            std::string clsName(GetName());
            clsName += '.';
            const char *clsName_ = clsName.c_str();
            const char *fnName = fndecl-> GetLabel();
            methodLabels-> Append(clsName_ + fnName);
        }
    }
}

Location *ClassDecl::Emit(CodeGenerator *cg) {
    BuildClass();
    members-> EmitAll(cg);
    cg-> GenVTable(GetName(), methodLabels);
    return NULL;
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

/*modify the ast_decl.cc to add support for checking for pure function declaration*/
bool FnDecl::IsMethodDecl() 
  { return dynamic_cast<ClassDecl*>(parent) != NULL || dynamic_cast<InterfaceDecl*>(parent) != NULL; }

Location *FnDecl::Emit(CodeGenerator *cg) {
    cg-> GenLabel(/*need to get the function label in char* type.*/);
    BeginFunc *bgfunc = cg-> GenBeginFunc(this);
    int offset_param = CodeGenerator::OffsetToFirstParam;
    if (IsMethodDecl()) {}
    for (int i = 0; i < formals-> NumElements(); i++) {
        VarDecl *vardecl = formals-> Nth(i);
        Location *L_param = new Location(Segment::fpRelative, offset_param, vardecl-> GetName());
        vardecl-> SetLocation(L_param);
        offset_param += CodeGenerator::VarSize;
    }
    if (body != NULL) {
        body-> Emit(cg);
    }
    // int offset_local = CodeGenerator::OffsetToFirstLocal;
    // bgfunc-> SetFrameSize(offset_local); // need to get number of variables according to calculation within body.
    bgfunc->SetFrameSize(body->GetFrameSize());
    cg-> GenEndFunc();
    return NULL;
}


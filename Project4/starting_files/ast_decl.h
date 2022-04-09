/* File: ast_decl.h
 * ----------------
 * In our parse tree, Decl nodes are used to represent and
 * manage declarations. There are 4 subclasses of the base class,
 * specialized for declarations of variables, functions, classes,
 * and interfaces.
 *
 * pp4: You will need to extend the Decl classes to implement 
 * code generation for declarations.
 */

#ifndef _H_ast_decl
#define _H_ast_decl

#include "ast.h"
#include "ast_type.h"
#include "list.h"

class Identifier;
class Stmt;

class Decl : public Node {
  protected:
    Identifier *id;
    int offset;
  
  public:
    Decl(Identifier *name);
    friend std::ostream& operator<<(std::ostream& out, Decl *d) { return out << d->id; }
    const char *GetName() { return id-> GetName(); }
    Identifier *GetID() { return id; }

    virtual bool isClass() { return false; }
    virtual bool isInter() { return false; }
    virtual bool isFunct() { return false; }
    virtual Location *Emit(CodeGenerator *cg) { return NULL; }
    void SetOffset(int off) { offset = off; }
    int GetOffset() { return offset; }
};

class VarDecl : public Decl {
  protected:
    Type *type;
    Location *loc = NULL;
    
  public:
    VarDecl(Identifier *name, Type *type);

    void SetLocation(Location *l) { loc = l; }
    Location *GetLocation() { return loc; }
    Type *GetType() { return type; }
    bool InClass() { return dynamic_cast<ClassDecl *>(parent); }
    Location *Emit(CodeGenerator *cg);
};

class ClassDecl : public Decl {
  protected:
    List<Decl*> *members;
    NamedType *extends;
    List<NamedType*> *implements;

  public:
    ClassDecl(Identifier *name, NamedType *extends, 
              List<NamedType*> *implements, List<Decl*> *members);
    
    Location *Emit(CodeGenerator *cg);
    bool isClass() { return true; }
};

class InterfaceDecl : public Decl {
  protected:
    List<Decl*> *members;
    
  public:
    InterfaceDecl(Identifier *name, List<Decl*> *members);

    bool isInter() { return true; }
};

class FnDecl : public Decl {
  protected:
    List<VarDecl*> *formals;
    Type *returnType;
    Stmt *body;
    std::string label;
    Location *loc;
    
  public:
    FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
    List<VarDecl*> *GetFormals() { return formals; }
    void SetFunctionBody(Stmt *b);

    bool isFunct() { return true; }
    bool IsMethodDecl();
    void SetLabel(const std::string &s) { label = s; }
    const char *GetLabel() { return label.c_str(); }
    Type *GetType() { return returnType; }
    Location *Emit(CodeGenerator *cg);
};

#endif

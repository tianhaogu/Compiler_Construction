/* File: ast_decl.h
 * ----------------
 * In our parse tree, Decl nodes are used to represent and
 * manage declarations. There are 4 subclasses of the base class,
 * specialized for declarations of variables, functions, classes,
 * and interfaces.
 *
 * pp3: You will need to extend the Decl classes to implement
 * semantic processing including detection of declaration conflicts
 * and managing scoping issues.
 */

#ifndef _H_ast_decl
#define _H_ast_decl

#include "ast.h"
#include "ast_type.h"
#include "list.h"

class Identifier;
class Stmt;

class Decl : public Node
{
protected:
  Identifier *id;

public:
  Decl(Identifier *name);
  friend std::ostream &operator<<(std::ostream &out, Decl *d) { return out << d->id; }
  const char *GetName() { return id->GetName(); }
  Identifier *getID() { return id; }

  virtual void Check() {}
  virtual bool isClass() { return false; }
  virtual bool isInter() { return false; }
  virtual bool isFunct() { return false; }
  // virtual bool ConflictsWithPrevious(Decl *prev);

  // virtual bool IsVarDecl() { return false; }
  // virtual bool IsClassDecl() { return false; }
  // virtual bool IsInterfaceDecl() { return false; }
  // virtual bool IsFnDecl() { return false; }
  // virtual bool IsMethodDecl() { return false; }
  // virtual bool IsIvarDecl() { return false; }
};

class VarDecl : public Decl
{
protected:
  Type *type;

public:
  VarDecl(Identifier *name, Type *type);
  Type *GetType() { return type; }
  void Check() { scope = new Scope(); type->Check(); if (type->isError()) { type = Type::errorType; } }
};

class ClassDecl : public Decl
{
protected:
  List<Decl *> *members;
  NamedType *extends;
  List<NamedType *> *implements;
  Type *t;

  Hashtable<const char *> *parents;
  List<Scope *> *inters;

public:
  ClassDecl(Identifier *name, NamedType *extends,
            List<NamedType *> *implements, List<Decl *> *members);
  bool isClass() { return true; }
  void Check();
  Scope *GetScope();
  Type *GetType() { return t; }
  bool isParent(const char *c) { return parents->Lookup(c) != NULL; }
};

class InterfaceDecl : public Decl
{
protected:
  List<Decl *> *members;

public:
  InterfaceDecl(Identifier *name, List<Decl *> *members);
  bool isInter() { return true; }
  void Check();
  Scope *GetScope();
};

class FnDecl : public Decl
{
protected:
  List<VarDecl *> *formals;
  Type *returnType;
  Stmt *body;

public:
  FnDecl(Identifier *name, Type *returnType, List<VarDecl *> *formals);
  void SetFunctionBody(Stmt *b);
  bool isFunct() { return true; }
  bool IsEquivalentTo(FnDecl *fn);
  void Check();
  Type *getReturnType() { return returnType; }
  List<VarDecl *> *getFormals() { return formals; }
};

#endif

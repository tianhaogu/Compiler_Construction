/* File: ast_type.h
 * ----------------
 * In our parse tree, Type nodes are used to represent and
 * store type information. The base Type class is used
 * for built-in types, the NamedType for classes and interfaces,
 * and the ArrayType for arrays of other types.  
 *
 * pp3: You will need to extend the Type classes to implement
 * the type system and rules for type equivalency and compatibility.
 */

#ifndef _H_ast_type
#define _H_ast_type

#include "ast.h"
#include "list.h"
#include <iostream>

class Type : public Node
{
protected:
  char *typeName;

public:
  static Type *intType, *doubleType, *boolType, *voidType,
      *nullType, *stringType, *errorType;

  Type(yyltype loc) : Node(loc) { scope = new Scope(); }
  Type(const char *str);

  virtual void PrintToStream(std::ostream &out) { out << typeName; }
  friend std::ostream &operator<<(std::ostream &out, Type *t)
  {
    t->PrintToStream(out);
    return out;
  }
  virtual bool IsEquivalentTo(Type *other) { return this == other; }
  virtual void Check() {}
  virtual const char *GetTypeName() { return typeName; }
  virtual bool isError() { return false; }
};

class NamedType : public Type
{
protected:
  Identifier *id;
  Decl *d;
  bool error;

public:
  NamedType(Identifier *i);

  bool IsEquivalentTo(Type *other) { return strcmp(this->GetTypeName(), other->GetTypeName()) == 0; }
  void PrintToStream(std::ostream &out) { out << id; }
  void Check();
  Decl *getDecl() { return d; }
  Identifier *getID() { return id; }
  const char *GetTypeName() { return id->GetName(); }
  bool isError() { return error; }
};

class ArrayType : public Type
{
protected:
  Type *elemType;
  bool error;

public:
  ArrayType(yyltype loc, Type *elemType);

  void PrintToStream(std::ostream &out) { out << elemType << "[]"; }
  bool IsEquivalentTo(Type *other);
  const char *GetTypeName() { return "[]"; }
  Type *getElementType() { return elemType; }
  bool isError() { return error; }
  void Check();
};

#endif

#ifndef _H_scope
#define _H_scope

#include "hashtable.h"

class Decl;
class Identifier;
class ClassDecl;

class Scope
{
protected:
  Hashtable<Decl *> t;

public:
  Decl *Find(Identifier *id);
  bool Declare(Decl *d);
  void Copy(Scope *s);
};

#endif
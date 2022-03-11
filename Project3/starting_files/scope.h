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
  void Remove(Decl *d);
  bool Declare(Decl *d);
  void Copy(Scope *s);
  int NumEntries();
};

#endif
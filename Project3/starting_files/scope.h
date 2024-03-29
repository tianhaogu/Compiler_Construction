#ifndef _H_scope
#define _H_scope

#include "hashtable.h"

class Decl;
class Identifier;
class ClassDecl;

class Scope
{
protected:
  Hashtable<Decl *> *t;

public:
  Scope() { t = new Hashtable<Decl *>; }
  Decl *Find(Identifier *id);
  void Remove(Decl *d);
  bool Declare(Decl *d, Hashtable<const char *> *flag = NULL);
  void Copy(Scope *s);
  int NumEntries();
  Iterator<Decl *> GetIter() { return t->GetIterator(); }
};

#endif
/* File: ast_stmt.h
 * ----------------
 * The Stmt class and its subclasses are used to represent
 * statements in the parse tree.  For each statment in the
 * language (for, if, return, etc.) there is a corresponding
 * node class for that construct. 
 *
 * pp3: You will need to extend the Stmt classes to implement
 * semantic analysis for rules pertaining to statements.
 */

#ifndef _H_ast_stmt
#define _H_ast_stmt

#include "list.h"
#include "ast.h"

class Decl;
class VarDecl;
class Expr;

class Program : public Node
{
protected:
  List<Decl *> *decls;

public:
  Program(List<Decl *> *declList);
  void Check();
};

class Stmt : public Node
{
public:
  Stmt() : Node() {}
  Stmt(yyltype loc) : Node(loc) {}
  virtual void Check() {}
};

class StmtBlock : public Stmt
{
protected:
  List<VarDecl *> *decls;
  List<Stmt *> *stmts;

public:
  StmtBlock(List<VarDecl *> *variableDeclarations, List<Stmt *> *statements);
  void Check();
};

class IntConst : public Stmt
{
protected:
  int value;

public:
  IntConst(yyltype loc, int val);
};

class CaseExpr : public Stmt
{
protected:
  IntConst *test;
  List<Stmt *> *stmts;

public:
  CaseExpr(IntConst *test, List<Stmt *> *stmts);
  void Check();
};

class DefaultBlock : public Stmt
{
protected:
  List<Stmt *> *stmts;

public:
  DefaultBlock(List<Stmt *> *stmts);
  void Check();
};

class SwitchStmt : public Stmt
{
protected:
  Expr *test;
  List<CaseExpr *> *stmts;
  DefaultBlock *defaultBody;

public:
  SwitchStmt(Expr *testExpr, List<CaseExpr *> *statements, DefaultBlock *defaultBody);
  void Check();
};

class ConditionalStmt : public Stmt
{
protected:
  Expr *test;
  Stmt *body;

public:
  ConditionalStmt(Expr *testExpr, Stmt *body);
};

class LoopStmt : public ConditionalStmt
{
public:
  LoopStmt(Expr *testExpr, Stmt *body)
      : ConditionalStmt(testExpr, body) {}
};

class ForStmt : public LoopStmt
{
protected:
  Expr *init, *step;

public:
  ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
  void Check();
};

class WhileStmt : public LoopStmt
{
public:
  WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
  void Check();
};

class IfStmt : public ConditionalStmt
{
protected:
  Stmt *elseBody;

public:
  IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
  void Check();
};

class BreakStmt : public Stmt
{
public:
  BreakStmt(yyltype loc) : Stmt(loc) {}
  void Check();
};

class ReturnStmt : public Stmt
{
protected:
  Expr *expr;

public:
  ReturnStmt(yyltype loc, Expr *expr);
  void Check();
};

class PrintStmt : public Stmt
{
protected:
  List<Expr *> *args;

public:
  PrintStmt(List<Expr *> *arguments);
  void Check();
};

#endif

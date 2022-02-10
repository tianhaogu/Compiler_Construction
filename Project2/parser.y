/* File: parser.y
 * --------------
 * Yacc input file to generate the parser for the compiler.
 *
 * pp2: your job is to write a parser that will construct the parse tree
 *      and if no parse errors were found, print it.  The parser should 
 *      accept the language as described in specification, and as augmented 
 *      in the pp2 handout.
 */

%{

/* Just like lex, the text within this first region delimited by %{ and %}
 * is assumed to be C/C++ code and will be copied verbatim to the y.tab.c
 * file ahead of the definitions of the yyparse() function. Add other header
 * file inclusions or C++ variable declarations/prototypes that are needed
 * by your code here.
 */
#include "scanner.h" // for yylex
#include "parser.h"
#include "errors.h"

void yyerror(const char *msg); // standard error-handling routine

%}

/* The section before the first %% is the Definitions section of the yacc
 * input file. Here is where you declare tokens and types, add precedence
 * and associativity options, and so on.
 */
 
/* yylval 
 * ------
 * Here we define the type of the yylval global variable that is used by
 * the scanner to store attibute information about the token just scanned
 * and thus communicate that information to the parser. 
 *
 * pp2: You will need to add new fields to this union as you add different 
 *      attributes to your non-terminal symbols.
 */
%union {
    Program *program;
    int integerConstant;
    bool boolConstant;
    char *stringConstant;
    double doubleConstant;
    char identifier[MaxIdentLen+1]; // +1 for terminating null
    Decl *decl;
    List<Decl*> *declList;
    VarDecl *vardecl;
    Type *type;
    FnDecl *fndecl;
    List<VarDecl*> *varList;
    ClassDecl *classdecl;
    NamedType *namedtype;
    List<NamedType*> *identifierlist;
    InterfaceDecl *interfacedecl;
    Stmt *stmt;
    List<Stmt*> *stmtList;
    StmtBlock *stmtblock;
    IfStmt *ifstmt;
    ForStmt *forstmt;
    WhileStmt *whilestmt;
    PrintStmt *printstmt;
    ReturnStmt *returnstmt;
    BreakStmt *breakstmt;
    Expr *expr;
    List<Expr*> *exprList;
    SwitchStmt *switchstmt;
    CaseExpr *caseexpr;
    List<CaseExpr*> *caseList;
    DefaultBrack *defaultbrack;
    LValue *lvalue;
    Call *call;
    AssignExpr *assignexpr;
    LogicalExpr *logicalexpr;
    PostfixExpr *postfixexpr;
    EqualityExpr *equalityexpr;
    ArithmeticExpr *arithmeticexpr;
    RelationalExpr *relationalexpr;
    ReadIntegerExpr *readintegerexpr;
    ReadLineExpr *readlineexpr;
    NewExpr *newexpr;
    NewArrayExpr *newarrayexpr;
    FieldAccess *fieldaccess;
    ArrayAccess *arrayaccess;
}


/* Tokens
 * ------
 * Here we tell yacc about all the token types that we are using.
 * Yacc will assign unique numbers to these and export the #define
 * in the generated y.tab.h header file.
 */
%token   T_Void T_Bool T_Int T_Double T_String T_Class 
%token   T_LessEqual T_GreaterEqual T_Equal T_NotEqual T_Dims
%token   T_And T_Or T_Null T_Extends T_This T_Interface T_Implements
%token   T_While T_For T_If T_Else T_Return T_Break
%token   T_New T_NewArray T_Print T_ReadInteger T_ReadLine

%token   <identifier> T_Identifier
%token   <stringConstant> T_StringConstant 
%token   <integerConstant> T_IntConstant
%token   <doubleConstant> T_DoubleConstant
%token   <boolConstant> T_BoolConstant

%token   T_Increm T_Decrem T_Switch T_Case T_Default


/* Non-terminal types
 * ------------------
 * In order for yacc to assign/access the correct field of $$, $1, we
 * must to declare which field is appropriate for the non-terminal.
 * As an example, this first type declaration establishes that the DeclList
 * non-terminal uses the field named "declList" in the yylval union. This
 * means that when we are setting $$ for a reduction for DeclList or reading
 * $n which corresponds to a DeclList nonterminal we are accessing the field
 * of the union named "declList" which is of type List<Decl*>.
 * pp2: You'll need to add many of these of your own.
 */
%type <program>           Program
%type <declList>          DeclList 
%type <decl>              Decl
%type <vardecl>           VarDecl
%type <vardecl>           Var
%type <type>              Type
%type <fndecl>            FnDecl
%type <varList>           Formals
%type <varList>           VarList
%type <classdecl>         ClassDecl
%type <identifierlist>    IdentifierList
%type <declList>          FieldList
%type <decl>              Field
%type <interfacedecl>     InterfaceDecl
%type <declList>          ProtoTypeList
%type <decl>              ProtoType
%type <stmtblock>         StmtBlock
%type <varList>           VarDeclList
%type <stmtList>          StmtList
%type <stmt>              Stmt
%type <expr>              ExprBrack
%type <ifstmt>            IfStmt
%type <forstmt>           ForStmt
%type <whilestmt>         WhileStmt
%type <printstmt>         PrintStmt
%type <returnstmt>        ReturnStmt
%type <breakstmt>         BreakStmt
%type <exprList>          ExprList
%type <switchstmt>        SwitchStmt
%type <caseexpr>          Case
%type <defaultbrack>      DefaultBrack
%type <caseList>          CaseList
%type <expr>              Expr
%type <lvalue>            LValue
%type <expr>              Constant
%type <call>              Call
%type <exprList>          Actuals
%type <assignexpr>        AssignExpr
%type <logicalexpr>       LogicalExpr
%type <postfixexpr>       PostfixExpr
%type <equalityexpr>      EqualityExpr
%type <arithmeticexpr>    ArithmeticExpr
%type <relationalexpr>    RelationalExpr
%type <readintegerexpr>   ReadIntegerExpr
%type <readlineexpr>      ReadLineExpr
%type <newexpr>           NewExpr
%type <newarrayexpr>      NewArrayExpr
// %type <namedtype>         NamedType
// %type <fieldaccess>       FieldAccess
// %type <arrayaccess>       ArrayAccess


%nonassoc WO_ELSE
%nonassoc T_Else
%nonassoc '='
%left     T_Or
%left     T_And	
%nonassoc T_Equal T_NotEqual
%nonassoc '<' T_LessEqual '>' T_GreaterEqual
%left     '+' '-' 
%left     '*' '/' '%'
%nonassoc '!' NEGT T_Increm T_Decrem
%left     '[' '.'


%%
/* Rules
 * -----
 * All productions and actions should be placed between the start and stop
 * %% markers which delimit the Rules section.
	 
 */
Program   :    DeclList            { 
                                      @1; 
                                      /* pp2: The @1 is needed to convince 
                                       * yacc to set up yylloc. You can remove 
                                       * it once you have other uses of @n*/
                                      Program *program = new Program($1);
                                      // if no errors, advance to next phase
                                      if (ReportError::NumErrors() == 0) 
                                          program->Print(0);
                                    }
          ;

DeclList  :    DeclList Decl        { ($$=$1)-> Append($2); }
          |    Decl                 { ($$ = new List<Decl*>)-> Append($1); }
          ;

Decl      :    VarDecl               { $$=$1; }
          |    FnDecl                { $$=$1; }
          |    ClassDecl             { $$=$1; }
          |    InterfaceDecl         { $$=$1; } 
          ;

VarDecl    :    Var ';'   { $$=$1; }
           ;

Var   :    Type T_Identifier    {
          Identifier *identifier = new Identifier(@2, $2);
          $$ = new VarDecl(identifier, $1);
      }
      ;

Type    :    T_Int    { $$ = Type::intType; }
        |    T_Double    { $$ = Type::doubleType; }
        |    T_Bool    { $$ = Type::boolType; }
        |    T_String    { $$ = Type::stringType; }
        |    T_Identifier    {
            Identifier *identifier = new Identifier(@1, $1);
            $$ = new NamedType(identifier);
        }
        |    Type T_Dims   { $$ = new ArrayType(@1, $1); }
        ;

FnDecl    :    T_Void T_Identifier '(' Formals ')' StmtBlock    {
              Identifier *identifier = new Identifier(@2, $2);
              Type *type_ = Type::voidType;
              $$ = new FnDecl(identifier, type_, $4);
              $$-> SetFunctionBody($6);
          }
          |    Type T_Identifier '(' Formals ')' StmtBlock    {
              Identifier *identifier = new Identifier(@2, $2);
              $$ = new FnDecl(identifier, $1, $4);
              $$-> SetFunctionBody($6);
          }
          ;

Formals    :    VarList    { $$=$1; }
           |        { $$ = new List<VarDecl*>; }
           ;

VarList    :    VarList ',' Var    { ($$=$1)-> Append($3); }
           |    Var    { ($$ = new List<VarDecl*>)-> Append($1); }
           ;

ClassDecl    :    T_Class T_Identifier '{' FieldList '}'    {
                 Identifier *identifier = new Identifier(@2, $2);
                 List<NamedType*> *impList = new List<NamedType*>;
                 $$ = new ClassDecl(identifier, NULL, impList, $4);
             }
             |    T_Class T_Identifier T_Extends T_Identifier '{' FieldList '}'    {
                 Identifier *identifier = new Identifier(@2, $2);
                 Identifier *ext_ident = new Identifier(@4, $4);
                 NamedType *extends = new NamedType(ext_ident);
                 List<NamedType*> *impList = new List<NamedType*>;
                 $$ = new ClassDecl(identifier, extends, impList, $6);
             }
             |    T_Class T_Identifier T_Implements IdentifierList '{' FieldList '}'    {
                 Identifier *identifier = new Identifier(@2, $2);
                 $$ = new ClassDecl(identifier, NULL, $4, $6);
             }
             |    T_Class T_Identifier T_Extends T_Identifier T_Implements IdentifierList '{' FieldList '}'    {
                 Identifier *identifier = new Identifier(@2, $2);
                 Identifier *ext_ident = new Identifier(@4, $4);
                 NamedType *extends = new NamedType(ext_ident);
                 $$ = new ClassDecl(identifier, extends, $6, $8);
             }
             |    T_Class T_Identifier '{' '}'    {
                 Identifier *identifier = new Identifier(@2, $2);
                 List<NamedType*> *impList = new List<NamedType*>;
                 $$ = new ClassDecl(identifier, NULL, impList, new List<Decl*>);
             }
             |    T_Class T_Identifier T_Extends T_Identifier '{' '}'    {
                 Identifier *identifier = new Identifier(@2, $2);
                 Identifier *ext_ident = new Identifier(@4, $4);
                 NamedType *extends = new NamedType(ext_ident);
                 List<NamedType*> *impList = new List<NamedType*>;
                 $$ = new ClassDecl(identifier, extends, impList, new List<Decl*>);
             }
             |    T_Class T_Identifier T_Implements IdentifierList '{' '}'    {
                 Identifier *identifier = new Identifier(@2, $2);
                 $$ = new ClassDecl(identifier, NULL, $4, new List<Decl*>);
             }
             |    T_Class T_Identifier T_Extends T_Identifier T_Implements IdentifierList '{' '}'    {
                 Identifier *identifier = new Identifier(@2, $2);
                 Identifier *ext_ident = new Identifier(@4, $4);
                 NamedType *extends = new NamedType(ext_ident);
                 $$ = new ClassDecl(identifier, extends, $6, new List<Decl*>);
             }
             ;

IdentifierList    :    IdentifierList ',' T_Identifier    {
                      Identifier *identifier = new Identifier(@3, $3);
                      NamedType *extends = new NamedType(identifier);
                      ($$=$1)-> Append(extends);
                  }
                  |    T_Identifier    {
                      Identifier *identifier = new Identifier(@1, $1);
                      NamedType *extends = new NamedType(identifier);
                      ($$ = new List<NamedType*>)-> Append(extends);
                  }
                  ;

FieldList    :    FieldList Field    { ($$=$1)-> Append($2); }
             |    Field { ($$=new List<Decl*>)-> Append($1); }
             ;

Field    :    VarDecl    { $$=$1; }
         |    FnDecl    { $$=$1; }
         ;

InterfaceDecl    :    T_Interface T_Identifier '{' ProtoTypeList '}'    {
                     Identifier *identifier = new Identifier(@2, $2);
                     $$ = new InterfaceDecl(identifier, $4);
                 }
                 |    T_Interface T_Identifier '{' '}'    {
                     Identifier *identifier = new Identifier(@2, $2);
                     $$ = new InterfaceDecl(identifier, new List<Decl*>);
                 }
                 ;

ProtoTypeList    :    ProtoTypeList ProtoType    { ($$=$1)-> Append($2); }
                 |    ProtoType    { ($$=new List<Decl*>)-> Append($1); }
                 ;

ProtoType    :    Type T_Identifier '(' Formals ')' ';'    {
                 Identifier *identifier = new Identifier(@2, $2);
                 $$ = new FnDecl(identifier, $1, $4);
             }
             |    T_Void T_Identifier '(' Formals ')' ';'    {
                 Identifier *identifier = new Identifier(@2, $2);
                 Type *type = Type::voidType;
                 $$ = new FnDecl(identifier, type, $4);
             }
             ;

StmtBlock    :    '{' VarDeclList StmtList '}'    { $$ = new StmtBlock($2, $3); }
             |    '{' StmtList '}'    { $$ = new StmtBlock(new List<VarDecl*>, $2); }
             |    '{' VarDeclList '}'    { $$ = new StmtBlock($2, new List<Stmt*>); }
             |    '{' '}'    { $$ = new StmtBlock(new List<VarDecl*>, new List<Stmt*>); }
             ;

VarDeclList    :    VarDeclList VarDecl    { ($$=$1)-> Append($2); }
               |    VarDecl    { ($$=new List<VarDecl*>)-> Append($1); }
               ;

StmtList    :    StmtList Stmt   { ($$=$1)-> Append($2); } 
            |    Stmt    { ($$=new List<Stmt*>)-> Append($1); }
            ;

Stmt    :    ExprBrack ';'    { $$=$1; }
        |    IfStmt    { $$=$1; }
        |    SwitchStmt    { $$=$1; }
        |    WhileStmt    { $$=$1; }
        |    ForStmt    { $$=$1; }
        |    BreakStmt    { $$=$1; }
        |    ReturnStmt    { $$=$1; }
        |    PrintStmt    { $$=$1; }
        |    StmtBlock    { $$=$1; }
        ;

IfStmt    :    T_If '(' Expr ')' Stmt %prec WO_ELSE   { $$ = new IfStmt($3, $5, NULL); }
          |    T_If '(' Expr ')' Stmt T_Else Stmt    { $$ = new IfStmt($3, $5, $7); }
          ;

ForStmt    :    T_For '(' ExprBrack ';' Expr ';' ExprBrack ')' Stmt    { $$ = new ForStmt($3, $5, $7, $9); }
           ;

WhileStmt    :    T_While '(' Expr ')' Stmt    { $$ = new WhileStmt($3, $5); }
             ;

ReturnStmt    :    T_Return ExprBrack ';'    { $$ = new ReturnStmt(Join(@1, @2), $2); }
              ;

ExprBrack    :    Expr    { $$=$1; }
             |        { $$ = new EmptyExpr(); }
             ;

BreakStmt    :    T_Break ';'    { $$ = new BreakStmt(@1); }
             ;

PrintStmt    :    T_Print '(' ExprList ')' ';'    { $$ = new PrintStmt($3); }
             ;

ExprList    :    ExprList ',' Expr    { ($$=$1)-> Append($3); }
            |    Expr    { ($$ = new List<Expr*>)-> Append($1); }
            ;

SwitchStmt    :    T_Switch '(' Expr ')' '{' CaseList DefaultBrack '}'    { $$ = new SwitchStmt($3, $6, $7); }
              ;

CaseList    :    CaseList Case    { ($$=$1)-> Append($2); }
            |    Case    { ($$ = new List<CaseExpr*>)-> Append($1); }
            ;

Case    :    T_Case T_IntConstant ':' StmtList    { 
            IntConst *intConst = new IntConst(@2, $2);
            $$ = new CaseExpr(intConst, $4);
        }
        |    T_Case T_IntConstant ':'    { 
            IntConst *intConst = new IntConst(@2, $2);
            $$ = new CaseExpr(intConst, new List<Stmt*>);
        }
        ;

DefaultBrack    :    T_Default ':' StmtList    { $$ = new DefaultBrack($3); }
                |           { $$ = NULL; }
                ;

Expr    :    AssignExpr    { $$=$1; }
        |    Constant    { $$=$1; }
        |    LValue    { $$=$1; }
        |    T_This    { $$ = new This(@1); }
        |    Call    { $$=$1; }
        |    '(' Expr ')'    { $$=$2; }
        |    ArithmeticExpr    { $$=$1; }
        |    RelationalExpr    { $$=$1; }
        |    EqualityExpr    { $$=$1; }
        |    LogicalExpr    { $$=$1; }
        |    PostfixExpr    { $$=$1; }
        |    ReadIntegerExpr    { $$=$1; }
        |    ReadLineExpr    { $$=$1; }
        |    NewExpr    { $$=$1; }
        |    NewArrayExpr    { $$=$1; }
        ;

AssignExpr    :    LValue '=' Expr    {
                  Operator *equal = new Operator(@2, "=");
                  $$ = new AssignExpr($1, equal, $3);
              }
              ;

LValue    :    T_Identifier    {
              Identifier *identifier = new Identifier(@1, $1);
              $$ = new FieldAccess(NULL, identifier);
          }
          |    Expr '.' T_Identifier    {
              Identifier *identifier = new Identifier(@3, $3);
              $$ = new FieldAccess($1, identifier);
          }
          |    Expr '[' Expr ']'    {
              $$ = new ArrayAccess(Join(@1, @4), $1, $3);
          }
          ;

Call    :    T_Identifier '(' Actuals ')'    {
            Identifier *identifier = new Identifier(@1, $1);
            $$ = new Call(Join(@1, @4), NULL, identifier, $3);
        }
        |    Expr '.' T_Identifier '(' Actuals ')'    {
            Identifier *identifier = new Identifier(@3, $3);
            $$ = new Call(Join(@1, @6), $1, identifier, $5);
        }
        ;

Actuals    :    ExprList    { $$=$1; }
           |                { $$ = new List<Expr*>; }
           ;

Constant    :    T_IntConstant    { $$ = new IntConstant(@1, $1); }
            |    T_DoubleConstant    { $$ = new DoubleConstant(@1, $1); }
            |    T_BoolConstant    { $$ = new BoolConstant(@1, $1); }
            |    T_StringConstant    { $$ = new StringConstant(@1, $1); }
            |    T_Null    { $$ = new NullConstant(@1); }
            ;

ArithmeticExpr    :    Expr '+' Expr    {
                      Operator *plus = new Operator(@2, "+");
                      $$ = new ArithmeticExpr($1, plus, $3);
                  }
                  |    Expr '-' Expr    {
                      Operator *minus = new Operator(@2, "-");
                      $$ = new ArithmeticExpr($1, minus, $3);
                  }
                  |    Expr '*' Expr    {
                      Operator *times = new Operator(@2, "*");
                      $$ = new ArithmeticExpr($1, times, $3);
                  }
                  |    Expr '/' Expr    {
                      Operator *devide = new Operator(@2, "/");
                      $$ = new ArithmeticExpr($1, devide, $3);
                  }
                  |    Expr '%' Expr    {
                      Operator *mod = new Operator(@2, "%");
                      $$ = new ArithmeticExpr($1, mod, $3);
                  }
                  |    '-' Expr %prec NEGT   {
                      Operator *neg = new Operator(@1, "-");
                      $$ = new ArithmeticExpr(neg, $2);
                  }
                  ;

RelationalExpr    :    Expr T_LessEqual Expr    {
                      Operator *leq = new Operator(@2, "<=");
                      $$ = new RelationalExpr($1, leq, $3);
                  }
                  |    Expr '<' Expr    {
                      Operator *less = new Operator(@2, "<");
                      $$ = new RelationalExpr($1, less, $3);
                  }
                  |    Expr T_GreaterEqual Expr    {
                      Operator *geq = new Operator(@2, ">=");
                      $$ = new RelationalExpr($1, geq, $3);
                  }
                  |    Expr '>' Expr    {
                      Operator *greater = new Operator(@2, ">");
                      $$ = new RelationalExpr($1, greater, $3);
                  }
                  ;

EqualityExpr    :    Expr T_Equal Expr    {
                    Operator *equal__ = new Operator(@2, "==");
                    $$ = new EqualityExpr($1, equal__, $3);
                }
                |    Expr T_NotEqual Expr    {
                    Operator *notEqual = new Operator(@2, "!=");
                    $$ = new EqualityExpr($1, notEqual, $3);
                }
                ;

LogicalExpr    :    Expr T_And Expr    {
                   Operator *and_ = new Operator(@2, "&&");
                   $$ = new LogicalExpr($1, and_, $3);
               }
               |    Expr T_Or Expr    {
                   Operator *or_ = new Operator(@2, "||");
                   $$ = new LogicalExpr($1, or_, $3);
               }
               |    '!' Expr    {
                   Operator *not_ = new Operator(@2, "!");
                   $$ = new LogicalExpr(not_, $2);
               }
               ;

ReadIntegerExpr    :    T_ReadInteger '(' ')'    { $$ = new ReadIntegerExpr(@1); }
                   ;

ReadLineExpr       :    T_ReadLine '(' ')'    { $$ = new ReadLineExpr(@1); }
                   ;

NewExpr    :    T_New '(' T_Identifier ')'    {
               Identifier *identifier = new Identifier(@3, $3);
               NamedType *namedtype = new NamedType(identifier);
               $$ = new NewExpr(Join(@1, @4), namedtype);
           }
           ;

NewArrayExpr    :    T_NewArray '(' Expr ',' Type ')'    { $$ = new NewArrayExpr(Join(@1, @6), $3, $5); }
                ;

PostfixExpr    :    LValue T_Increm     {
                   Operator *inc_ = new Operator(@2, "++");
                   $$ = new PostfixExpr($1, inc_);
               }
               |    LValue T_Decrem    {
                   Operator *dec_ = new Operator(@2, "--");
                   $$ = new PostfixExpr($1, dec_);
               }
               ;


%%

/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated y.tab.c file.
 * This section is where you put definitions of helper functions.
 */

/* Function: InitParser
 * --------------------
 * This function will be called before any calls to yyparse().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the parser (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yydebug that controls whether yacc prints debugging information about
 * parser actions (shift/reduce) and contents of state stack during parser.
 * If set to false, no information is printed. Setting it to true will give
 * you a running trail that might be helpful when debugging your parser.
 * Please be sure the variable is set to false when submitting your final
 * version.
 */
void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   yydebug = false;
}

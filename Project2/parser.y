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
    List<VarDecl*> vardeclList;
    FnDecl *fndecl;
    ClassDecl *classdecl;
    InterfaceDecl *interfacedecl;
    Type *type;
    NamedType *namedtype;
    Stmt *stmt;
    List<Stmt*> stmtList;
    StmtBlock *stmtblock;
    IfStmt *ifstmt;
    ForStmt *forstmt;
    WhileStmt *whilestmt;
    PrintStmt *printstmt;
    ReturnStmt *returnstmt;
    BreakStmt *breakstmt;
    SwitchStmt *switchstmt;
    Expr *expr;
    List<Expr*> *exprList;
    AssignExpr *assignexpr;
    LogicalExpr *logicalexpr;
    PostfixExpr *postfixexpr;
    EqualityExpr *equalityexpr;
    ArithmeticExpr *arithmeticexpr;
    RelationalExpr *relationalexpr;
    ReadIntegerExpr *readintegerexpr;
    NewExpr *newexpr;
    NewArrayExpr *newarrayexpr;
    FieldAccess *fieldaccess;
    ArrayAccess *arrayaccess;
    NullConstant *nullconstant;
    Default *default;
    Call *call;
    Case *case;
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
 * means that when we are setting $$ for a reduction for DeclList ore reading
 * $n which corresponds to a DeclList nonterminal we are accessing the field
 * of the union named "declList" which is of type List<Decl*>.
 * pp2: You'll need to add many of these of your own.
 */
%type <program>           Program
%type <declList>          DeclList 
%type <decl>              Decl
%type <vardecl>           VarDecl
%type <vardeclList>       VarDeclList
%type <fndecl>            FnDecl
%type <classdecl>         ClassDecl
%type <interfacedecl>     InterfaceDecl
%type <type>              Type
%type <namedtype>         NamedType
%type <stmt>              Stmt
%type <stmtList>          StmtList
%type <stmtblock>         StmtBlock
%type <ifstmt>            IfStmt
%type <forstmt>           ForStmt
%type <whilestmt>         WhileStmt
%type <printstmt>         PrintStmt
%type <returnstmt>        ReturnStmt
%type <breakstmt>         BreakStmt
%type <switchstmt>        SwitchStmt
%type <expr>              Expr
%type <exprList>          ExprList
%type <assignexpr>        AssignExpr
%type <logicalexpr>       LogicalExpr
%type <postfixexpr>       PostfixExpr
%type <equalityexpr>      EqualityExpr
%type <arithmeticexpr>    ArithmeticExpr
%type <relationalexpr>    RelationalExpr
%type <readintegerexpr>   ReadIntegerExpr
%type <newexpr>           NewExpr
%type <newarrayexpr>      NewArrayExpr
%type <fieldaccess>       FieldAccess
%type <arrayaccess>       ArrayAccess
%type <call>              Call
%type <case>              Case


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

Decl      :    VarDecl               {   }
          |    FnDecl                {   }
          |    ClassDecl             {   }
          |    InterfaceDecl         {   } 
          ;

VarDecl    :    Var    {   }
           ;

Var   :    Type T_Identifier ';'    {
                                        Idetifier *identifier = new Idetifier(@2, $2);
                                        $$ = new VarDecl(identifier, $1);
                                    }
      ;

Type    :    T_int    {   }
        |    T_Double    {   }
        |    T_Bool    {   }
        |    T_String    {   }
        |    T_Identifier    {   }
        |    Type T_Dims    {   }
        ;

FnDecl    :    T_void T_Identifier '(' Formals ')' StmtBlock    {
                                                                    Identifier *identifier = new Identifier(@2, $2);
                                                                    ($$ = new FnDecl(identifier, $1, $4))-> SetFunctionBody($6);
                                                                }
          |    Type T_Identifier '(' Formals ')' StmtBlock    {
                                                                    Identifier *identifier = new Identifier(@2, $2);
                                                                    ($$ = new FnDecl(identifier, $1, $4))-> SetFunctionBody($6);
                                                              }
          ;

Formals    :    VarList    {   }
           |        {   }
           ;

VarList    :    VarList ',' Var    {   }
           |    Var    {   }
           ;

ClassDecl    :    T_Class T_Identifier '{' FieldList '}'    {   }
             |    T_Class T_Identifier T_Extends T_Identifier '{' FieldList '}'    {   }
             |    T_Class T_Identifier T_Implements IdentifierList '{' FieldList '}'    {   }
             |    T_Class T_Identifier T_Extends T_Identifier T_Implements IdentifierList '{' FieldList '}'    {   }
             ;

IdentifierList    :    IdentifierList ',' T_Identifier    {   }
                  |    T_Identifier    {   }
                  ;

FieldList    :        {   }
             |    FieldList Field    {   }
             ;

Field    :    VarDecl    {   }
         |    FnDecl    {   }
         ;

InterfaceDecl    :    T_Interface T_Identifier ProtoTypeList    {
                                                                    Identifier *identifier = new Identifier(@2, $2);
                                                                    $$ = new InterfaceDecl(identifier, );
                                                                }
                 ;

ProtoTypeList    :        {   }
                 |    ProtoTypeList ProtoType    {   }
                 ;

ProtoType    :    Type T_Identifier '(' Formals ')' ';'    {   }
             |    T_Void T_Identifier '(' Formals ')' ';'    {   }
             ;

StmtBlock    :    '{' VarDeclList StmtList '}'    {   }
             ;

VarDeclList    :    {   }
               |    VarDeclList VarDecl    {   }
               ;

StmtList    :        {   }
            |    StmtList Stmt    {   }
            ;

Stmt    :    ExprBrack    {   }
        |    IfStmt    {   }
        |    ForStmt    {   }
        |    WhileStmt    {   }
        |    ReturnStmt    {   }
        |    BreakStmt    {   }
        |    PrintStmt    {   }
        |    SwitchStmt    {   }
        |    StmtBlock    {   }
        ;

ExprBrack    :        {   }
             |    Expr    {   }
             ;

IfStmt    :    T_If '(' Expr ')' Stmt    {   }
          |    T_If '(' Expr ')' StmtBlock T_Else Stmt    {   }
          ;

ForStmt    :    T_For '(' ExprBrack ';' Expr ';' ExprBrack ')' StmtBlock    {   }
           ;

WhileStmt    :    T_While '(' Expr ')' Stmt    {   }
             ;

ReturnStmt    :    T_Return ExprBrack ';'        {   }
              ;

BreakStmt    :    T_Break ';'        {   }
             ;

PrintStmt    :    T_Print '(' ExprList ')' ';'        {   }
             ;

ExprList    :    ExprList Expr    {   }
            |    Expr    {   }
            ;

SwitchStmt    :    T_Switch '(' Expr ')' CaseList DefaultBrack    {   }
              ;

CaseList    :    CaseList Case    {   }
            |    Case    {   }
            ;

Case    :    T_Case StmtList    {   }
        ;

DefaultBrack    :    T_Default StmtList    {   }
                ;

Expr    :    LValue    {   }
        |    Constant    {   }
        |    T_This    {   }
        |    Call    {   }
        |    '(' Expr ')'    {   }
        |    AssignExpr    {   }
        |    LogicalExpr    {   }
        |    PostfixExpr    {   }
        |    EqualityExpr    {   }
        |    ArithmeticExpr    {   }
        |    RelationalExpr    {   }
        |    ReadIntegerExpr    {   }
        |    NewExpr    {   }
        |    NewArrayExpr    {   }
        ;

LValue    :    T_Identifier    {   }
          |    Expr '.' T_Identifier    {   }
          |    Expr '[' Expr ']'    {   }
          ;

Constant    :    T_IntConstant    {   }
            |    T_DoubleConstant    {   }
            |    T_BoolConstant    {   }
            |    T_StringConstant    {   }
            |    T_Null    {   }
            ;

Call    :    T_Identifier '(' Actuals ')'    {   }
        |    Expr '.' T_Identifier '(' Actuals ')'    {   }
        ;

Actuals    :    ExprList    {   }
           |                {   }
           ;

AssignExpr    :    LValue '=' Expr    {   }
              ;

LogicalExpr    :    Expr T_And Expr    {   }
               |    Expr T_Or Expr    {   }
               |    '!' Expr    {   }
               ;

PostfixExpr    :    LValue T_Increm    {   }
               |    LValue T_Decrem    {   }
               ;

EqualityExpr    :    Expr T_Equal Expr    {   }
                |    Expr T_NotEqual Expr    {   }
                ;

ArithmeticExpr    :    Expr '+' Expr    {   }
                  |    Expr '-' Expr    {   }
                  |    Expr '*' Expr    {   }
                  |    Expr '/' Expr    {   }
                  |    Expr '%' Expr    {   }
                  |    '-' Expr    {   }
                  ;

RelationalExpr    :    Expr T_LessEqual Expr    {   }
                  |    Expr '<' Expr    {   }
                  |    Expr T_GreaterEqual Expr    {   }
                  |    Expr '>' Expr    {   }
                  ;

ReadIntegerExpr    :    T_ReadInteger '(' ')'    {   }
                   ;

NewExpr    :    T_New '(' T_Identifier ')'    {   }
           ;

NewArrayExpr    :    T_NewArray '(' Expr ',' Type ')'    {   }
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

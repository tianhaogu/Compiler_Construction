/* File:  scanner.l
 * ----------------
 * Lex inupt file to generate the scanner for the compiler.
 */

%{

/* The text within this first region delimited by %{ and %} is assumed to
 * be C/C++ code and will be copied verbatim to the lex.yy.c file ahead
 * of the definitions of the yylex() function. Add other header file inclusions
 * or C++ variable declarations/prototypes that are needed by your code here.
 */

#include <string.h>
#include "scanner.h"
#include "utility.h" // for PrintDebug()
#include "errors.h"

/* Global variable: yylval
 * -----------------------
 * This global variable is how we get attribute information about the token
 * just scanned to the client. The scanner sets the global variable
 * appropriately and since it's global the client can just read it.  In the
 * future, this variable will be declared for us in the y.tab.c file
 * produced by Yacc, but for now, we declare it manually.
 */
YYSTYPE yylval;  // manually declared for pp1, later Yacc provides

/* Global variable: yylloc
 * -----------------------
 * This global variable is how we get position information about the token
 * just scanned to the client. (Operates similarly to yylval above)
 */
struct yyltype yylloc; // manually dclared for pp1, later Yacc provides

int currLine = 1;
int currCol = 1;

/* Macro: YY_USER_ACTION 
 * ---------------------
 * This flex built-in macro can be defined to provide an action which is
 * always executed prior to any matched rule's action. Basically, it is
 * a way of having a piece of code common to all actions factored out to
 * this routine.  We already defined it for you and left the empty
 * function DoBeforeEachAction ready for your use as needed. It will
 * be called once for each pattern scanned from the file, before
 * executing its action.
 */
static void DoBeforeEachAction(); 
#define YY_USER_ACTION DoBeforeEachAction();

%}

 /* The section before the first %% is the Definitions section of the lex
  * input file. Here is where you set options for the scanner, define lex
  * states, and can set up definitions to give names to regular expressions
  * as a simple substitution mechanism that allows for more readable
  * entries in the Rules section later. 
  */


VOID (void)
INT (int)
DOUBLE (double)
BOOL (bool)
STRING (string)
CLASS (class)
INTERFACE (interface)
NULL (null)
THIS (this)
EXTENDS (extends)
IMPLEMENTS (implements)
FOR (for)
WHILE (while)
IF (if)
ELSE (else)
RETURN (return)
BREAK (break)
NEW (New)
NEWARRAY (NewArray)

BOOLCONST (true|false)
IDENTIFIER ([a-zA-Z][0-9a-zA-Z_]*)
DEC_DIGIT ([0-9])
HEX_DIGIT ([0-9a-fA-F])
DEC_INT ({DEC_DIGIT}+)
HEX_INT (0[x|X]{HEX_DIGIT}+)
INTCONST ({DEC_INT}|{HEX_INT})
EXPONENT ([e|E][+]?{DEC_INT})
DOUBLECONST ({DEC_INT}\.{DEC_DIGIT}*{EXPONENT}?)
STRINGCONST (\"[^\n\"]*\")

LEQ (<=)
EQ (==)
GEQ (>=)
NEQ (!=)
AND (&&)
OR (\|\|)
OPERATOR ([-+*/%<=>!;,.[\](){}])

NEWLINE (\n)
STRINGINCONST (\"[^\n\"]*{NEWLINE})
SPACE ([ ]+)
NOMATCH (.)


%%             /* BEGIN RULES SECTION */
 /* All patterns and actions should be placed between the start and stop
  * %% markers which delimit the Rules section. 
  */


{VOID} {return T_Void;}
{INT} {return T_Int;}
{DOUBLE} {return T_Double;}
{BOOL} {return T_Bool;}
{STRING} {return T_String;}
{CLASS} {return T_Class;}
{INTERFACE} {return T_Interface;}
{NULL} {return T_Null;}
{THIS} {return T_This;}
{EXTENDS} {return T_Extends;}
{IMPLEMENTS} {return T_Implements;}
{FOR} {return T_For;}
{WHILE} {return T_While;}
{IF} {return T_If;}
{ELSE} {return T_Else;}
{RETURN} {return T_Return;}
{BREAK} {return T_Break;}
{NEW} {return T_New;}
{NEWARRAY} {return T_NewArray;}

{BOOLCONST} {
    yylval.boolConstant = (strlen(yytext) == 4) ? true : false;
    return T_BoolConstant;
}
{INTCONST} {
    bool check_dec = true;
    for (int i = 0; i < strlen(yytext); i++) {
        if (isdigit(yytext[i]) == 0) {
            check_dec = false;
            break;
        }
    }
    yylval.integerConstant = check_dec ? strtol(yytext, NULL, 10) : strtol(yytext, NULL, 16);
    return T_IntConstant;
}
{DOUBLECONST} {
    yylval.doubleConstant = atof(yytext);
    return T_DoubleConstant;
}
{STRINGCONST} {
    yylval.stringConstant = yytext;
    return T_StringConstant;
}
{IDENTIFIER} {
    if (strlen(yytext) > MaxIdentLen) {
        ReportError::LongIdentifier(&yylloc, yytext);
    }
    for (int i = 0; i < MaxIdentLen; ++i) {
        yylval.identifier[i] = (i < strlen(yytext)) ? yytext[i] : '\0';
    }
    return T_Identifier;
}

{LEQ} {return T_LessEqual;}
{GEQ} {return T_GreaterEqual;}
{EQ} {return T_Equal;}
{NEQ} {return T_NotEqual;}
{AND} {return T_And;}
{OR} {return T_Or;}
{OPERATOR} {return yytext[0];}

{NEWLINE} {
    currLine += 1;
    currCol = 1;
}
{STRINGINCONST} {
    string truncate = "";
    for (int i = 0; i < strlen(yytext); i++) {
        if (yytext[i] == '\n') {
            currLine += 1;
            continue;
        }
        truncate += yytext[i];
    }
    currCol = 1;
    ReportError::UntermString(&yylloc, truncate.c_str());
}
{SPACE} {}
{NOMATCH} {ReportError::UnrecogChar(&yylloc, yytext[0]);}


%%
/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated lex.yy.c file.
 * This section is where you put definitions of helper functions.
 */


/* Function: InitScanner
 * ---------------------
 * This function will be called before any calls to yylex().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the scanner (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yy_flex_debug that controls whether flex prints debugging information
 * about each token and what rule was matched. If set to false, no information
 * is printed. Setting it to true will give you a running trail that might
 * be helpful when debugging your scanner. Please be sure the variable is
 * set to false when submitting your final version.
 */
void InitScanner() {
    PrintDebug("lex", "Initializing scanner");
    yy_flex_debug = false;
}


/* Function: DoBeforeEachAction()
 * ------------------------------
 * This function is installed as the YY_USER_ACTION. This is a place
 * to group code common to all actions.
 */
static void DoBeforeEachAction() {
    yylloc.first_line = currLine;
    yylloc.last_line = currLine;
    yylloc.first_column = currCol;
    yylloc.last_column = currCol + strlen(yytext) - 1;
    currCol += strlen(yytext);
}

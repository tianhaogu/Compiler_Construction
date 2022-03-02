/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 11 "parser.y"


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


#line 86 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_Void = 258,
    T_Bool = 259,
    T_Int = 260,
    T_Double = 261,
    T_String = 262,
    T_Class = 263,
    T_LessEqual = 264,
    T_GreaterEqual = 265,
    T_Equal = 266,
    T_NotEqual = 267,
    T_Dims = 268,
    T_And = 269,
    T_Or = 270,
    T_Null = 271,
    T_Extends = 272,
    T_This = 273,
    T_Interface = 274,
    T_Implements = 275,
    T_While = 276,
    T_For = 277,
    T_If = 278,
    T_Else = 279,
    T_Return = 280,
    T_Break = 281,
    T_New = 282,
    T_NewArray = 283,
    T_Print = 284,
    T_ReadInteger = 285,
    T_ReadLine = 286,
    T_Identifier = 287,
    T_StringConstant = 288,
    T_IntConstant = 289,
    T_DoubleConstant = 290,
    T_BoolConstant = 291,
    T_Increm = 292,
    T_Decrem = 293,
    T_Switch = 294,
    T_Case = 295,
    T_Default = 296
  };
#endif
/* Tokens.  */
#define T_Void 258
#define T_Bool 259
#define T_Int 260
#define T_Double 261
#define T_String 262
#define T_Class 263
#define T_LessEqual 264
#define T_GreaterEqual 265
#define T_Equal 266
#define T_NotEqual 267
#define T_Dims 268
#define T_And 269
#define T_Or 270
#define T_Null 271
#define T_Extends 272
#define T_This 273
#define T_Interface 274
#define T_Implements 275
#define T_While 276
#define T_For 277
#define T_If 278
#define T_Else 279
#define T_Return 280
#define T_Break 281
#define T_New 282
#define T_NewArray 283
#define T_Print 284
#define T_ReadInteger 285
#define T_ReadLine 286
#define T_Identifier 287
#define T_StringConstant 288
#define T_IntConstant 289
#define T_DoubleConstant 290
#define T_BoolConstant 291
#define T_Increm 292
#define T_Decrem 293
#define T_Switch 294
#define T_Case 295
#define T_Default 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 41 "parser.y"

    Program *program;
    int integerConstant;
    bool boolConstant;
    char *stringConstant;
    double doubleConstant;
    char identifier[MaxIdentLen+1]; // +1 for terminating null
    Decl *decl;
    List<Decl*> *declList;
    VarDecl *vardecl;
    Var *var;
    Type *type;
    FnDecl *fndecl;
    List<VarDecl*> *varList;
    ClassDecl *classdecl;
    NamedType *namedtype;
    List<NamedType*> *identifierlist;
    InterfaceDecl *interfacedecl;
    Stmt *stmt;
    List<Stmt*> stmtList;
    StmtBlock *stmtblock;
    IfStmt *ifstmt;
    ForStmt *forstmt;
    WhileStmt *whilestmt;
    PrintStmt *printstmt;
    ReturnStmt *returnstmt;
    BreakStmt *breakstmt;
    Expr *expr;
    List<Expr*> *exprList;
    LValue *lvalue;
    Call *call;
    AssignExpr *assignexpr;
    LogicalExpr *logicalexpr;
    EqualityExpr *equalityexpr;
    ArithmeticExpr *arithmeticexpr;
    RelationalExpr *relationalexpr;
    ReadIntegerExpr *readintegerexpr;
    ReadLineExpr *readlineexpr;
    NewExpr *newexpr;
    NewArrayExpr *newarrayexpr;

#line 262 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  21
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   426

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  209

#define YYUNDEFTOK  2
#define YYMAXUTOK   296


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,     2,     2,    57,     2,     2,
      43,    44,    55,    53,    45,    54,    48,    56,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    42,
      58,    51,    59,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    50,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,    47,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   168,   168,   180,   181,   184,   185,   186,   187,   190,
     193,   199,   200,   201,   202,   203,   207,   210,   215,   221,
     222,   225,   226,   229,   233,   239,   243,   251,   256,   263,
     264,   267,   268,   271,   277,   278,   281,   285,   292,   295,
     296,   299,   300,   303,   304,   305,   306,   307,   308,   309,
     310,   313,   314,   317,   318,   321,   324,   327,   330,   333,
     336,   337,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   356,   360,   364,   369,
     370,   371,   372,   373,   376,   380,   386,   387,   390,   396,
     400,   404,   410,   414,   420,   424,   428,   432,   436,   440,
     446,   450,   454,   458,   464,   467,   470,   477
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_Void", "T_Bool", "T_Int", "T_Double",
  "T_String", "T_Class", "T_LessEqual", "T_GreaterEqual", "T_Equal",
  "T_NotEqual", "T_Dims", "T_And", "T_Or", "T_Null", "T_Extends", "T_This",
  "T_Interface", "T_Implements", "T_While", "T_For", "T_If", "T_Else",
  "T_Return", "T_Break", "T_New", "T_NewArray", "T_Print", "T_ReadInteger",
  "T_ReadLine", "T_Identifier", "T_StringConstant", "T_IntConstant",
  "T_DoubleConstant", "T_BoolConstant", "T_Increm", "T_Decrem", "T_Switch",
  "T_Case", "T_Default", "';'", "'('", "')'", "','", "'{'", "'}'", "'.'",
  "'['", "']'", "'='", "'!'", "'+'", "'-'", "'*'", "'/'", "'%'", "'<'",
  "'>'", "$accept", "Program", "DeclList", "Decl", "VarDecl", "Var",
  "Type", "FnDecl", "Formals", "VarList", "ClassDecl", "IdentifierList",
  "FieldList", "Field", "InterfaceDecl", "ProtoTypeList", "ProtoType",
  "StmtBlock", "VarDeclList", "StmtList", "Stmt", "ExprBrack", "IfStmt",
  "ForStmt", "WhileStmt", "ReturnStmt", "BreakStmt", "PrintStmt",
  "ExprList", "Expr", "LValue", "Constant", "Call", "Actuals",
  "AssignExpr", "LogicalExpr", "EqualityExpr", "ArithmeticExpr",
  "RelationalExpr", "ReadIntegerExpr", "ReadLineExpr", "NewExpr",
  "NewArrayExpr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,    59,    40,    41,    44,   123,   125,    46,    91,
      93,    61,    33,    43,    45,    42,    47,    37,    60,    62
};
# endif

#define YYPACT_NINF (-84)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      96,   -17,   -84,   -84,   -84,   -84,    -6,    18,   -84,    22,
      96,   -84,   -84,    15,    -8,   -84,   -84,   -84,    35,     8,
     -84,   -84,   -84,   -84,   -84,    40,    26,    48,    52,   -84,
     287,   -84,    26,   -84,    10,    46,    74,     0,   -84,    61,
       6,    88,    24,   -84,    79,    82,    81,    26,    52,   -84,
      97,   -84,   -84,   -84,   -84,   -84,    95,   103,    81,   -84,
     -84,   -84,    71,    90,   -84,   241,    26,    26,   -84,    26,
     -84,   -84,   -84,   106,   123,   -84,   279,   271,   126,   127,
     -84,   -84,   129,   132,   133,   372,   128,   134,   137,   138,
     139,   147,   157,   -84,   -84,   -84,   -84,   372,   -84,   372,
     372,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     213,   122,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,   372,   372,   372,   159,
     -84,   170,   372,   372,   173,   174,   372,    77,   213,   213,
     372,   372,   372,   372,   372,   372,   187,   372,   372,   372,
     372,   372,   372,   372,   372,   372,    99,   172,   130,   -84,
     176,   150,   343,   213,   -84,   -84,   372,   177,   -84,   213,
     213,   213,   213,   213,   213,   183,   182,   213,   213,   213,
     213,   213,   213,   213,   213,   314,   372,   314,   -84,    26,
     191,   213,   -84,   372,   -84,   -84,   201,   205,   -10,   -84,
     190,   372,   314,   -84,   -84,   198,   -84,   314,   -84
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    13,    11,    12,    14,     0,     0,    15,     0,
       2,     4,     5,     0,     0,     6,     7,     8,     0,     0,
      34,     1,     3,     9,    16,     0,    20,     0,     0,    29,
      33,    10,    20,    22,     0,     0,    19,     0,    28,     0,
       0,     0,     0,    35,     0,     0,     0,     0,     0,    29,
       0,    29,    23,    31,    32,    30,     0,     0,     0,    39,
      17,    21,     0,     0,    27,     0,    20,    20,    18,    41,
      29,    24,    25,     0,     0,    40,     0,     0,     0,     0,
      83,    64,     0,     0,     0,    51,     0,     0,     0,     0,
       0,     0,    76,    82,    79,    80,    81,     0,    38,     0,
       0,    50,    42,    43,    44,    45,    46,    47,    48,    49,
      52,    62,    63,    65,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    26,    37,    36,     0,    51,     0,     0,
      58,     0,     0,     0,     0,     0,    87,     0,    91,    99,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    57,
       0,     0,     0,    61,   104,   105,    86,     0,    66,   100,
     102,    92,    93,    89,    90,    77,     0,    94,    95,    96,
      97,    98,   101,   103,    88,    51,     0,    51,   106,     0,
       0,    60,    84,    87,    78,    56,     0,    53,     0,    59,
       0,    51,    51,   107,    85,     0,    54,    51,    55
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -84,   -84,   -84,   242,     7,   -18,   -26,    65,   -31,   -84,
     -84,   203,    28,   -84,   -84,   -84,   -84,   -19,   -84,   -84,
     -36,   -83,   -84,   -84,   -84,   -84,   -84,   -84,   120,   -81,
     -84,   -84,   -84,    70,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,   -84
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    11,    53,    13,    14,    54,    35,    36,
      16,    39,    40,    55,    17,    30,    43,   101,    69,    76,
     102,   103,   104,   105,   106,   107,   108,   109,   166,   110,
     111,   112,   113,   167,   114,   115,   116,   117,   118,   119,
     120,   121,   122
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      34,    44,   129,    24,    42,    24,    34,    12,    33,     1,
       2,     3,     4,     5,    33,    18,   137,    12,   138,   139,
      48,    34,    21,    24,    25,    27,    19,    60,    28,    61,
       2,     3,     4,     5,   203,    73,    74,    24,     8,    68,
      34,    34,    45,    34,   157,   156,    49,   158,    33,    33,
      20,   161,   163,    52,    29,   163,    57,    23,     8,   169,
     170,   171,   172,   173,   174,    15,   176,   177,   178,   179,
     180,   181,   182,   183,   184,    15,    75,    63,    26,    65,
      37,   191,    31,    32,    38,   191,   140,   141,   142,   143,
      46,   144,   145,     1,     2,     3,     4,     5,    77,     1,
       2,     3,     4,     5,     6,   196,    50,    51,   140,   141,
     142,   143,   163,   144,   145,     7,    50,    70,   205,    47,
      56,   168,     8,    58,    31,   146,   147,    59,     8,    64,
     148,   149,   150,   151,   152,   153,   154,    71,    66,   140,
     141,   142,   143,   185,   144,   145,    67,   146,   147,   195,
      78,   197,   148,   149,   150,   151,   152,   153,   154,   140,
     141,   142,   143,   198,   144,   145,   206,    79,   124,   125,
     130,   208,   126,   155,   187,   127,   128,   131,   146,   147,
     132,   133,   134,   148,   149,   150,   151,   152,   153,   154,
     135,   140,   141,   142,   143,   189,   144,   145,   146,   147,
     136,   159,   160,   148,   149,   150,   151,   152,   153,   154,
     140,   141,   142,   143,   186,   144,   145,   164,   165,   175,
     188,   192,   140,   141,   142,   143,   193,   144,   145,   202,
     146,   147,   194,   199,   204,   148,   149,   150,   151,   152,
     153,   154,   207,   201,     1,     2,     3,     4,     5,   146,
     147,    62,    22,   162,   148,   149,   150,   151,   152,   153,
     154,   146,   147,   200,     0,     0,   148,   149,   150,   151,
     152,   153,   154,     8,     1,     2,     3,     4,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    72,     0,
      41,     2,     3,     4,     5,    80,     0,    81,     0,     0,
      82,    83,    84,     8,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,     0,     0,   123,     8,
       0,     0,    97,     0,     0,    59,    98,     0,     0,     0,
      80,    99,    81,   100,     0,    82,    83,    84,     0,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,     0,     0,     0,     0,     0,     0,    97,     0,    80,
      59,    81,     0,     0,     0,     0,    99,     0,   100,     0,
      87,    88,     0,    90,    91,    92,    93,    94,    95,    96,
       0,     0,     0,     0,     0,     0,    97,   190,    80,     0,
      81,     0,     0,     0,     0,    99,     0,   100,     0,    87,
      88,     0,    90,    91,    92,    93,    94,    95,    96,     0,
       0,     0,     0,     0,     0,    97,     0,     0,     0,     0,
       0,     0,     0,     0,    99,     0,   100
};

static const yytype_int16 yycheck[] =
{
      26,    32,    85,    13,    30,    13,    32,     0,    26,     3,
       4,     5,     6,     7,    32,    32,    97,    10,    99,   100,
      20,    47,     0,    13,    32,    17,    32,    46,    20,    47,
       4,     5,     6,     7,    44,    66,    67,    13,    32,    58,
      66,    67,    32,    69,   127,   126,    46,   128,    66,    67,
      32,   132,   133,    47,    46,   136,    32,    42,    32,   140,
     141,   142,   143,   144,   145,     0,   147,   148,   149,   150,
     151,   152,   153,   154,   155,    10,    69,    49,    43,    51,
      32,   162,    42,    43,    32,   166,     9,    10,    11,    12,
      44,    14,    15,     3,     4,     5,     6,     7,    70,     3,
       4,     5,     6,     7,     8,   186,    45,    46,     9,    10,
      11,    12,   193,    14,    15,    19,    45,    46,   201,    45,
      32,    44,    32,    44,    42,    48,    49,    46,    32,    32,
      53,    54,    55,    56,    57,    58,    59,    47,    43,     9,
      10,    11,    12,    44,    14,    15,    43,    48,    49,   185,
      44,   187,    53,    54,    55,    56,    57,    58,    59,     9,
      10,    11,    12,   189,    14,    15,   202,    44,    42,    42,
      42,   207,    43,    51,    44,    43,    43,    43,    48,    49,
      43,    43,    43,    53,    54,    55,    56,    57,    58,    59,
      43,     9,    10,    11,    12,    45,    14,    15,    48,    49,
      43,    42,    32,    53,    54,    55,    56,    57,    58,    59,
       9,    10,    11,    12,    42,    14,    15,    44,    44,    32,
      44,    44,     9,    10,    11,    12,    43,    14,    15,    24,
      48,    49,    50,    42,    44,    53,    54,    55,    56,    57,
      58,    59,    44,    42,     3,     4,     5,     6,     7,    48,
      49,    48,    10,   133,    53,    54,    55,    56,    57,    58,
      59,    48,    49,   193,    -1,    -1,    53,    54,    55,    56,
      57,    58,    59,    32,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
       3,     4,     5,     6,     7,    16,    -1,    18,    -1,    -1,
      21,    22,    23,    32,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    47,    32,
      -1,    -1,    43,    -1,    -1,    46,    47,    -1,    -1,    -1,
      16,    52,    18,    54,    -1,    21,    22,    23,    -1,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    16,
      46,    18,    -1,    -1,    -1,    -1,    52,    -1,    54,    -1,
      27,    28,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    16,    -1,
      18,    -1,    -1,    -1,    -1,    52,    -1,    54,    -1,    27,
      28,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    54
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    19,    32,    61,
      62,    63,    64,    65,    66,    67,    70,    74,    32,    32,
      32,     0,    63,    42,    13,    32,    43,    17,    20,    46,
      75,    42,    43,    65,    66,    68,    69,    32,    32,    71,
      72,     3,    66,    76,    68,    32,    44,    45,    20,    46,
      45,    46,    47,    64,    67,    73,    32,    32,    44,    46,
      77,    65,    71,    72,    32,    72,    43,    43,    77,    78,
      46,    47,    47,    68,    68,    64,    79,    72,    44,    44,
      16,    18,    21,    22,    23,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    43,    47,    52,
      54,    77,    80,    81,    82,    83,    84,    85,    86,    87,
      89,    90,    91,    92,    94,    95,    96,    97,    98,    99,
     100,   101,   102,    47,    42,    42,    43,    43,    43,    81,
      42,    43,    43,    43,    43,    43,    43,    89,    89,    89,
       9,    10,    11,    12,    14,    15,    48,    49,    53,    54,
      55,    56,    57,    58,    59,    51,    89,    81,    89,    42,
      32,    89,    88,    89,    44,    44,    88,    93,    44,    89,
      89,    89,    89,    89,    89,    32,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    44,    42,    44,    44,    45,
      44,    89,    44,    43,    50,    80,    89,    80,    66,    42,
      93,    42,    24,    44,    44,    81,    80,    44,    80
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    60,    61,    62,    62,    63,    63,    63,    63,    64,
      65,    66,    66,    66,    66,    66,    66,    67,    67,    68,
      68,    69,    69,    70,    70,    70,    70,    71,    71,    72,
      72,    73,    73,    74,    75,    75,    76,    76,    77,    78,
      78,    79,    79,    80,    80,    80,    80,    80,    80,    80,
      80,    81,    81,    82,    82,    83,    84,    85,    86,    87,
      88,    88,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    90,    90,    90,    91,
      91,    91,    91,    91,    92,    92,    93,    93,    94,    95,
      95,    95,    96,    96,    97,    97,    97,    97,    97,    97,
      98,    98,    98,    98,    99,   100,   101,   102
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     2,
       3,     1,     1,     1,     1,     1,     2,     6,     6,     1,
       0,     3,     1,     5,     7,     7,     9,     3,     1,     0,
       2,     1,     1,     3,     0,     2,     6,     6,     4,     0,
       2,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     5,     7,     9,     5,     3,     2,     5,
       2,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     4,     1,
       1,     1,     1,     1,     4,     6,     1,     0,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     2,
       3,     3,     3,     3,     3,     3,     4,     6
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 168 "parser.y"
                                   { 
                                      (yylsp[0]); 
                                      /* pp2: The @1 is needed to convince 
                                       * yacc to set up yylloc. You can remove 
                                       * it once you have other uses of @n*/
                                      Program *program = new Program((yyvsp[0].declList));
                                      // if no errors, advance to next phase
                                      if (ReportError::NumErrors() == 0) 
                                          program->Print(0);
                                    }
#line 1752 "y.tab.c"
    break;

  case 3:
#line 180 "parser.y"
                                    { ((yyval.declList)=(yyvsp[-1].declList))-> Append((yyvsp[0].decl)); }
#line 1758 "y.tab.c"
    break;

  case 4:
#line 181 "parser.y"
                                    { ((yyval.declList) = new List<Decl*>)-> Append((yyvsp[0].decl)); }
#line 1764 "y.tab.c"
    break;

  case 5:
#line 184 "parser.y"
                                     {(yyval.decl)=(yyvsp[0].vardecl);}
#line 1770 "y.tab.c"
    break;

  case 6:
#line 185 "parser.y"
                                     {(yyval.decl)=(yyvsp[0].fndecl);}
#line 1776 "y.tab.c"
    break;

  case 7:
#line 186 "parser.y"
                                     {(yyval.decl)=(yyvsp[0].classdecl);}
#line 1782 "y.tab.c"
    break;

  case 8:
#line 187 "parser.y"
                                     {(yyval.decl)=(yyvsp[0].interfacedecl);}
#line 1788 "y.tab.c"
    break;

  case 9:
#line 190 "parser.y"
                           { (yyval.vardecl)=(yyvsp[-1].var); }
#line 1794 "y.tab.c"
    break;

  case 10:
#line 193 "parser.y"
                                    {
          Idetifier *identifier = new Idetifier((yylsp[-1]), (yyvsp[-1].identifier));
          (yyval.var) = new VarDecl(identifier, (yyvsp[-2].type));
      }
#line 1803 "y.tab.c"
    break;

  case 11:
#line 199 "parser.y"
                      { (yyval.type) = Type::intType; }
#line 1809 "y.tab.c"
    break;

  case 12:
#line 200 "parser.y"
                         { (yyval.type) = Type::doubleType; }
#line 1815 "y.tab.c"
    break;

  case 13:
#line 201 "parser.y"
                       { (yyval.type) = Type::boolType; }
#line 1821 "y.tab.c"
    break;

  case 14:
#line 202 "parser.y"
                         { (yyval.type) = Type::stringType; }
#line 1827 "y.tab.c"
    break;

  case 15:
#line 203 "parser.y"
                             {
            Idetifier *identifier = new Idetifier((yylsp[0]), (yyvsp[0].identifier));
            (yyval.type) = new NamedType(identifier);
        }
#line 1836 "y.tab.c"
    break;

  case 16:
#line 207 "parser.y"
                            { (yyval.type) = new ArrayType((yylsp[-1]), (yyvsp[-1].type)); }
#line 1842 "y.tab.c"
    break;

  case 17:
#line 210 "parser.y"
                                                                {
              Identifier *identifier = new Identifier((yylsp[-4]), (yyvsp[-4].identifier));
              Type *type = Type::voidType;
              ((yyval.fndecl) = new FnDecl(identifier, type, (yyvsp[-2].varList)))-> SetFunctionBody((yyvsp[0].stmtblock));
          }
#line 1852 "y.tab.c"
    break;

  case 18:
#line 215 "parser.y"
                                                              {
              Identifier *identifier = new Identifier((yylsp[-4]), (yyvsp[-4].identifier));
              ((yyval.fndecl) = new FnDecl(identifier, (yyvsp[-5].type), (yyvsp[-2].varList)))-> SetFunctionBody((yyvsp[0].stmtblock));
          }
#line 1861 "y.tab.c"
    break;

  case 19:
#line 221 "parser.y"
                           { (yyval.varList)=(yyvsp[0].varList); }
#line 1867 "y.tab.c"
    break;

  case 20:
#line 222 "parser.y"
                    {   }
#line 1873 "y.tab.c"
    break;

  case 21:
#line 225 "parser.y"
                                   { ((yyval.varList)=(yyvsp[-2].varList))-> Append((yyvsp[0].var)); }
#line 1879 "y.tab.c"
    break;

  case 22:
#line 226 "parser.y"
                       { ((yyval.varList) = new List<VarDecl*>)-> Append((yyvsp[0].var)); }
#line 1885 "y.tab.c"
    break;

  case 23:
#line 229 "parser.y"
                                                            {
                 Identifier *identifier = new Identifier((yylsp[-3]), (yyvsp[-3].identifier));
                 (yyval.classdecl) = new ClassDecl(identifier, NULL, NULL, (yyvsp[-1].declList));
             }
#line 1894 "y.tab.c"
    break;

  case 24:
#line 233 "parser.y"
                                                                                   {
                 Identifier *identifier = new Identifier((yylsp[-5]), (yyvsp[-5].identifier));
                 Identifier *ext_ident = new Identifier((yylsp[-3]), (yyvsp[-3].identifier));
                 NamedType *extends = new NamedType(ext_ident);
                 (yyval.classdecl) = new ClassDecl(identifier, extends, NULL, (yyvsp[-1].declList));
             }
#line 1905 "y.tab.c"
    break;

  case 25:
#line 239 "parser.y"
                                                                                        {
                 Identifier *identifier = new Identifier((yylsp[-5]), (yyvsp[-5].identifier));
                 (yyval.classdecl) = new ClassDecl(identifier, NULL, (yyvsp[-1].declList), (yyvsp[-1].declList));
             }
#line 1914 "y.tab.c"
    break;

  case 26:
#line 243 "parser.y"
                                                                                                               {
                 Identifier *identifier = new Identifier((yylsp[-7]), (yyvsp[-7].identifier));
                 Identifier *ext_ident = new Identifier((yylsp[-5]), (yyvsp[-5].identifier));
                 NamedType *extends = new NamedType(ext_ident);
                 (yyval.classdecl) = new ClassDecl(identifier, extends, (yyvsp[-3].identifierlist), (yyvsp[-1].declList));
             }
#line 1925 "y.tab.c"
    break;

  case 27:
#line 251 "parser.y"
                                                          {
                      Identifier *identifier = new Identifier((yylsp[0]), (yyvsp[0].identifier));
                      NamedType *extends = new NamedType(identifier);
                      ((yyval.identifierlist)=(yyvsp[-2].identifierlist))-> Append(extends);
                  }
#line 1935 "y.tab.c"
    break;

  case 28:
#line 256 "parser.y"
                                       {
                      Identifier *identifier = new Identifier((yylsp[0]), (yyvsp[0].identifier));
                      NamedType *extends = new NamedType(identifier);
                      ((yyval.identifierlist) = new List<NamedType*>)-> Append(extends);
                  }
#line 1945 "y.tab.c"
    break;

  case 29:
#line 263 "parser.y"
                      {   }
#line 1951 "y.tab.c"
    break;

  case 30:
#line 264 "parser.y"
                                     { ((yyval.declList)=(yyvsp[-1].declList))-> Append((yyvsp[0].decl)); }
#line 1957 "y.tab.c"
    break;

  case 31:
#line 267 "parser.y"
                         { (yyval.decl)=(yyvsp[0].vardecl); }
#line 1963 "y.tab.c"
    break;

  case 32:
#line 268 "parser.y"
                        { (yyval.decl)=(yyvsp[0].fndecl); }
#line 1969 "y.tab.c"
    break;

  case 33:
#line 271 "parser.y"
                                                                {
                     Identifier *identifier = new Identifier((yylsp[-1]), (yyvsp[-1].identifier));
                     (yyval.interfacedecl) = new InterfaceDecl(identifier, (yyvsp[0].declList));
                 }
#line 1978 "y.tab.c"
    break;

  case 34:
#line 277 "parser.y"
                          {   }
#line 1984 "y.tab.c"
    break;

  case 35:
#line 278 "parser.y"
                                                 { ((yyval.declList)=(yyvsp[-1].declList))-> Append((yyvsp[0].decl)); }
#line 1990 "y.tab.c"
    break;

  case 36:
#line 281 "parser.y"
                                                           {
                 Identifier *identifier = new Identifier((yylsp[-4]), (yyvsp[-4].identifier));
                 (yyval.decl) = new FnDecl(identifier, (yyvsp[-5].type), (yyvsp[-2].varList));
             }
#line 1999 "y.tab.c"
    break;

  case 37:
#line 285 "parser.y"
                                                             {
                 Identifier *identifier = new Identifier((yylsp[-4]), (yyvsp[-4].identifier));
                 Type *type = Type::voidType;
                 (yyval.decl) = new FnDecl(identifier, type, (yyvsp[-2].varList));
             }
#line 2009 "y.tab.c"
    break;

  case 38:
#line 292 "parser.y"
                                                  { (yyval.stmtblock) = new StmtBlock((yyvsp[-2].varList), (yyvsp[-1].stmtList)); }
#line 2015 "y.tab.c"
    break;

  case 39:
#line 295 "parser.y"
                        {   }
#line 2021 "y.tab.c"
    break;

  case 40:
#line 296 "parser.y"
                                           { ((yyval.varList)=(yyvsp[-1].varList))-> Append((yyvsp[0].vardecl)); }
#line 2027 "y.tab.c"
    break;

  case 41:
#line 299 "parser.y"
                     {   }
#line 2033 "y.tab.c"
    break;

  case 42:
#line 300 "parser.y"
                                  { ((yyval.stmtList)=(yyvsp[-1].stmtList))-> Append((yyvsp[0].stmt)); }
#line 2039 "y.tab.c"
    break;

  case 43:
#line 303 "parser.y"
                          { (yyval.stmt)=(yyvsp[0].expr); }
#line 2045 "y.tab.c"
    break;

  case 44:
#line 304 "parser.y"
                       { (yyval.stmt)=(yyvsp[0].ifstmt); }
#line 2051 "y.tab.c"
    break;

  case 45:
#line 305 "parser.y"
                        { (yyval.stmt)=(yyvsp[0].forstmt); }
#line 2057 "y.tab.c"
    break;

  case 46:
#line 306 "parser.y"
                          { (yyval.stmt)=(yyvsp[0].whilestmt); }
#line 2063 "y.tab.c"
    break;

  case 47:
#line 307 "parser.y"
                           { (yyval.stmt)=(yyvsp[0].returnstmt); }
#line 2069 "y.tab.c"
    break;

  case 48:
#line 308 "parser.y"
                          { (yyval.stmt)=(yyvsp[0].breakstmt); }
#line 2075 "y.tab.c"
    break;

  case 49:
#line 309 "parser.y"
                          { (yyval.stmt)=(yyvsp[0].printstmt); }
#line 2081 "y.tab.c"
    break;

  case 50:
#line 310 "parser.y"
                          { (yyval.stmt)=(yyvsp[0].stmtblock); }
#line 2087 "y.tab.c"
    break;

  case 51:
#line 313 "parser.y"
                      { (yyval.expr) = new EmptyExpr(); }
#line 2093 "y.tab.c"
    break;

  case 52:
#line 314 "parser.y"
                          { (yyval.expr) = (yyvsp[0].expr); }
#line 2099 "y.tab.c"
    break;

  case 53:
#line 317 "parser.y"
                                         { (yyval.ifstmt) = new IfStmt((yyvsp[-2].expr), (yyvsp[0].stmt), NULL); }
#line 2105 "y.tab.c"
    break;

  case 54:
#line 318 "parser.y"
                                                     { (yyval.ifstmt) = new IfStmt((yyvsp[-4].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt)); }
#line 2111 "y.tab.c"
    break;

  case 55:
#line 321 "parser.y"
                                                                       { (yyval.forstmt) = new ForStmt((yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2117 "y.tab.c"
    break;

  case 56:
#line 324 "parser.y"
                                               { (yyval.whilestmt) = new WhileStmt((yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2123 "y.tab.c"
    break;

  case 57:
#line 327 "parser.y"
                                             { (yyval.returnstmt) = new ReturnStmt((yylsp[-1]), (yyvsp[-1].expr)); }
#line 2129 "y.tab.c"
    break;

  case 58:
#line 330 "parser.y"
                                 { (yyval.breakstmt) = new BreakStmt((yylsp[-1])); }
#line 2135 "y.tab.c"
    break;

  case 59:
#line 333 "parser.y"
                                                  { (yyval.printstmt) = new PrintStmt((yyvsp[-2].exprList)); }
#line 2141 "y.tab.c"
    break;

  case 60:
#line 336 "parser.y"
                                  { ((yyval.exprList)=(yyvsp[-1].exprList))-> Append((yyvsp[0].expr)); }
#line 2147 "y.tab.c"
    break;

  case 61:
#line 337 "parser.y"
                         { ((yyval.exprList) = new List<Expr*>)-> Append((yyvsp[0].expr)); }
#line 2153 "y.tab.c"
    break;

  case 62:
#line 340 "parser.y"
                       { (yyval.expr)=(yyvsp[0].lvalue); }
#line 2159 "y.tab.c"
    break;

  case 63:
#line 341 "parser.y"
                         { (yyval.expr)=(yyvsp[0].expr); }
#line 2165 "y.tab.c"
    break;

  case 64:
#line 342 "parser.y"
                       { (yyval.expr) = new This((yylsp[0])); }
#line 2171 "y.tab.c"
    break;

  case 65:
#line 343 "parser.y"
                     { (yyval.expr)=(yyvsp[0].call); }
#line 2177 "y.tab.c"
    break;

  case 66:
#line 344 "parser.y"
                             { (yyval.expr)=(yyvsp[-1].expr); }
#line 2183 "y.tab.c"
    break;

  case 67:
#line 345 "parser.y"
                           { (yyval.expr)=(yyvsp[0].assignexpr); }
#line 2189 "y.tab.c"
    break;

  case 68:
#line 346 "parser.y"
                            { (yyval.expr)=(yyvsp[0].logicalexpr); }
#line 2195 "y.tab.c"
    break;

  case 69:
#line 347 "parser.y"
                             { (yyval.expr)=(yyvsp[0].equalityexpr); }
#line 2201 "y.tab.c"
    break;

  case 70:
#line 348 "parser.y"
                               { (yyval.expr)=(yyvsp[0].arithmeticexpr); }
#line 2207 "y.tab.c"
    break;

  case 71:
#line 349 "parser.y"
                               { (yyval.expr)=(yyvsp[0].relationalexpr); }
#line 2213 "y.tab.c"
    break;

  case 72:
#line 350 "parser.y"
                                { (yyval.expr)=(yyvsp[0].readintegerexpr); }
#line 2219 "y.tab.c"
    break;

  case 73:
#line 351 "parser.y"
                             { (yyval.expr)=(yyvsp[0].readlineexpr); }
#line 2225 "y.tab.c"
    break;

  case 74:
#line 352 "parser.y"
                        { (yyval.expr)=(yyvsp[0].newexpr); }
#line 2231 "y.tab.c"
    break;

  case 75:
#line 353 "parser.y"
                             { (yyval.expr)=(yyvsp[0].newarrayexpr); }
#line 2237 "y.tab.c"
    break;

  case 76:
#line 356 "parser.y"
                               {
              Identifier *identifier = new Identifier((yylsp[0]), (yyvsp[0].identifier));
              (yyval.lvalue) = new FieldAccess(new EmptyExpr(), identifier);
          }
#line 2246 "y.tab.c"
    break;

  case 77:
#line 360 "parser.y"
                                        {
              Identifier *identifier = new Identifier((yylsp[0]), (yyvsp[0].identifier));
              (yyval.lvalue) = new FieldAccess((yyvsp[-2].expr), identifier);
          }
#line 2255 "y.tab.c"
    break;

  case 78:
#line 364 "parser.y"
                                    {
              (yyval.lvalue) = new ArrayAccess(Join((yylsp[-3]), (yylsp[0])), (yyvsp[-3].expr), (yyvsp[-1].expr));
          }
#line 2263 "y.tab.c"
    break;

  case 79:
#line 369 "parser.y"
                                  { (yyval.expr) = new IntConstant((yylsp[0]), (yyvsp[0].integerConstant)); }
#line 2269 "y.tab.c"
    break;

  case 80:
#line 370 "parser.y"
                                     { (yyval.expr) = new DoubleConstant((yylsp[0]), (yyvsp[0].doubleConstant)); }
#line 2275 "y.tab.c"
    break;

  case 81:
#line 371 "parser.y"
                                   { (yyval.expr) = new BoolConstant((yylsp[0]), (yyvsp[0].boolConstant)); }
#line 2281 "y.tab.c"
    break;

  case 82:
#line 372 "parser.y"
                                     { (yyval.expr) = new StringConstant((yylsp[0]), (yyvsp[0].stringConstant)); }
#line 2287 "y.tab.c"
    break;

  case 83:
#line 373 "parser.y"
                           { (yyval.expr) = new NullConstant((yylsp[0])); }
#line 2293 "y.tab.c"
    break;

  case 84:
#line 376 "parser.y"
                                             {
            Identifier *identifier = new Identifier((yylsp[-3]), (yyvsp[-3].identifier));
            (yyval.call) = new Call(Join((yylsp[-3]), (yylsp[0])), new EmptyExpr(), identifier, (yyvsp[-1].exprList));
        }
#line 2302 "y.tab.c"
    break;

  case 85:
#line 380 "parser.y"
                                                      {
            Identifier *identifier = new Identifier((yylsp[-5]), (yyvsp[-5].expr));
            (yyval.call) = new Call(Join((yylsp[-5]), (yylsp[0])), (yyvsp[-5].expr), identifier, (yyvsp[-3].identifier));
        }
#line 2311 "y.tab.c"
    break;

  case 86:
#line 386 "parser.y"
                            { (yyval.exprList)=(yyvsp[0].exprList); }
#line 2317 "y.tab.c"
    break;

  case 87:
#line 387 "parser.y"
                            { (yyval.exprList) = new List<Expr*>; }
#line 2323 "y.tab.c"
    break;

  case 88:
#line 390 "parser.y"
                                      {
                  Operator *operator = new Operator((yylsp[-1]), "=");
                  (yyval.assignexpr) = new AssignExpr((yyvsp[-2].lvalue), operator, (yyvsp[0].expr));
              }
#line 2332 "y.tab.c"
    break;

  case 89:
#line 396 "parser.y"
                                       {
                   Operator *and = new Operator((yylsp[-1]), "&&");
                   (yyval.logicalexpr) = new LogicalExpr((yyvsp[-2].expr), and, (yyvsp[0].expr));
               }
#line 2341 "y.tab.c"
    break;

  case 90:
#line 400 "parser.y"
                                      {
                   Operator *or = new Operator((yylsp[-1]), "||");
                   (yyval.logicalexpr) = new LogicalExpr((yyvsp[-2].expr), or, (yyvsp[0].expr));
               }
#line 2350 "y.tab.c"
    break;

  case 91:
#line 404 "parser.y"
                                {
                   Operator *not = new Operator((yylsp[0]), "!");
                   (yyval.logicalexpr) = new LogicalExpr(not, (yyvsp[0].expr));
               }
#line 2359 "y.tab.c"
    break;

  case 92:
#line 410 "parser.y"
                                          {
                    Operator *equal = new Operator((yylsp[-1]), "==");
                    (yyval.equalityexpr) = new LogicalExpr((yyvsp[-2].expr), equal, (yyvsp[0].expr));
                }
#line 2368 "y.tab.c"
    break;

  case 93:
#line 414 "parser.y"
                                             {
                    Operator *notEqual = new Operator((yylsp[-1]), "!=");
                    (yyval.equalityexpr) = new LogicalExpr((yyvsp[-2].expr), notEqual, (yyvsp[0].expr));
                }
#line 2377 "y.tab.c"
    break;

  case 94:
#line 420 "parser.y"
                                        {
                      Operator *plus = new Operator((yylsp[-1]), "+");
                      (yyval.arithmeticexpr) = new ArithmeticExpr((yyvsp[-2].expr), plus, (yyvsp[0].expr));
                  }
#line 2386 "y.tab.c"
    break;

  case 95:
#line 424 "parser.y"
                                        {
                      Operator *minus = new Operator((yylsp[-1]), "-");
                      (yyval.arithmeticexpr) = new ArithmeticExpr((yyvsp[-2].expr), minus, (yyvsp[0].expr));
                  }
#line 2395 "y.tab.c"
    break;

  case 96:
#line 428 "parser.y"
                                        {
                      Operator *times = new Operator((yylsp[-1]), "*");
                      (yyval.arithmeticexpr) = new ArithmeticExpr((yyvsp[-2].expr), times, (yyvsp[0].expr));
                  }
#line 2404 "y.tab.c"
    break;

  case 97:
#line 432 "parser.y"
                                        {
                      Operator *devide = new Operator((yylsp[-1]), "/");
                      (yyval.arithmeticexpr) = new ArithmeticExpr((yyvsp[-2].expr), devide, (yyvsp[0].expr));
                  }
#line 2413 "y.tab.c"
    break;

  case 98:
#line 436 "parser.y"
                                        {
                      Operator *mod = new Operator((yylsp[-1]), "%");
                      (yyval.arithmeticexpr) = new ArithmeticExpr((yyvsp[-2].expr), mod, (yyvsp[0].expr));
                  }
#line 2422 "y.tab.c"
    break;

  case 99:
#line 440 "parser.y"
                                   {
                      Operator *neg = new Operator((yylsp[-1]), "-");
                      (yyval.arithmeticexpr) = new ArithmeticExpr(neg, (yyvsp[0].expr));
                  }
#line 2431 "y.tab.c"
    break;

  case 100:
#line 446 "parser.y"
                                                {
                      Operator *leq = new Operator((yylsp[-1]), "<=");
                      (yyval.relationalexpr) = new RelationalExpr((yyvsp[-2].expr), leq, (yyvsp[0].expr));
                  }
#line 2440 "y.tab.c"
    break;

  case 101:
#line 450 "parser.y"
                                        {
                      Operator *less = new Operator((yylsp[-1]), '<');
                      (yyval.relationalexpr) = new RelationalExpr((yyvsp[-2].expr), less, (yyvsp[0].expr));
                  }
#line 2449 "y.tab.c"
    break;

  case 102:
#line 454 "parser.y"
                                                   {
                      Operator *geq = new Operator((yylsp[-1]), ">=");
                      (yyval.relationalexpr) = new RelationalExpr((yyvsp[-2].expr), geq, (yyvsp[0].expr));
                  }
#line 2458 "y.tab.c"
    break;

  case 103:
#line 458 "parser.y"
                                        {
                      Operator *greater = new Operator((yylsp[-1]), '>');
                      (yyval.relationalexpr) = new RelationalExpr((yyvsp[-2].expr), greater, (yyvsp[0].expr));
                  }
#line 2467 "y.tab.c"
    break;

  case 104:
#line 464 "parser.y"
                                                 { (yyval.readintegerexpr) = new ReadIntegerExpr((yylsp[-2])); }
#line 2473 "y.tab.c"
    break;

  case 105:
#line 467 "parser.y"
                                              { (yyval.readlineexpr) = new ReadLine((yylsp[-2])); }
#line 2479 "y.tab.c"
    break;

  case 106:
#line 470 "parser.y"
                                              {
               Identifier *identifier = new Identifier((yylsp[-1]), (yyvsp[-1].identifier));
               NamedType *namedtype = new NamedType(identifier);
               (yyval.newexpr) = new NewExpr((yylsp[-3]), namedtype);
           }
#line 2489 "y.tab.c"
    break;

  case 107:
#line 477 "parser.y"
                                                         { (yyval.newarrayexpr) = new NewArrayExpr((yylsp[-5]), (yyvsp[-3].expr), (yyvsp[-1].type)); }
#line 2495 "y.tab.c"
    break;


#line 2499 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 481 "parser.y"


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

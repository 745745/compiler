/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

            /* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include "../include/node.h"
#include <cstdio>
#include <cstdlib>
extern int yylineno;
extern char* yytext;
void yyerror(const char* msg) { printf("line %d : %s at %s\n", yylineno, msg, yytext); exit(0); }
extern int yylex();
//don't use "using namespace std" in yacc
NCompUnit* CompUnit;
// the top node of ast

#line 79 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
   /* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif




/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
enum yytokentype
{
    CONST = 258,
    INT = 259,
    VOID = 260,
    IF = 261,
    ELSE = 262,
    WHILE = 263,
    BREAK = 264,
    CONTINUE = 265,
    RETURN = 266,
    EQ = 267,
    NE = 268,
    LE = 269,
    GE = 270,
    LT = 271,
    GT = 272,
    NOT = 273,
    AND = 274,
    OR = 275,
    ADD = 276,
    SUB = 277,
    MUL = 278,
    DIV = 279,
    MOD = 280,
    Ident = 281,
    IntConst = 282,
    UNIMUS = 283,
    IFX = 284
};
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 15 "parser.y" /* yacc.c:355  */

    std::string* string;
    int token;//a number about sign
    NCompUnit* compunit;
    NFuncDecl* funcdecl;
    NVarDecl* vardecl;
    NStmt* stmt;
    NExp* exp;
    std::vector<NDecl*>* decllist;
    std::vector<NStmt*>* stmtlist;
    std::vector<NVarDecl*>* vardecllist;
    std::vector<NExp*>* explist;
    NIdentifier* ident;
    NInteger* integer;

#line 165 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse(void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 182 "parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
void* malloc(YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free(void*); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
    yytype_int16 yyss_alloc;
    YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

   /* Relocate STACK from its old location to the new one.  The
      local variables YYSIZE and YYSTACKSIZE give the old and new number of
      elements in the stack, and YYPTR gives the new location of the
      stack.  Advance YYPTR to a properly aligned location for the next
      stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
      /* Copy COUNT objects from SRC to DST.  The source and destination do
         not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

         /* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   277

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  152

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

   /* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
      as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      37,    38,     2,     2,    31,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    30,
       2,    32,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    33,     2,    34,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,    36,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    62,    62,    69,    74,    80,    85,    86,    89,    95,
     101,   109,   115,   122,   127,   133,   138,   145,   149,   155,
     156,   160,   166,   171,   178,   182,   186,   190,   196,   201,
     208,   212,   218,   224,   229,   232,   233,   236,   237,   240,
     245,   249,   255,   259,   263,   267,   268,   272,   276,   280,
     284,   290,   294,   300,   305,   312,   316,   320,   324,   328,
     332,   336,   340,   344,   347,   351,   355,   359,   363,   367,
     371,   375,   379,   383,   387,   388,   392,   398,   404
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char* const yytname[] =
{
  "$end", "error", "$undefined", "CONST", "INT", "VOID", "IF", "ELSE",
  "WHILE", "BREAK", "CONTINUE", "RETURN", "EQ", "NE", "LE", "GE", "LT",
  "GT", "NOT", "AND", "OR", "ADD", "SUB", "MUL", "DIV", "MOD", "Ident",
  "IntConst", "UNIMUS", "IFX", "';'", "','", "'='", "'['", "']'", "'{'",
  "'}'", "'('", "')'", "$accept", "CompUnit", "Decl", "Declaration",
  "ConstDecl", "ConstDeclFoot", "ConstDef", "ArrayDef", "VarDecl",
  "VarDefFoot", "VarDef", "InitVal", "InitValFoot", "FuncDef",
  "FuncFParams", "FuncFParam", "Block", "BlockItems", "BlockItem",
  "Statement", "BlockStmt", "DeclStmt", "Stmt", "IfStmt", "ExpFoot",
  "LExp", "Exp", "Identifier", "Integer", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
      59,    44,    61,    91,    93,   123,   125,    40,    41
};
# endif

#define YYPACT_NINF -115

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-115)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -115,    26,    98,  -115,     4,    22,    22,  -115,  -115,  -115,
    -115,    22,  -115,   -26,  -115,    -2,    14,    49,  -115,  -115,
    -115,    22,     7,    51,     8,  -115,    22,    54,  -115,  -115,
      22,    19,   -11,  -115,   166,   186,    19,    18,  -115,   166,
      27,  -115,  -115,    58,    19,   186,   186,   186,  -115,   159,
     186,  -115,   252,    31,  -115,   194,  -115,    19,  -115,    38,
      55,  -115,  -115,  -115,  -115,  -115,  -115,  -115,    21,     9,
     186,   186,   186,   186,   186,   152,    41,  -115,  -115,  -115,
      22,    56,    59,    82,    83,   184,  -115,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,   208,    31,   166,
    -115,  -115,   104,   104,  -115,  -115,  -115,  -115,    40,   252,
      41,   186,   186,  -115,  -115,  -115,   218,  -115,    76,  -115,
     186,  -115,   121,   252,   134,  -115,   186,   252,   186,   186,
     186,   186,   186,   186,   186,   186,    89,    89,   228,   106,
     106,  -115,  -115,  -115,  -115,   255,   247,    99,  -115,  -115,
      89,  -115
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     2,     1,     0,     0,     0,     4,     7,     6,
       3,     0,    77,     0,    15,    13,     0,     0,     9,    13,
      14,     0,     0,    17,     0,     8,     0,     0,    16,    13,
       0,     0,     0,    29,     0,     0,     0,     0,    10,     0,
      30,    34,    27,     0,     0,     0,     0,     0,    78,     0,
       0,    18,    19,    13,    74,     0,    25,     0,    11,     0,
       0,    28,    26,    71,    69,    70,    21,    22,     0,     0,
       0,     0,     0,     0,     0,     0,    73,    12,    24,    13,
       0,     0,     0,     0,     0,     0,    44,    32,    41,    40,
      39,    33,    36,    38,    35,    37,    45,     0,    13,     0,
      20,    72,    67,    68,    64,    65,    66,    75,     0,    53,
      31,     0,     0,    47,    48,    49,     0,    43,    73,    23,
       0,    76,     0,    63,     0,    50,     0,    54,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    58,
      57,    61,    62,    59,    60,    56,    55,    51,    46,    42,
       0,    52
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -115,  -115,  -115,  -115,    57,  -115,    88,    -9,    65,  -115,
     109,   -30,  -115,  -115,   115,   100,    -7,  -115,  -115,  -114,
    -115,  -115,  -115,  -115,  -115,    32,   -32,    -5,  -115
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     7,     8,    17,    18,    23,     9,    13,
      14,    51,    68,    10,    32,    33,    90,    60,    91,    92,
      93,    94,    95,    96,   108,   122,   123,    53,    54
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      15,    16,    52,    55,    20,    21,    19,    52,    11,    58,
      27,    30,    30,    63,    64,    65,    29,    52,    69,    67,
      43,    19,   147,   148,    42,    40,     3,    44,    97,    56,
      70,    71,    72,    73,    74,    22,   151,    62,   102,   103,
     104,   105,   106,   109,    76,    31,    36,   101,    12,    43,
      78,    24,    99,   116,    41,    98,    57,   100,     4,    80,
      59,    81,    30,    82,    83,    84,    85,    52,    75,   119,
     110,   120,    79,    45,    35,    29,    46,    47,   121,    25,
      26,    12,    48,    34,    35,    86,    39,    35,   127,   118,
      41,    87,    50,   111,   138,    81,   112,    82,    83,    84,
      85,     4,     5,     6,    97,    97,   150,    45,   126,    35,
      46,    47,   113,   114,    38,    12,    48,    88,    97,    86,
     130,   131,   132,   133,    41,    89,    50,    72,    73,    74,
      28,    98,    98,   128,   129,   130,   131,   132,   133,    37,
     134,   135,     0,    61,   124,    98,   128,   129,   130,   131,
     132,   133,     0,   134,   135,     0,     0,     0,     0,   136,
     139,   140,   141,   142,   143,   144,   145,   146,     0,     0,
      45,     0,   137,    46,    47,     0,     0,    45,    12,    48,
      46,    47,     0,     0,    45,    12,    48,    46,    47,    50,
     107,     0,    12,    48,    49,    66,    50,     0,     0,     0,
       0,    49,    45,    50,    45,    46,    47,    46,    47,     0,
      12,    48,    12,    48,   115,    70,    71,    72,    73,    74,
       0,    50,     0,    50,     0,     0,     0,     0,    77,    70,
      71,    72,    73,    74,     0,     0,     0,     0,   117,    70,
      71,    72,    73,    74,     0,     0,     0,     0,   125,    70,
      71,    72,    73,    74,     0,     0,     0,     0,   149,   128,
     129,   130,   131,   132,   133,     0,   134,   128,   129,   130,
     131,   132,   133,    70,    71,    72,    73,    74
};

static const yytype_int16 yycheck[] =
{
       5,     6,    34,    35,    30,    31,    11,    39,     4,    39,
      19,     4,     4,    45,    46,    47,    21,    49,    50,    49,
      31,    26,   136,   137,    31,    30,     0,    38,    60,    36,
      21,    22,    23,    24,    25,    37,   150,    44,    70,    71,
      72,    73,    74,    75,    53,    38,    38,    38,    26,    31,
      57,    37,    31,    85,    35,    60,    38,    36,     3,     4,
      33,     6,     4,     8,     9,    10,    11,    99,    37,    99,
      79,    31,    34,    18,    33,    80,    21,    22,    38,    30,
      31,    26,    27,    32,    33,    30,    32,    33,   120,    98,
      35,    36,    37,    37,   126,     6,    37,     8,     9,    10,
      11,     3,     4,     5,   136,   137,     7,    18,    32,    33,
      21,    22,    30,    30,    26,    26,    27,    60,   150,    30,
      14,    15,    16,    17,    35,    60,    37,    23,    24,    25,
      21,   136,   137,    12,    13,    14,    15,    16,    17,    24,
      19,    20,    -1,    43,   112,   150,    12,    13,    14,    15,
      16,    17,    -1,    19,    20,    -1,    -1,    -1,    -1,    38,
     128,   129,   130,   131,   132,   133,   134,   135,    -1,    -1,
      18,    -1,    38,    21,    22,    -1,    -1,    18,    26,    27,
      21,    22,    -1,    -1,    18,    26,    27,    21,    22,    37,
      38,    -1,    26,    27,    35,    36,    37,    -1,    -1,    -1,
      -1,    35,    18,    37,    18,    21,    22,    21,    22,    -1,
      26,    27,    26,    27,    30,    21,    22,    23,    24,    25,
      -1,    37,    -1,    37,    -1,    -1,    -1,    -1,    34,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    30,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    30,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    30,    12,
      13,    14,    15,    16,    17,    -1,    19,    12,    13,    14,
      15,    16,    17,    21,    22,    23,    24,    25
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    40,    41,     0,     3,     4,     5,    42,    43,    47,
      52,     4,    26,    48,    49,    66,    66,    44,    45,    66,
      30,    31,    37,    46,    37,    30,    31,    46,    49,    66,
       4,    38,    53,    54,    32,    33,    38,    53,    45,    32,
      66,    35,    55,    31,    38,    18,    21,    22,    27,    35,
      37,    50,    65,    66,    67,    65,    55,    38,    50,    33,
      56,    54,    55,    65,    65,    65,    36,    50,    51,    65,
      21,    22,    23,    24,    25,    37,    46,    34,    55,    34,
       4,     6,     8,     9,    10,    11,    30,    36,    43,    47,
      55,    57,    58,    59,    60,    61,    62,    65,    66,    31,
      36,    38,    65,    65,    65,    65,    65,    38,    63,    65,
      46,    37,    37,    30,    30,    30,    65,    30,    46,    50,
      31,    38,    64,    65,    64,    30,    32,    65,    12,    13,
      14,    15,    16,    17,    19,    20,    38,    38,    65,    64,
      64,    64,    64,    64,    64,    64,    64,    58,    58,    30,
       7,    58
};

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    41,    41,    41,    42,    42,    43,    44,
      44,    45,    46,    46,    47,    48,    48,    49,    49,    50,
      50,    50,    51,    51,    52,    52,    52,    52,    53,    53,
      54,    54,    55,    56,    56,    57,    57,    58,    58,    59,
      60,    60,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    62,    62,    63,    63,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    66,    67
};

/* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     0,     1,     1,     4,     1,
       3,     4,     4,     0,     3,     1,     3,     2,     4,     1,
       3,     2,     1,     3,     6,     5,     6,     5,     3,     1,
       2,     5,     3,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     5,     2,     1,     1,     5,     2,     2,     2,
       3,     5,     7,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     3,     3,     3,     2,
       2,     2,     3,     2,     1,     3,     4,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print(FILE* yyoutput, int yytype, YYSTYPE const* const yyvaluep)
{
    FILE* yyo = yyoutput;
    YYUSE(yyo);
    if (!yyvaluep)
        return;
# ifdef YYPRINT
    if (yytype < YYNTOKENS)
        YYPRINT(yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    YYUSE(yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print(FILE* yyoutput, int yytype, YYSTYPE const* const yyvaluep)
{
    YYFPRINTF(yyoutput, "%s %s (",
        yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

    yy_symbol_value_print(yyoutput, yytype, yyvaluep);
    YYFPRINTF(yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print(yytype_int16* yybottom, yytype_int16* yytop)
{
    YYFPRINTF(stderr, "Stack now");
    for (; yybottom <= yytop; yybottom++)
    {
        int yybot = *yybottom;
        YYFPRINTF(stderr, " %d", yybot);
    }
    YYFPRINTF(stderr, "\n");
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
yy_reduce_print(yytype_int16* yyssp, YYSTYPE* yyvsp, int yyrule)
{
    unsigned long int yylno = yyrline[yyrule];
    int yynrhs = yyr2[yyrule];
    int yyi;
    YYFPRINTF(stderr, "Reducing stack by rule %d (line %lu):\n",
        yyrule - 1, yylno);
    /* The symbols being reduced.  */
    for (yyi = 0; yyi < yynrhs; yyi++)
    {
        YYFPRINTF(stderr, "   $%d = ", yyi + 1);
        yy_symbol_print(stderr,
            yystos[yyssp[yyi + 1 - yynrhs]],
            &(yyvsp[(yyi + 1) - (yynrhs)])
        );
        YYFPRINTF(stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
#   define yystrlen strlen
#  else
   /* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen(const char* yystr)
{
    YYSIZE_T yylen;
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
static char*
yystpcpy(char* yydest, const char* yysrc)
{
    char* yyd = yydest;
    const char* yys = yysrc;

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
static YYSIZE_T
yytnamerr(char* yyres, const char* yystr)
{
    if (*yystr == '"')
    {
        YYSIZE_T yyn = 0;
        char const* yyp = yystr;

        for (;;)
            switch (*++yyp)
            {
            case '\'':
            case ',':
                goto do_not_strip_quotes;

            case '\\':
                if (*++yyp != '\\')
                    goto do_not_strip_quotes;
                /* Fall through.  */
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
    do_not_strip_quotes:;
    }

    if (!yyres)
        return yystrlen(yystr);

    return yystpcpy(yyres, yystr) - yyres;
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
yysyntax_error(YYSIZE_T* yymsg_alloc, char** yymsg,
    yytype_int16* yyssp, int yytoken)
{
    YYSIZE_T yysize0 = yytnamerr(YY_NULLPTR, yytname[yytoken]);
    YYSIZE_T yysize = yysize0;
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    /* Internationalized format string. */
    const char* yyformat = YY_NULLPTR;
    /* Arguments of yyformat. */
    char const* yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
    /* Number of reported tokens (one for the "unexpected", one per
       "expected"). */
    int yycount = 0;

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
        int yyn = yypact[*yyssp];
        yyarg[yycount++] = yytname[yytoken];
        if (!yypact_value_is_default(yyn))
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
                    && !yytable_value_is_error(yytable[yyx + yyn]))
                {
                    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                        yycount = 1;
                        yysize = yysize0;
                        break;
                    }
                    yyarg[yycount++] = yytname[yyx];
                    {
                        YYSIZE_T yysize1 = yysize + yytnamerr(YY_NULLPTR, yytname[yyx]);
                        if (!(yysize <= yysize1
                            && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                            return 2;
                        yysize = yysize1;
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
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

    {
        YYSIZE_T yysize1 = yysize + yystrlen(yyformat);
        if (!(yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
            return 2;
        yysize = yysize1;
    }

    if (*yymsg_alloc < yysize)
    {
        *yymsg_alloc = 2 * yysize;
        if (!(yysize <= *yymsg_alloc
            && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
            *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
        return 1;
    }

    /* Avoid sprintf, as that infringes on the user's name space.
       Don't have undefined behavior even if the translation
       produced a string with the wrong number of "%s"s.  */
    {
        char* yyp = *yymsg;
        int yyi = 0;
        while ((*yyp = *yyformat) != '\0')
            if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
            {
                yyp += yytnamerr(yyp, yyarg[yyi++]);
                yyformat += 2;
            }
            else
            {
                yyp++;
                yyformat++;
            }
    }
    return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct(const char* yymsg, int yytype, YYSTYPE* yyvaluep)
{
    YYUSE(yyvaluep);
    if (!yymsg)
        yymsg = "Deleting";
    YY_SYMBOL_PRINT(yymsg, yytype, yyvaluep, yylocationp);

    YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
        YYUSE(yytype);
    YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse(void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

       /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16* yyss;
    yytype_int16* yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE* yyvs;
    YYSTYPE* yyvsp;

    YYSIZE_T yystacksize;

    int yyn;
    int yyresult;
    /* Lookahead token as an internal (translated) token number.  */
    int yytoken = 0;
    /* The variables used to return semantic value and location from the
       action routines.  */
    YYSTYPE yyval;

#if YYERROR_VERBOSE
    /* Buffer for error messages, and its allocated size.  */
    char yymsgbuf[128];
    char* yymsg = yymsgbuf;
    YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

    /* The number of symbols on the RHS of the reduced rule.
       Keep to zero when no symbol should be popped.  */
    int yylen = 0;

    yyssp = yyss = yyssa;
    yyvsp = yyvs = yyvsa;
    yystacksize = YYINITDEPTH;

    YYDPRINTF((stderr, "Starting parse\n"));

    yystate = 0;
    yyerrstatus = 0;
    yynerrs = 0;
    yychar = YYEMPTY; /* Cause a token to be read.  */
    goto yysetstate;

    /*------------------------------------------------------------.
    | yynewstate -- Push a new state, which is found in yystate.  |
    `------------------------------------------------------------*/
yynewstate:
    /* In all cases, when you get here, the value and location stacks
       have just been pushed.  So pushing a state here evens the stacks.  */
    yyssp++;

yysetstate:
    *yyssp = yystate;

    if (yyss + yystacksize - 1 <= yyssp)
    {
        /* Get the current used size of the three stacks, in elements.  */
        YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
        {
            /* Give user a chance to reallocate the stack.  Use copies of
               these so that the &'s don't force the real ones into
               memory.  */
            YYSTYPE* yyvs1 = yyvs;
            yytype_int16* yyss1 = yyss;

            /* Each stack pointer address is followed by the size of the
               data in use in that stack, in bytes.  This used to be a
               conditional around just the two extra args, but that might
               be undefined if yyoverflow is a macro.  */
            yyoverflow(YY_("memory exhausted"),
                &yyss1, yysize * sizeof(*yyssp),
                &yyvs1, yysize * sizeof(*yyvsp),
                &yystacksize);

            yyss = yyss1;
            yyvs = yyvs1;
        }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
        goto yyexhaustedlab;
# else
        /* Extend the stack our own way.  */
        if (YYMAXDEPTH <= yystacksize)
            goto yyexhaustedlab;
        yystacksize *= 2;
        if (YYMAXDEPTH < yystacksize)
            yystacksize = YYMAXDEPTH;

        {
            yytype_int16* yyss1 = yyss;
            union yyalloc* yyptr =
                (union yyalloc*)YYSTACK_ALLOC(YYSTACK_BYTES(yystacksize));
            if (!yyptr)
                goto yyexhaustedlab;
            YYSTACK_RELOCATE(yyss_alloc, yyss);
            YYSTACK_RELOCATE(yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
            if (yyss1 != yyssa)
                YYSTACK_FREE(yyss1);
        }
# endif
#endif /* no yyoverflow */

        yyssp = yyss + yysize - 1;
        yyvsp = yyvs + yysize - 1;

        YYDPRINTF((stderr, "Stack size increased to %lu\n",
            (unsigned long int) yystacksize));

        if (yyss + yystacksize - 1 <= yyssp)
            YYABORT;
    }

    YYDPRINTF((stderr, "Entering state %d\n", yystate));

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
    if (yypact_value_is_default(yyn))
        goto yydefault;

    /* Not known => get a lookahead token if don't already have one.  */

    /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
    if (yychar == YYEMPTY)
    {
        YYDPRINTF((stderr, "Reading a token: "));
        yychar = yylex();
    }

    if (yychar <= YYEOF)
    {
        yychar = yytoken = YYEOF;
        YYDPRINTF((stderr, "Now at end of input.\n"));
    }
    else
    {
        yytoken = YYTRANSLATE(yychar);
        YY_SYMBOL_PRINT("Next token is", yytoken, &yylval, &yylloc);
    }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
        goto yydefault;
    yyn = yytable[yyn];
    if (yyn <= 0)
    {
        if (yytable_value_is_error(yyn))
            goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
    }

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus)
        yyerrstatus--;

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the shifted token.  */
    yychar = YYEMPTY;

    yystate = yyn;
    YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
        * ++yyvsp = yylval;
    YY_IGNORE_MAYBE_UNINITIALIZED_END

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
    | yyreduce -- Do a reduction.  |
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
    yyval = yyvsp[1 - yylen];


    YY_REDUCE_PRINT(yyn);
    switch (yyn)
    {
    case 2:
#line 63 "parser.y" /* yacc.c:1646  */
    {
        CompUnit = new NCompUnit(*(yyvsp[0].decllist));
        delete (yyvsp[0].decllist);
    }
#line 1388 "parser.cpp" /* yacc.c:1646  */
    break;

    case 3:
#line 70 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[-1].decllist)->push_back((yyvsp[0].funcdecl));
        (yyval.decllist) = (yyvsp[-1].decllist);
    }
#line 1397 "parser.cpp" /* yacc.c:1646  */
    break;

    case 4:
#line 75 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[0].decllist)->insert((yyvsp[0].decllist)->begin(), (yyvsp[-1].decllist)->begin(), (yyvsp[-1].decllist)->end());
        (yyval.decllist) = (yyvsp[0].decllist);
    }
#line 1406 "parser.cpp" /* yacc.c:1646  */
    break;

    case 5:
#line 80 "parser.y" /* yacc.c:1646  */
    {
        (yyval.decllist) = new NDeclList();
    }
#line 1414 "parser.cpp" /* yacc.c:1646  */
    break;

    case 8:
#line 90 "parser.y" /* yacc.c:1646  */
    {
        (yyval.decllist) = (yyvsp[-1].decllist);
    }
#line 1422 "parser.cpp" /* yacc.c:1646  */
    break;

    case 9:
#line 96 "parser.y" /* yacc.c:1646  */
    {
        (yyval.vardecllist) = new NVarDeclList();
        (yyvsp[0].vardecl)->setTypeforConst();
        (yyval.vardecllist)->push_back((yyvsp[0].vardecl));
    }
#line 1432 "parser.cpp" /* yacc.c:1646  */
    break;

    case 10:
#line 102 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[0].vardecl)->setTypeforConst();
        (yyvsp[-2].vardecllist)->push_back((yyvsp[0].vardecl));
        (yyval.vardecllist) = (yyvsp[-2].vardecllist);
    }
#line 1442 "parser.cpp" /* yacc.c:1646  */
    break;

    case 11:
#line 110 "parser.y" /* yacc.c:1646  */
    {
        (yyval.vardecl) = new NVarDecl(*(yyvsp[-3].ident), *(yyvsp[-2].explist), (yyvsp[0].exp));
    }
#line 1450 "parser.cpp" /* yacc.c:1646  */
    break;

    case 12:
#line 116 "parser.y" /* yacc.c:1646  */
    {

        (yyvsp[-3].explist)->push_back((yyvsp[-1].exp));
        (yyval.explist) = (yyvsp[-3].explist);
    }
#line 1460 "parser.cpp" /* yacc.c:1646  */
    break;

    case 13:
#line 122 "parser.y" /* yacc.c:1646  */
    {
        (yyval.explist) = new NExpList();
    }
#line 1468 "parser.cpp" /* yacc.c:1646  */
    break;

    case 14:
#line 128 "parser.y" /* yacc.c:1646  */
    {
        (yyval.decllist) = (yyvsp[-1].decllist);
    }
#line 1476 "parser.cpp" /* yacc.c:1646  */
    break;

    case 15:
#line 134 "parser.y" /* yacc.c:1646  */
    {
        (yyval.vardecllist) = new NVarDeclList();
        (yyval.vardecllist)->push_back((yyvsp[0].vardecl));
    }
#line 1485 "parser.cpp" /* yacc.c:1646  */
    break;

    case 16:
#line 139 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[-2].vardecllist)->push_back((yyvsp[0].vardecl));
        (yyval.vardecllist) = (yyvsp[-2].vardecllist);
    }
#line 1494 "parser.cpp" /* yacc.c:1646  */
    break;

    case 17:
#line 146 "parser.y" /* yacc.c:1646  */
    {
        (yyval.vardecl) = new NVarDecl(*(yyvsp[-1].ident), *(yyvsp[0].explist));
    }
#line 1502 "parser.cpp" /* yacc.c:1646  */
    break;

    case 18:
#line 150 "parser.y" /* yacc.c:1646  */
    {
        (yyval.vardecl) = new NVarDecl(*(yyvsp[-3].ident), *(yyvsp[-2].explist), (yyvsp[0].exp));
    }
#line 1510 "parser.cpp" /* yacc.c:1646  */
    break;

    case 20:
#line 157 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NInitListExp(*(yyvsp[-1].explist));
    }
#line 1518 "parser.cpp" /* yacc.c:1646  */
    break;

    case 21:
#line 161 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NInitListExp();
    }
#line 1526 "parser.cpp" /* yacc.c:1646  */
    break;

    case 22:
#line 167 "parser.y" /* yacc.c:1646  */
    {
        (yyval.explist) = new NExpList();
        (yyval.explist)->push_back((yyvsp[0].exp));
    }
#line 1535 "parser.cpp" /* yacc.c:1646  */
    break;

    case 23:
#line 172 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[-2].explist)->push_back((yyvsp[0].exp));
        (yyval.explist) = (yyvsp[-2].explist);
    }
#line 1544 "parser.cpp" /* yacc.c:1646  */
    break;

    case 24:
#line 179 "parser.y" /* yacc.c:1646  */
    {
        (yyval.funcdecl) = new NFuncDecl(*(yyvsp[-5].string), *(yyvsp[-4].ident), *(yyvsp[-2].vardecllist), *(yyvsp[0].stmtlist));
    }
#line 1552 "parser.cpp" /* yacc.c:1646  */
    break;

    case 25:
#line 183 "parser.y" /* yacc.c:1646  */
    {
        (yyval.funcdecl) = new NFuncDecl(*(yyvsp[-4].string), *(yyvsp[-3].ident), *(yyvsp[0].stmtlist));
    }
#line 1560 "parser.cpp" /* yacc.c:1646  */
    break;

    case 26:
#line 187 "parser.y" /* yacc.c:1646  */
    {
        (yyval.funcdecl) = new NFuncDecl(*(yyvsp[-5].string), *(yyvsp[-4].ident), *(yyvsp[-2].vardecllist), *(yyvsp[0].stmtlist));
    }
#line 1568 "parser.cpp" /* yacc.c:1646  */
    break;

    case 27:
#line 191 "parser.y" /* yacc.c:1646  */
    {
        (yyval.funcdecl) = new NFuncDecl(*(yyvsp[-4].string), *(yyvsp[-3].ident), *(yyvsp[0].stmtlist));
    }
#line 1576 "parser.cpp" /* yacc.c:1646  */
    break;

    case 28:
#line 197 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[-2].vardecllist)->push_back((yyvsp[0].vardecl));
        (yyval.vardecllist) = (yyvsp[-2].vardecllist);
    }
#line 1585 "parser.cpp" /* yacc.c:1646  */
    break;

    case 29:
#line 202 "parser.y" /* yacc.c:1646  */
    {
        (yyval.vardecllist) = new NVarDeclList();
        (yyval.vardecllist)->push_back((yyvsp[0].vardecl));
    }
#line 1594 "parser.cpp" /* yacc.c:1646  */
    break;

    case 30:
#line 209 "parser.y" /* yacc.c:1646  */
    {
        (yyval.vardecl) = new NVarDecl(*(yyvsp[-1].string), *(yyvsp[0].ident));
    }
#line 1602 "parser.cpp" /* yacc.c:1646  */
    break;

    case 31:
#line 213 "parser.y" /* yacc.c:1646  */
    {
        (yyval.vardecl) = new NVarDecl(*(yyvsp[-4].string), *(yyvsp[-3].ident), *(yyvsp[0].explist));
    }
#line 1610 "parser.cpp" /* yacc.c:1646  */
    break;

    case 32:
#line 219 "parser.y" /* yacc.c:1646  */
    {
        (yyval.stmtlist) = (yyvsp[-1].stmtlist);
    }
#line 1618 "parser.cpp" /* yacc.c:1646  */
    break;

    case 33:
#line 225 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[-1].stmtlist)->push_back((yyvsp[0].stmt));
        (yyval.stmtlist) = (yyvsp[-1].stmtlist);
    }
#line 1627 "parser.cpp" /* yacc.c:1646  */
    break;

    case 34:
#line 229 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtlist) = new NStmtList(); }
#line 1633 "parser.cpp" /* yacc.c:1646  */
    break;

    case 39:
#line 241 "parser.y" /* yacc.c:1646  */
    {
        (yyval.stmt) = new NBlockStmt(*(yyvsp[0].stmtlist));
    }
#line 1641 "parser.cpp" /* yacc.c:1646  */
    break;

    case 40:
#line 246 "parser.y" /* yacc.c:1646  */
    {
        (yyval.stmt) = new NDeclStmt(*(yyvsp[0].decllist));
    }
#line 1649 "parser.cpp" /* yacc.c:1646  */
    break;

    case 41:
#line 250 "parser.y" /* yacc.c:1646  */
    {
        (yyval.stmt) = new NDeclStmt(*(yyvsp[0].decllist));
    }
#line 1657 "parser.cpp" /* yacc.c:1646  */
    break;

    case 42:
#line 256 "parser.y" /* yacc.c:1646  */
    {
        (yyval.stmt) = new NAssignStmt(*(yyvsp[-4].ident), *(yyvsp[-3].explist), *(yyvsp[-1].exp));
    }
#line 1665 "parser.cpp" /* yacc.c:1646  */
    break;

    case 43:
#line 260 "parser.y" /* yacc.c:1646  */
    {
        (yyval.stmt) = new NExpStmt(*(yyvsp[-1].exp));
    }
#line 1673 "parser.cpp" /* yacc.c:1646  */
    break;

    case 44:
#line 264 "parser.y" /* yacc.c:1646  */
    {
        (yyval.stmt) = new NNullStmt();
    }
#line 1681 "parser.cpp" /* yacc.c:1646  */
    break;

    case 46:
#line 269 "parser.y" /* yacc.c:1646  */
    {
        (yyval.stmt) = new NWhileStmt(*(yyvsp[-2].exp), *(yyvsp[0].stmt));
    }
#line 1689 "parser.cpp" /* yacc.c:1646  */
    break;

    case 47:
#line 273 "parser.y" /* yacc.c:1646  */
    {
        (yyval.stmt) = new NBreakStmt();
    }
#line 1697 "parser.cpp" /* yacc.c:1646  */
    break;

    case 48:
#line 277 "parser.y" /* yacc.c:1646  */
    {
        (yyval.stmt) = new NContinueStmt();
    }
#line 1705 "parser.cpp" /* yacc.c:1646  */
    break;

    case 49:
#line 281 "parser.y" /* yacc.c:1646  */
    {
        (yyval.stmt) = new NReturnStmt();
    }
#line 1713 "parser.cpp" /* yacc.c:1646  */
    break;

    case 50:
#line 285 "parser.y" /* yacc.c:1646  */
    {
        (yyval.stmt) = new NReturnStmt((yyvsp[-1].exp));
    }
#line 1721 "parser.cpp" /* yacc.c:1646  */
    break;

    case 51:
#line 291 "parser.y" /* yacc.c:1646  */
    {
        (yyval.stmt) = new NIfStmt(*(yyvsp[-2].exp), *(yyvsp[0].stmt));
    }
#line 1729 "parser.cpp" /* yacc.c:1646  */
    break;

    case 52:
#line 295 "parser.y" /* yacc.c:1646  */
    {
        (yyval.stmt) = new NIfStmt(*(yyvsp[-4].exp), *(yyvsp[-2].stmt), (yyvsp[0].stmt));
    }
#line 1737 "parser.cpp" /* yacc.c:1646  */
    break;

    case 53:
#line 301 "parser.y" /* yacc.c:1646  */
    {
        (yyval.explist) = new NExpList();
        (yyval.explist)->push_back((yyvsp[0].exp));
    }
#line 1746 "parser.cpp" /* yacc.c:1646  */
    break;

    case 54:
#line 306 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[-2].explist)->push_back((yyvsp[0].exp));
        (yyval.explist) = (yyvsp[-2].explist);
    }
#line 1755 "parser.cpp" /* yacc.c:1646  */
    break;

    case 55:
#line 313 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NBinaryExp(*(yyvsp[-2].exp), (yyvsp[-1].token), *(yyvsp[0].exp));
    }
#line 1763 "parser.cpp" /* yacc.c:1646  */
    break;

    case 56:
#line 317 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NBinaryExp(*(yyvsp[-2].exp), (yyvsp[-1].token), *(yyvsp[0].exp));
    }
#line 1771 "parser.cpp" /* yacc.c:1646  */
    break;

    case 57:
#line 321 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NBinaryExp(*(yyvsp[-2].exp), (yyvsp[-1].token), *(yyvsp[0].exp));
    }
#line 1779 "parser.cpp" /* yacc.c:1646  */
    break;

    case 58:
#line 325 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NBinaryExp(*(yyvsp[-2].exp), (yyvsp[-1].token), *(yyvsp[0].exp));
    }
#line 1787 "parser.cpp" /* yacc.c:1646  */
    break;

    case 59:
#line 329 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NBinaryExp(*(yyvsp[-2].exp), (yyvsp[-1].token), *(yyvsp[0].exp));
    }
#line 1795 "parser.cpp" /* yacc.c:1646  */
    break;

    case 60:
#line 333 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NBinaryExp(*(yyvsp[-2].exp), (yyvsp[-1].token), *(yyvsp[0].exp));
    }
#line 1803 "parser.cpp" /* yacc.c:1646  */
    break;

    case 61:
#line 337 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NBinaryExp(*(yyvsp[-2].exp), (yyvsp[-1].token), *(yyvsp[0].exp));
    }
#line 1811 "parser.cpp" /* yacc.c:1646  */
    break;

    case 62:
#line 341 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NBinaryExp(*(yyvsp[-2].exp), (yyvsp[-1].token), *(yyvsp[0].exp));
    }
#line 1819 "parser.cpp" /* yacc.c:1646  */
    break;

    case 64:
#line 348 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NBinaryExp(*(yyvsp[-2].exp), (yyvsp[-1].token), *(yyvsp[0].exp));
    }
#line 1827 "parser.cpp" /* yacc.c:1646  */
    break;

    case 65:
#line 352 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NBinaryExp(*(yyvsp[-2].exp), (yyvsp[-1].token), *(yyvsp[0].exp));
    }
#line 1835 "parser.cpp" /* yacc.c:1646  */
    break;

    case 66:
#line 356 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NBinaryExp(*(yyvsp[-2].exp), (yyvsp[-1].token), *(yyvsp[0].exp));
    }
#line 1843 "parser.cpp" /* yacc.c:1646  */
    break;

    case 67:
#line 360 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NBinaryExp(*(yyvsp[-2].exp), (yyvsp[-1].token), *(yyvsp[0].exp));
    }
#line 1851 "parser.cpp" /* yacc.c:1646  */
    break;

    case 68:
#line 364 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NBinaryExp(*(yyvsp[-2].exp), (yyvsp[-1].token), *(yyvsp[0].exp));
    }
#line 1859 "parser.cpp" /* yacc.c:1646  */
    break;

    case 69:
#line 368 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NUnaryExp((yyvsp[-1].token), *(yyvsp[0].exp));
    }
#line 1867 "parser.cpp" /* yacc.c:1646  */
    break;

    case 70:
#line 372 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NUnaryExp((yyvsp[-1].token), *(yyvsp[0].exp));
    }
#line 1875 "parser.cpp" /* yacc.c:1646  */
    break;

    case 71:
#line 376 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NUnaryExp((yyvsp[-1].token), *(yyvsp[0].exp));
    }
#line 1883 "parser.cpp" /* yacc.c:1646  */
    break;

    case 72:
#line 380 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = (yyvsp[-1].exp);
    }
#line 1891 "parser.cpp" /* yacc.c:1646  */
    break;

    case 73:
#line 384 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NIdentifierExp(*(yyvsp[-1].ident), *(yyvsp[0].explist));
    }
#line 1899 "parser.cpp" /* yacc.c:1646  */
    break;

    case 75:
#line 389 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NCallExp(*(yyvsp[-2].ident));
    }
#line 1907 "parser.cpp" /* yacc.c:1646  */
    break;

    case 76:
#line 393 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NCallExp(*(yyvsp[-3].ident), *(yyvsp[-1].explist));
    }
#line 1915 "parser.cpp" /* yacc.c:1646  */
    break;

    case 77:
#line 399 "parser.y" /* yacc.c:1646  */
    {
        (yyval.ident) = new NIdentifier(*(yyvsp[0].string));
    }
#line 1923 "parser.cpp" /* yacc.c:1646  */
    break;

    case 78:
#line 405 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exp) = new NInteger((yyvsp[0].token));
    }
#line 1931 "parser.cpp" /* yacc.c:1646  */
    break;


#line 1935 "parser.cpp" /* yacc.c:1646  */
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
    YY_SYMBOL_PRINT("-> $$ =", yyr1[yyn], &yyval, &yyloc);

    YYPOPSTACK(yylen);
    yylen = 0;
    YY_STACK_PRINT(yyss, yyssp);

    *++yyvsp = yyval;

    /* Now 'shift' the result of the reduction.  Determine what state
       that goes to, based on the state we popped back to and the rule
       number reduced by.  */

    yyn = yyr1[yyn];

    yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
    if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
        yystate = yytable[yystate];
    else
        yystate = yydefgoto[yyn - YYNTOKENS];

    goto yynewstate;


    /*--------------------------------------.
    | yyerrlab -- here on detecting error.  |
    `--------------------------------------*/
yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE(yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus)
    {
        ++yynerrs;
#if ! YYERROR_VERBOSE
        yyerror(YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
        {
            char const* yymsgp = YY_("syntax error");
            int yysyntax_error_status;
            yysyntax_error_status = YYSYNTAX_ERROR;
            if (yysyntax_error_status == 0)
                yymsgp = yymsg;
            else if (yysyntax_error_status == 1)
            {
                if (yymsg != yymsgbuf)
                    YYSTACK_FREE(yymsg);
                yymsg = (char*)YYSTACK_ALLOC(yymsg_alloc);
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
            yyerror(yymsgp);
            if (yysyntax_error_status == 2)
                goto yyexhaustedlab;
        }
# undef YYSYNTAX_ERROR
#endif
    }



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
            yydestruct("Error: discarding",
                yytoken, &yylval);
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (/*CONSTCOND*/ 0)
        goto yyerrorlab;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    YYPOPSTACK(yylen);
    yylen = 0;
    YY_STACK_PRINT(yyss, yyssp);
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
        if (!yypact_value_is_default(yyn))
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


        yydestruct("Error: popping",
            yystos[yystate], yyvsp);
        YYPOPSTACK(1);
        yystate = *yyssp;
        YY_STACK_PRINT(yyss, yyssp);
    }

    YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
        * ++yyvsp = yylval;
    YY_IGNORE_MAYBE_UNINITIALIZED_END


        /* Shift the error token.  */
        YY_SYMBOL_PRINT("Shifting", yystos[yyn], yyvsp, yylsp);

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
    yyerror(YY_("memory exhausted"));
    yyresult = 2;
    /* Fall through.  */
#endif

yyreturn:
    if (yychar != YYEMPTY)
    {
        /* Make sure we have latest lookahead translation.  See comments at
           user semantic actions for why this is necessary.  */
        yytoken = YYTRANSLATE(yychar);
        yydestruct("Cleanup: discarding lookahead",
            yytoken, &yylval);
    }
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    YYPOPSTACK(yylen);
    YY_STACK_PRINT(yyss, yyssp);
    while (yyssp != yyss)
    {
        yydestruct("Cleanup: popping",
            yystos[*yyssp], yyvsp);
        YYPOPSTACK(1);
    }
#ifndef yyoverflow
    if (yyss != yyssa)
        YYSTACK_FREE(yyss);
#endif
#if YYERROR_VERBOSE
    if (yymsg != yymsgbuf)
        YYSTACK_FREE(yymsg);
#endif
    return yyresult;
}

/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         javalette_parse
#define yylex           javalette_lex
#define yyerror         javalette_error
#define yydebug         javalette_debug
#define yynerrs         javalette_nerrs

/* First part of user prologue.  */
#line 20 "Javalette.y"

/* Begin C preamble code */

#include <algorithm> /* for std::reverse */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Absyn.H"

#define YYMAXDEPTH 10000000

/* The type yyscan_t is defined by flex, but we need it in the parser already. */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE javalette__scan_string(const char *str, yyscan_t scanner);
extern void javalette__delete_buffer(YY_BUFFER_STATE buf, yyscan_t scanner);

extern void javalette_lex_destroy(yyscan_t scanner);
extern char* javalette_get_text(yyscan_t scanner);

extern yyscan_t javalette__initialize_lexer(FILE * inp);

/* End C preamble code */

#line 105 "Parser.C"

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

#include "Bison.H"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL__ERROR_ = 3,                    /* _ERROR_  */
  YYSYMBOL__LPAREN = 4,                    /* _LPAREN  */
  YYSYMBOL__RPAREN = 5,                    /* _RPAREN  */
  YYSYMBOL__STAR = 6,                      /* _STAR  */
  YYSYMBOL__COMMA = 7,                     /* _COMMA  */
  YYSYMBOL__SEMI = 8,                      /* _SEMI  */
  YYSYMBOL__EQ = 9,                        /* _EQ  */
  YYSYMBOL__EMPTYBRACK = 10,               /* _EMPTYBRACK  */
  YYSYMBOL__KW_boolean = 11,               /* _KW_boolean  */
  YYSYMBOL__KW_class = 12,                 /* _KW_class  */
  YYSYMBOL__KW_double = 13,                /* _KW_double  */
  YYSYMBOL__KW_enum = 14,                  /* _KW_enum  */
  YYSYMBOL__KW_extends = 15,               /* _KW_extends  */
  YYSYMBOL__KW_false = 16,                 /* _KW_false  */
  YYSYMBOL__KW_int = 17,                   /* _KW_int  */
  YYSYMBOL__KW_struct = 18,                /* _KW_struct  */
  YYSYMBOL__KW_true = 19,                  /* _KW_true  */
  YYSYMBOL__KW_typedef = 20,               /* _KW_typedef  */
  YYSYMBOL__KW_void = 21,                  /* _KW_void  */
  YYSYMBOL__LBRACE = 22,                   /* _LBRACE  */
  YYSYMBOL__DBAR = 23,                     /* _DBAR  */
  YYSYMBOL__RBRACE = 24,                   /* _RBRACE  */
  YYSYMBOL__STRING_ = 25,                  /* _STRING_  */
  YYSYMBOL__INTEGER_ = 26,                 /* _INTEGER_  */
  YYSYMBOL__DOUBLE_ = 27,                  /* _DOUBLE_  */
  YYSYMBOL__IDENT_ = 28,                   /* _IDENT_  */
  YYSYMBOL_YYACCEPT = 29,                  /* $accept  */
  YYSYMBOL_Prog = 30,                      /* Prog  */
  YYSYMBOL_TopDef = 31,                    /* TopDef  */
  YYSYMBOL_FnDef = 32,                     /* FnDef  */
  YYSYMBOL_EVal = 33,                      /* EVal  */
  YYSYMBOL_ListEVal = 34,                  /* ListEVal  */
  YYSYMBOL_Arg = 35,                       /* Arg  */
  YYSYMBOL_ListArg = 36,                   /* ListArg  */
  YYSYMBOL_ListTopDef = 37,                /* ListTopDef  */
  YYSYMBOL_Type = 38,                      /* Type  */
  YYSYMBOL_BracketsOpt = 39,               /* BracketsOpt  */
  YYSYMBOL_SBlk = 40,                      /* SBlk  */
  YYSYMBOL_CBlk = 41,                      /* CBlk  */
  YYSYMBOL_Memdef = 42,                    /* Memdef  */
  YYSYMBOL_ListMemdef = 43,                /* ListMemdef  */
  YYSYMBOL_CMemdef = 44,                   /* CMemdef  */
  YYSYMBOL_ListCMemdef = 45,               /* ListCMemdef  */
  YYSYMBOL_Blk = 46,                       /* Blk  */
  YYSYMBOL_ListStmt = 47,                  /* ListStmt  */
  YYSYMBOL_Stmt = 48,                      /* Stmt  */
  YYSYMBOL_Item = 49,                      /* Item  */
  YYSYMBOL_ListItem = 50,                  /* ListItem  */
  YYSYMBOL_Expr7 = 51,                     /* Expr7  */
  YYSYMBOL_Expr = 52,                      /* Expr  */
  YYSYMBOL_Expr1 = 53,                     /* Expr1  */
  YYSYMBOL_Expr2 = 54,                     /* Expr2  */
  YYSYMBOL_Expr3 = 55,                     /* Expr3  */
  YYSYMBOL_Expr4 = 56,                     /* Expr4  */
  YYSYMBOL_Expr5 = 57,                     /* Expr5  */
  YYSYMBOL_Expr6 = 58                      /* Expr6  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 82 "Javalette.y"

void yyerror(YYLTYPE *loc, yyscan_t scanner, YYSTYPE *result, const char *msg)
{
  fprintf(stderr, "error: %d,%d: %s at %s\n",
    loc->first_line, loc->first_column, msg, javalette_get_text(scanner));
}

int yyparse(yyscan_t scanner, YYSTYPE *result);

extern int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, yyscan_t scanner);

#line 209 "Parser.C"


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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  19
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   109

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  103

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   283


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   158,   158,   160,   161,   162,   163,   164,   165,   166,
     168,   170,   172,   173,   174,   176,   178,   179,   180,   182,
     183,   185,   186,   187,   188,   189,   190,   192,   201,   203,
     205,   207,   208,   210,   211,   213,   214,   216,   218,   219,
     221,   222,   223,   225,   226,   228,   229,   231,   232,   233,
     234,   235,   236,   237,   239,   240,   242,   244,   246,   248,
     250,   252
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "_ERROR_", "_LPAREN",
  "_RPAREN", "_STAR", "_COMMA", "_SEMI", "_EQ", "_EMPTYBRACK",
  "_KW_boolean", "_KW_class", "_KW_double", "_KW_enum", "_KW_extends",
  "_KW_false", "_KW_int", "_KW_struct", "_KW_true", "_KW_typedef",
  "_KW_void", "_LBRACE", "_DBAR", "_RBRACE", "_STRING_", "_INTEGER_",
  "_DOUBLE_", "_IDENT_", "$accept", "Prog", "TopDef", "FnDef", "EVal",
  "ListEVal", "Arg", "ListArg", "ListTopDef", "Type", "BracketsOpt",
  "SBlk", "CBlk", "Memdef", "ListMemdef", "CMemdef", "ListCMemdef", "Blk",
  "ListStmt", "Stmt", "Item", "ListItem", "Expr7", "Expr", "Expr1",
  "Expr2", "Expr3", "Expr4", "Expr5", "Expr6", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283
};
#endif

#define YYPACT_NINF (-67)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      38,   -67,   -23,   -67,   -21,   -67,   -20,    -8,   -67,   -67,
      18,    38,   -67,   -67,    -7,    21,    13,    16,    17,   -67,
     -67,   -67,    35,   -67,    19,   -67,   -67,    25,   -67,    46,
      -2,    69,    24,    50,   -67,    53,    33,    51,   -67,    37,
      63,    66,    65,    -1,   -67,   -67,   -67,     1,   -67,   -67,
      25,    68,   -67,     2,   -67,    73,    49,    69,    61,   -67,
      11,   -67,   -67,    76,   -67,    77,   -67,   -67,   -67,   -67,
     -67,    20,   -67,   -67,     4,   -67,   -67,    78,    81,    83,
      -3,    64,   -67,    -3,   -67,   -67,   -67,   -67,   -67,   -67,
      70,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,    84,
      -3,   -67,   -67
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    23,     0,    22,     0,    21,     0,     0,    24,    25,
       0,    19,     9,     2,     0,     0,     0,     0,     0,     1,
      20,    27,     0,    26,     0,    35,     7,    12,    31,     0,
       0,    16,     0,     0,    11,    13,     0,     0,     3,     0,
       0,    17,     0,     0,     8,    29,    34,     0,    33,    36,
      12,     0,    28,     0,    32,     0,     0,    16,     0,    15,
       0,    14,     6,     0,     4,     0,    18,    38,    10,    30,
       5,     0,    40,    37,     0,    41,    39,    43,    45,     0,
       0,     0,    42,     0,    50,    49,    51,    47,    48,    52,
      61,    44,    55,    56,    57,    58,    59,    60,    46,     0,
       0,    53,    54
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -67,   -67,   -67,    62,   -67,    44,   -67,    39,    87,   -31,
     -67,    71,    67,    72,   -67,   -67,   -67,    29,   -67,   -67,
     -67,    22,   -67,   -66,   -67,   -67,   -67,   -67,   -67,   -67
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    10,    11,    12,    35,    36,    41,    42,    13,    14,
      23,    29,    26,    48,    37,    49,    33,    68,    71,    76,
      78,    79,    90,    91,    92,    93,    94,    95,    96,    97
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      43,    83,    47,    21,    39,    15,    53,    16,    17,    21,
      18,    21,    21,    84,    21,    31,    85,    99,    19,    69,
      28,    22,    86,    87,    88,    89,    43,    59,    72,    60,
      63,     1,    77,     3,   102,    27,    24,     5,    28,    31,
      74,     8,    67,    25,    73,    30,    25,    32,     9,     1,
       2,     3,     4,    34,    38,     5,     6,    51,     7,     8,
      50,     1,     1,     3,     3,    55,     9,     5,     5,    56,
      58,     8,     8,    57,    45,    52,    62,    65,     9,     9,
       1,    64,     3,    67,    69,    70,     5,    80,    81,   101,
       8,    82,    77,   100,    61,    46,    66,     9,    20,    44,
      75,    40,     0,    98,     0,     0,     0,     0,     0,    54
};

static const yytype_int8 yycheck[] =
{
      31,     4,    33,    10,     6,    28,    37,    28,    28,    10,
      18,    10,    10,    16,    10,     4,    19,    83,     0,     8,
      22,    28,    25,    26,    27,    28,    57,    28,     8,    28,
      28,    11,    28,    13,   100,    22,    15,    17,    22,     4,
      71,    21,    22,    22,    24,    28,    22,    28,    28,    11,
      12,    13,    14,    28,     8,    17,    18,    24,    20,    21,
       7,    11,    11,    13,    13,    28,    28,    17,    17,     6,
       5,    21,    21,     7,    24,    24,     8,    28,    28,    28,
      11,     8,    13,    22,     8,     8,    17,     9,     7,     5,
      21,     8,    28,    23,    50,    33,    57,    28,    11,    32,
      71,    30,    -1,    81,    -1,    -1,    -1,    -1,    -1,    37
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    11,    12,    13,    14,    17,    18,    20,    21,    28,
      30,    31,    32,    37,    38,    28,    28,    28,    18,     0,
      37,    10,    28,    39,    15,    22,    41,    22,    22,    40,
      28,     4,    28,    45,    28,    33,    34,    43,     8,     6,
      40,    35,    36,    38,    41,    24,    32,    38,    42,    44,
       7,    24,    24,    38,    42,    28,     6,     7,     5,    28,
      28,    34,     8,    28,     8,    28,    36,    22,    46,     8,
       8,    47,     8,    24,    38,    46,    48,    28,    49,    50,
       9,     7,     8,     4,    16,    19,    25,    26,    27,    28,
      51,    52,    53,    54,    55,    56,    57,    58,    50,    52,
      23,     5,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    29,    30,    31,    31,    31,    31,    31,    31,    31,
      32,    33,    34,    34,    34,    35,    36,    36,    36,    37,
      37,    38,    38,    38,    38,    38,    38,    39,    40,    41,
      42,    43,    43,    44,    44,    45,    45,    46,    47,    47,
      48,    48,    48,    49,    49,    50,    50,    51,    51,    51,
      51,    51,    51,    51,    52,    52,    53,    54,    55,    56,
      57,    58
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     4,     6,     7,     6,     3,     5,     1,
       6,     1,     0,     1,     3,     2,     0,     1,     3,     1,
       2,     1,     1,     1,     1,     1,     2,     1,     3,     3,
       3,     0,     2,     1,     1,     0,     2,     3,     0,     2,
       1,     1,     3,     1,     3,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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
        yyerror (&yylloc, scanner, result, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

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

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, scanner, result); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, YYSTYPE *result)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (result);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, YYSTYPE *result)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, scanner, result);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, yyscan_t scanner, YYSTYPE *result)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), scanner, result);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner, result); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t scanner, YYSTYPE *result)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (result);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner, YYSTYPE *result)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

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
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  case 2: /* Prog: ListTopDef  */
#line 158 "Javalette.y"
                  { std::reverse((yyvsp[0].listtopdef_)->begin(),(yyvsp[0].listtopdef_)->end()) ;(yyval.prog_) = new Program((yyvsp[0].listtopdef_)); result->prog_ = (yyval.prog_); }
#line 1352 "Parser.C"
    break;

  case 3: /* TopDef: _KW_struct _IDENT_ SBlk _SEMI  */
#line 160 "Javalette.y"
                                       { (yyval.topdef_) = new Struct((yyvsp[-2]._string), (yyvsp[-1].sblk_)); }
#line 1358 "Parser.C"
    break;

  case 4: /* TopDef: _KW_typedef _KW_struct _IDENT_ _STAR _IDENT_ _SEMI  */
#line 161 "Javalette.y"
                                                       { (yyval.topdef_) = new TypeDef((yyvsp[-3]._string), (yyvsp[-1]._string)); }
#line 1364 "Parser.C"
    break;

  case 5: /* TopDef: _KW_typedef _KW_struct _IDENT_ SBlk _STAR _IDENT_ _SEMI  */
#line 162 "Javalette.y"
                                                            { (yyval.topdef_) = new TypeDefWS((yyvsp[-4]._string), (yyvsp[-3].sblk_), (yyvsp[-1]._string)); }
#line 1370 "Parser.C"
    break;

  case 6: /* TopDef: _KW_enum _IDENT_ _LBRACE ListEVal _RBRACE _SEMI  */
#line 163 "Javalette.y"
                                                    { std::reverse((yyvsp[-2].listeval_)->begin(),(yyvsp[-2].listeval_)->end()) ;(yyval.topdef_) = new Enum((yyvsp[-4]._string), (yyvsp[-2].listeval_)); }
#line 1376 "Parser.C"
    break;

  case 7: /* TopDef: _KW_class _IDENT_ CBlk  */
#line 164 "Javalette.y"
                           { (yyval.topdef_) = new Class((yyvsp[-1]._string), (yyvsp[0].cblk_)); }
#line 1382 "Parser.C"
    break;

  case 8: /* TopDef: _KW_class _IDENT_ _KW_extends _IDENT_ CBlk  */
#line 165 "Javalette.y"
                                               { (yyval.topdef_) = new ClassWE((yyvsp[-3]._string), (yyvsp[-1]._string), (yyvsp[0].cblk_)); }
#line 1388 "Parser.C"
    break;

  case 9: /* TopDef: FnDef  */
#line 166 "Javalette.y"
          { (yyval.topdef_) = new GFuncDef((yyvsp[0].fndef_)); }
#line 1394 "Parser.C"
    break;

  case 10: /* FnDef: Type _IDENT_ _LPAREN ListArg _RPAREN Blk  */
#line 168 "Javalette.y"
                                                 { std::reverse((yyvsp[-2].listarg_)->begin(),(yyvsp[-2].listarg_)->end()) ;(yyval.fndef_) = new FuncDef((yyvsp[-5].type_), (yyvsp[-4]._string), (yyvsp[-2].listarg_), (yyvsp[0].blk_)); }
#line 1400 "Parser.C"
    break;

  case 11: /* EVal: _IDENT_  */
#line 170 "Javalette.y"
               { (yyval.eval_) = new EnumValue((yyvsp[0]._string)); }
#line 1406 "Parser.C"
    break;

  case 12: /* ListEVal: %empty  */
#line 172 "Javalette.y"
                       { (yyval.listeval_) = new ListEVal(); }
#line 1412 "Parser.C"
    break;

  case 13: /* ListEVal: EVal  */
#line 173 "Javalette.y"
         { (yyval.listeval_) = new ListEVal(); (yyval.listeval_)->push_back((yyvsp[0].eval_)); }
#line 1418 "Parser.C"
    break;

  case 14: /* ListEVal: EVal _COMMA ListEVal  */
#line 174 "Javalette.y"
                         { (yyvsp[0].listeval_)->push_back((yyvsp[-2].eval_)); (yyval.listeval_) = (yyvsp[0].listeval_); }
#line 1424 "Parser.C"
    break;

  case 15: /* Arg: Type _IDENT_  */
#line 176 "Javalette.y"
                   { (yyval.arg_) = new Argument((yyvsp[-1].type_), (yyvsp[0]._string)); }
#line 1430 "Parser.C"
    break;

  case 16: /* ListArg: %empty  */
#line 178 "Javalette.y"
                      { (yyval.listarg_) = new ListArg(); }
#line 1436 "Parser.C"
    break;

  case 17: /* ListArg: Arg  */
#line 179 "Javalette.y"
        { (yyval.listarg_) = new ListArg(); (yyval.listarg_)->push_back((yyvsp[0].arg_)); }
#line 1442 "Parser.C"
    break;

  case 18: /* ListArg: Arg _COMMA ListArg  */
#line 180 "Javalette.y"
                       { (yyvsp[0].listarg_)->push_back((yyvsp[-2].arg_)); (yyval.listarg_) = (yyvsp[0].listarg_); }
#line 1448 "Parser.C"
    break;

  case 19: /* ListTopDef: TopDef  */
#line 182 "Javalette.y"
                    { (yyval.listtopdef_) = new ListTopDef(); (yyval.listtopdef_)->push_back((yyvsp[0].topdef_)); }
#line 1454 "Parser.C"
    break;

  case 20: /* ListTopDef: TopDef ListTopDef  */
#line 183 "Javalette.y"
                      { (yyvsp[0].listtopdef_)->push_back((yyvsp[-1].topdef_)); (yyval.listtopdef_) = (yyvsp[0].listtopdef_); }
#line 1460 "Parser.C"
    break;

  case 21: /* Type: _KW_int  */
#line 185 "Javalette.y"
               { (yyval.type_) = new Int(); }
#line 1466 "Parser.C"
    break;

  case 22: /* Type: _KW_double  */
#line 186 "Javalette.y"
               { (yyval.type_) = new Doub(); }
#line 1472 "Parser.C"
    break;

  case 23: /* Type: _KW_boolean  */
#line 187 "Javalette.y"
                { (yyval.type_) = new Bool(); }
#line 1478 "Parser.C"
    break;

  case 24: /* Type: _KW_void  */
#line 188 "Javalette.y"
             { (yyval.type_) = new Void(); }
#line 1484 "Parser.C"
    break;

  case 25: /* Type: _IDENT_  */
#line 189 "Javalette.y"
            { (yyval.type_) = new ObjT((yyvsp[0]._string)); }
#line 1490 "Parser.C"
    break;

  case 26: /* Type: Type BracketsOpt  */
#line 190 "Javalette.y"
                     { (yyval.type_) = new Array((yyvsp[-1].type_), (yyvsp[0].bracketsopt_)); }
#line 1496 "Parser.C"
    break;

  case 27: /* BracketsOpt: _EMPTYBRACK  */
#line 192 "Javalette.y"
                          { (yyval.bracketsopt_) = new BracketsEmpty(); }
#line 1502 "Parser.C"
    break;

  case 28: /* SBlk: _LBRACE ListMemdef _RBRACE  */
#line 201 "Javalette.y"
                                  { (yyval.sblk_) = new SBlock((yyvsp[-1].listmemdef_)); }
#line 1508 "Parser.C"
    break;

  case 29: /* CBlk: _LBRACE ListCMemdef _RBRACE  */
#line 203 "Javalette.y"
                                   { (yyval.cblk_) = new CBlock((yyvsp[-1].listcmemdef_)); }
#line 1514 "Parser.C"
    break;

  case 30: /* Memdef: Type _IDENT_ _SEMI  */
#line 205 "Javalette.y"
                            { (yyval.memdef_) = new MemberDef((yyvsp[-2].type_), (yyvsp[-1]._string)); }
#line 1520 "Parser.C"
    break;

  case 31: /* ListMemdef: %empty  */
#line 207 "Javalette.y"
                         { (yyval.listmemdef_) = new ListMemdef(); }
#line 1526 "Parser.C"
    break;

  case 32: /* ListMemdef: ListMemdef Memdef  */
#line 208 "Javalette.y"
                      { (yyvsp[-1].listmemdef_)->push_back((yyvsp[0].memdef_)); (yyval.listmemdef_) = (yyvsp[-1].listmemdef_); }
#line 1532 "Parser.C"
    break;

  case 33: /* CMemdef: Memdef  */
#line 210 "Javalette.y"
                 { (yyval.cmemdef_) = new CVarDef((yyvsp[0].memdef_)); }
#line 1538 "Parser.C"
    break;

  case 34: /* CMemdef: FnDef  */
#line 211 "Javalette.y"
          { (yyval.cmemdef_) = new CFuncDef((yyvsp[0].fndef_)); }
#line 1544 "Parser.C"
    break;

  case 35: /* ListCMemdef: %empty  */
#line 213 "Javalette.y"
                          { (yyval.listcmemdef_) = new ListCMemdef(); }
#line 1550 "Parser.C"
    break;

  case 36: /* ListCMemdef: ListCMemdef CMemdef  */
#line 214 "Javalette.y"
                        { (yyvsp[-1].listcmemdef_)->push_back((yyvsp[0].cmemdef_)); (yyval.listcmemdef_) = (yyvsp[-1].listcmemdef_); }
#line 1556 "Parser.C"
    break;

  case 37: /* Blk: _LBRACE ListStmt _RBRACE  */
#line 216 "Javalette.y"
                               { (yyval.blk_) = new Block((yyvsp[-1].liststmt_)); }
#line 1562 "Parser.C"
    break;

  case 38: /* ListStmt: %empty  */
#line 218 "Javalette.y"
                       { (yyval.liststmt_) = new ListStmt(); }
#line 1568 "Parser.C"
    break;

  case 39: /* ListStmt: ListStmt Stmt  */
#line 219 "Javalette.y"
                  { (yyvsp[-1].liststmt_)->push_back((yyvsp[0].stmt_)); (yyval.liststmt_) = (yyvsp[-1].liststmt_); }
#line 1574 "Parser.C"
    break;

  case 40: /* Stmt: _SEMI  */
#line 221 "Javalette.y"
             { (yyval.stmt_) = new Empty(); }
#line 1580 "Parser.C"
    break;

  case 41: /* Stmt: Blk  */
#line 222 "Javalette.y"
        { (yyval.stmt_) = new BStmt((yyvsp[0].blk_)); }
#line 1586 "Parser.C"
    break;

  case 42: /* Stmt: Type ListItem _SEMI  */
#line 223 "Javalette.y"
                        { std::reverse((yyvsp[-1].listitem_)->begin(),(yyvsp[-1].listitem_)->end()) ;(yyval.stmt_) = new Decl((yyvsp[-2].type_), (yyvsp[-1].listitem_)); }
#line 1592 "Parser.C"
    break;

  case 43: /* Item: _IDENT_  */
#line 225 "Javalette.y"
               { (yyval.item_) = new NoInit((yyvsp[0]._string)); }
#line 1598 "Parser.C"
    break;

  case 44: /* Item: _IDENT_ _EQ Expr  */
#line 226 "Javalette.y"
                     { (yyval.item_) = new Init((yyvsp[-2]._string), (yyvsp[0].expr_)); }
#line 1604 "Parser.C"
    break;

  case 45: /* ListItem: Item  */
#line 228 "Javalette.y"
                { (yyval.listitem_) = new ListItem(); (yyval.listitem_)->push_back((yyvsp[0].item_)); }
#line 1610 "Parser.C"
    break;

  case 46: /* ListItem: Item _COMMA ListItem  */
#line 229 "Javalette.y"
                         { (yyvsp[0].listitem_)->push_back((yyvsp[-2].item_)); (yyval.listitem_) = (yyvsp[0].listitem_); }
#line 1616 "Parser.C"
    break;

  case 47: /* Expr7: _INTEGER_  */
#line 231 "Javalette.y"
                  { (yyval.expr_) = new ELitInt((yyvsp[0]._int)); }
#line 1622 "Parser.C"
    break;

  case 48: /* Expr7: _DOUBLE_  */
#line 232 "Javalette.y"
             { (yyval.expr_) = new ELitDoub((yyvsp[0]._double)); }
#line 1628 "Parser.C"
    break;

  case 49: /* Expr7: _KW_true  */
#line 233 "Javalette.y"
             { (yyval.expr_) = new ELitTrue(); }
#line 1634 "Parser.C"
    break;

  case 50: /* Expr7: _KW_false  */
#line 234 "Javalette.y"
              { (yyval.expr_) = new ELitFalse(); }
#line 1640 "Parser.C"
    break;

  case 51: /* Expr7: _STRING_  */
#line 235 "Javalette.y"
             { (yyval.expr_) = new EString((yyvsp[0]._string)); }
#line 1646 "Parser.C"
    break;

  case 52: /* Expr7: _IDENT_  */
#line 236 "Javalette.y"
            { (yyval.expr_) = new EVar((yyvsp[0]._string)); }
#line 1652 "Parser.C"
    break;

  case 53: /* Expr7: _LPAREN Expr _RPAREN  */
#line 237 "Javalette.y"
                         { (yyval.expr_) = (yyvsp[-1].expr_); }
#line 1658 "Parser.C"
    break;

  case 54: /* Expr: Expr7 _DBAR Expr  */
#line 239 "Javalette.y"
                        { (yyval.expr_) = new EOr((yyvsp[-2].expr_), (yyvsp[0].expr_)); }
#line 1664 "Parser.C"
    break;

  case 55: /* Expr: Expr1  */
#line 240 "Javalette.y"
          { (yyval.expr_) = (yyvsp[0].expr_); }
#line 1670 "Parser.C"
    break;

  case 56: /* Expr1: Expr2  */
#line 242 "Javalette.y"
              { (yyval.expr_) = (yyvsp[0].expr_); }
#line 1676 "Parser.C"
    break;

  case 57: /* Expr2: Expr3  */
#line 244 "Javalette.y"
              { (yyval.expr_) = (yyvsp[0].expr_); }
#line 1682 "Parser.C"
    break;

  case 58: /* Expr3: Expr4  */
#line 246 "Javalette.y"
              { (yyval.expr_) = (yyvsp[0].expr_); }
#line 1688 "Parser.C"
    break;

  case 59: /* Expr4: Expr5  */
#line 248 "Javalette.y"
              { (yyval.expr_) = (yyvsp[0].expr_); }
#line 1694 "Parser.C"
    break;

  case 60: /* Expr5: Expr6  */
#line 250 "Javalette.y"
              { (yyval.expr_) = (yyvsp[0].expr_); }
#line 1700 "Parser.C"
    break;

  case 61: /* Expr6: Expr7  */
#line 252 "Javalette.y"
              { (yyval.expr_) = (yyvsp[0].expr_); }
#line 1706 "Parser.C"
    break;


#line 1710 "Parser.C"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (&yylloc, scanner, result, YY_("syntax error"));
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
                      yytoken, &yylval, &yylloc, scanner, result);
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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, scanner, result);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, result, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, scanner, result);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, scanner, result);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 259 "Javalette.y"



/* Entrypoint: parse Prog* from file. */
Prog* pProg(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = javalette__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  javalette_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.prog_;
  }
}

/* Entrypoint: parse Prog* from string. */
Prog* psProg(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = javalette__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = javalette__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  javalette__delete_buffer(buf, scanner);
  javalette_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.prog_;
  }
}




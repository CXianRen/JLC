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
  YYSYMBOL__BANG = 4,                      /* _BANG  */
  YYSYMBOL__BANGEQ = 5,                    /* _BANGEQ  */
  YYSYMBOL__PERCENT = 6,                   /* _PERCENT  */
  YYSYMBOL__DAMP = 7,                      /* _DAMP  */
  YYSYMBOL__LPAREN = 8,                    /* _LPAREN  */
  YYSYMBOL__RPAREN = 9,                    /* _RPAREN  */
  YYSYMBOL__STAR = 10,                     /* _STAR  */
  YYSYMBOL__PLUS = 11,                     /* _PLUS  */
  YYSYMBOL__DPLUS = 12,                    /* _DPLUS  */
  YYSYMBOL__COMMA = 13,                    /* _COMMA  */
  YYSYMBOL__MINUS = 14,                    /* _MINUS  */
  YYSYMBOL__DMINUS = 15,                   /* _DMINUS  */
  YYSYMBOL__RARROW = 16,                   /* _RARROW  */
  YYSYMBOL__DOT = 17,                      /* _DOT  */
  YYSYMBOL__SLASH = 18,                    /* _SLASH  */
  YYSYMBOL__COLON = 19,                    /* _COLON  */
  YYSYMBOL__SEMI = 20,                     /* _SEMI  */
  YYSYMBOL__LT = 21,                       /* _LT  */
  YYSYMBOL__LDARROW = 22,                  /* _LDARROW  */
  YYSYMBOL__EQ = 23,                       /* _EQ  */
  YYSYMBOL__DEQ = 24,                      /* _DEQ  */
  YYSYMBOL__GT = 25,                       /* _GT  */
  YYSYMBOL__GTEQ = 26,                     /* _GTEQ  */
  YYSYMBOL__LBRACK = 27,                   /* _LBRACK  */
  YYSYMBOL__EMPTYBRACK = 28,               /* _EMPTYBRACK  */
  YYSYMBOL__RBRACK = 29,                   /* _RBRACK  */
  YYSYMBOL__KW_boolean = 30,               /* _KW_boolean  */
  YYSYMBOL__KW_class = 31,                 /* _KW_class  */
  YYSYMBOL__KW_double = 32,                /* _KW_double  */
  YYSYMBOL__KW_else = 33,                  /* _KW_else  */
  YYSYMBOL__KW_enum = 34,                  /* _KW_enum  */
  YYSYMBOL__KW_extends = 35,               /* _KW_extends  */
  YYSYMBOL__KW_false = 36,                 /* _KW_false  */
  YYSYMBOL__KW_for = 37,                   /* _KW_for  */
  YYSYMBOL__KW_if = 38,                    /* _KW_if  */
  YYSYMBOL__KW_int = 39,                   /* _KW_int  */
  YYSYMBOL__KW_new = 40,                   /* _KW_new  */
  YYSYMBOL__KW_null = 41,                  /* _KW_null  */
  YYSYMBOL__KW_return = 42,                /* _KW_return  */
  YYSYMBOL__KW_struct = 43,                /* _KW_struct  */
  YYSYMBOL__KW_true = 44,                  /* _KW_true  */
  YYSYMBOL__KW_typedef = 45,               /* _KW_typedef  */
  YYSYMBOL__KW_void = 46,                  /* _KW_void  */
  YYSYMBOL__KW_while = 47,                 /* _KW_while  */
  YYSYMBOL__LBRACE = 48,                   /* _LBRACE  */
  YYSYMBOL__DBAR = 49,                     /* _DBAR  */
  YYSYMBOL__RBRACE = 50,                   /* _RBRACE  */
  YYSYMBOL__STRING_ = 51,                  /* _STRING_  */
  YYSYMBOL__INTEGER_ = 52,                 /* _INTEGER_  */
  YYSYMBOL__DOUBLE_ = 53,                  /* _DOUBLE_  */
  YYSYMBOL__IDENT_ = 54,                   /* _IDENT_  */
  YYSYMBOL_YYACCEPT = 55,                  /* $accept  */
  YYSYMBOL_Prog = 56,                      /* Prog  */
  YYSYMBOL_TopDef = 57,                    /* TopDef  */
  YYSYMBOL_FnDef = 58,                     /* FnDef  */
  YYSYMBOL_EVal = 59,                      /* EVal  */
  YYSYMBOL_ListEVal = 60,                  /* ListEVal  */
  YYSYMBOL_Arg = 61,                       /* Arg  */
  YYSYMBOL_ListArg = 62,                   /* ListArg  */
  YYSYMBOL_ListTopDef = 63,                /* ListTopDef  */
  YYSYMBOL_BType = 64,                     /* BType  */
  YYSYMBOL_OType = 65,                     /* OType  */
  YYSYMBOL_AType = 66,                     /* AType  */
  YYSYMBOL_Type = 67,                      /* Type  */
  YYSYMBOL_BracketsOpt = 68,               /* BracketsOpt  */
  YYSYMBOL_SBlk = 69,                      /* SBlk  */
  YYSYMBOL_CBlk = 70,                      /* CBlk  */
  YYSYMBOL_MemItem = 71,                   /* MemItem  */
  YYSYMBOL_ListMemItem = 72,               /* ListMemItem  */
  YYSYMBOL_Memdef = 73,                    /* Memdef  */
  YYSYMBOL_ListMemdef = 74,                /* ListMemdef  */
  YYSYMBOL_CMemdef = 75,                   /* CMemdef  */
  YYSYMBOL_ListCMemdef = 76,               /* ListCMemdef  */
  YYSYMBOL_Blk = 77,                       /* Blk  */
  YYSYMBOL_ListStmt = 78,                  /* ListStmt  */
  YYSYMBOL_Stmt = 79,                      /* Stmt  */
  YYSYMBOL_Item = 80,                      /* Item  */
  YYSYMBOL_ListItem = 81,                  /* ListItem  */
  YYSYMBOL_Expr6 = 82,                     /* Expr6  */
  YYSYMBOL_DimExpr = 83,                   /* DimExpr  */
  YYSYMBOL_ListDimExpr = 84,               /* ListDimExpr  */
  YYSYMBOL_Expr5 = 85,                     /* Expr5  */
  YYSYMBOL_Expr4 = 86,                     /* Expr4  */
  YYSYMBOL_Expr3 = 87,                     /* Expr3  */
  YYSYMBOL_Expr2 = 88,                     /* Expr2  */
  YYSYMBOL_Expr = 89,                      /* Expr  */
  YYSYMBOL_Expr1 = 90,                     /* Expr1  */
  YYSYMBOL_ListExpr = 91,                  /* ListExpr  */
  YYSYMBOL_AddOp = 92,                     /* AddOp  */
  YYSYMBOL_MulOp = 93,                     /* MulOp  */
  YYSYMBOL_RelOp = 94                      /* RelOp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 92 "Javalette.y"

void yyerror(YYLTYPE *loc, yyscan_t scanner, YYSTYPE *result, const char *msg)
{
  fprintf(stderr, "error: %d,%d: %s at %s\n",
    loc->first_line, loc->first_column, msg, javalette_get_text(scanner));
}

int yyparse(yyscan_t scanner, YYSTYPE *result);

extern int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, yyscan_t scanner);

#line 245 "Parser.C"


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
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   278

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  194

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   309


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   203,   203,   205,   206,   207,   208,   209,   210,   211,
     213,   215,   217,   218,   219,   221,   223,   224,   225,   227,
     228,   230,   231,   232,   233,   235,   237,   239,   240,   241,
     243,   252,   254,   256,   258,   259,   260,   262,   264,   265,
     267,   268,   270,   271,   273,   275,   276,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   290,   291,
     293,   294,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   316,   318,   319,   321,   322,   323,   325,   326,   328,
     329,   330,   332,   333,   335,   336,   338,   340,   341,   342,
     344,   345,   347,   348,   349,   351,   352,   353,   354,   355,
     356
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
  "\"end of file\"", "error", "\"invalid token\"", "_ERROR_", "_BANG",
  "_BANGEQ", "_PERCENT", "_DAMP", "_LPAREN", "_RPAREN", "_STAR", "_PLUS",
  "_DPLUS", "_COMMA", "_MINUS", "_DMINUS", "_RARROW", "_DOT", "_SLASH",
  "_COLON", "_SEMI", "_LT", "_LDARROW", "_EQ", "_DEQ", "_GT", "_GTEQ",
  "_LBRACK", "_EMPTYBRACK", "_RBRACK", "_KW_boolean", "_KW_class",
  "_KW_double", "_KW_else", "_KW_enum", "_KW_extends", "_KW_false",
  "_KW_for", "_KW_if", "_KW_int", "_KW_new", "_KW_null", "_KW_return",
  "_KW_struct", "_KW_true", "_KW_typedef", "_KW_void", "_KW_while",
  "_LBRACE", "_DBAR", "_RBRACE", "_STRING_", "_INTEGER_", "_DOUBLE_",
  "_IDENT_", "$accept", "Prog", "TopDef", "FnDef", "EVal", "ListEVal",
  "Arg", "ListArg", "ListTopDef", "BType", "OType", "AType", "Type",
  "BracketsOpt", "SBlk", "CBlk", "MemItem", "ListMemItem", "Memdef",
  "ListMemdef", "CMemdef", "ListCMemdef", "Blk", "ListStmt", "Stmt",
  "Item", "ListItem", "Expr6", "DimExpr", "ListDimExpr", "Expr5", "Expr4",
  "Expr3", "Expr2", "Expr", "Expr1", "ListExpr", "AddOp", "MulOp", "RelOp", YY_NULLPTR
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
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309
};
#endif

#define YYPACT_NINF (-152)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-26)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     214,  -152,   -44,  -152,   -37,  -152,   -32,     5,  -152,  -152,
      53,   214,  -152,  -152,  -152,  -152,  -152,   -22,    -9,    18,
      19,    11,  -152,  -152,  -152,    61,  -152,    16,  -152,  -152,
      28,  -152,    64,    -3,   107,    41,    56,  -152,    79,    40,
     224,  -152,    39,    84,    83,    89,   -19,  -152,  -152,  -152,
     -16,  -152,  -152,    28,    80,  -152,   -13,  -152,    92,    45,
     107,    55,  -152,    61,    91,   100,  -152,  -152,  -152,  -152,
     113,  -152,  -152,  -152,    82,  -152,  -152,    77,  -152,   178,
     159,   198,  -152,  -152,   132,   133,   148,  -152,    10,  -152,
     134,  -152,  -152,  -152,  -152,    -5,   -12,  -152,  -152,   208,
    -152,    69,    17,    52,    35,    94,   136,  -152,    -1,   138,
     208,   107,   178,   125,   141,   141,  -152,   154,   178,   178,
     122,   162,   156,  -152,  -152,   123,   127,   178,   141,  -152,
    -152,  -152,  -152,   178,  -152,  -152,   178,  -152,   178,  -152,
    -152,  -152,  -152,  -152,   178,  -152,   178,   178,   198,  -152,
      -7,   170,  -152,  -152,  -152,   174,   171,   176,   178,   139,
    -152,  -152,   180,   161,  -152,  -152,    69,  -152,    17,    52,
     177,  -152,   208,   182,   118,   118,   178,  -152,  -152,  -152,
     178,  -152,  -152,   178,   163,  -152,  -152,   195,   199,   118,
    -152,   118,  -152,  -152
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    23,     0,    22,     0,    21,     0,     0,    24,    25,
       0,    19,     9,     2,    27,    28,    29,     0,     0,     0,
       0,     0,     1,    20,    30,     0,    26,     0,    42,     7,
      12,    38,     0,     0,    16,     0,     0,    11,    13,     0,
       0,     3,     0,     0,    17,     0,     0,     8,    32,    41,
      34,    40,    43,    12,     0,    31,    34,    39,     0,     0,
      16,     0,    15,    33,    35,     0,    14,     6,    33,     4,
       0,    18,    45,    10,    34,    37,     5,     0,    36,     0,
       0,     0,    47,    67,     0,     0,     0,    63,     0,    66,
       0,    44,    68,    64,    65,    69,     0,    48,    46,    86,
      88,    91,    93,    96,     0,    95,    69,    85,     0,     0,
      84,     0,     0,    71,     0,     0,    53,     0,     0,    97,
      58,    60,     0,    78,    79,     0,     0,     0,    82,    77,
     104,   102,   103,     0,   100,   101,     0,   110,     0,   105,
     106,   109,   107,   108,     0,    50,     0,     0,     0,    80,
       0,     0,    75,    76,    52,     0,    98,     0,     0,     0,
      49,    72,    73,     0,    83,    87,    89,    90,    92,     0,
       0,    94,    62,     0,     0,     0,    97,    70,    59,    61,
      97,    81,    51,     0,    54,    56,    99,     0,     0,     0,
      74,     0,    55,    57
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -152,  -152,  -152,   173,  -152,   164,  -152,   147,   204,   130,
     135,  -152,     0,  -152,   193,   192,  -152,   166,   188,  -152,
    -152,  -152,   172,  -152,   -40,  -152,    78,   -80,  -152,   -95,
     -77,   105,    99,   103,   -75,    98,  -151,  -152,  -152,  -152
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    10,    11,    12,    38,    39,    44,    45,    13,    14,
      15,    16,    96,    26,    32,    29,    64,    65,    51,    40,
      52,    36,    97,    77,    98,   121,   122,    99,   128,   129,
     100,   101,   102,   103,   104,   105,   157,   136,   133,   144
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      17,   110,   107,   119,   -25,   109,    24,    42,   148,    24,
      18,    17,    24,   117,    79,    24,    24,    19,    80,   152,
     153,    24,    20,   -25,    81,   186,    27,    24,   134,   187,
     116,   135,    25,   164,    46,    62,    50,   151,    63,    28,
      56,    68,   120,   155,   156,    31,    83,   173,    21,   -25,
      86,    87,   163,    22,    89,   145,   165,   137,   146,   138,
      46,    92,    93,    94,   106,    33,    30,    31,   172,    34,
      35,   170,   171,   139,   140,   130,   141,   142,   143,   131,
     108,    79,    37,   178,    41,    80,     1,   132,     3,    28,
      54,    81,    53,    58,    59,     5,    60,    82,    61,    70,
      67,   156,     8,    72,    74,   156,    48,     1,   188,     3,
       9,   150,    69,    83,    84,    85,     5,    86,    87,    88,
      75,    89,    79,     8,    90,    72,    80,    91,    92,    93,
      94,    95,    81,    76,   184,   185,    68,     1,    82,     3,
     111,   112,   118,   147,   119,   158,     5,   149,     1,   192,
       3,   193,   -25,     8,    83,    84,    85,     5,    86,    87,
      88,     9,    89,    79,     8,    90,    72,    80,   127,    92,
      93,    94,    95,    81,   154,   159,   160,   161,     1,   174,
       3,   162,    79,   175,   176,   177,    80,     5,   180,     1,
     181,     3,    81,   120,     8,    83,   189,   182,     5,    86,
      87,   183,   113,    89,   190,     8,    80,    71,   191,    49,
      92,    93,    94,    95,    83,    23,   114,    66,    86,    87,
     123,   115,    89,   124,   125,   126,    43,    47,    57,    92,
      93,    94,   106,    73,    83,   127,   167,   179,    86,    87,
      78,   166,    89,   168,     1,     2,     3,   169,     4,    92,
      93,    94,   106,     5,     1,     0,     3,     6,     0,     7,
       8,     0,     0,     5,     0,     0,     0,     0,     9,     0,
       8,     0,     0,     0,    55,     0,     0,     0,     9
};

static const yytype_int16 yycheck[] =
{
       0,    81,    79,     8,     9,    80,    28,    10,     9,    28,
      54,    11,    28,    88,     4,    28,    28,    54,     8,   114,
     115,    28,    54,    28,    14,   176,    35,    28,    11,   180,
      20,    14,    54,   128,    34,    54,    36,   112,    54,    48,
      40,    54,    54,   118,   119,    48,    36,    54,    43,    54,
      40,    41,   127,     0,    44,    20,   133,     5,    23,     7,
      60,    51,    52,    53,    54,    54,    48,    48,   148,     8,
      54,   146,   147,    21,    22,     6,    24,    25,    26,    10,
      80,     4,    54,   158,    20,     8,    30,    18,    32,    48,
      50,    14,    13,    54,    10,    39,    13,    20,     9,    54,
      20,   176,    46,    48,    13,   180,    50,    30,   183,    32,
      54,   111,    20,    36,    37,    38,    39,    40,    41,    42,
      20,    44,     4,    46,    47,    48,     8,    50,    51,    52,
      53,    54,    14,    20,   174,   175,    54,    30,    20,    32,
       8,     8,     8,    49,     8,    23,    39,     9,    30,   189,
      32,   191,    27,    46,    36,    37,    38,    39,    40,    41,
      42,    54,    44,     4,    46,    47,    48,     8,    27,    51,
      52,    53,    54,    14,    20,    13,    20,    54,    30,     9,
      32,    54,     4,     9,    13,     9,     8,    39,     8,    30,
      29,    32,    14,    54,    46,    36,    33,    20,    39,    40,
      41,    19,    54,    44,     9,    46,     8,    60,     9,    36,
      51,    52,    53,    54,    36,    11,    86,    53,    40,    41,
      12,    86,    44,    15,    16,    17,    33,    35,    40,    51,
      52,    53,    54,    61,    36,    27,   138,   159,    40,    41,
      74,   136,    44,   144,    30,    31,    32,   144,    34,    51,
      52,    53,    54,    39,    30,    -1,    32,    43,    -1,    45,
      46,    -1,    -1,    39,    -1,    -1,    -1,    -1,    54,    -1,
      46,    -1,    -1,    -1,    50,    -1,    -1,    -1,    54
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    30,    31,    32,    34,    39,    43,    45,    46,    54,
      56,    57,    58,    63,    64,    65,    66,    67,    54,    54,
      54,    43,     0,    63,    28,    54,    68,    35,    48,    70,
      48,    48,    69,    54,     8,    54,    76,    54,    59,    60,
      74,    20,    10,    69,    61,    62,    67,    70,    50,    58,
      67,    73,    75,    13,    50,    50,    67,    73,    54,    10,
      13,     9,    54,    54,    71,    72,    60,    20,    54,    20,
      54,    62,    48,    77,    13,    20,    20,    78,    72,     4,
       8,    14,    20,    36,    37,    38,    40,    41,    42,    44,
      47,    50,    51,    52,    53,    54,    67,    77,    79,    82,
      85,    86,    87,    88,    89,    90,    54,    85,    67,    89,
      82,     8,     8,    54,    64,    65,    20,    89,     8,     8,
      54,    80,    81,    12,    15,    16,    17,    27,    83,    84,
       6,    10,    18,    93,    11,    14,    92,     5,     7,    21,
      22,    24,    25,    26,    94,    20,    23,    49,     9,     9,
      67,    89,    84,    84,    20,    89,    89,    91,    23,    13,
      20,    54,    54,    89,    84,    85,    86,    90,    87,    88,
      89,    89,    82,    54,     9,     9,    13,     9,    89,    81,
       8,    29,    20,    19,    79,    79,    91,    91,    89,    33,
       9,     9,    79,    79
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    55,    56,    57,    57,    57,    57,    57,    57,    57,
      58,    59,    60,    60,    60,    61,    62,    62,    62,    63,
      63,    64,    64,    64,    64,    65,    66,    67,    67,    67,
      68,    69,    70,    71,    72,    72,    72,    73,    74,    74,
      75,    75,    76,    76,    77,    78,    78,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    80,    80,
      81,    81,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    83,    84,    84,    85,    85,    85,    86,    86,    87,
      87,    87,    88,    88,    89,    89,    90,    91,    91,    91,
      92,    92,    93,    93,    93,    94,    94,    94,    94,    94,
      94
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     4,     6,     7,     6,     3,     5,     1,
       6,     1,     0,     1,     3,     2,     0,     1,     3,     1,
       2,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     3,     3,     1,     0,     1,     3,     3,     0,     2,
       1,     1,     0,     2,     3,     0,     2,     1,     1,     3,
       2,     4,     3,     2,     5,     7,     5,     8,     1,     3,
       1,     3,     4,     1,     1,     1,     1,     1,     1,     1,
       4,     2,     3,     3,     6,     3,     3,     2,     2,     2,
       3,     3,     1,     2,     2,     2,     1,     3,     1,     3,
       3,     1,     3,     1,     3,     1,     1,     0,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
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
#line 203 "Javalette.y"
                  { std::reverse((yyvsp[0].listtopdef_)->begin(),(yyvsp[0].listtopdef_)->end()) ;(yyval.prog_) = new Program((yyvsp[0].listtopdef_)); result->prog_ = (yyval.prog_); }
#line 1476 "Parser.C"
    break;

  case 3: /* TopDef: _KW_struct _IDENT_ SBlk _SEMI  */
#line 205 "Javalette.y"
                                       { (yyval.topdef_) = new Struct((yyvsp[-2]._string), (yyvsp[-1].sblk_)); }
#line 1482 "Parser.C"
    break;

  case 4: /* TopDef: _KW_typedef _KW_struct _IDENT_ _STAR _IDENT_ _SEMI  */
#line 206 "Javalette.y"
                                                       { (yyval.topdef_) = new TypeDef((yyvsp[-3]._string), (yyvsp[-1]._string)); }
#line 1488 "Parser.C"
    break;

  case 5: /* TopDef: _KW_typedef _KW_struct _IDENT_ SBlk _STAR _IDENT_ _SEMI  */
#line 207 "Javalette.y"
                                                            { (yyval.topdef_) = new TypeDefWS((yyvsp[-4]._string), (yyvsp[-3].sblk_), (yyvsp[-1]._string)); }
#line 1494 "Parser.C"
    break;

  case 6: /* TopDef: _KW_enum _IDENT_ _LBRACE ListEVal _RBRACE _SEMI  */
#line 208 "Javalette.y"
                                                    { std::reverse((yyvsp[-2].listeval_)->begin(),(yyvsp[-2].listeval_)->end()) ;(yyval.topdef_) = new Enum((yyvsp[-4]._string), (yyvsp[-2].listeval_)); }
#line 1500 "Parser.C"
    break;

  case 7: /* TopDef: _KW_class _IDENT_ CBlk  */
#line 209 "Javalette.y"
                           { (yyval.topdef_) = new Class((yyvsp[-1]._string), (yyvsp[0].cblk_)); }
#line 1506 "Parser.C"
    break;

  case 8: /* TopDef: _KW_class _IDENT_ _KW_extends _IDENT_ CBlk  */
#line 210 "Javalette.y"
                                               { (yyval.topdef_) = new ClassWE((yyvsp[-3]._string), (yyvsp[-1]._string), (yyvsp[0].cblk_)); }
#line 1512 "Parser.C"
    break;

  case 9: /* TopDef: FnDef  */
#line 211 "Javalette.y"
          { (yyval.topdef_) = new GFuncDef((yyvsp[0].fndef_)); }
#line 1518 "Parser.C"
    break;

  case 10: /* FnDef: Type _IDENT_ _LPAREN ListArg _RPAREN Blk  */
#line 213 "Javalette.y"
                                                 { std::reverse((yyvsp[-2].listarg_)->begin(),(yyvsp[-2].listarg_)->end()) ;(yyval.fndef_) = new FuncDef((yyvsp[-5].type_), (yyvsp[-4]._string), (yyvsp[-2].listarg_), (yyvsp[0].blk_)); }
#line 1524 "Parser.C"
    break;

  case 11: /* EVal: _IDENT_  */
#line 215 "Javalette.y"
               { (yyval.eval_) = new EnumValue((yyvsp[0]._string)); }
#line 1530 "Parser.C"
    break;

  case 12: /* ListEVal: %empty  */
#line 217 "Javalette.y"
                       { (yyval.listeval_) = new ListEVal(); }
#line 1536 "Parser.C"
    break;

  case 13: /* ListEVal: EVal  */
#line 218 "Javalette.y"
         { (yyval.listeval_) = new ListEVal(); (yyval.listeval_)->push_back((yyvsp[0].eval_)); }
#line 1542 "Parser.C"
    break;

  case 14: /* ListEVal: EVal _COMMA ListEVal  */
#line 219 "Javalette.y"
                         { (yyvsp[0].listeval_)->push_back((yyvsp[-2].eval_)); (yyval.listeval_) = (yyvsp[0].listeval_); }
#line 1548 "Parser.C"
    break;

  case 15: /* Arg: Type _IDENT_  */
#line 221 "Javalette.y"
                   { (yyval.arg_) = new Argument((yyvsp[-1].type_), (yyvsp[0]._string)); }
#line 1554 "Parser.C"
    break;

  case 16: /* ListArg: %empty  */
#line 223 "Javalette.y"
                      { (yyval.listarg_) = new ListArg(); }
#line 1560 "Parser.C"
    break;

  case 17: /* ListArg: Arg  */
#line 224 "Javalette.y"
        { (yyval.listarg_) = new ListArg(); (yyval.listarg_)->push_back((yyvsp[0].arg_)); }
#line 1566 "Parser.C"
    break;

  case 18: /* ListArg: Arg _COMMA ListArg  */
#line 225 "Javalette.y"
                       { (yyvsp[0].listarg_)->push_back((yyvsp[-2].arg_)); (yyval.listarg_) = (yyvsp[0].listarg_); }
#line 1572 "Parser.C"
    break;

  case 19: /* ListTopDef: TopDef  */
#line 227 "Javalette.y"
                    { (yyval.listtopdef_) = new ListTopDef(); (yyval.listtopdef_)->push_back((yyvsp[0].topdef_)); }
#line 1578 "Parser.C"
    break;

  case 20: /* ListTopDef: TopDef ListTopDef  */
#line 228 "Javalette.y"
                      { (yyvsp[0].listtopdef_)->push_back((yyvsp[-1].topdef_)); (yyval.listtopdef_) = (yyvsp[0].listtopdef_); }
#line 1584 "Parser.C"
    break;

  case 21: /* BType: _KW_int  */
#line 230 "Javalette.y"
                { (yyval.btype_) = new Int(); }
#line 1590 "Parser.C"
    break;

  case 22: /* BType: _KW_double  */
#line 231 "Javalette.y"
               { (yyval.btype_) = new Doub(); }
#line 1596 "Parser.C"
    break;

  case 23: /* BType: _KW_boolean  */
#line 232 "Javalette.y"
                { (yyval.btype_) = new Bool(); }
#line 1602 "Parser.C"
    break;

  case 24: /* BType: _KW_void  */
#line 233 "Javalette.y"
             { (yyval.btype_) = new Void(); }
#line 1608 "Parser.C"
    break;

  case 25: /* OType: _IDENT_  */
#line 235 "Javalette.y"
                { (yyval.otype_) = new ObjT((yyvsp[0]._string)); }
#line 1614 "Parser.C"
    break;

  case 26: /* AType: Type BracketsOpt  */
#line 237 "Javalette.y"
                         { (yyval.atype_) = new Array((yyvsp[-1].type_), (yyvsp[0].bracketsopt_)); }
#line 1620 "Parser.C"
    break;

  case 27: /* Type: BType  */
#line 239 "Javalette.y"
             { (yyval.type_) = new BaseType((yyvsp[0].btype_)); }
#line 1626 "Parser.C"
    break;

  case 28: /* Type: OType  */
#line 240 "Javalette.y"
          { (yyval.type_) = new ObjType((yyvsp[0].otype_)); }
#line 1632 "Parser.C"
    break;

  case 29: /* Type: AType  */
#line 241 "Javalette.y"
          { (yyval.type_) = new ArrType((yyvsp[0].atype_)); }
#line 1638 "Parser.C"
    break;

  case 30: /* BracketsOpt: _EMPTYBRACK  */
#line 243 "Javalette.y"
                          { (yyval.bracketsopt_) = new BracketsEmpty(); }
#line 1644 "Parser.C"
    break;

  case 31: /* SBlk: _LBRACE ListMemdef _RBRACE  */
#line 252 "Javalette.y"
                                  { (yyval.sblk_) = new SBlock((yyvsp[-1].listmemdef_)); }
#line 1650 "Parser.C"
    break;

  case 32: /* CBlk: _LBRACE ListCMemdef _RBRACE  */
#line 254 "Javalette.y"
                                   { (yyval.cblk_) = new CBlock((yyvsp[-1].listcmemdef_)); }
#line 1656 "Parser.C"
    break;

  case 33: /* MemItem: _IDENT_  */
#line 256 "Javalette.y"
                  { (yyval.memitem_) = new MemberItem((yyvsp[0]._string)); }
#line 1662 "Parser.C"
    break;

  case 34: /* ListMemItem: %empty  */
#line 258 "Javalette.y"
                          { (yyval.listmemitem_) = new ListMemItem(); }
#line 1668 "Parser.C"
    break;

  case 35: /* ListMemItem: MemItem  */
#line 259 "Javalette.y"
            { (yyval.listmemitem_) = new ListMemItem(); (yyval.listmemitem_)->push_back((yyvsp[0].memitem_)); }
#line 1674 "Parser.C"
    break;

  case 36: /* ListMemItem: MemItem _COMMA ListMemItem  */
#line 260 "Javalette.y"
                               { (yyvsp[0].listmemitem_)->push_back((yyvsp[-2].memitem_)); (yyval.listmemitem_) = (yyvsp[0].listmemitem_); }
#line 1680 "Parser.C"
    break;

  case 37: /* Memdef: Type ListMemItem _SEMI  */
#line 262 "Javalette.y"
                                { std::reverse((yyvsp[-1].listmemitem_)->begin(),(yyvsp[-1].listmemitem_)->end()) ;(yyval.memdef_) = new MemberDef((yyvsp[-2].type_), (yyvsp[-1].listmemitem_)); }
#line 1686 "Parser.C"
    break;

  case 38: /* ListMemdef: %empty  */
#line 264 "Javalette.y"
                         { (yyval.listmemdef_) = new ListMemdef(); }
#line 1692 "Parser.C"
    break;

  case 39: /* ListMemdef: ListMemdef Memdef  */
#line 265 "Javalette.y"
                      { (yyvsp[-1].listmemdef_)->push_back((yyvsp[0].memdef_)); (yyval.listmemdef_) = (yyvsp[-1].listmemdef_); }
#line 1698 "Parser.C"
    break;

  case 40: /* CMemdef: Memdef  */
#line 267 "Javalette.y"
                 { (yyval.cmemdef_) = new CVarDef((yyvsp[0].memdef_)); }
#line 1704 "Parser.C"
    break;

  case 41: /* CMemdef: FnDef  */
#line 268 "Javalette.y"
          { (yyval.cmemdef_) = new CFuncDef((yyvsp[0].fndef_)); }
#line 1710 "Parser.C"
    break;

  case 42: /* ListCMemdef: %empty  */
#line 270 "Javalette.y"
                          { (yyval.listcmemdef_) = new ListCMemdef(); }
#line 1716 "Parser.C"
    break;

  case 43: /* ListCMemdef: ListCMemdef CMemdef  */
#line 271 "Javalette.y"
                        { (yyvsp[-1].listcmemdef_)->push_back((yyvsp[0].cmemdef_)); (yyval.listcmemdef_) = (yyvsp[-1].listcmemdef_); }
#line 1722 "Parser.C"
    break;

  case 44: /* Blk: _LBRACE ListStmt _RBRACE  */
#line 273 "Javalette.y"
                               { (yyval.blk_) = new Block((yyvsp[-1].liststmt_)); }
#line 1728 "Parser.C"
    break;

  case 45: /* ListStmt: %empty  */
#line 275 "Javalette.y"
                       { (yyval.liststmt_) = new ListStmt(); }
#line 1734 "Parser.C"
    break;

  case 46: /* ListStmt: ListStmt Stmt  */
#line 276 "Javalette.y"
                  { (yyvsp[-1].liststmt_)->push_back((yyvsp[0].stmt_)); (yyval.liststmt_) = (yyvsp[-1].liststmt_); }
#line 1740 "Parser.C"
    break;

  case 47: /* Stmt: _SEMI  */
#line 278 "Javalette.y"
             { (yyval.stmt_) = new Empty(); }
#line 1746 "Parser.C"
    break;

  case 48: /* Stmt: Blk  */
#line 279 "Javalette.y"
        { (yyval.stmt_) = new BStmt((yyvsp[0].blk_)); }
#line 1752 "Parser.C"
    break;

  case 49: /* Stmt: Type ListItem _SEMI  */
#line 280 "Javalette.y"
                        { std::reverse((yyvsp[-1].listitem_)->begin(),(yyvsp[-1].listitem_)->end()) ;(yyval.stmt_) = new Decl((yyvsp[-2].type_), (yyvsp[-1].listitem_)); }
#line 1758 "Parser.C"
    break;

  case 50: /* Stmt: Expr _SEMI  */
#line 281 "Javalette.y"
               { (yyval.stmt_) = new SExp((yyvsp[-1].expr_)); }
#line 1764 "Parser.C"
    break;

  case 51: /* Stmt: Expr _EQ Expr _SEMI  */
#line 282 "Javalette.y"
                        { (yyval.stmt_) = new Ass((yyvsp[-3].expr_), (yyvsp[-1].expr_)); }
#line 1770 "Parser.C"
    break;

  case 52: /* Stmt: _KW_return Expr _SEMI  */
#line 283 "Javalette.y"
                          { (yyval.stmt_) = new Ret((yyvsp[-1].expr_)); }
#line 1776 "Parser.C"
    break;

  case 53: /* Stmt: _KW_return _SEMI  */
#line 284 "Javalette.y"
                     { (yyval.stmt_) = new VRet(); }
#line 1782 "Parser.C"
    break;

  case 54: /* Stmt: _KW_if _LPAREN Expr _RPAREN Stmt  */
#line 285 "Javalette.y"
                                     { (yyval.stmt_) = new Cond((yyvsp[-2].expr_), (yyvsp[0].stmt_)); }
#line 1788 "Parser.C"
    break;

  case 55: /* Stmt: _KW_if _LPAREN Expr _RPAREN Stmt _KW_else Stmt  */
#line 286 "Javalette.y"
                                                   { (yyval.stmt_) = new CondElse((yyvsp[-4].expr_), (yyvsp[-2].stmt_), (yyvsp[0].stmt_)); }
#line 1794 "Parser.C"
    break;

  case 56: /* Stmt: _KW_while _LPAREN Expr _RPAREN Stmt  */
#line 287 "Javalette.y"
                                        { (yyval.stmt_) = new While((yyvsp[-2].expr_), (yyvsp[0].stmt_)); }
#line 1800 "Parser.C"
    break;

  case 57: /* Stmt: _KW_for _LPAREN Type _IDENT_ _COLON Expr _RPAREN Stmt  */
#line 288 "Javalette.y"
                                                          { (yyval.stmt_) = new ForLoop((yyvsp[-5].type_), (yyvsp[-4]._string), (yyvsp[-2].expr_), (yyvsp[0].stmt_)); }
#line 1806 "Parser.C"
    break;

  case 58: /* Item: _IDENT_  */
#line 290 "Javalette.y"
               { (yyval.item_) = new NoInit((yyvsp[0]._string)); }
#line 1812 "Parser.C"
    break;

  case 59: /* Item: _IDENT_ _EQ Expr  */
#line 291 "Javalette.y"
                     { (yyval.item_) = new Init((yyvsp[-2]._string), (yyvsp[0].expr_)); }
#line 1818 "Parser.C"
    break;

  case 60: /* ListItem: Item  */
#line 293 "Javalette.y"
                { (yyval.listitem_) = new ListItem(); (yyval.listitem_)->push_back((yyvsp[0].item_)); }
#line 1824 "Parser.C"
    break;

  case 61: /* ListItem: Item _COMMA ListItem  */
#line 294 "Javalette.y"
                         { (yyvsp[0].listitem_)->push_back((yyvsp[-2].item_)); (yyval.listitem_) = (yyvsp[0].listitem_); }
#line 1830 "Parser.C"
    break;

  case 62: /* Expr6: _LPAREN Type _RPAREN Expr6  */
#line 296 "Javalette.y"
                                   { (yyval.expr_) = new Ecast((yyvsp[-2].type_), (yyvsp[0].expr_)); }
#line 1836 "Parser.C"
    break;

  case 63: /* Expr6: _KW_null  */
#line 297 "Javalette.y"
             { (yyval.expr_) = new ELitNull(); }
#line 1842 "Parser.C"
    break;

  case 64: /* Expr6: _INTEGER_  */
#line 298 "Javalette.y"
              { (yyval.expr_) = new ELitInt((yyvsp[0]._int)); }
#line 1848 "Parser.C"
    break;

  case 65: /* Expr6: _DOUBLE_  */
#line 299 "Javalette.y"
             { (yyval.expr_) = new ELitDoub((yyvsp[0]._double)); }
#line 1854 "Parser.C"
    break;

  case 66: /* Expr6: _KW_true  */
#line 300 "Javalette.y"
             { (yyval.expr_) = new ELitTrue(); }
#line 1860 "Parser.C"
    break;

  case 67: /* Expr6: _KW_false  */
#line 301 "Javalette.y"
              { (yyval.expr_) = new ELitFalse(); }
#line 1866 "Parser.C"
    break;

  case 68: /* Expr6: _STRING_  */
#line 302 "Javalette.y"
             { (yyval.expr_) = new EString((yyvsp[0]._string)); }
#line 1872 "Parser.C"
    break;

  case 69: /* Expr6: _IDENT_  */
#line 303 "Javalette.y"
            { (yyval.expr_) = new EVar((yyvsp[0]._string)); }
#line 1878 "Parser.C"
    break;

  case 70: /* Expr6: _IDENT_ _LPAREN ListExpr _RPAREN  */
#line 304 "Javalette.y"
                                     { std::reverse((yyvsp[-1].listexpr_)->begin(),(yyvsp[-1].listexpr_)->end()) ;(yyval.expr_) = new EApp((yyvsp[-3]._string), (yyvsp[-1].listexpr_)); }
#line 1884 "Parser.C"
    break;

  case 71: /* Expr6: _KW_new _IDENT_  */
#line 305 "Javalette.y"
                    { (yyval.expr_) = new ENewObj((yyvsp[0]._string)); }
#line 1890 "Parser.C"
    break;

  case 72: /* Expr6: Expr6 _RARROW _IDENT_  */
#line 306 "Javalette.y"
                          { (yyval.expr_) = new EArrow((yyvsp[-2].expr_), (yyvsp[0]._string)); }
#line 1896 "Parser.C"
    break;

  case 73: /* Expr6: Expr6 _DOT _IDENT_  */
#line 307 "Javalette.y"
                       { (yyval.expr_) = new Epropety((yyvsp[-2].expr_), (yyvsp[0]._string)); }
#line 1902 "Parser.C"
    break;

  case 74: /* Expr6: Expr6 _DOT _IDENT_ _LPAREN ListExpr _RPAREN  */
#line 308 "Javalette.y"
                                                { std::reverse((yyvsp[-1].listexpr_)->begin(),(yyvsp[-1].listexpr_)->end()) ;(yyval.expr_) = new EFunc((yyvsp[-5].expr_), (yyvsp[-3]._string), (yyvsp[-1].listexpr_)); }
#line 1908 "Parser.C"
    break;

  case 75: /* Expr6: _KW_new BType ListDimExpr  */
#line 309 "Javalette.y"
                              { std::reverse((yyvsp[0].listdimexpr_)->begin(),(yyvsp[0].listdimexpr_)->end()) ;(yyval.expr_) = new ENewBArr((yyvsp[-1].btype_), (yyvsp[0].listdimexpr_)); }
#line 1914 "Parser.C"
    break;

  case 76: /* Expr6: _KW_new OType ListDimExpr  */
#line 310 "Javalette.y"
                              { std::reverse((yyvsp[0].listdimexpr_)->begin(),(yyvsp[0].listdimexpr_)->end()) ;(yyval.expr_) = new ENewOArr((yyvsp[-1].otype_), (yyvsp[0].listdimexpr_)); }
#line 1920 "Parser.C"
    break;

  case 77: /* Expr6: Expr6 ListDimExpr  */
#line 311 "Javalette.y"
                      { std::reverse((yyvsp[0].listdimexpr_)->begin(),(yyvsp[0].listdimexpr_)->end()) ;(yyval.expr_) = new EAcc((yyvsp[-1].expr_), (yyvsp[0].listdimexpr_)); }
#line 1926 "Parser.C"
    break;

  case 78: /* Expr6: Expr6 _DPLUS  */
#line 312 "Javalette.y"
                 { (yyval.expr_) = new EInc((yyvsp[-1].expr_)); }
#line 1932 "Parser.C"
    break;

  case 79: /* Expr6: Expr6 _DMINUS  */
#line 313 "Javalette.y"
                  { (yyval.expr_) = new EDecr((yyvsp[-1].expr_)); }
#line 1938 "Parser.C"
    break;

  case 80: /* Expr6: _LPAREN Expr _RPAREN  */
#line 314 "Javalette.y"
                         { (yyval.expr_) = (yyvsp[-1].expr_); }
#line 1944 "Parser.C"
    break;

  case 81: /* DimExpr: _LBRACK Expr _RBRACK  */
#line 316 "Javalette.y"
                               { (yyval.dimexpr_) = new Dim((yyvsp[-1].expr_)); }
#line 1950 "Parser.C"
    break;

  case 82: /* ListDimExpr: DimExpr  */
#line 318 "Javalette.y"
                      { (yyval.listdimexpr_) = new ListDimExpr(); (yyval.listdimexpr_)->push_back((yyvsp[0].dimexpr_)); }
#line 1956 "Parser.C"
    break;

  case 83: /* ListDimExpr: DimExpr ListDimExpr  */
#line 319 "Javalette.y"
                        { (yyvsp[0].listdimexpr_)->push_back((yyvsp[-1].dimexpr_)); (yyval.listdimexpr_) = (yyvsp[0].listdimexpr_); }
#line 1962 "Parser.C"
    break;

  case 84: /* Expr5: _MINUS Expr6  */
#line 321 "Javalette.y"
                     { (yyval.expr_) = new ENeg((yyvsp[0].expr_)); }
#line 1968 "Parser.C"
    break;

  case 85: /* Expr5: _BANG Expr5  */
#line 322 "Javalette.y"
                { (yyval.expr_) = new ENot((yyvsp[0].expr_)); }
#line 1974 "Parser.C"
    break;

  case 86: /* Expr5: Expr6  */
#line 323 "Javalette.y"
          { (yyval.expr_) = (yyvsp[0].expr_); }
#line 1980 "Parser.C"
    break;

  case 87: /* Expr4: Expr4 MulOp Expr5  */
#line 325 "Javalette.y"
                          { (yyval.expr_) = new EMul((yyvsp[-2].expr_), (yyvsp[-1].mulop_), (yyvsp[0].expr_)); }
#line 1986 "Parser.C"
    break;

  case 88: /* Expr4: Expr5  */
#line 326 "Javalette.y"
          { (yyval.expr_) = (yyvsp[0].expr_); }
#line 1992 "Parser.C"
    break;

  case 89: /* Expr3: Expr3 AddOp Expr4  */
#line 328 "Javalette.y"
                          { (yyval.expr_) = new EAdd((yyvsp[-2].expr_), (yyvsp[-1].addop_), (yyvsp[0].expr_)); }
#line 1998 "Parser.C"
    break;

  case 90: /* Expr3: Expr2 _DAMP Expr1  */
#line 329 "Javalette.y"
                      { (yyval.expr_) = new EAnd((yyvsp[-2].expr_), (yyvsp[0].expr_)); }
#line 2004 "Parser.C"
    break;

  case 91: /* Expr3: Expr4  */
#line 330 "Javalette.y"
          { (yyval.expr_) = (yyvsp[0].expr_); }
#line 2010 "Parser.C"
    break;

  case 92: /* Expr2: Expr2 RelOp Expr3  */
#line 332 "Javalette.y"
                          { (yyval.expr_) = new ERel((yyvsp[-2].expr_), (yyvsp[-1].relop_), (yyvsp[0].expr_)); }
#line 2016 "Parser.C"
    break;

  case 93: /* Expr2: Expr3  */
#line 333 "Javalette.y"
          { (yyval.expr_) = (yyvsp[0].expr_); }
#line 2022 "Parser.C"
    break;

  case 94: /* Expr: Expr1 _DBAR Expr  */
#line 335 "Javalette.y"
                        { (yyval.expr_) = new EOr((yyvsp[-2].expr_), (yyvsp[0].expr_)); }
#line 2028 "Parser.C"
    break;

  case 95: /* Expr: Expr1  */
#line 336 "Javalette.y"
          { (yyval.expr_) = (yyvsp[0].expr_); }
#line 2034 "Parser.C"
    break;

  case 96: /* Expr1: Expr2  */
#line 338 "Javalette.y"
              { (yyval.expr_) = (yyvsp[0].expr_); }
#line 2040 "Parser.C"
    break;

  case 97: /* ListExpr: %empty  */
#line 340 "Javalette.y"
                       { (yyval.listexpr_) = new ListExpr(); }
#line 2046 "Parser.C"
    break;

  case 98: /* ListExpr: Expr  */
#line 341 "Javalette.y"
         { (yyval.listexpr_) = new ListExpr(); (yyval.listexpr_)->push_back((yyvsp[0].expr_)); }
#line 2052 "Parser.C"
    break;

  case 99: /* ListExpr: Expr _COMMA ListExpr  */
#line 342 "Javalette.y"
                         { (yyvsp[0].listexpr_)->push_back((yyvsp[-2].expr_)); (yyval.listexpr_) = (yyvsp[0].listexpr_); }
#line 2058 "Parser.C"
    break;

  case 100: /* AddOp: _PLUS  */
#line 344 "Javalette.y"
              { (yyval.addop_) = new Plus(); }
#line 2064 "Parser.C"
    break;

  case 101: /* AddOp: _MINUS  */
#line 345 "Javalette.y"
           { (yyval.addop_) = new Minus(); }
#line 2070 "Parser.C"
    break;

  case 102: /* MulOp: _STAR  */
#line 347 "Javalette.y"
              { (yyval.mulop_) = new Times(); }
#line 2076 "Parser.C"
    break;

  case 103: /* MulOp: _SLASH  */
#line 348 "Javalette.y"
           { (yyval.mulop_) = new Div(); }
#line 2082 "Parser.C"
    break;

  case 104: /* MulOp: _PERCENT  */
#line 349 "Javalette.y"
             { (yyval.mulop_) = new Mod(); }
#line 2088 "Parser.C"
    break;

  case 105: /* RelOp: _LT  */
#line 351 "Javalette.y"
            { (yyval.relop_) = new LTH(); }
#line 2094 "Parser.C"
    break;

  case 106: /* RelOp: _LDARROW  */
#line 352 "Javalette.y"
             { (yyval.relop_) = new LE(); }
#line 2100 "Parser.C"
    break;

  case 107: /* RelOp: _GT  */
#line 353 "Javalette.y"
        { (yyval.relop_) = new GTH(); }
#line 2106 "Parser.C"
    break;

  case 108: /* RelOp: _GTEQ  */
#line 354 "Javalette.y"
          { (yyval.relop_) = new GE(); }
#line 2112 "Parser.C"
    break;

  case 109: /* RelOp: _DEQ  */
#line 355 "Javalette.y"
         { (yyval.relop_) = new EQU(); }
#line 2118 "Parser.C"
    break;

  case 110: /* RelOp: _BANGEQ  */
#line 356 "Javalette.y"
            { (yyval.relop_) = new NE(); }
#line 2124 "Parser.C"
    break;


#line 2128 "Parser.C"

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

#line 359 "Javalette.y"



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




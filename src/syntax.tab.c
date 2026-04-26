/* A Bison parser, made by GNU Bison 3.8.2.  */

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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "syntax.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TS.h" 
#include "quad.h" /* <-- AJOUT: Inclusion des quadruplets */

int nb_temp = 1;
char temp_nom[20]; // Buffer pour stocker le nom du temporaire

extern int nb_ligne;
extern int col;
int yylex();
void yyerror(const char *s);

/* Variables globales pour l'analyse sémantique */
char sauvType[20];
char idf_tab[50][30]; /* Tableau pour stocker "a | b | c" avant de savoir le type */
int nb_idfs = 0;

/* Variables pour les quadruplets du IF */
int Fin_if = 0, deb_else = 0;
char tmp[20];

/* Variables pour les quadruplets des boucles */
int deb_while = 0, fin_while = 0;
int deb_for = 0, fin_for = 0;
char iter_for[30]; /* Pour sauvegarder l'itérateur du FOR */

#line 101 "syntax.tab.c"

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

#include "syntax.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_BEGIN_PROJECT = 3,              /* BEGIN_PROJECT  */
  YYSYMBOL_END_PROJECT = 4,                /* END_PROJECT  */
  YYSYMBOL_SETUP = 5,                      /* SETUP  */
  YYSYMBOL_RUN = 6,                        /* RUN  */
  YYSYMBOL_DEFINE = 7,                     /* DEFINE  */
  YYSYMBOL_CONST = 8,                      /* CONST  */
  YYSYMBOL_INTEGER = 9,                    /* INTEGER  */
  YYSYMBOL_FLOAT = 10,                     /* FLOAT  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_THEN = 12,                      /* THEN  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_ENDIF = 14,                     /* ENDIF  */
  YYSYMBOL_LOOP = 15,                      /* LOOP  */
  YYSYMBOL_WHILE = 16,                     /* WHILE  */
  YYSYMBOL_ENDLOOP = 17,                   /* ENDLOOP  */
  YYSYMBOL_FOR = 18,                       /* FOR  */
  YYSYMBOL_IN = 19,                        /* IN  */
  YYSYMBOL_TO = 20,                        /* TO  */
  YYSYMBOL_ENDFOR = 21,                    /* ENDFOR  */
  YYSYMBOL_OUT = 22,                       /* OUT  */
  YYSYMBOL_AND = 23,                       /* AND  */
  YYSYMBOL_OR = 24,                        /* OR  */
  YYSYMBOL_NON = 25,                       /* NON  */
  YYSYMBOL_AFFECT = 26,                    /* AFFECT  */
  YYSYMBOL_COMP_GE = 27,                   /* COMP_GE  */
  YYSYMBOL_EXPECT = 28,                    /* EXPECT  */
  YYSYMBOL_COMP_LE = 29,                   /* COMP_LE  */
  YYSYMBOL_COMP_EQ = 30,                   /* COMP_EQ  */
  YYSYMBOL_COMP_NEQ = 31,                  /* COMP_NEQ  */
  YYSYMBOL_COMP_GT = 32,                   /* COMP_GT  */
  YYSYMBOL_COMP_LT = 33,                   /* COMP_LT  */
  YYSYMBOL_COMP_AFFECT = 34,               /* COMP_AFFECT  */
  YYSYMBOL_PLUS = 35,                      /* PLUS  */
  YYSYMBOL_MINUS = 36,                     /* MINUS  */
  YYSYMBOL_MULT = 37,                      /* MULT  */
  YYSYMBOL_DIV = 38,                       /* DIV  */
  YYSYMBOL_SEMI = 39,                      /* SEMI  */
  YYSYMBOL_COLON = 40,                     /* COLON  */
  YYSYMBOL_COMMA = 41,                     /* COMMA  */
  YYSYMBOL_PIPE = 42,                      /* PIPE  */
  YYSYMBOL_LPAREN = 43,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 44,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 45,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 46,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 47,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 48,                  /* RBRACKET  */
  YYSYMBOL_T_IDF = 49,                     /* T_IDF  */
  YYSYMBOL_T_ENTIER = 50,                  /* T_ENTIER  */
  YYSYMBOL_T_FLOAT = 51,                   /* T_FLOAT  */
  YYSYMBOL_T_CHAINE = 52,                  /* T_CHAINE  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_programme = 54,                 /* programme  */
  YYSYMBOL_contenu = 55,                   /* contenu  */
  YYSYMBOL_SETUP_BLOCK = 56,               /* SETUP_BLOCK  */
  YYSYMBOL_RUN_BLOCK = 57,                 /* RUN_BLOCK  */
  YYSYMBOL_declarations = 58,              /* declarations  */
  YYSYMBOL_declaration = 59,               /* declaration  */
  YYSYMBOL_idfs = 60,                      /* idfs  */
  YYSYMBOL_61_1 = 61,                      /* $@1  */
  YYSYMBOL_type = 62,                      /* type  */
  YYSYMBOL_instructions = 63,              /* instructions  */
  YYSYMBOL_instruction = 64,               /* instruction  */
  YYSYMBOL_in_out = 65,                    /* in_out  */
  YYSYMBOL_expression = 66,                /* expression  */
  YYSYMBOL_construct_if = 67,              /* construct_if  */
  YYSYMBOL_68_2 = 68,                      /* @2  */
  YYSYMBOL_69_3 = 69,                      /* @3  */
  YYSYMBOL_else_block = 70,                /* else_block  */
  YYSYMBOL_construct_while = 71,           /* construct_while  */
  YYSYMBOL_72_4 = 72,                      /* @4  */
  YYSYMBOL_73_5 = 73,                      /* @5  */
  YYSYMBOL_construct_for = 74,             /* construct_for  */
  YYSYMBOL_75_6 = 75,                      /* @6  */
  YYSYMBOL_76_7 = 76,                      /* @7  */
  YYSYMBOL_condition = 77                  /* condition  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   195

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  162

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   307


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
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    62,    62,    65,    66,    70,    74,    78,    79,    87,
      99,   113,   131,   142,   143,   143,   148,   149,   153,   154,
     162,   176,   188,   189,   190,   191,   195,   201,   213,   216,
     219,   226,   245,   250,   255,   260,   265,   273,   276,   273,
     288,   289,   293,   295,   293,   310,   322,   310,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358
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
  "\"end of file\"", "error", "\"invalid token\"", "BEGIN_PROJECT",
  "END_PROJECT", "SETUP", "RUN", "DEFINE", "CONST", "INTEGER", "FLOAT",
  "IF", "THEN", "ELSE", "ENDIF", "LOOP", "WHILE", "ENDLOOP", "FOR", "IN",
  "TO", "ENDFOR", "OUT", "AND", "OR", "NON", "AFFECT", "COMP_GE", "EXPECT",
  "COMP_LE", "COMP_EQ", "COMP_NEQ", "COMP_GT", "COMP_LT", "COMP_AFFECT",
  "PLUS", "MINUS", "MULT", "DIV", "SEMI", "COLON", "COMMA", "PIPE",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "T_IDF",
  "T_ENTIER", "T_FLOAT", "T_CHAINE", "$accept", "programme", "contenu",
  "SETUP_BLOCK", "RUN_BLOCK", "declarations", "declaration", "idfs", "$@1",
  "type", "instructions", "instruction", "in_out", "expression",
  "construct_if", "@2", "@3", "else_block", "construct_while", "@4", "@5",
  "construct_for", "@6", "@7", "condition", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-45)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-15)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       2,   -28,    25,   -11,   -45,    -2,    18,    19,    48,    70,
     -45,    12,    43,    60,   -45,    61,    62,   -45,    12,    -4,
     -45,    72,    75,    76,   -45,    69,   132,   100,   107,   108,
     -24,   106,    -4,   -45,   -45,   -45,   -45,   111,    -1,    64,
     -19,   112,   135,   110,   105,    51,    51,   -45,   -45,    61,
     -45,   -45,    64,    21,   128,   -19,   -19,   113,   -45,   -45,
      90,    24,   -45,   114,   117,   121,    51,    68,    45,   -45,
     119,    51,   -45,    51,   -45,    34,    31,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,   -19,
     -19,   151,   -19,   -45,   126,   118,    54,   -45,   134,   116,
      94,    99,   -45,   -45,    49,   109,   109,   109,   109,   109,
     109,   109,    58,    58,   -45,   -45,   145,   -45,   130,    33,
     152,   -45,   127,    51,   125,   -45,   -45,   -45,   129,   131,
     133,   136,   104,   138,   -45,   -45,   137,   -45,   -45,   -45,
      -4,    -4,   -45,   139,   140,    -4,   -45,   161,   141,   166,
     142,   159,   143,   170,   -45,   150,    -4,   153,   -45,   144,
     -45,   -45
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     0,     0,     0,
       4,     8,     0,     0,     3,     0,     0,     5,     8,    19,
       2,    13,     0,     0,     7,     0,     0,     0,     0,     0,
       0,     0,    19,    25,    22,    23,    24,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,    18,     0,
      16,    17,     0,     0,     0,     0,     0,    30,    28,    29,
       0,     0,    42,     0,     0,     0,     0,     0,     0,    15,
       0,     0,     9,     0,    57,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    45,     0,     0,     0,    20,     0,     0,
       0,     0,    36,    58,     0,    53,    48,    54,    49,    50,
      51,    52,    32,    33,    34,    35,    55,    56,     0,     0,
       0,    26,     0,     0,     0,    10,    12,    31,     0,     0,
       0,     0,     0,     0,    37,    43,     0,    27,    21,    11,
      19,    19,    46,     0,     0,    19,    38,     0,     0,    41,
       0,     0,     0,     0,    44,     0,    19,     0,    47,     0,
      39,    40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -45,   -45,   -45,   -45,   182,   175,   -45,   146,   -45,   -26,
     -32,   -45,   -45,   -44,   -45,   -45,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,   -45,   -39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     8,     9,    10,    17,    18,    22,    37,    53,
      31,    32,    33,    60,    34,   140,   149,   153,    35,    92,
     141,    36,   120,   145,    61
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      48,    67,    68,     6,     7,     1,    55,    25,    50,    51,
      45,    26,    75,    54,    27,    28,    74,    76,    29,    15,
      16,     3,    96,    46,    56,     4,    70,   100,     5,   101,
      57,    58,    59,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    30,    52,    89,    90,    71,
     116,   117,    13,   119,    89,    90,    89,    90,    11,    12,
      72,    78,    79,    80,    81,    82,    83,    84,    91,    85,
      86,    87,    88,    50,    51,   103,     7,   129,   102,   132,
      85,    86,    87,    88,    85,    86,    87,    88,    19,    85,
      86,    87,    88,    98,    66,    87,    88,   127,   102,    20,
      57,    58,    59,    85,    86,    87,    88,    97,   143,   144,
      21,    23,    40,   148,   -14,    38,    39,    78,    79,    80,
      81,    82,    83,    84,   159,    85,    86,    87,    88,    85,
      86,    87,    88,   125,    85,    86,    87,    88,   126,    85,
      86,    87,    88,   138,    85,    86,    87,    88,    41,    42,
      43,    44,    47,    49,    63,    62,    73,    65,    99,    64,
      77,    94,    95,   118,    93,   121,   124,   122,   123,    90,
     128,   131,   130,   133,   134,   137,   135,   139,   150,   152,
     155,   154,   142,   136,   157,   146,   147,   151,   156,   158,
     161,    14,   160,    24,     0,    69
};

static const yytype_int16 yycheck[] =
{
      32,    45,    46,     5,     6,     3,    25,    11,     9,    10,
      34,    15,    56,    39,    18,    19,    55,    56,    22,     7,
       8,    49,    66,    47,    43,     0,    52,    71,    39,    73,
      49,    50,    51,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    49,    47,    23,    24,    28,
      89,    90,     4,    92,    23,    24,    23,    24,    40,    40,
      39,    27,    28,    29,    30,    31,    32,    33,    44,    35,
      36,    37,    38,     9,    10,    44,     6,    44,    44,   123,
      35,    36,    37,    38,    35,    36,    37,    38,    45,    35,
      36,    37,    38,    48,    43,    37,    38,    48,    44,    39,
      49,    50,    51,    35,    36,    37,    38,    39,   140,   141,
      49,    49,    43,   145,    42,    40,    40,    27,    28,    29,
      30,    31,    32,    33,   156,    35,    36,    37,    38,    35,
      36,    37,    38,    39,    35,    36,    37,    38,    39,    35,
      36,    37,    38,    39,    35,    36,    37,    38,    16,    49,
      43,    43,    46,    42,    19,    43,    28,    52,    39,    49,
      47,    44,    41,    12,    50,    39,    50,    49,    34,    24,
      40,    44,    20,    48,    45,    39,    45,    39,    17,    13,
      21,    39,    45,    50,    14,    46,    46,    46,    45,    39,
      46,     9,    39,    18,    -1,    49
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    54,    49,     0,    39,     5,     6,    55,    56,
      57,    40,    40,     4,    57,     7,     8,    58,    59,    45,
      39,    49,    60,    49,    58,    11,    15,    18,    19,    22,
      49,    63,    64,    65,    67,    71,    74,    61,    40,    40,
      43,    16,    49,    43,    43,    34,    47,    46,    63,    42,
       9,    10,    47,    62,    62,    25,    43,    49,    50,    51,
      66,    77,    43,    19,    49,    52,    43,    66,    66,    60,
      62,    28,    39,    28,    77,    66,    77,    47,    27,    28,
      29,    30,    31,    32,    33,    35,    36,    37,    38,    23,
      24,    44,    72,    50,    44,    41,    66,    39,    48,    39,
      66,    66,    44,    44,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    77,    77,    12,    77,
      75,    39,    49,    34,    50,    39,    39,    48,    40,    44,
      20,    44,    66,    48,    45,    45,    50,    39,    39,    39,
      68,    73,    45,    63,    63,    76,    46,    46,    63,    69,
      17,    46,    13,    70,    39,    21,    45,    14,    39,    63,
      39,    46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    57,    58,    58,    59,
      59,    59,    59,    60,    61,    60,    62,    62,    63,    63,
      64,    64,    64,    64,    64,    64,    65,    65,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    68,    69,    67,
      70,    70,    72,    73,    71,    75,    76,    74,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     2,     1,     3,     5,     2,     0,     5,
       7,     9,     7,     1,     0,     4,     1,     1,     2,     0,
       4,     7,     1,     1,     1,     1,     5,     7,     1,     1,
       1,     4,     3,     3,     3,     3,     3,     0,     0,    14,
       4,     0,     0,     0,    12,     0,     0,    13,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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
    YYNOMEM;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programme: BEGIN_PROJECT T_IDF SEMI contenu END_PROJECT SEMI  */
#line 62 "syntax.y"
                                                      { printf("\n>> Compilation terminee avec succes !\n"); }
#line 1271 "syntax.tab.c"
    break;

  case 9: /* declaration: DEFINE idfs COLON type SEMI  */
#line 87 "syntax.y"
                                {
        for(int i = 0; i < nb_idfs; i++) {
            if (est_declare(idf_tab[i])) {
                printf("Erreur Semantique, ligne %d, colonne %d : Double declaration de la variable '%s'\n", nb_ligne, col, idf_tab[i]);
            } else {
                inserer_type_nature(idf_tab[i], sauvType, "VAR", 0);
            }
        }
        nb_idfs = 0; /* Reset pour la prochaine ligne */
    }
#line 1286 "syntax.tab.c"
    break;

  case 10: /* declaration: DEFINE idfs COLON type EXPECT expression SEMI  */
#line 99 "syntax.y"
                                                    {
        if (nb_idfs != 1) {
            printf("Erreur Syntaxe, ligne %d, colonne %d : Initialisation non permise pour de multiples identifiants.\n", nb_ligne, col);
        } else {
            if (est_declare(idf_tab[0])) {
                printf("Erreur Semantique, ligne %d, colonne %d : Double declaration de '%s'\n", nb_ligne, col, idf_tab[0]);
            } else {
                inserer_type_nature(idf_tab[0], sauvType, "VAR", 0);
            }
        }
        nb_idfs = 0;
    }
#line 1303 "syntax.tab.c"
    break;

  case 11: /* declaration: DEFINE idfs COLON LBRACKET type SEMI T_ENTIER RBRACKET SEMI  */
#line 113 "syntax.y"
                                                                  {
        if (nb_idfs != 1) {
            printf("Erreur Syntaxe, ligne %d, colonne %d : Declaration de tableaux multiples non supportee.\n", nb_ligne, col);
        } else {
            if (est_declare(idf_tab[0])) {
                printf("Erreur Semantique, ligne %d, colonne %d : Double declaration du tableau '%s'\n", nb_ligne, col, idf_tab[0]);
            } else {
                if (atoi((yyvsp[-2].str)) <= 0) {
                    printf("Erreur Semantique, ligne %d, colonne %d : La taille du tableau '%s' doit etre > 0\n", nb_ligne, col, idf_tab[0]);
                } else {
                    inserer_type_nature(idf_tab[0], sauvType, "TAB", atoi((yyvsp[-2].str)));
                }
            }
        }
        nb_idfs = 0;
    }
#line 1324 "syntax.tab.c"
    break;

  case 12: /* declaration: CONST T_IDF COLON type EXPECT expression SEMI  */
#line 131 "syntax.y"
                                                    {
        if (est_declare((yyvsp[-5].str))) {
            printf("Erreur Semantique, ligne %d, colonne %d : Double declaration de la constante '%s'\n", nb_ligne, col, (yyvsp[-5].str));
        } else {
            inserer_type_nature((yyvsp[-5].str), sauvType, "CONST", 0);
        }
    }
#line 1336 "syntax.tab.c"
    break;

  case 13: /* idfs: T_IDF  */
#line 142 "syntax.y"
          { strcpy(idf_tab[nb_idfs++], (yyvsp[0].str)); }
#line 1342 "syntax.tab.c"
    break;

  case 14: /* $@1: %empty  */
#line 143 "syntax.y"
            { strcpy(idf_tab[nb_idfs++], (yyvsp[0].str)); }
#line 1348 "syntax.tab.c"
    break;

  case 16: /* type: INTEGER  */
#line 148 "syntax.y"
            { strcpy(sauvType, "integer"); }
#line 1354 "syntax.tab.c"
    break;

  case 17: /* type: FLOAT  */
#line 149 "syntax.y"
            { strcpy(sauvType, "float"); }
#line 1360 "syntax.tab.c"
    break;

  case 20: /* instruction: T_IDF COMP_AFFECT expression SEMI  */
#line 162 "syntax.y"
                                      {
        if (!est_declare((yyvsp[-3].str))) {
            printf("Erreur Semantique, ligne %d : Variable '%s' non declaree\n", nb_ligne, (yyvsp[-3].str));
        } else if (strcmp(get_nature((yyvsp[-3].str)), "VAR") != 0) {
            printf("Erreur Semantique, ligne %d : '%s' n'est pas une variable simple\n", nb_ligne, (yyvsp[-3].str));
        } else if (est_constante((yyvsp[-3].str))) {
            printf("Erreur Semantique, ligne %d : Modification de la constante '%s' interdite\n", nb_ligne, (yyvsp[-3].str));
        } else {
            // Génération du quadruplet d'affectation simple
            quadr("<-", (yyvsp[-1].str), "vide", (yyvsp[-3].str));
        }
    }
#line 1377 "syntax.tab.c"
    break;

  case 21: /* instruction: T_IDF LBRACKET expression RBRACKET COMP_AFFECT expression SEMI  */
#line 176 "syntax.y"
                                                                     {
        if (!est_declare((yyvsp[-6].str))) {
            printf("Erreur Semantique, ligne %d : Tableau '%s' non declare\n", nb_ligne, (yyvsp[-6].str));
        } else if (strcmp(get_nature((yyvsp[-6].str)), "TAB") != 0) {
            printf("Erreur Semantique, ligne %d : '%s' n'est pas un tableau\n", nb_ligne, (yyvsp[-6].str));
        } else {
            // Génération du quadruplet pour tableau
            char dest[50];
            sprintf(dest, "%s[%s]", (yyvsp[-6].str), (yyvsp[-4].str));
            quadr("<-", (yyvsp[-1].str), "vide", dest);
        }
    }
#line 1394 "syntax.tab.c"
    break;

  case 26: /* in_out: IN LPAREN T_IDF RPAREN SEMI  */
#line 195 "syntax.y"
                                {
        if (!est_declare((yyvsp[-2].str))) {
            printf("Erreur Semantique, ligne %d, colonne %d : Variable '%s' non declaree (Input)\n", nb_ligne, col, (yyvsp[-2].str));
        }
        quadr("IN", "vide", "vide", (yyvsp[-2].str));
    }
#line 1405 "syntax.tab.c"
    break;

  case 27: /* in_out: OUT LPAREN T_CHAINE COMMA T_IDF RPAREN SEMI  */
#line 201 "syntax.y"
                                                  {
        if (!est_declare((yyvsp[-2].str))) {
            printf("Erreur Semantique, ligne %d, colonne %d : Variable '%s' non declaree (Output)\n", nb_ligne, col, (yyvsp[-2].str));
        }
        quadr("OUT", (yyvsp[-4].str), "vide", (yyvsp[-2].str));
    }
#line 1416 "syntax.tab.c"
    break;

  case 28: /* expression: T_ENTIER  */
#line 213 "syntax.y"
             { 
        (yyval.str) = strdup((yyvsp[0].str)); // On transmet la valeur brute (ex: "5")
    }
#line 1424 "syntax.tab.c"
    break;

  case 29: /* expression: T_FLOAT  */
#line 216 "syntax.y"
              { 
        (yyval.str) = strdup((yyvsp[0].str)); 
    }
#line 1432 "syntax.tab.c"
    break;

  case 30: /* expression: T_IDF  */
#line 219 "syntax.y"
            {
        if (!est_declare((yyvsp[0].str))) {
            printf("Erreur Semantique, ligne %d : '%s' non declaree\n", nb_ligne, (yyvsp[0].str));
        }
        (yyval.str) = strdup((yyvsp[0].str)); // On transmet le nom de l'IDF
    }
#line 1443 "syntax.tab.c"
    break;

  case 31: /* expression: T_IDF LBRACKET expression RBRACKET  */
#line 226 "syntax.y"
                                         {
        if (!est_declare((yyvsp[-3].str))) {
            printf("Erreur Semantique : %s non declare\n", (yyvsp[-3].str));
        } else if (strcmp(get_nature((yyvsp[-3].str)), "TAB") != 0) {
            printf("Erreur Semantique : %s n'est pas un tableau\n", (yyvsp[-3].str));
        } else {
            // Création du temporaire
            sprintf(temp_nom, "t%d", nb_temp++);
            
            // Génération : (= [], NomTableau, Indice, Temporaire)
            char src[50];
            sprintf(src, "%s[%s]", (yyvsp[-3].str), (yyvsp[-1].str));
            quadr("=", src, "vide", temp_nom);
            
            // On remonte le nom du temporaire vers le parent
            (yyval.str) = strdup(temp_nom);
        }
    }
#line 1466 "syntax.tab.c"
    break;

  case 32: /* expression: expression PLUS expression  */
#line 245 "syntax.y"
                                 {
        sprintf(temp_nom, "t%d", nb_temp++);
        quadr("+", (yyvsp[-2].str), (yyvsp[0].str), temp_nom);
        (yyval.str) = strdup(temp_nom);
    }
#line 1476 "syntax.tab.c"
    break;

  case 33: /* expression: expression MINUS expression  */
#line 250 "syntax.y"
                                  {
        sprintf(temp_nom, "t%d", nb_temp++);
        quadr("-", (yyvsp[-2].str), (yyvsp[0].str), temp_nom);
        (yyval.str) = strdup(temp_nom);
    }
#line 1486 "syntax.tab.c"
    break;

  case 34: /* expression: expression MULT expression  */
#line 255 "syntax.y"
                                 {
        sprintf(temp_nom, "t%d", nb_temp++);
        quadr("*", (yyvsp[-2].str), (yyvsp[0].str), temp_nom);
        (yyval.str) = strdup(temp_nom);
    }
#line 1496 "syntax.tab.c"
    break;

  case 35: /* expression: expression DIV expression  */
#line 260 "syntax.y"
                                {
        sprintf(temp_nom, "t%d", nb_temp++);
        quadr("/", (yyvsp[-2].str), (yyvsp[0].str), temp_nom);
        (yyval.str) = strdup(temp_nom);
    }
#line 1506 "syntax.tab.c"
    break;

  case 36: /* expression: LPAREN expression RPAREN  */
#line 265 "syntax.y"
                               {
        (yyval.str) = strdup((yyvsp[-1].str));
    }
#line 1514 "syntax.tab.c"
    break;

  case 37: /* @2: %empty  */
#line 273 "syntax.y"
                                                 {
        (yyval.entier) = qc;
        quadr("BZ", "vide", (yyvsp[-4].str), "vide");
    }
#line 1523 "syntax.tab.c"
    break;

  case 38: /* @3: %empty  */
#line 276 "syntax.y"
                          {
        (yyval.entier) = qc;
        quadr("BR", "vide", "vide", "vide");
        sprintf(tmp, "%d", qc);
        updateQuad((yyvsp[-2].entier), 3, tmp);
    }
#line 1534 "syntax.tab.c"
    break;

  case 39: /* construct_if: IF LPAREN condition RPAREN THEN COLON LBRACE @2 instructions RBRACE @3 else_block ENDIF SEMI  */
#line 281 "syntax.y"
                            {
        sprintf(tmp, "%d", qc);
        updateQuad((yyvsp[-3].entier), 3, tmp);
    }
#line 1543 "syntax.tab.c"
    break;

  case 42: /* @4: %empty  */
#line 293 "syntax.y"
                      { 
        (yyval.entier) = qc; /* $4: Sauvegarde de la position de la condition */
    }
#line 1551 "syntax.tab.c"
    break;

  case 43: /* @5: %empty  */
#line 295 "syntax.y"
                              {
        (yyval.entier) = qc; /* $8: Sauvegarde de la position du BZ */
        quadr("BZ", "vide", (yyvsp[-2].str), "vide"); /* Saut si condition fausse */
    }
#line 1560 "syntax.tab.c"
    break;

  case 44: /* construct_while: LOOP WHILE LPAREN @4 condition RPAREN LBRACE @5 instructions RBRACE ENDLOOP SEMI  */
#line 298 "syntax.y"
                                       {
        /* Fin de la boucle, remonter à la condition */
        sprintf(tmp, "%d", (yyvsp[-8].entier));
        quadr("BR", "vide", "vide", tmp);
        
        /* Mettre à jour le BZ pour pointer APRES la boucle */
        sprintf(tmp, "%d", qc);
        updateQuad((yyvsp[-4].entier), 3, tmp);
    }
#line 1574 "syntax.tab.c"
    break;

  case 45: /* @6: %empty  */
#line 310 "syntax.y"
                          {
        if (!est_declare((yyvsp[-2].str))) {
            printf("Erreur Semantique, ligne %d, colonne %d : Variable de boucle '%s' non declaree\n", nb_ligne, col, (yyvsp[-2].str));
        } else {
            /* 1. Initialisation : iterateur <- T_ENTIER (début) */
            char valDebut[20];
            strcpy(valDebut, (yyvsp[0].str));
            quadr("<-", valDebut, "vide", (yyvsp[-2].str));
            strcpy(iter_for, (yyvsp[-2].str)); /* On sauvegarde le nom de la variable pour l'incrémentation */
        }
        (yyval.entier) = qc; /* $5: Début de condition */
        
    }
#line 1592 "syntax.tab.c"
    break;

  case 46: /* @7: %empty  */
#line 322 "syntax.y"
                         {
        /* 2. Condition : iterateur <= T_ENTIER (fin) */
        char valFin[20];
        strcpy(valFin, (yyvsp[-1].str));
        sprintf(temp_nom, "t%d", nb_temp++);     
        quadr("<=", iter_for, valFin, temp_nom);
        
        (yyval.entier) = qc; /* $9: Position du BZ */
        quadr("BZ", "vide", temp_nom, "vide"); /* Sortir si faux */
        
    }
#line 1608 "syntax.tab.c"
    break;

  case 47: /* construct_for: FOR T_IDF IN T_ENTIER @6 TO T_ENTIER LBRACE @7 instructions RBRACE ENDFOR SEMI  */
#line 332 "syntax.y"
                                      {
        /* 3. Incrémentation : iter_for <- iter_for + 1 */
        sprintf(temp_nom, "t%d", nb_temp++);
        quadr("+", iter_for, "1", temp_nom);
        quadr("<-", temp_nom, "vide", iter_for);
        
        /* 4. Remonter à l'évaluation de la condition */
        sprintf(tmp, "%d", (yyvsp[-8].entier));
        quadr("BR", "vide", "vide", tmp);
        
        /* 5. Mettre à jour le BZ pour sortir complètement de la boucle */
        sprintf(tmp, "%d", qc);
        updateQuad((yyvsp[-4].entier), 3, tmp);
    }
#line 1627 "syntax.tab.c"
    break;

  case 48: /* condition: expression EXPECT expression  */
#line 348 "syntax.y"
                                 { sprintf(temp_nom, "t%d", nb_temp++); quadr("=", (yyvsp[-2].str), (yyvsp[0].str), temp_nom); (yyval.str) = strdup(temp_nom); }
#line 1633 "syntax.tab.c"
    break;

  case 49: /* condition: expression COMP_EQ expression  */
#line 349 "syntax.y"
                                    { sprintf(temp_nom, "t%d", nb_temp++); quadr("==", (yyvsp[-2].str), (yyvsp[0].str), temp_nom); (yyval.str) = strdup(temp_nom); }
#line 1639 "syntax.tab.c"
    break;

  case 50: /* condition: expression COMP_NEQ expression  */
#line 350 "syntax.y"
                                     { sprintf(temp_nom, "t%d", nb_temp++); quadr("!=", (yyvsp[-2].str), (yyvsp[0].str), temp_nom); (yyval.str) = strdup(temp_nom); }
#line 1645 "syntax.tab.c"
    break;

  case 51: /* condition: expression COMP_GT expression  */
#line 351 "syntax.y"
                                    { sprintf(temp_nom, "t%d", nb_temp++); quadr(">", (yyvsp[-2].str), (yyvsp[0].str), temp_nom); (yyval.str) = strdup(temp_nom); }
#line 1651 "syntax.tab.c"
    break;

  case 52: /* condition: expression COMP_LT expression  */
#line 352 "syntax.y"
                                    { sprintf(temp_nom, "t%d", nb_temp++); quadr("<", (yyvsp[-2].str), (yyvsp[0].str), temp_nom); (yyval.str) = strdup(temp_nom); }
#line 1657 "syntax.tab.c"
    break;

  case 53: /* condition: expression COMP_GE expression  */
#line 353 "syntax.y"
                                    { sprintf(temp_nom, "t%d", nb_temp++); quadr(">=", (yyvsp[-2].str), (yyvsp[0].str), temp_nom); (yyval.str) = strdup(temp_nom); }
#line 1663 "syntax.tab.c"
    break;

  case 54: /* condition: expression COMP_LE expression  */
#line 354 "syntax.y"
                                    { sprintf(temp_nom, "t%d", nb_temp++); quadr("<=", (yyvsp[-2].str), (yyvsp[0].str), temp_nom); (yyval.str) = strdup(temp_nom); }
#line 1669 "syntax.tab.c"
    break;

  case 55: /* condition: condition AND condition  */
#line 355 "syntax.y"
                              { sprintf(temp_nom, "t%d", nb_temp++); quadr("AND", (yyvsp[-2].str), (yyvsp[0].str), temp_nom); (yyval.str) = strdup(temp_nom); }
#line 1675 "syntax.tab.c"
    break;

  case 56: /* condition: condition OR condition  */
#line 356 "syntax.y"
                             { sprintf(temp_nom, "t%d", nb_temp++); quadr("OR", (yyvsp[-2].str), (yyvsp[0].str), temp_nom); (yyval.str) = strdup(temp_nom); }
#line 1681 "syntax.tab.c"
    break;

  case 57: /* condition: NON condition  */
#line 357 "syntax.y"
                    { sprintf(temp_nom, "t%d", nb_temp++); quadr("NOT", (yyvsp[0].str), "vide", temp_nom); (yyval.str) = strdup(temp_nom); }
#line 1687 "syntax.tab.c"
    break;

  case 58: /* condition: LPAREN condition RPAREN  */
#line 358 "syntax.y"
                              { (yyval.str) = strdup((yyvsp[-1].str)); }
#line 1693 "syntax.tab.c"
    break;


#line 1697 "syntax.tab.c"

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
      yyerror (YY_("syntax error"));
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
          yydestruct ("Error: discarding",
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 361 "syntax.y"


void yyerror(const char *s) {
    fprintf(stderr, "Erreur syntaxique, ligne %d, colonne %d\n", nb_ligne, col);
}

int main(void) {
    initialization();
    
    // yyparse() returns 0 on success, 1 on syntax error
    if (yyparse() == 0) {
        afficher();
        afficher_qdr();
    } else {
        printf("\n>> Echec de la compilation : tables et quadruplets non generes.\n");
    }
    
    return 0;
}

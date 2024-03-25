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
#line 1 "parse.y"

//display栈、符号表栈、代码地址栈、循环栈、程序栈
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userdef.h"
#define stack_size 128


char infile[32];
char *outfile;
FILE *fin;
FILE *fout;
extern FILE * yyin;
extern FILE * yyout;


int code_line=1;                                                    /*记录代码行数*/
extern varIndex strMem[256];
int error_cnt = 0;

int iMaxIndex=0;  
int iCurIndex=0;  
int yylex(void);
void yyerror(char *);

FILE *CodeOutput;                                                   /*code输出文件指针*/
int total_line=0;                                                   /*pcode总的行数*/
int cur_layer = 1;                                                  /*现在的层数*/
int code_address_stack[stack_size];                                 /*记录代码地址的栈*/
int code_address_stack_point=0;                                     /*代码地址栈顶*/
int loop_stack[stack_size];                                         /*用于循环的栈*/
int loop_stack_point = 0;                                           /*循环栈顶*/

struct code_struct *mycode;                                         /*存储翻译之后的代码*/
struct sign *sign_stack;                                            /*标志（符号）栈*/
int sign_top = 0;                                                   /*标志栈顶*/

int display_stack[stack_size];                                      /*display栈*/
int display_top = 0;                                                /*display的栈顶*/

struct procedure_pos * procedure_position;                          /*过程位置*/
int pro_ct = 0;                                                     /*记录过程的个数*/
int procedure_stack[stack_size];                                            /*过程栈*/
int procedure_stack_point = 0;                                      /*过程栈顶*/
int cur_pro_ct=0;                                                   /*现在过程的代号*/

void PushProcedurePosition(char *c,int p);                          /*将程序的位置记录在procedure_position中*/
int FindProcedurePosition(char *s);                                 /*找到过程位置*/
int CheckSignIsDeclare(char *tag_name);                             /*看定义的标识符之前有没有定义过*/
int FindSign(char *tag_name);                                       /*找sign是否存在*/
void PopSignStack();                                                /*将所有的sign退栈，并且display中最上面的程序也需要退出来*/
void PushSignStack(char *s,int t);                                  /*将s加入sign栈中*/
void AddPcode(int thef, int thel, int thea);                        /*添加类PCODE代码*/
void ChangePcode(int theline, int thef, int thel, int thea);        /*将第theline行代码改为所指的*/
int CaculateA(int pos_flag);                                        /*计算偏移量a*/
void PrintPcode(struct code_struct ToPrint);                        /*按照类PCODE输出代码*/
int cmp(const void *a ,const void *b);                              /*排序函数*/


#line 132 "parse.tab.c"

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

#include "parse.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_THEN = 4,                       /* THEN  */
  YYSYMBOL_WHILE = 5,                      /* WHILE  */
  YYSYMBOL_DO = 6,                         /* DO  */
  YYSYMBOL_READ = 7,                       /* READ  */
  YYSYMBOL_WRITE = 8,                      /* WRITE  */
  YYSYMBOL_CALL = 9,                       /* CALL  */
  YYSYMBOL_BEGINN = 10,                    /* BEGINN  */
  YYSYMBOL_END = 11,                       /* END  */
  YYSYMBOL_CONST = 12,                     /* CONST  */
  YYSYMBOL_VAR = 13,                       /* VAR  */
  YYSYMBOL_PROCEDURE = 14,                 /* PROCEDURE  */
  YYSYMBOL_ODD = 15,                       /* ODD  */
  YYSYMBOL_FOR = 16,                       /* FOR  */
  YYSYMBOL_TO = 17,                        /* TO  */
  YYSYMBOL_DOWNTO = 18,                    /* DOWNTO  */
  YYSYMBOL_IDENTIFIER = 19,                /* IDENTIFIER  */
  YYSYMBOL_NUMBER = 20,                    /* NUMBER  */
  YYSYMBOL_ASSIGNMENT = 21,                /* ASSIGNMENT  */
  YYSYMBOL_22_ = 22,                       /* "<="  */
  YYSYMBOL_23_ = 23,                       /* ">="  */
  YYSYMBOL_24_ = 24,                       /* '>'  */
  YYSYMBOL_25_ = 25,                       /* '<'  */
  YYSYMBOL_26_ = 26,                       /* '='  */
  YYSYMBOL_27_ = 27,                       /* '#'  */
  YYSYMBOL_28_ = 28,                       /* '+'  */
  YYSYMBOL_29_ = 29,                       /* '-'  */
  YYSYMBOL_30_ = 30,                       /* '*'  */
  YYSYMBOL_31_ = 31,                       /* '/'  */
  YYSYMBOL_32_ = 32,                       /* '('  */
  YYSYMBOL_33_ = 33,                       /* ')'  */
  YYSYMBOL_34_ = 34,                       /* '.'  */
  YYSYMBOL_35_ = 35,                       /* ';'  */
  YYSYMBOL_36_ = 36,                       /* ','  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_program = 38,                   /* program  */
  YYSYMBOL_39_1 = 39,                      /* $@1  */
  YYSYMBOL_subprogram = 40,                /* subprogram  */
  YYSYMBOL_41_2 = 41,                      /* $@2  */
  YYSYMBOL_constInstruction = 42,          /* constInstruction  */
  YYSYMBOL_constDeclaration = 43,          /* constDeclaration  */
  YYSYMBOL_44_3 = 44,                      /* $@3  */
  YYSYMBOL_variableInstruction = 45,       /* variableInstruction  */
  YYSYMBOL_46_4 = 46,                      /* $@4  */
  YYSYMBOL_variableDeclaration = 47,       /* variableDeclaration  */
  YYSYMBOL_48_5 = 48,                      /* $@5  */
  YYSYMBOL_procedureInstruction = 49,      /* procedureInstruction  */
  YYSYMBOL_50_6 = 50,                      /* $@6  */
  YYSYMBOL_procedureHeader = 51,           /* procedureHeader  */
  YYSYMBOL_sentence = 52,                  /* sentence  */
  YYSYMBOL_assignmentSentence = 53,        /* assignmentSentence  */
  YYSYMBOL_54_7 = 54,                      /* $@7  */
  YYSYMBOL_multiSentence = 55,             /* multiSentence  */
  YYSYMBOL_compoundSentence = 56,          /* compoundSentence  */
  YYSYMBOL_condition = 57,                 /* condition  */
  YYSYMBOL_conditionSentence = 58,         /* conditionSentence  */
  YYSYMBOL_59_8 = 59,                      /* $@8  */
  YYSYMBOL_whileLoop = 60,                 /* whileLoop  */
  YYSYMBOL_61_9 = 61,                      /* $@9  */
  YYSYMBOL_62_10 = 62,                     /* $@10  */
  YYSYMBOL_procedureCall = 63,             /* procedureCall  */
  YYSYMBOL_forLoop = 64,                   /* forLoop  */
  YYSYMBOL_65_11 = 65,                     /* $@11  */
  YYSYMBOL_66_12 = 66,                     /* $@12  */
  YYSYMBOL_67_13 = 67,                     /* $@13  */
  YYSYMBOL_68_14 = 68,                     /* $@14  */
  YYSYMBOL_readPara = 69,                  /* readPara  */
  YYSYMBOL_70_15 = 70,                     /* $@15  */
  YYSYMBOL_writePara = 71,                 /* writePara  */
  YYSYMBOL_72_16 = 72,                     /* $@16  */
  YYSYMBOL_readSentence = 73,              /* readSentence  */
  YYSYMBOL_writeSentence = 74,             /* writeSentence  */
  YYSYMBOL_expression = 75,                /* expression  */
  YYSYMBOL_76_17 = 76,                     /* $@17  */
  YYSYMBOL_77_18 = 77,                     /* $@18  */
  YYSYMBOL_item = 78,                      /* item  */
  YYSYMBOL_factor = 79,                    /* factor  */
  YYSYMBOL_addItem = 80,                   /* addItem  */
  YYSYMBOL_81_19 = 81,                     /* $@19  */
  YYSYMBOL_mulItem = 82,                   /* mulItem  */
  YYSYMBOL_plusOp = 83,                    /* plusOp  */
  YYSYMBOL_mulOp = 84,                     /* mulOp  */
  YYSYMBOL_relationOp = 85                 /* relationOp  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   111

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   278


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
       2,     2,     2,     2,     2,    27,     2,     2,     2,     2,
      32,    33,    30,    28,    36,    29,    34,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    35,
      25,    26,    24,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    75,    75,    75,    95,    92,   106,   107,   112,   117,
     117,   127,   126,   134,   140,   139,   147,   152,   151,   161,
     166,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     197,   197,   215,   216,   218,   223,   224,   228,   228,   242,
     246,   242,   264,   282,   296,   281,   320,   334,   319,   362,
     374,   374,   390,   394,   394,   402,   405,   410,   413,   410,
     417,   421,   426,   439,   442,   447,   446,   449,   453,   454,
     458,   459,   462,   463,   467,   468,   469,   470,   471,   472
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
  "\"end of file\"", "error", "\"invalid token\"", "IF", "THEN", "WHILE",
  "DO", "READ", "WRITE", "CALL", "BEGINN", "END", "CONST", "VAR",
  "PROCEDURE", "ODD", "FOR", "TO", "DOWNTO", "IDENTIFIER", "NUMBER",
  "ASSIGNMENT", "\"<=\"", "\">=\"", "'>'", "'<'", "'='", "'#'", "'+'",
  "'-'", "'*'", "'/'", "'('", "')'", "'.'", "';'", "','", "$accept",
  "program", "$@1", "subprogram", "$@2", "constInstruction",
  "constDeclaration", "$@3", "variableInstruction", "$@4",
  "variableDeclaration", "$@5", "procedureInstruction", "$@6",
  "procedureHeader", "sentence", "assignmentSentence", "$@7",
  "multiSentence", "compoundSentence", "condition", "conditionSentence",
  "$@8", "whileLoop", "$@9", "$@10", "procedureCall", "forLoop", "$@11",
  "$@12", "$@13", "$@14", "readPara", "$@15", "writePara", "$@16",
  "readSentence", "writeSentence", "expression", "$@17", "$@18", "item",
  "factor", "addItem", "$@19", "mulItem", "plusOp", "mulOp", "relationOp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-69)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-54)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -69,    13,     3,   -69,    10,    -3,    20,    23,     1,    50,
      32,    38,    33,   -69,   -69,   -69,    35,   -69,     3,    19,
      21,    26,    18,    27,    22,    37,    28,   -69,   -12,   -69,
      34,    36,    45,    18,    46,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,    10,   -69,   -69,   -10,
     -69,   -69,   -69,   -69,   -10,   -69,    16,   -24,    14,   -69,
     -12,    48,   -10,   -69,    39,    58,    51,    52,    38,   -69,
      21,   -69,    42,    67,   -69,   -69,   -69,   -69,   -69,   -69,
     -10,   -69,    -8,   -69,   -69,   -69,    -8,    -8,   -69,    40,
      44,    47,    43,    18,   -69,    61,   -10,   -69,   -69,   -69,
      18,   -69,   -69,   -69,   -69,    76,    49,   -69,   -69,    53,
     -69,    65,   -69,   -69,   -24,   -24,    18,    48,   -10,    69,
      66,   -69,   -69,   -69,   -69,   -69,    68,    70,   -69,   -69,
      81,    85,    18,    18,   -69,   -69
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     7,     1,     0,     0,    13,     0,     0,     0,
       0,    19,     0,     6,     3,    11,     0,     4,     7,     8,
      16,     0,    29,     0,     0,     0,     0,    20,     0,    39,
       0,     0,     0,    29,     0,    30,     5,    21,    22,    23,
      24,    25,    28,    26,    27,    17,     0,    14,    12,     0,
      62,    63,    70,    71,     0,    37,     0,    67,    69,    57,
       0,     0,     0,    42,    33,     0,     0,     0,    19,    10,
      16,    36,     0,     0,    77,    79,    78,    76,    74,    75,
       0,    60,     0,    72,    73,    61,     0,     0,    40,    49,
       0,     0,    52,    29,    34,     0,     0,    18,    15,    64,
      29,    35,    65,    68,    58,     0,     0,    55,    56,     0,
      32,    43,    31,    38,    67,    67,    29,     0,     0,     0,
       0,    66,    59,    41,    51,    54,     0,     0,    44,    47,
       0,     0,    29,    29,    45,    48
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -69,   -69,   -69,    74,   -69,   -69,    54,   -69,   -69,   -69,
      25,   -69,    29,   -69,   -69,   -22,   -69,   -69,     0,   -69,
      41,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -21,   -69,   -20,   -69,   -69,   -69,   -48,   -69,
     -69,   -52,    17,   -68,   -69,   -69,   -55,   -69,   -69
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     5,    22,     6,     8,    24,    11,    20,
      26,    70,    17,    68,    18,    64,    37,    67,    65,    38,
      55,    39,    73,    40,    60,   105,    41,    42,   119,   130,
     120,   131,    90,   106,    91,   109,    43,    44,    56,    87,
     115,    57,    58,    81,   114,    85,    59,    86,    80
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      36,    71,    82,    49,    52,    53,    72,    50,    51,    50,
      51,    50,    51,     3,    92,     4,    52,    53,    52,    53,
      54,    28,    54,    29,    54,    30,    31,    32,    33,     7,
     102,     9,   101,    10,    34,   104,    13,    35,    74,    75,
      76,    77,    78,    79,    83,    84,   121,   122,   112,    12,
      14,    15,    16,    19,    21,    -9,    47,    25,    46,    82,
      82,    27,    45,    48,    63,    66,    61,    89,    62,    94,
      92,   100,    95,    96,    93,    99,   -50,   107,   113,   -53,
     108,   111,   116,   -46,   127,   117,   126,   132,   128,   118,
     129,   133,    23,   110,   123,    98,   124,    97,   125,     0,
      69,    88,     0,   103,     0,     0,     0,     0,     0,     0,
     134,   135
};

static const yytype_int16 yycheck[] =
{
      22,    49,    57,    15,    28,    29,    54,    19,    20,    19,
      20,    19,    20,     0,    62,    12,    28,    29,    28,    29,
      32,     3,    32,     5,    32,     7,     8,     9,    10,    19,
      82,    34,    80,    13,    16,    87,    35,    19,    22,    23,
      24,    25,    26,    27,    30,    31,   114,   115,    96,    26,
       0,    19,    14,    20,    19,    36,    19,    36,    36,   114,
     115,    35,    35,    35,    19,    19,    32,    19,    32,    11,
     118,     4,    21,    21,    35,    33,    36,    33,   100,    36,
      33,    20,     6,    18,    18,    36,    17,     6,    20,    36,
      20,     6,    18,    93,   116,    70,   117,    68,   118,    -1,
      46,    60,    -1,    86,    -1,    -1,    -1,    -1,    -1,    -1,
     132,   133
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    38,    39,     0,    12,    40,    42,    19,    43,    34,
      13,    45,    26,    35,     0,    19,    14,    49,    51,    20,
      46,    19,    41,    40,    44,    36,    47,    35,     3,     5,
       7,     8,     9,    10,    16,    19,    52,    53,    56,    58,
      60,    63,    64,    73,    74,    35,    36,    19,    35,    15,
      19,    20,    28,    29,    32,    57,    75,    78,    79,    83,
      61,    32,    32,    19,    52,    55,    19,    54,    50,    43,
      48,    75,    75,    59,    22,    23,    24,    25,    26,    27,
      85,    80,    83,    30,    31,    82,    84,    76,    57,    19,
      69,    71,    75,    35,    11,    21,    21,    49,    47,    33,
       4,    75,    78,    79,    78,    62,    70,    33,    33,    72,
      55,    20,    75,    52,    81,    77,     6,    36,    36,    65,
      67,    80,    80,    52,    69,    71,    17,    18,    20,    20,
      66,    68,     6,     6,    52,    52
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    39,    38,    41,    40,    42,    42,    43,    44,
      43,    46,    45,    45,    48,    47,    47,    50,    49,    49,
      51,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      54,    53,    55,    55,    56,    57,    57,    59,    58,    61,
      62,    60,    63,    65,    66,    64,    67,    68,    64,    69,
      70,    69,    71,    72,    71,    73,    74,    76,    77,    75,
      75,    78,    79,    79,    79,    81,    80,    80,    82,    82,
      83,    83,    84,    84,    85,    85,    85,    85,    85,    85
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     4,     0,     5,     3,     0,     3,     0,
       6,     0,     5,     0,     0,     4,     0,     0,     5,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       0,     4,     3,     1,     3,     3,     2,     0,     5,     0,
       0,     6,     2,     0,     0,    10,     0,     0,    10,     1,
       0,     4,     1,     0,     4,     4,     4,     0,     0,     5,
       2,     2,     1,     1,     3,     0,     4,     0,     2,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
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

  if (yychar <= ENDD)
    {
      yychar = ENDD;
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
  case 2: /* $@1: %empty  */
#line 75 "parse.y"
                    {
                    display_top++; 
                    display_stack[display_top] = 1; 
                    PushProcedurePosition("program",0); //改变procedure_position
                    cur_pro_ct = pro_ct-1; 
                    procedure_stack[procedure_stack_point] = pro_ct-1; 
                    procedure_stack_point++;
                    }
#line 1301 "parse.tab.c"
    break;

  case 3: /* program: $@1 subprogram '.' "end of file"  */
#line 84 "parse.y"
                    {
                    printf("\nSuccessfully Compiled\n0 error(s) 0 warning(s)\n"); 
                    AddPcode(8,0,0);
                    }
#line 1310 "parse.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 95 "parse.y"
                {
                procedure_position[cur_pro_ct].pos = total_line; //记录程序的位置
                AddPcode(5,0,3+procedure_position[cur_pro_ct].var_number);
                }
#line 1319 "parse.tab.c"
    break;

  case 8: /* constDeclaration: IDENTIFIER '=' NUMBER  */
#line 112 "parse.y"
                                {
                                if(CheckSignIsDeclare(strMem[yyvsp[-2]].sMark) == 1){
                                    PushSignStack(strMem[yyvsp[-2]].sMark,yyvsp[0]);
                                }
                                }
#line 1329 "parse.tab.c"
    break;

  case 9: /* $@3: %empty  */
#line 117 "parse.y"
                                {
                                if(CheckSignIsDeclare(strMem[yyvsp[-2]].sMark) == 1){
                                    PushSignStack(strMem[yyvsp[-2]].sMark,yyvsp[0]);
                                }
                                }
#line 1339 "parse.tab.c"
    break;

  case 11: /* $@4: %empty  */
#line 127 "parse.y"
                    {
                    if(CheckSignIsDeclare(strMem[yyvsp[0]].sMark) == 1){
                        PushSignStack(strMem[yyvsp[0]].sMark,-1);
                        procedure_position[cur_pro_ct].var_number++;//当前程序变量数目+1
                    } 
                    }
#line 1350 "parse.tab.c"
    break;

  case 14: /* $@5: %empty  */
#line 140 "parse.y"
                    {
                    if(CheckSignIsDeclare(strMem[yyvsp[0]].sMark) == 1){
                        PushSignStack(strMem[yyvsp[0]].sMark,-1);
                        procedure_position[cur_pro_ct].var_number++;//当前程序变量数目+1
                    } 
                    }
#line 1361 "parse.tab.c"
    break;

  case 17: /* $@6: %empty  */
#line 152 "parse.y"
            {
            cur_layer--; /*程序结束后退栈*/
            procedure_stack_point--;  /*指向的是过程栈的顶，没东西，因此要--*/
            cur_pro_ct = procedure_stack[procedure_stack_point-1]; /*获得退栈后所在过程的编号，因此[]中要-1*/
            procedure_stack[procedure_stack_point] = -1; /*清空栈*/
            PopSignStack(); /*把该过程的ID清空*/
            AddPcode(8,0,0); 
            }
#line 1374 "parse.tab.c"
    break;

  case 20: /* procedureHeader: PROCEDURE IDENTIFIER ';'  */
#line 167 "parse.y"
                {
                if(CheckSignIsDeclare(strMem[yyvsp[-1]].sMark) == 1){
                    PushSignStack(strMem[yyvsp[-1]].sMark,-2);
                    display_top++; 
                    display_stack[display_top] = sign_top+1; 
                    cur_layer++; 
                    PushProcedurePosition(strMem[yyvsp[-1]].sMark,total_line+1);//有pro_ct++
                    cur_pro_ct = pro_ct-1; /*在一个过程开始时，记录这个过程的编号*/
                    procedure_stack[procedure_stack_point] = pro_ct - 1; /*存下这个过程的编号，方便程序中用到procedure_position时直接访问该过程的信息*/
                    procedure_stack_point++; 
                }  
                }
#line 1391 "parse.tab.c"
    break;

  case 30: /* $@7: %empty  */
#line 197 "parse.y"
                    {
                    int pos_flag = FindSign(strMem[yyvsp[0]].sMark); //找sign是否存在，返回在sign_stack的位置
                    if(pos_flag > 0){ 
                        if(sign_stack[pos_flag].type != -1){//-1表示为var类型的标识符
                            printf("in line %d illegal name\n",code_line); 
                            exit(1);
                        }  
                    } 
                    }
#line 1405 "parse.tab.c"
    break;

  case 31: /* assignmentSentence: IDENTIFIER $@7 ASSIGNMENT expression  */
#line 207 "parse.y"
                    {
                    int pos_flag = FindSign(strMem[yyvsp[-3]].sMark); 
                    AddPcode(3,cur_layer-sign_stack[pos_flag].layer,CaculateA(pos_flag));/*STO l a*/
                    }
#line 1414 "parse.tab.c"
    break;

  case 35: /* condition: expression relationOp expression  */
#line 223 "parse.y"
                                           {AddPcode(8,0,yyvsp[-1]);}
#line 1420 "parse.tab.c"
    break;

  case 36: /* condition: ODD expression  */
#line 224 "parse.y"
                        {AddPcode(8,0,6);}
#line 1426 "parse.tab.c"
    break;

  case 37: /* $@8: %empty  */
#line 228 "parse.y"
                        {
                        AddPcode(7,0,-1); /*JPC，条件跳转，栈顶布尔值非真跳转到地址a，条件不满足时转*/
                        code_address_stack[code_address_stack_point] = total_line-1; /*记录条件判断的位置*/
                        code_address_stack_point++;  
                        }
#line 1436 "parse.tab.c"
    break;

  case 38: /* conditionSentence: IF condition $@8 THEN sentence  */
#line 233 "parse.y"
                       {/*条件满足*/
                        code_address_stack_point--;
                        int target_line = code_address_stack[code_address_stack_point]; 
                        code_address_stack[code_address_stack_point]  = -1; 
                        ChangePcode(target_line,7,0,total_line); /*此时的total_line表示的是if语句结束后的pcode代码的位置*/
                        }
#line 1447 "parse.tab.c"
    break;

  case 39: /* $@9: %empty  */
#line 242 "parse.y"
                    {
                    loop_stack[loop_stack_point] = total_line; /*记录JMP回来的位置*/
                    loop_stack_point++; 
                    }
#line 1456 "parse.tab.c"
    break;

  case 40: /* $@10: %empty  */
#line 246 "parse.y"
                    {  
                    AddPcode(7,0,-1); /*JPC 要跳转的地址还没有，先存为-1，后面有ChangePcode()*/
                    code_address_stack[code_address_stack_point] = total_line-1; /*记录条件判断的位置，方便后面ChangePcode找到要修改的位置*/
                    code_address_stack_point++; 
                    }
#line 1466 "parse.tab.c"
    break;

  case 41: /* whileLoop: WHILE $@9 condition $@10 DO sentence  */
#line 251 "parse.y"
                   { 
                    loop_stack_point--;  
                    AddPcode(6,0,loop_stack[loop_stack_point]); /*JMP 无条件跳转至a地址*/
                    loop_stack[loop_stack_point] = -1;  
                    code_address_stack_point--; 
                    int target_line = code_address_stack[code_address_stack_point]; 
                    ChangePcode(target_line,7,0,total_line); 
                    code_address_stack[code_address_stack_point]  = -1; 
                    }
#line 1480 "parse.tab.c"
    break;

  case 42: /* procedureCall: CALL IDENTIFIER  */
#line 264 "parse.y"
                        {
                        int pos_flag = FindSign(strMem[yyvsp[0]].sMark); 
                        if(pos_flag > 0){
                            if(sign_stack[pos_flag].type==-2 || sign_stack[pos_flag].type == -3){
                                int target_pos = FindProcedurePosition(strMem[yyvsp[0]].sMark); /*根据procedure的名字来找位置*/
                                AddPcode(4,cur_layer-sign_stack[pos_flag].layer,target_pos); /*CAL l a 调用过程 a为调用地址，l为层差*/
                            }else{
                                printf("error in line %d illegal name\n",code_line); exit(1);
                            }      
                        }  
                        }
#line 1496 "parse.tab.c"
    break;

  case 43: /* $@11: %empty  */
#line 282 "parse.y"
                            {
                            int pos_flag = FindSign(strMem[yyvsp[-2]].sMark); /*返回ID的地址*/
                            if(pos_flag > 0){ /*ID不存在，报错*/
                                if(sign_stack[pos_flag].type == -1){} /*ID为var类型*/
                                else{
                                    printf("error in line %d illegal input\n",code_line);
                                    exit(1);
                                }
                            } 
                            AddPcode(1,0,yyvsp[0]);/*LIT 0 a 把NUMBER的值取到栈顶*/
                            AddPcode(3,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); /*STO 0 a 把栈顶的值存到ID中*/
                            loop_stack[loop_stack_point] = total_line; /*loop_stack中存下循环入口指令的地址*/
                            loop_stack_point++; /*如果有多层循环，那么loop_stack中会有多层循环的入口地址*/
                            }
#line 1515 "parse.tab.c"
    break;

  case 44: /* $@12: %empty  */
#line 296 "parse.y"
                        { 
                        int pos_flag = FindSign(strMem[yyvsp[-5]].sMark); /*找到ID的地址*/
                        AddPcode(2,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); /*将变量值取到栈顶*/
                        AddPcode(1,0,yyvsp[0]);/*LIT*/
                        AddPcode(8,0,13);/*OPR < */
                        AddPcode(7,0,-1);/*JPC*/
                        code_address_stack[code_address_stack_point] = total_line-1; /*存着上条JPC的位置，方便后面ChangePcode修改地址，因为跳转的地址只有在循环结束后才能知道*/
                        code_address_stack_point++;  
                        }
#line 1529 "parse.tab.c"
    break;

  case 45: /* forLoop: FOR IDENTIFIER ASSIGNMENT NUMBER $@11 TO NUMBER $@12 DO sentence  */
#line 305 "parse.y"
                        { 
                        int pos_flag = FindSign(strMem[yyvsp[-8]].sMark);   
                        AddPcode(2,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); /*把ID的值取到栈顶*/
                        AddPcode(1,0,1);/*把常数1取到栈顶*/
                        AddPcode(8,0,2);/*模拟循环变量+1的操作*/
                        AddPcode(3,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag));  /*将+1后的值存到循环变量里*/
                        loop_stack_point--; /*前面有++，退一层，找到本层循环的入口地址*/
                        AddPcode(6,0,loop_stack[loop_stack_point]); /*JMP 0 a 无条件跳转至a地址（循环开始的位置）*/
                        loop_stack[loop_stack_point] = -1;  /*该层循环结束，清空栈*/
                        code_address_stack_point--;   
                        int target_line = code_address_stack[code_address_stack_point];  /*找到需要修改的代码的地址*/
                        ChangePcode(target_line,7,0,total_line);   /*修改地址*/
                        code_address_stack[code_address_stack_point]  = -1;  /*清空栈*/
                        }
#line 1548 "parse.tab.c"
    break;

  case 46: /* $@13: %empty  */
#line 320 "parse.y"
                            {
                            int pos_flag = FindSign(strMem[yyvsp[-2]].sMark); 
                            if(pos_flag>0){
                                if(sign_stack[pos_flag].type == -1){} 
                                else{
                                    printf("error in line %d illegal input\n",code_line);
                                    exit(1);
                                }
                            } 
                            AddPcode(1,0,yyvsp[0]);
                            AddPcode(3,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); 
                            loop_stack[loop_stack_point] = total_line; 
                            loop_stack_point++; 
                            }
#line 1567 "parse.tab.c"
    break;

  case 47: /* $@14: %empty  */
#line 334 "parse.y"
                            {  
                            int pos_flag = FindSign(strMem[yyvsp[-5]].sMark);  
                            AddPcode(2,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); 
                            AddPcode(1,0,yyvsp[0]); 
                            AddPcode(8,0,11);
                            AddPcode(7,0,-1);   
                            code_address_stack[code_address_stack_point] = total_line-1; 
                            code_address_stack_point++; 
                            }
#line 1581 "parse.tab.c"
    break;

  case 48: /* forLoop: FOR IDENTIFIER ASSIGNMENT NUMBER $@13 DOWNTO NUMBER $@14 DO sentence  */
#line 343 "parse.y"
                            { 
                            int pos_flag = FindSign(strMem[yyvsp[-8]].sMark);   
                            AddPcode(2,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag));   
                            AddPcode(1,0,1);AddPcode(8,0,3); 
                            AddPcode(3,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); 
                            loop_stack_point--; 
                            AddPcode(6,0,loop_stack[loop_stack_point]); 
                            loop_stack[loop_stack_point] = -1;  
                            code_address_stack_point--;  
                            int target_line = code_address_stack[code_address_stack_point]; 
                            ChangePcode(target_line,7,0,total_line);  
                            code_address_stack[code_address_stack_point]  = -1; 
                            }
#line 1599 "parse.tab.c"
    break;

  case 49: /* readPara: IDENTIFIER  */
#line 362 "parse.y"
                    {
                    int pos_flag = FindSign(strMem[yyvsp[0]].sMark);  
                    if(pos_flag>0){
                        if(sign_stack[pos_flag].type == -1){
                            AddPcode(8,0,16); /*从命令行读入一个并放入栈顶*/
                            AddPcode(3,cur_layer-sign_stack[pos_flag].layer,CaculateA(pos_flag));/*栈顶的值放入变量ID中*/
                        } else {
                            printf("error in line  %d  change a const parameter\n",code_line); 
                            exit(1);
                        }    
                    } 
                    }
#line 1616 "parse.tab.c"
    break;

  case 50: /* $@15: %empty  */
#line 374 "parse.y"
                    {
                    int pos_flag = FindSign(strMem[yyvsp[0]].sMark);  
                    if(pos_flag>0){
                        if(sign_stack[pos_flag].type == -1){
                            AddPcode(8,0,16); /*从命令行读入一个并放入栈顶*/
                            AddPcode(3,cur_layer-sign_stack[pos_flag].layer,CaculateA(pos_flag));/*栈顶的值放入变量ID中*/
                        } else {
                            printf("error in line  %d  change a const parameter\n",code_line); 
                            exit(1);
                        }    
                    } 
                    }
#line 1633 "parse.tab.c"
    break;

  case 52: /* writePara: expression  */
#line 390 "parse.y"
                    {
                    AddPcode(8,0,14);
                    AddPcode(8,0,15);
                    }
#line 1642 "parse.tab.c"
    break;

  case 53: /* $@16: %empty  */
#line 394 "parse.y"
                    {
                    AddPcode(8,0,14);
                    AddPcode(8,0,15);
                    }
#line 1651 "parse.tab.c"
    break;

  case 57: /* $@17: %empty  */
#line 410 "parse.y"
                {
                AddPcode(1,0,0);
                }
#line 1659 "parse.tab.c"
    break;

  case 58: /* $@18: %empty  */
#line 413 "parse.y"
                {
                AddPcode(8,0,yyvsp[-2]);
                }
#line 1667 "parse.tab.c"
    break;

  case 62: /* factor: IDENTIFIER  */
#line 426 "parse.y"
                    {
                    int pos_flag = FindSign(strMem[yyvsp[0]].sMark); 
                    if(pos_flag > 0) {
                        if(sign_stack[pos_flag].type == -1){
                            AddPcode(2,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag));  /*LOD var*/
                        } else if(sign_stack[pos_flag].type>=0){
                            AddPcode(1,0,sign_stack[pos_flag].type);/*LIT const*/
                        } else{
                            printf("error in line: %d  illegal name\n",code_line);
                            exit(1);
                        } 
                    }  
                    }
#line 1685 "parse.tab.c"
    break;

  case 63: /* factor: NUMBER  */
#line 439 "parse.y"
                  {
                        AddPcode(1,0,yyvsp[0]); 
                        }
#line 1693 "parse.tab.c"
    break;

  case 65: /* $@19: %empty  */
#line 447 "parse.y"
             {AddPcode(8,0,yyvsp[-1]);}
#line 1699 "parse.tab.c"
    break;

  case 68: /* mulItem: mulOp factor  */
#line 453 "parse.y"
                     {AddPcode(8,0,yyvsp[-1]);}
#line 1705 "parse.tab.c"
    break;

  case 70: /* plusOp: '+'  */
#line 458 "parse.y"
            {yyval = 2; }
#line 1711 "parse.tab.c"
    break;

  case 71: /* plusOp: '-'  */
#line 459 "parse.y"
            {yyval = 3; }
#line 1717 "parse.tab.c"
    break;

  case 72: /* mulOp: '*'  */
#line 462 "parse.y"
            {yyval = 4; }
#line 1723 "parse.tab.c"
    break;

  case 73: /* mulOp: '/'  */
#line 463 "parse.y"
            {yyval = 5; }
#line 1729 "parse.tab.c"
    break;

  case 74: /* relationOp: '='  */
#line 467 "parse.y"
            {yyval = 8; }
#line 1735 "parse.tab.c"
    break;

  case 75: /* relationOp: '#'  */
#line 468 "parse.y"
            {yyval = 9; }
#line 1741 "parse.tab.c"
    break;

  case 76: /* relationOp: '<'  */
#line 469 "parse.y"
            {yyval = 10; }
#line 1747 "parse.tab.c"
    break;

  case 77: /* relationOp: "<="  */
#line 470 "parse.y"
              {yyval = 13; }
#line 1753 "parse.tab.c"
    break;

  case 78: /* relationOp: '>'  */
#line 471 "parse.y"
            {yyval = 12; }
#line 1759 "parse.tab.c"
    break;

  case 79: /* relationOp: ">="  */
#line 472 "parse.y"
              {yyval = 11; }
#line 1765 "parse.tab.c"
    break;


#line 1769 "parse.tab.c"

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

      if (yychar <= ENDD)
        {
          /* Return failure if at end of input.  */
          if (yychar == ENDD)
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

#line 475 "parse.y"

/*将程序的位置记录在procedure_position中*/
void PushProcedurePosition(char *c,int p){ 
    for(int i = 0; i < 11; ++i){
        procedure_position[pro_ct].name[i] = '\0';
    }
    strcpy(procedure_position[pro_ct].name, c);  
    procedure_position[pro_ct].pos = p;
    procedure_position[pro_ct].var_number = 0;
    pro_ct ++;  //程序个数加一
}
/*看定义的标识符之前有没有定义过*/
int CheckSignIsDeclare(char *tag_name){  
    int bias = display_stack[display_top];  //栈顶偏差
    while(bias <= sign_top){
        if(strcmp(tag_name,sign_stack[bias].name) == 0){  //定义过，返回错误
            printf("error!!! line %d: declare repeatedly \n",code_line);
            exit(1);
        }
        if(sign_stack[bias].previous == 0){
            break;
        }
        bias ++;
    }
    return 1;
}
/*找sign是否存在*/
int FindSign(char *tag_name){  
    int display_bias = display_top;
    int cur_bias;
    while(display_bias > 0){
        cur_bias = display_stack[display_bias];
        while(cur_bias <= sign_top){
            if(strcmp(tag_name,sign_stack[cur_bias].name) == 0){//find
                return cur_bias;
            }
            if(sign_stack[cur_bias].previous==0){  //代表找到这个程序的底部
                break;
            }
            cur_bias++;
        }
        display_bias --;
    }
    printf("error!!! line %d: no such parameter \n",code_line);  //没找到
    exit(1);
}
/*将该过程的所有的sign退栈，并且display中最上面的程序也需要退出来*/
void PopSignStack(){  
    
    int bias = display_stack[display_top]-1;
    
    for(int i=sign_top; i>bias;--i){  //退sign
        sign_stack[i].type = -10;
        sign_stack[i].layer = -1;
        sign_stack[i].previous = -1;
        for(int j=0;j<11;++j){
            sign_stack[i].name[j] = '\0';
        }
    }
    sign_top = bias;
    sign_stack[sign_top].previous = 0;
    
    sign_stack[sign_top].type = -3;
    display_stack[display_top] = 0;  //退display
    display_top--;
}
/*将s加入sign 栈中*/
void PushSignStack(char *s,int t){ 
    sign_top++;
    for(int i=0;i<11;++i){
        sign_stack[sign_top].name[i] = '\0';
    }
    strcpy(sign_stack[sign_top].name,s);
    sign_stack[sign_top].type = t;
    sign_stack[sign_top].layer = cur_layer;
    sign_stack[sign_top].previous = 0;
    if(sign_top > 1){  //按照实际情况更新previous的值
        int pre_bias = sign_top-1;
        if(sign_stack[pre_bias].type > -2){
            sign_stack[pre_bias].previous = sign_top;
        }
        else if(sign_stack[pre_bias].type == -3){
            sign_stack[pre_bias].previous = sign_top;
        }
    }
}
/*添加类PCODE代码*/
void AddPcode(int thef, int thel, int thea){  
    mycode[total_line].line = total_line;
    mycode[total_line].f = thef;
    mycode[total_line].l = thel;
    mycode[total_line].a = thea;
    total_line++;
    
}
/*将第theline行代码改为所指的*/
void ChangePcode(int theline, int thef, int thel, int thea){   
    mycode[theline].f = thef;
    mycode[theline].l = thel;
    mycode[theline].a = thea;
}
/*计算偏移量*/
int CaculateA(int pos_flag){  
    int target_flag = pos_flag;
    
    if(pos_flag >= 1){
        while(target_flag >= 1){
            if(sign_stack[target_flag].type <= -2 || sign_stack[target_flag].type >= 0){
                return pos_flag-target_flag + 2;
            }
            target_flag--;
        }
        return pos_flag+2;
    }
    else{  //不正确
        printf("error\n");
        exit(1);
    }
}
/*找到过程位置*/
int FindProcedurePosition(char *s){   
    
    for(int i=cur_pro_ct; i<pro_ct; ++i){
        if(strcmp(procedure_position[i].name,s) == 0){
            
            return procedure_position[i].pos;
        }
    }
    printf("error in func FindProcedurePosition\n");  //找不到
    exit(1);
}
/*按照类PCODE输出代码*/
void PrintPcode(struct code_struct ToPrint){   
    int thef = ToPrint.f;
    fprintf(CodeOutput,"(%d)\t", ToPrint.line);
    switch(thef){
        case 1:fprintf(CodeOutput,"LIT\t");break;
        case 2:fprintf(CodeOutput,"LOD\t");break;
        case 3:fprintf(CodeOutput,"STO\t");break;
        case 4:fprintf(CodeOutput,"CAL\t");break;
        case 5:fprintf(CodeOutput,"INT\t");break;
        case 6:fprintf(CodeOutput,"JMP\t");break;
        case 7:fprintf(CodeOutput,"JPC\t");break;
        case 8:fprintf(CodeOutput,"OPR\t");break;
        default:fprintf(CodeOutput,"error");exit(1);
    }
    fprintf(CodeOutput,"%d\t",ToPrint.l);
    fprintf(CodeOutput,"%d\n",ToPrint.a);
}

/*排序函数*/
int cmp(const void *a ,const void *b){   
    return (*(struct code_struct *)a).line > (*(struct code_struct *)b).line ? 1:-1;
}


int main(int argc, char *argv[]) {
    char *infile;

    // Check if the correct number of command line arguments is provided
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;  // Exit with an error code
    }

    // Use the command line argument as the input file name
    infile = argv[1];

    // Open the file for reading
    FILE *fin = fopen(infile, "r");
    if (fin == NULL) {
        printf("Cannot open the input file: %s\n", infile);
        return 2;  // Exit with an error code
    }

    CodeOutput = fopen("./result/pcode.txt","w");  //类PCODE存放文件
    mycode = (struct code_struct*)malloc(sizeof(struct code_struct)* 2000);
    sign_stack = (struct sign*)malloc(sizeof(struct sign) * 100);
    procedure_position = (struct procedure_pos*)malloc(sizeof(struct procedure_pos) * 30);
    
    /*初始化*/
    for(int i = 0; i < stack_size; ++i){   
        procedure_stack[i] = -1;
        loop_stack[i] = -1;
        code_address_stack[i] = -1;
    }
   
    yyin = fin;
    yyparse();
    /*含有跳转的指令，都要加上现有过程的数量，即加上前面JMP指令的数量*/
    int code_bias = pro_ct;  
    for(int i = 0; i < total_line; ++i){
        //printf("%d\n",ycode[i].f);
        mycode[i].line += code_bias;
        if(mycode[i].f == 4 ||mycode[i].f == 6 || mycode[i].f == 7 ){
            mycode[i].a += code_bias;
        }
    }

    for(int i = 0; i < pro_ct; ++i){
        procedure_position[i].pos += code_bias;
    }
    /*补上前面的JMP*/
    for(int i = 0; i < pro_ct; ++i){
        mycode[total_line].line = i;
        mycode[total_line].f = 6;
        mycode[total_line].l = 0;
        mycode[total_line].a = procedure_position[i].pos;
        total_line++;
    }

    qsort(mycode,total_line,sizeof(mycode[0]),cmp);  //对代码按照行标号排序


    printf("\n");
    for(int i = 0; i < total_line; ++i){  //输出类PCODE
        PrintPcode(mycode[i]);
    }
    FILE *num_file;
    num_file = fopen("./result/number.txt","w");  //在number文件中写下总的行数
    fprintf(num_file,"%d",total_line);

 
    return 0;
}
int yywrap(){
    return 1;
}
void yyerror(char *s) {
    printf("error in line %d %s\n",code_line-1, s);
    exit(1);
}


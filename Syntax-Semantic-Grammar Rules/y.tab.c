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
#line 2 "1605010.y" /* yacc.c:339  */

#include<bits/stdc++.h>
#include "MySymbolTable.h"
#define YYSTYPE SymbolInfo*
using namespace std;
int yyparse(void);
int yylex(void);
extern FILE *yyin;
extern int line_count;
FILE *fp,*log_out,*error_out;
SymbolTable *table = new SymbolTable();
int ScopeTable::assign_id = 1;

 

vector<string>current_parameter_list_name;
vector<string>current_parameter_list_type;
stack< vector<string> >current_argument_list;
string current_return_type = "";
int error_count = 0;

void yyerror(char *s)
{

	fprintf(log_out,"At line no : %d syntax error\n",line_count);
	//write your code
	// int x; here, name = x,type = ID,sub_type = INT
}

string change_comma_to_space(string str)
{
	for(int i=0;i<str.size();i++)
	{
		if(str[i] == ',')
		{
			str[i] = ' ';
		}
	}
	return str;
}


vector<string> tokenize(string str)
{
	stringstream s(str);
    string word;
	vector<string>vec;
  
    while (s >> word) 
        vec.push_back(word);
	return vec;
}

pair<bool,int>check_if_array(string str)
{
	bool first = 0;
	int arr_size = 0;

	if(str[str.size()-1] == ']')
	{
		first = 1;
		
		bool ok = 0;
		for(int i=0;i<str.size();i++)
		{
			if(ok)
			{
                if(str[i] == ']')
				{
					ok = 0;
				}
				else
				{
					if(str[i]>='0'&&str[i]<='9')
					{
						arr_size = arr_size*10 + (str[i]-'0');
					}
					else
					{
						arr_size = -1;
						break;
					}
				}
			}
			else if(str[i]=='[')
			{
				ok = 1;
			}
		}
	}

	return {first,arr_size};
   
}

string arr_tream(string str)
{
	string s = "";
	for(int i=0;i<str.size();i++)
	{
		if(str[i] == '[')
		{
			return s;
		}
		else{
			s += str[i];
		}
	}
}



#line 179 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    IF = 258,
    ELSE = 259,
    FOR = 260,
    WHILE = 261,
    INT = 262,
    FLOAT = 263,
    DOUBLE = 264,
    CHAR = 265,
    RETURN = 266,
    VOID = 267,
    PRINTLN = 268,
    ADDOP = 269,
    MULOP = 270,
    ASSIGNOP = 271,
    RELOP = 272,
    LOGICOP = 273,
    NOT = 274,
    SEMICOLON = 275,
    COMMA = 276,
    LPAREN = 277,
    RPAREN = 278,
    LCURL = 279,
    RCURL = 280,
    LTHIRD = 281,
    RTHIRD = 282,
    INCOP = 283,
    DECOP = 284,
    CONST_INT = 285,
    CONST_FLOAT = 286,
    ID = 287,
    LOWER_THAN_ELSE = 288
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define INT 262
#define FLOAT 263
#define DOUBLE 264
#define CHAR 265
#define RETURN 266
#define VOID 267
#define PRINTLN 268
#define ADDOP 269
#define MULOP 270
#define ASSIGNOP 271
#define RELOP 272
#define LOGICOP 273
#define NOT 274
#define SEMICOLON 275
#define COMMA 276
#define LPAREN 277
#define RPAREN 278
#define LCURL 279
#define RCURL 280
#define LTHIRD 281
#define RTHIRD 282
#define INCOP 283
#define DECOP 284
#define CONST_INT 285
#define CONST_FLOAT 286
#define ID 287
#define LOWER_THAN_ELSE 288

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef SymbolInfo* YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 296 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   145

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  123

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   124,   124,   131,   137,   145,   151,   157,   165,   216,
     250,   249,   336,   335,   390,   403,   415,   427,   441,   440,
     489,   488,   540,   621,   628,   635,   643,   649,   656,   663,
     672,   678,   686,   692,   698,   704,   715,   726,   737,   748,
     754,   767,   773,   782,   808,   856,   862,   879,   885,   903,
     909,   928,   934,   962,   968,  1012,  1019,  1026,  1034,  1040,
    1040,  1081,  1088,  1095,  1102,  1109,  1118,  1125,  1128,  1137
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "FOR", "WHILE", "INT",
  "FLOAT", "DOUBLE", "CHAR", "RETURN", "VOID", "PRINTLN", "ADDOP", "MULOP",
  "ASSIGNOP", "RELOP", "LOGICOP", "NOT", "SEMICOLON", "COMMA", "LPAREN",
  "RPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD", "INCOP", "DECOP",
  "CONST_INT", "CONST_FLOAT", "ID", "LOWER_THAN_ELSE", "$accept", "start",
  "program", "unit", "func_declaration", "func_definition", "$@1", "$@2",
  "parameter_list", "compound_statement", "$@3", "$@4", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement",
  "expression_statement", "variable", "expression", "logic_expression",
  "rel_expression", "simple_expression", "term", "unary_expression",
  "factor", "$@5", "argument_list", "arguments", YY_NULLPTR
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
     285,   286,   287,   288
};
# endif

#define YYPACT_NINF -73

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-73)))

#define YYTABLE_NINF -21

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       9,   -73,   -73,   -73,    48,     9,   -73,   -73,   -73,   -73,
       0,   -73,   -73,    -7,    32,     1,    27,   -73,    24,    38,
      14,    28,    34,    33,   -73,    42,     9,    47,   -73,   -73,
      45,    37,   -73,    36,   -73,    42,    56,    96,    64,   -73,
     -73,   -73,    65,    73,    78,    92,    83,    92,    92,   -73,
      92,   -73,   -73,    12,   -73,   -73,    80,    66,   -73,   -73,
      -2,    93,   -73,    99,    30,   104,   -73,   -73,   -73,    92,
      62,    92,   101,    97,    26,   -73,   -73,   102,   -73,    92,
     105,   -73,   -73,    92,   -73,   -73,   -73,    92,    92,    92,
      92,   107,    62,   109,   -73,   110,   -73,    92,   108,   -73,
     -73,   104,   120,   -73,    96,    92,    96,   116,   -73,   114,
     117,   -73,   135,   118,   -73,   -73,   -73,    92,    96,    96,
     -73,   -73,   -73
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    23,    24,    25,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    28,     0,     0,     0,    22,     0,    12,
       0,    17,     0,    26,     9,     0,     0,    10,    16,    29,
       0,    18,    13,    15,     8,     0,     0,     0,     0,    14,
      11,    27,     0,     0,     0,     0,     0,     0,     0,    41,
       0,    62,    63,    43,    34,    32,     0,     0,    30,    33,
      58,     0,    45,    47,    49,    51,    53,    57,    21,     0,
       0,     0,     0,     0,    58,    55,    56,     0,    59,     0,
      28,    19,    31,     0,    64,    65,    42,     0,     0,     0,
       0,     0,     0,     0,    40,     0,    61,    67,     0,    46,
      48,    52,    50,    54,     0,     0,     0,     0,    69,     0,
      66,    44,    36,     0,    38,    39,    60,     0,     0,     0,
      68,    37,    35
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -73,   -73,   -73,   137,   -73,   -73,   -73,   -73,   -73,    -5,
     -73,   -73,    18,     7,   -73,   -73,   -55,   -64,   -47,   -40,
     -72,    53,    54,    57,   -44,   -73,   -73,   -73,   -73
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    35,    25,    20,    54,
      37,    38,    55,    56,    14,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    97,   109,   110
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      74,    74,    82,    75,    76,    72,    92,    10,     1,     2,
      77,    99,    10,     3,    83,    15,     1,     2,     9,    16,
      32,     3,    21,     9,    19,   108,    84,    85,   105,    91,
      40,    93,    13,    33,    78,    26,    74,    27,    79,    98,
      74,    74,    74,    74,    88,   120,   103,    89,    11,   112,
      74,   114,    17,    18,    84,    85,    23,    22,    24,    30,
      28,    29,   -20,   121,   122,   113,    31,    34,    39,    42,
      74,    43,    44,     1,     2,    36,    47,    45,     3,    46,
      47,    48,    49,    41,    50,    48,    49,    69,    50,    68,
      31,    81,    51,    52,    53,    70,    51,    52,    53,    42,
      71,    43,    44,     1,     2,    73,    47,    45,     3,    46,
      47,    48,    80,    86,    50,    48,    49,    87,    50,    90,
      31,    94,    51,    52,    53,    96,    51,    52,    53,    95,
     104,    16,   106,   107,    88,   111,   115,   116,   117,   118,
     100,   119,    12,   102,     0,   101
};

static const yytype_int8 yycheck[] =
{
      47,    48,    57,    47,    48,    45,    70,     0,     7,     8,
      50,    83,     5,    12,    16,    22,     7,     8,     0,    26,
      25,    12,    15,     5,    23,    97,    28,    29,    92,    69,
      35,    71,    32,    26,    22,    21,    83,    23,    26,    79,
      87,    88,    89,    90,    14,   117,    90,    17,     0,   104,
      97,   106,    20,    21,    28,    29,    32,    30,    20,    26,
      32,    27,    25,   118,   119,   105,    24,    20,    32,     3,
     117,     5,     6,     7,     8,    30,    14,    11,    12,    13,
      14,    19,    20,    27,    22,    19,    20,    22,    22,    25,
      24,    25,    30,    31,    32,    22,    30,    31,    32,     3,
      22,     5,     6,     7,     8,    22,    14,    11,    12,    13,
      14,    19,    32,    20,    22,    19,    20,    18,    22,    15,
      24,    20,    30,    31,    32,    23,    30,    31,    32,    32,
      23,    26,    23,    23,    14,    27,    20,    23,    21,     4,
      87,    23,     5,    89,    -1,    88
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,    12,    35,    36,    37,    38,    39,    46,
      47,     0,    37,    32,    48,    22,    26,    20,    21,    23,
      42,    47,    30,    32,    20,    41,    21,    23,    32,    27,
      26,    24,    43,    47,    20,    40,    30,    44,    45,    32,
      43,    27,     3,     5,     6,    11,    13,    14,    19,    20,
      22,    30,    31,    32,    43,    46,    47,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    25,    22,
      22,    22,    53,    22,    52,    58,    58,    53,    22,    26,
      32,    25,    50,    16,    28,    29,    20,    18,    14,    17,
      15,    53,    51,    53,    20,    32,    23,    60,    53,    54,
      55,    57,    56,    58,    23,    51,    23,    23,    54,    61,
      62,    27,    50,    53,    50,    20,    23,    21,     4,    23,
      54,    50,    50
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    37,    38,    38,
      40,    39,    41,    39,    42,    42,    42,    42,    44,    43,
      45,    43,    46,    47,    47,    47,    48,    48,    48,    48,
      49,    49,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    51,    51,    52,    52,    53,    53,    54,    54,    55,
      55,    56,    56,    57,    57,    58,    58,    58,    59,    60,
      59,    59,    59,    59,    59,    59,    61,    61,    62,    62
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     6,     4,     3,     2,     1,     0,     4,
       0,     3,     3,     1,     1,     1,     3,     6,     1,     4,
       1,     2,     1,     1,     1,     7,     5,     7,     5,     5,
       3,     1,     2,     1,     4,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     2,     2,     1,     1,     0,
       5,     3,     1,     1,     2,     2,     1,     0,     3,     1
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
yystrlen (const char *yystr)
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
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
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
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
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

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
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
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
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
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
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 125 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
		              fprintf(log_out,"At line no : %d start : program\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
	             }
#line 1466 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 132 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-1])->get_name()+"\n"+(yyvsp[0])->get_name(),"");
					  fprintf(log_out,"At line no : %d program : program unit\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 1476 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 138 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
                      fprintf(log_out,"At line no : %d program : unit\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 1486 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 146 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
                      fprintf(log_out,"At line no : %d unit : var_declaration\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 1496 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 152 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
                      fprintf(log_out,"At line no : %d unit : func_declaration\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 1506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 158 "1605010.y" /* yacc.c:1646  */
    { 
					  (yyval) = (yyvsp[0]);
                      fprintf(log_out,"At line no : %d unit : func_definition\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 1516 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 166 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-5])->get_name()+" "+(yyvsp[-4])->get_name()+(yyvsp[-3])->get_name()+(yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name()+"\n","");
                      string return_type = (yyvsp[-5])->get_name();
					  string function_name = (yyvsp[-4])->get_name();
					  SymbolInfo *temp = table->my_look_up(function_name);

					  if(temp == nullptr)
					  {
						  bool ok = 0;
						  for(string s:current_parameter_list_type)
						  {
							  if(s == "void")
							  {
								  ok = 1;
								  break;
							  }

						  }
						  if(ok && current_parameter_list_type.size()>1)
						  {
							  fprintf(error_out,"At line no : %d void should be the only parameter\n",line_count);
							  error_count++;
						  }


                          SymbolInfo info;
						  info.name = function_name;
						  info.type = "ID";
						  info.sub_type = return_type;
						  info.return_type = return_type;
						  info.parameter_list = current_parameter_list_type;
						  if(ok && current_parameter_list_type.size()==1)
						  {
							  info.parameter_list.clear();
						  }
						  info.is_function = 1;
						  table->my_insert(info);
					  }
					  else
					  {
						  fprintf(error_out,"At line no : %d function renaming\n",line_count);
						  error_count++;
					  }

                      fprintf(log_out,"At line no : %d func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());

					  current_parameter_list_name.clear();
					  current_parameter_list_type.clear();
				  }
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 217 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-4])->get_name()+" "+(yyvsp[-3])->get_name()+(yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name()+"\n","");
                    
					  string return_type = (yyvsp[-4])->get_name();
					  string function_name = (yyvsp[-3])->get_name();
					  SymbolInfo *temp = table->my_look_up(function_name);

					  if(temp == nullptr)
					  {
						  
                          SymbolInfo info;
						  info.name = function_name;
						  info.type = "ID";
						  info.sub_type = return_type;
						  info.return_type = return_type;
						  info.is_function = 1;
						  table->my_insert(info);
					  }
					  else
					  {
						  fprintf(error_out,"At line no : %d function rename\n",line_count);
						  error_count++;
					  }

                      fprintf(log_out,"At line no : %d func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());

					  current_parameter_list_name.clear();
					  current_parameter_list_type.clear();
				  }
#line 1606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 250 "1605010.y" /* yacc.c:1646  */
    {
					  current_return_type = (yyvsp[-4])->get_name();
					  string function_name = (yyvsp[-3])->get_name();
                      
					  SymbolInfo *temp = table->my_look_up(function_name);
                      
					  if(temp == nullptr)
					  {
						  bool ok = 0;
						  for(string s:current_parameter_list_type)
						  {
							  
							  if(s == "void")
							  {
								  ok = 1;
								  break;
							  }

						  }

						  if(ok && current_parameter_list_type.size()>1)
						  {
							  fprintf(error_out,"At line no : %d void should be the only parameter\n",line_count);
							  error_count++;
						  }
						  

                          SymbolInfo info;
						  info.name = function_name;
						  info.type = "ID";
						  info.sub_type = current_return_type;
						  info.return_type = current_return_type;
						  info.parameter_list = current_parameter_list_type;
						  info.is_function = 1;
						  info.is_defined_yet = 1;
						  table->my_insert(info);
					  }
					  else
					  {
						  if(temp->is_function && !temp->is_defined_yet)
						  {
							  if(temp->parameter_list.size() != current_parameter_list_type.size())
							  {
								  fprintf(error_out,"At line no : %d parameter mismatch\n",line_count);
								  error_count++;
							  }
							  else if(temp->return_type != current_return_type)
							  {
                                  fprintf(error_out,"At line no : %d return type mismatch\n",line_count);
								  error_count++;
							  }
							  else
							  {
								  bool ok = 1;
								  for(int i=0;i<temp->parameter_list.size();i++)
								  {
									  if(temp->parameter_list[i] != current_parameter_list_type[i])
									  {
										  fprintf(error_out,"At line no : %d parameter mismatch\n",line_count);
										  error_count++;
										  ok = 0;
										  break;
									  }
								  }
								  if(ok)
								  {
									  temp->is_defined_yet = 1;
								  }
							  }
						  }
						  else
						  {
							  fprintf(error_out,"At line no : %d function mismatch\n",line_count);
							  error_count++;
						  }

					  }	  
				  }
#line 1689 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 329 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-6])->get_name()+" "+(yyvsp[-5])->get_name()+(yyvsp[-4])->get_name()+(yyvsp[-3])->get_name()+(yyvsp[-2])->get_name()+"\n"+(yyvsp[0])->get_name(),"");

                      fprintf(log_out,"At line no : %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 1700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 336 "1605010.y" /* yacc.c:1646  */
    {

					  current_return_type = (yyvsp[-3])->get_name();
					  string function_name = (yyvsp[-2])->get_name();
                      
					  SymbolInfo *temp = table->my_look_up(function_name);
                      
					  if(temp == nullptr)
					  {
                          SymbolInfo info;
						  info.name = function_name;
						  info.type = "ID";
						  info.sub_type = current_return_type;
						  info.return_type = current_return_type;
						  info.is_function = 1;
						  info.is_defined_yet = 1;
						  table->my_insert(info);
					  }
					  else
					  {
						  if(temp->is_function && !temp->is_defined_yet)
						  {
							  if(temp->parameter_list.size() != current_parameter_list_type.size())
							  {
								  fprintf(error_out,"At line no : %d parameter mismatch\n",line_count);
								  error_count++;
							  }
							  else if(temp->return_type != current_return_type)
							  {
                                  fprintf(error_out,"At line no : %d return type mismatch\n",line_count);
								  error_count++;
							  }
							  else
							  {
								  temp->is_defined_yet = 1;  
							  }
						  }
						  else
						  {
							  fprintf(error_out,"At line no : %d function mismatch\n",line_count);
							  error_count++;
						  }

					  }	  

				  }
#line 1751 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 383 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-5])->get_name()+" "+(yyvsp[-4])->get_name()+(yyvsp[-3])->get_name()+(yyvsp[-2])->get_name()+"\n"+(yyvsp[0])->get_name(),"");
                      
                      fprintf(log_out,"At line no : %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 1762 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 391 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-3])->get_name()+(yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+" "+(yyvsp[0])->get_name(),"");

					  


					  current_parameter_list_type.push_back((yyvsp[-1])->get_name());
					  current_parameter_list_name.push_back((yyvsp[0])->get_name());

                      fprintf(log_out,"At line no : %d parameter_list  : parameter_list COMMA type_specifier ID\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 1779 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 404 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");

					  

					  current_parameter_list_type.push_back((yyvsp[0])->get_name());


                      fprintf(log_out,"At line no : %d parameter_list  :  parameter_list COMMA type_specifier\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 416 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-1])->get_name()+" "+(yyvsp[0])->get_name(),"");

					  

					  current_parameter_list_type.push_back((yyvsp[-1])->get_name());
					  current_parameter_list_name.push_back((yyvsp[0])->get_name());

                      fprintf(log_out,"At line no : %d parameter_list : type_specifier ID\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 1811 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 428 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);

					  current_parameter_list_type.push_back((yyvsp[0])->get_name());

				

                      fprintf(log_out,"At line no : %d parameter_list : type_specifier\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 1826 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 441 "1605010.y" /* yacc.c:1646  */
    {
	                  table->enter_scope();
					  fprintf(log_out,"New ScopeTable with id %d created\n",table->current_scope_table->get_id());

					  if(current_parameter_list_name.size()!=0)
					  { 
						  if(current_parameter_list_name.size() != current_parameter_list_type.size())
						  {
							  fprintf(error_out,"At line no : %d incomplete parameter list\n",line_count);
							  error_count++;

						  }
						  
						  for(int i=0;i<current_parameter_list_name.size();i++)
						  {
							  SymbolInfo rhs;
							  rhs.name = current_parameter_list_name[i];
							  rhs.type = "ID";
							  rhs.sub_type = current_parameter_list_type[i];

							  SymbolInfo *temp = table->my_look_up_current(rhs.name);
 
							  if(temp != nullptr)
							  {
								 fprintf(error_out,"At line no : %d redeclaration\n",line_count);
								 error_count++;
							  }
							  else
							  {
								 table->my_insert(rhs);
							  }

						  }

						  current_parameter_list_name.clear();
					      current_parameter_list_type.clear();
					  }

				  }
#line 1870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 480 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo("{\n"+(yyvsp[-1])->get_name()+"\n}","");
                      fprintf(log_out,"At line no : %d compound_statement : LCURL statements RCURL\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
					  table->print_all_scope_table(log_out);
					  fprintf(log_out,"ScopeTable with id %d removed\n",table->current_scope_table->get_id());
					  table->exit_scope();
				  }
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 489 "1605010.y" /* yacc.c:1646  */
    {
					  table->enter_scope();
					  fprintf(log_out,"New ScopeTable with id %d created\n",table->current_scope_table->get_id());


					  if(current_parameter_list_name.size()!=0)
					  { 
						  if(current_parameter_list_name.size() != current_parameter_list_type.size())
						  {
							  fprintf(error_out,"At line no : %d incomplete parameter list\n",line_count);
							  error_count++;

						  }
					 
						  for(int i=0;i<current_parameter_list_name.size();i++)
						  {
							  SymbolInfo rhs;
							  rhs.name = current_parameter_list_name[i];
							  rhs.type = "ID";
							  rhs.sub_type = current_parameter_list_type[i];

							  SymbolInfo *temp = table->my_look_up_current(rhs.name);
 
							  if(temp != nullptr)
							  {
								 fprintf(error_out,"At line no : %d redeclaration\n",line_count);
								 error_count++;
							  }
							  else
							  {
								 table->my_insert(rhs);
							  }
							   

						  }
						  current_parameter_list_name.clear();
					      current_parameter_list_type.clear();
					  }
 

				  }
#line 1929 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 530 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo("{}","");
                      fprintf(log_out,"At line no : %d compound_statement : LCURL RCURL\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
					  table->print_all_scope_table(log_out);
					  fprintf(log_out,"ScopeTable with id %d removed\n",table->current_scope_table->get_id());
					  table->exit_scope();
				  }
#line 1942 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 541 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-2])->get_name()+" "+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name()+"\n","");

					  if((yyvsp[-2])->name == "void")
					  {
						  fprintf(error_out,"At linr no : %d variable type cannot be void\n",line_count);
						  error_count++;
					  }
					
					  string str = (yyvsp[-1])->get_name();

					  str = change_comma_to_space(str);

					  
					  vector<string> tokens = tokenize(str);
					

					  for(string s : tokens)
					  {
						  
						  pair<bool,int> res = check_if_array(s);
						  if(res.first == 0)
						  {
							  SymbolInfo rhs;
							  rhs.name = s;
							  rhs.type = "ID";
							  rhs.sub_type = (yyvsp[-2])->get_name();

							  SymbolInfo *temp = table->my_look_up_current(rhs.name);
 
							  if(temp != nullptr)
							  {
								   fprintf(error_out,"At line no : %d redeclaration\n",line_count);
								   error_count++;
							  }
							  else
							  {
								  table->my_insert(rhs);
							  }
						  }
						  else
						  {
							  if(res.second == -1)
							  {
								   fprintf(error_out,"At linr no : %d array size should be int\n",line_count);
								   error_count++;
							  }
							  else
							  {
								  SymbolInfo rhs;
							      rhs.name = arr_tream(s);
							      rhs.type = "ID";
							      rhs.sub_type = (yyvsp[-2])->get_name();
								  rhs.is_array = 1;
								  rhs.arr_size = res.second;


								  SymbolInfo *temp = table->my_look_up_current(rhs.name);
 
							      if(temp != nullptr)
							      {
								  	 fprintf(error_out,"At line no : %d redeclaration\n",line_count);
									 error_count++;
							      }
							      else
							      {
								  	 table->my_insert(rhs);
							      }

						 
							       
							  }
						  }
					  }
					  
                      fprintf(log_out,"At line no : %d var_declaration : type_specifier declaration_list SEMICOLON\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 2025 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 622 "1605010.y" /* yacc.c:1646  */
    {   
					  (yyval) = (yyvsp[0]);

				  	  fprintf(log_out,"At line no : %d type_specifier : INT\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 2036 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 628 "1605010.y" /* yacc.c:1646  */
    {
			          (yyval) = (yyvsp[0]);
					 
			 		  fprintf(log_out,"At line no : %d type_specifier : FLOAT\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());	
				 
			      }
#line 2048 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 635 "1605010.y" /* yacc.c:1646  */
    {
			          (yyval) = (yyvsp[0]);

			 		  fprintf(log_out,"At line no : %d type_specifier : VOID\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());	
			      }
#line 2059 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 644 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),""); 
                      fprintf(log_out,"At line no : %d declaration_list : declaration_list COMMA ID\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 2069 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 650 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-5])->get_name()+(yyvsp[-4])->get_name()+(yyvsp[-3])->get_name()+(yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");
                      fprintf(log_out,"At line no : %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n",line_count);
					  fprintf(log_out,"%s\n\n",(yyvsp[-1])->get_name().c_str());
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 2080 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 657 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
					  
                      fprintf(log_out,"At line no : %d declaration_list : ID\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 2091 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 664 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-3])->get_name()+(yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");
                      fprintf(log_out,"At line no : %d declaration_list : ID LTHIRD CONST_INT RTHIRD\n",line_count);
					  fprintf(log_out,"%s\n\n",(yyvsp[-1])->get_name().c_str());
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				  }
#line 2102 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 673 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
					  fprintf(log_out,"At line no : %d statements : statement\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				 }
#line 2112 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 679 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");
					  fprintf(log_out,"At line no : %d statements : statements statement\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				 }
#line 2122 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 687 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
                      fprintf(log_out,"At line no : %d statement : var_declaration\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				 }
#line 2132 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 693 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
                      fprintf(log_out,"At line no : %d statement : expression_statement\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				 }
#line 2142 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 699 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
                      fprintf(log_out,"At line no : %d statement : compound_statement\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				 }
#line 2152 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 705 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-6])->get_name()+(yyvsp[-5])->get_name()+(yyvsp[-4])->get_name()+(yyvsp[-3])->get_name()+(yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");
					  if((yyvsp[-3])->sub_type == "void"||(yyvsp[-2])->sub_type=="void")
					  {
						  fprintf(error_out,"At line no : %d expression evaluates void\n",line_count);
						  error_count++;
					  }
                      fprintf(log_out,"At line no : %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				 }
#line 2167 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 716 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-4])->get_name()+(yyvsp[-3])->get_name()+(yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");
					  if((yyvsp[-2])->sub_type == "void")
					  {
						  fprintf(error_out,"At line no : %d expression evaluates void\n",line_count);
						  error_count++;
					  }
                      fprintf(log_out,"At line no : %d statement : IF LPAREN expression RPAREN statement\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				 }
#line 2182 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 727 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-6])->get_name()+(yyvsp[-5])->get_name()+(yyvsp[-4])->get_name()+(yyvsp[-3])->get_name()+(yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");
                      if((yyvsp[-4])->sub_type == "void")
					  {
						  fprintf(error_out,"At line no : %d expression evaluates void\n",line_count);
						  error_count++;
					  }
                      fprintf(log_out,"At line no : %d statement : IF LPAREN expression RPAREN statement ELSE statement\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				 }
#line 2197 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 738 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-4])->get_name()+(yyvsp[-3])->get_name()+(yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");
					  if((yyvsp[-2])->sub_type == "void")
					  {
						  fprintf(error_out,"At line no : %d expression evaluates void\n",line_count);
						  error_count++;
					  }
                      fprintf(log_out,"At line no : %d statement : WHILE LPAREN expression RPAREN statement\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				 }
#line 2212 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 749 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-4])->get_name()+(yyvsp[-3])->get_name()+(yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name()+"\n","");
                      fprintf(log_out,"At line no : %d statement :  PRINTLN LPAREN ID RPAREN SEMICOLON\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				 }
#line 2222 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 755 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-2])->get_name()+" "+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name()+"\n","");
					  if((yyvsp[-1])->sub_type != current_return_type)
					  {
						  fprintf(error_out,"At line no : %d return type mismatch\n",line_count);
						  error_count++;
					  }
                      fprintf(log_out,"At line no : %d statement : RETURN expression SEMICOLON\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				 }
#line 2237 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 768 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
                      fprintf(log_out,"At line no : %d expression_statement : SEMICOLON\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2247 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 774 "1605010.y" /* yacc.c:1646  */
    { 
					  (yyval) = new SymbolInfo((yyvsp[-1])->get_name()+(yyvsp[0])->get_name()+"\n","");
					  
                      fprintf(log_out,"At line no : %d expression_statement : expression SEMICOLON\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2258 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 783 "1605010.y" /* yacc.c:1646  */
    {
					  SymbolInfo *temp = table->my_look_up((yyvsp[0])->get_name());

					  if(temp == nullptr)
					  {
						  fprintf(error_out,"At line no : %d undeclared variable\n",line_count);
						  error_count++;
					  }
					  else
					  {
						  if(temp->is_array)
						  {
							  fprintf(error_out,"At line no : %d type mismatch\n",line_count);
							  error_count++;
						  }
						 
                          (yyval) = temp;
					  }


					   

                      fprintf(log_out,"At line no : %d variable : ID\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2288 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 809 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-3])->get_name()+(yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");
					 

					  SymbolInfo *temp = table->my_look_up((yyvsp[-3])->get_name());

					  if(temp == nullptr)
					  {
						  fprintf(error_out,"At line no : %d undeclared variable\n",line_count);
						  error_count++;
					  }
					  else
					  {
						
						  
							if((yyvsp[-1])->sub_type != "int")
							{
								fprintf(error_out,"At line no : %d array index should be int\n",line_count);
								error_count++;
							}
							else
							{
								int my_arr_size = atoi((yyvsp[-1])->name.c_str());
								int mx_arr_size = temp->arr_size;

							

								if(my_arr_size<0||my_arr_size>=mx_arr_size)
								{
									fprintf(error_out,"At line no : %d index out of bound\n",line_count);
									error_count++;
								}

							}

							(yyval)->sub_type = temp->sub_type;
							(yyval)->is_array = temp->is_array;
							(yyval)->arr_size = temp->arr_size;
					 
					  }


                      fprintf(log_out,"At line no : %d variable : ID LTHIRD expression RTHIRD\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2338 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 857 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
                      fprintf(log_out,"At line no : %d expression : logic_expression\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2348 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 863 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");

					  if((yyvsp[-2])->sub_type != (yyvsp[0])->sub_type)
					  {
						  fprintf(error_out,"At line no : %d type mismatch\n",line_count);
						  error_count++;
					  }

					  (yyval)->sub_type = (yyvsp[-2])->sub_type;
					  
                      fprintf(log_out,"At line no : %d expression : variable ASSIGNOP logic_expression\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2367 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 880 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
                      fprintf(log_out,"At line no : %d logic_expression : rel_expression\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2377 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 886 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");

					  if(((yyvsp[-2])->sub_type != (yyvsp[0])->sub_type)&&((yyvsp[-2])->sub_type != "int"))
					  {
						  fprintf(error_out,"At line no : %d type mismatch\n",line_count);
						  error_count++;
					  }

					  (yyval)->sub_type = "int";


                      fprintf(log_out,"At line no : %d logic_expression : rel_expression LOGICOP rel_expression \n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2397 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 904 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
                      fprintf(log_out,"At line no : %d rel_expression : simple_expression \n",line_count); 
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2407 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 910 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");

					  if((yyvsp[-2])->sub_type == "void" || (yyvsp[0])->sub_type == "void")
					  {
						  fprintf(error_out,"At line no : %d type mismatch\n",line_count);
						  error_count++;
					  }

					  (yyval)->sub_type = "int";



                      fprintf(log_out,"At line no : %d rel_expression : simple_expression RELOP simple_expression\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2428 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 929 "1605010.y" /* yacc.c:1646  */
    {  
					  (yyval) = (yyvsp[0]);
                      fprintf(log_out,"At line no : %d simple_expression : term\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
			    }
#line 2438 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 935 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");

					  if((yyvsp[-2])->sub_type == "void" || (yyvsp[0])->sub_type == "void")
					  {
						  fprintf(error_out,"At line no : %d type mismatch\n",line_count);
						  error_count++;
					  }
					  else if((yyvsp[-2])->sub_type != (yyvsp[0])->sub_type)
					  {
						   
							
							(yyval)->sub_type = "float";  
					  }
					  else if((yyvsp[-2])->sub_type == (yyvsp[0])->sub_type)
					  {
						  (yyval)->sub_type = (yyvsp[-2])->sub_type;
					  }

					  


                      fprintf(log_out,"At line no : %d simple_expression : simple_expression ADDOP term\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2468 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 963 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
                      fprintf(log_out,"At line no : %d term : unary_expression \n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2478 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 969 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");

                      if((yyvsp[-2])->sub_type == "void" || (yyvsp[0])->sub_type == "void")
					  {
						  fprintf(error_out,"At line no : %d type mismatch\n",line_count);
						  error_count++;
					  }
					  else
					  {
						  if((yyvsp[-1])->name == "%")
						  {
							  if((yyvsp[-2])->sub_type == "float"||(yyvsp[0])->sub_type == "float")
							  {
								  fprintf(error_out,"At line no : %d modulus operator cannot have float operand\n",line_count);
								  error_count++;
							  }
							  (yyval)->sub_type = "int";
						  }	
						  else
						  {
							  if((yyvsp[-2])->sub_type == "float"||(yyvsp[0])->sub_type == "float")
							  {
								  (yyval)->sub_type = "float";
								   
							  }
							  else
							  {
								  (yyval)->sub_type = "int";

							  }
							  
						  }					   
						 
					  }
					   



                      fprintf(log_out,"At line no : %d term : term MULOP unary_expression\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2525 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1013 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");
					  (yyval)->sub_type = (yyvsp[0])->sub_type;
                      fprintf(log_out,"At line no : %d unary_expression : ADDOP unary_expression\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1020 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");
					  (yyval)->sub_type = (yyvsp[0])->sub_type;
                      fprintf(log_out,"At line no : %d unary_expression : NOT unary_expression\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
			    }
#line 2547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1027 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
                      fprintf(log_out,"At line no : %d unary_expression : factor\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2557 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1035 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
                      fprintf(log_out,"At line no : %d factor : variable \n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2567 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1040 "1605010.y" /* yacc.c:1646  */
    { current_argument_list.push(vector<string>()); }
#line 2573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1041 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-4])->get_name()+(yyvsp[-3])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");

					  SymbolInfo *temp = table->my_look_up((yyvsp[-4])->get_name());

					  if(temp == nullptr || !temp->is_function)
					  {
						  fprintf(error_out,"At line no : %d undeclared function calling\n",line_count);
						  error_count++;
					  }
					  else
					  {
						  if(temp->parameter_list.size()!=current_argument_list.top().size())
						  {
							  fprintf(error_out,"At line no : %d unequal number of arguments\n",line_count);
							  error_count++;
						  }
						  else
						  {
							  for(int i=0;i<current_argument_list.top().size();i++)
							  {
								  if(current_argument_list.top()[i] != temp->parameter_list[i])
								  {
									  fprintf(error_out,"At line no : %d invalid argument type\n",line_count);
									  error_count++;
									  break;
								  }
							  }
						  }

						  (yyval)->sub_type = temp->return_type;
					  }

					  current_argument_list.pop();


                      fprintf(log_out,"At line no : %d factor : ID LPAREN argument_list RPAREN\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
					  
				}
#line 2618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1082 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");
					  (yyval)->sub_type = (yyvsp[-1])->sub_type;
                      fprintf(log_out,"At line no : %d factor : LPAREN expression RPAREN\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1089 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
					  (yyval)->sub_type = "int";
                      fprintf(log_out,"At line no : %d factor : CONST_INT\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1096 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
					  (yyval)->sub_type = "float";
                      fprintf(log_out,"At line no : %d factor : CONST_FLOAT\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1103 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");
					  (yyval)->sub_type = (yyvsp[-1])->sub_type;
                      fprintf(log_out,"At line no : %d factor : variable INCOP\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1110 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = new SymbolInfo((yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");
					  (yyval)->sub_type = (yyvsp[-1])->sub_type;
                      fprintf(log_out,"At line no : %d factor : variable DECOP\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2673 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1119 "1605010.y" /* yacc.c:1646  */
    {
					  (yyval) = (yyvsp[0]);
					  
                      fprintf(log_out,"At line no : %d argument_list : arguments\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
				}
#line 2684 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1125 "1605010.y" /* yacc.c:1646  */
    {(yyval) = new SymbolInfo();}
#line 2690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1129 "1605010.y" /* yacc.c:1646  */
    {
				      (yyval) = new SymbolInfo((yyvsp[-2])->get_name()+(yyvsp[-1])->get_name()+(yyvsp[0])->get_name(),"");

					  current_argument_list.top().push_back((yyvsp[0])->sub_type);

                      fprintf(log_out,"At line no : %d arguments : arguments COMMA logic_expression \n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
			   }
#line 2703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1138 "1605010.y" /* yacc.c:1646  */
    {
				      (yyval) = (yyvsp[0]);

					  current_argument_list.top().push_back((yyvsp[0])->sub_type);
					  
					   
                      fprintf(log_out,"At line no : %d arguments : logic_expression\n",line_count);
					  fprintf(log_out,"%s\n",(yyval)->get_name().c_str());
			   }
#line 2717 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2721 "y.tab.c" /* yacc.c:1646  */
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

yyreturn:
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
                  yystos[*yyssp], yyvsp);
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
#line 1149 "1605010.y" /* yacc.c:1906  */

int main(int argc,char *argv[])
{
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}
	log_out = fopen("1605010_log.txt","w");
	error_out = fopen("1605010_error.txt","w");
	yyin=fp;
	yyparse();

	fprintf(error_out,"Total number of error : %d",error_count);

	fclose(log_out);
	fclose(error_out);
		
	return 0;
}

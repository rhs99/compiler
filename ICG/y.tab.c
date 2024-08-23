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
#line 2 "1605010.y"

#include<bits/stdc++.h>
#include "MySymbolTable.h"
#define YYSTYPE SymbolInfo*
using namespace std;
int yyparse(void);
int yylex(void);
extern FILE *yyin;
extern int line_count;
FILE *fp,*error_out,*asm_out;
SymbolTable *table = new SymbolTable();
int ScopeTable::assign_id = 1;

 

vector<string>current_parameter_list_name;
vector<string>current_parameter_list_type;
stack< vector<string> >current_argument_list;
string current_return_type = "";
int error_count = 0;


vector<string>variables;
vector<string>arrays;
vector<string>array_sizes;
string current_func_name;
string ret_var = "_ret";
stack< vector<string> >current_argument_name_with_id;


int label_count = 0;
int temp_count = 0;
int current_scope_table_id;

void yyerror(char *s)
{

	fprintf(error_out,"At line no : %d syntax error\n",line_count);
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

string int_to_string(int n)
{
	stack<int>stk;
	if(n == 0)
	{
		stk.push(0);
	}
	while(n>0)
	{
		stk.push(n%10);
		n = n/10;
	}

	string ret = "";
	while(!stk.empty())
	{
		int d = stk.top();
		stk.pop();
		char c = '0'+d;
		ret += c;
	}
	return ret;
}

string new_label()
{
	string temp = int_to_string(label_count);
	label_count++;
	return ("l" + temp);
}

string new_temp()
{
	string temp = int_to_string(temp_count);
	temp_count++;
	return ("t" + temp);
	 
}
string print_code()
{
	string temp = "PRINT PROC\n\  
    PUSH AX\n\
    PUSH BX\n\
    PUSH CX\n\
    PUSH DX\n\
    OR AX,AX\n\
    JGE END_IF1\n\
    PUSH AX\n\
    MOV DL,'-'\n\
    MOV AH,2\n\
    INT 21H\n\
    POP AX\n\
    NEG AX\n\
END_IF1: \n\
    XOR CX,CX\n\
    MOV BX,10D\n\
REPEAT1:\n\
    XOR DX,DX\n\
    DIV BX\n\
    PUSH DX\n\
    INC CX\n\
    OR AX,AX\n\
    JNE REPEAT1\n\
    MOV AH,2\n\
PRINT_LOOP:\n\
    POP DX\n\
    OR DL,30H\n\
    INT 21H\n\
    LOOP PRINT_LOOP\n\
	MOV AH,2\n\
	MOV DL,0DH\n\
    INT 21H\n\
	MOV DL,0AH\n\
    INT 21H\n\
    POP DX\n\
    POP CX\n\
    POP BX\n\
    POP AX\n\
    RET\n\
    PRINT ENDP\n";

	return temp;
}



#line 281 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IF = 258,                      /* IF  */
    ELSE = 259,                    /* ELSE  */
    FOR = 260,                     /* FOR  */
    WHILE = 261,                   /* WHILE  */
    INT = 262,                     /* INT  */
    FLOAT = 263,                   /* FLOAT  */
    DOUBLE = 264,                  /* DOUBLE  */
    CHAR = 265,                    /* CHAR  */
    RETURN = 266,                  /* RETURN  */
    VOID = 267,                    /* VOID  */
    PRINTLN = 268,                 /* PRINTLN  */
    ADDOP = 269,                   /* ADDOP  */
    MULOP = 270,                   /* MULOP  */
    ASSIGNOP = 271,                /* ASSIGNOP  */
    RELOP = 272,                   /* RELOP  */
    LOGICOP = 273,                 /* LOGICOP  */
    NOT = 274,                     /* NOT  */
    SEMICOLON = 275,               /* SEMICOLON  */
    COMMA = 276,                   /* COMMA  */
    LPAREN = 277,                  /* LPAREN  */
    RPAREN = 278,                  /* RPAREN  */
    LCURL = 279,                   /* LCURL  */
    RCURL = 280,                   /* RCURL  */
    LTHIRD = 281,                  /* LTHIRD  */
    RTHIRD = 282,                  /* RTHIRD  */
    INCOP = 283,                   /* INCOP  */
    DECOP = 284,                   /* DECOP  */
    CONST_INT = 285,               /* CONST_INT  */
    CONST_FLOAT = 286,             /* CONST_FLOAT  */
    ID = 287,                      /* ID  */
    LOWER_THAN_ELSE = 288          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
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
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_FOR = 5,                        /* FOR  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_FLOAT = 8,                      /* FLOAT  */
  YYSYMBOL_DOUBLE = 9,                     /* DOUBLE  */
  YYSYMBOL_CHAR = 10,                      /* CHAR  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_VOID = 12,                      /* VOID  */
  YYSYMBOL_PRINTLN = 13,                   /* PRINTLN  */
  YYSYMBOL_ADDOP = 14,                     /* ADDOP  */
  YYSYMBOL_MULOP = 15,                     /* MULOP  */
  YYSYMBOL_ASSIGNOP = 16,                  /* ASSIGNOP  */
  YYSYMBOL_RELOP = 17,                     /* RELOP  */
  YYSYMBOL_LOGICOP = 18,                   /* LOGICOP  */
  YYSYMBOL_NOT = 19,                       /* NOT  */
  YYSYMBOL_SEMICOLON = 20,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 21,                     /* COMMA  */
  YYSYMBOL_LPAREN = 22,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 23,                    /* RPAREN  */
  YYSYMBOL_LCURL = 24,                     /* LCURL  */
  YYSYMBOL_RCURL = 25,                     /* RCURL  */
  YYSYMBOL_LTHIRD = 26,                    /* LTHIRD  */
  YYSYMBOL_RTHIRD = 27,                    /* RTHIRD  */
  YYSYMBOL_INCOP = 28,                     /* INCOP  */
  YYSYMBOL_DECOP = 29,                     /* DECOP  */
  YYSYMBOL_CONST_INT = 30,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 31,               /* CONST_FLOAT  */
  YYSYMBOL_ID = 32,                        /* ID  */
  YYSYMBOL_LOWER_THAN_ELSE = 33,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 34,                  /* $accept  */
  YYSYMBOL_start = 35,                     /* start  */
  YYSYMBOL_program = 36,                   /* program  */
  YYSYMBOL_unit = 37,                      /* unit  */
  YYSYMBOL_func_declaration = 38,          /* func_declaration  */
  YYSYMBOL_func_definition = 39,           /* func_definition  */
  YYSYMBOL_40_1 = 40,                      /* $@1  */
  YYSYMBOL_41_2 = 41,                      /* $@2  */
  YYSYMBOL_parameter_list = 42,            /* parameter_list  */
  YYSYMBOL_compound_statement = 43,        /* compound_statement  */
  YYSYMBOL_44_3 = 44,                      /* $@3  */
  YYSYMBOL_45_4 = 45,                      /* $@4  */
  YYSYMBOL_var_declaration = 46,           /* var_declaration  */
  YYSYMBOL_type_specifier = 47,            /* type_specifier  */
  YYSYMBOL_declaration_list = 48,          /* declaration_list  */
  YYSYMBOL_statements = 49,                /* statements  */
  YYSYMBOL_statement = 50,                 /* statement  */
  YYSYMBOL_expression_statement = 51,      /* expression_statement  */
  YYSYMBOL_variable = 52,                  /* variable  */
  YYSYMBOL_expression = 53,                /* expression  */
  YYSYMBOL_logic_expression = 54,          /* logic_expression  */
  YYSYMBOL_rel_expression = 55,            /* rel_expression  */
  YYSYMBOL_simple_expression = 56,         /* simple_expression  */
  YYSYMBOL_term = 57,                      /* term  */
  YYSYMBOL_unary_expression = 58,          /* unary_expression  */
  YYSYMBOL_factor = 59,                    /* factor  */
  YYSYMBOL_60_5 = 60,                      /* $@5  */
  YYSYMBOL_argument_list = 61,             /* argument_list  */
  YYSYMBOL_arguments = 62                  /* arguments  */
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

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   288


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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   221,   221,   256,   262,   269,   274,   279,   287,   338,
     369,   368,   446,   445,   511,   519,   525,   532,   540,   539,
     580,   579,   621,   674,   678,   681,   686,   691,   696,   700,
     707,   711,   719,   724,   729,   734,   760,   776,   794,   813,
     823,   838,   843,   849,   871,   918,   924,   952,   957,  1020,
    1024,  1093,  1098,  1150,  1155,  1213,  1229,  1251,  1258,  1275,
    1274,  1328,  1333,  1343,  1354,  1382,  1413,  1418,  1421,  1430
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
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "FOR",
  "WHILE", "INT", "FLOAT", "DOUBLE", "CHAR", "RETURN", "VOID", "PRINTLN",
  "ADDOP", "MULOP", "ASSIGNOP", "RELOP", "LOGICOP", "NOT", "SEMICOLON",
  "COMMA", "LPAREN", "RPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD",
  "INCOP", "DECOP", "CONST_INT", "CONST_FLOAT", "ID", "LOWER_THAN_ELSE",
  "$accept", "start", "program", "unit", "func_declaration",
  "func_definition", "$@1", "$@2", "parameter_list", "compound_statement",
  "$@3", "$@4", "var_declaration", "type_specifier", "declaration_list",
  "statements", "statement", "expression_statement", "variable",
  "expression", "logic_expression", "rel_expression", "simple_expression",
  "term", "unary_expression", "factor", "$@5", "argument_list",
  "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-73)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-21)

#define yytable_value_is_error(Yyn) \
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
static const yytype_int8 yydefact[] =
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
       0,     4,     5,     6,     7,     8,    35,    25,    20,    54,
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

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
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

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    37,    38,    38,
      40,    39,    41,    39,    42,    42,    42,    42,    44,    43,
      45,    43,    46,    47,    47,    47,    48,    48,    48,    48,
      49,    49,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    51,    51,    52,    52,    53,    53,    54,    54,    55,
      55,    56,    56,    57,    57,    58,    58,    58,    59,    60,
      59,    59,    59,    59,    59,    59,    61,    61,    62,    62
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     6,     4,     3,     2,     1,     0,     4,
       0,     3,     3,     1,     1,     1,     3,     6,     1,     4,
       1,     2,     1,     1,     1,     7,     5,     7,     5,     5,
       3,     1,     2,     1,     4,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     2,     2,     1,     1,     0,
       5,     3,     1,     1,     2,     2,     1,     0,     3,     1
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
  case 2: /* start: program  */
#line 222 "1605010.y"
                     {
					  yyval = yyvsp[0];

					  if(error_count == 0)
					  {

						  fprintf(asm_out,".MODEL SMALL\n.STACK 100H\n.DATA\n");
						  fprintf(asm_out,"%s DW ?\n",ret_var.c_str());
						  for(string s : variables)
						  {
							  fprintf(asm_out,"%s DW ?\n",s.c_str());
						  }
						  for(int i=0;i<arrays.size();i++)
						  {
							  fprintf(asm_out,"%s DW %s DUP(?)\n",arrays[i].c_str(),array_sizes[i].c_str());
						  }
						  fprintf(asm_out,".CODE\n");
						  fprintf(asm_out,print_code().c_str());
						 
						  fprintf(asm_out,yyval->code.c_str());
 




					  }
					  else
					  {
						  fprintf(error_out,"Total number of errors : %d\n",line_count);

					  }
		           
	             }
#line 1553 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 257 "1605010.y"
                  {
					  yyval = new SymbolInfo(yyvsp[-1]->get_name()+"\n"+yyvsp[0]->get_name(),"");
					  yyval->code += (yyvsp[-1]->code + yyvsp[0]->code);
				 
				  }
#line 1563 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 263 "1605010.y"
                      {
					  yyval = yyvsp[0];
                    
				  }
#line 1572 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 270 "1605010.y"
                  {
					  yyval = yyvsp[0];
                      
				  }
#line 1581 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 275 "1605010.y"
                      {
					  yyval = yyvsp[0];
                     
				  }
#line 1590 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 280 "1605010.y"
                      { 
					  yyval = yyvsp[0];
					  
                      
				  }
#line 1600 "y.tab.c"
    break;

  case 8: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 288 "1605010.y"
                  {
					  yyval = new SymbolInfo(yyvsp[-5]->get_name()+" "+yyvsp[-4]->get_name()+yyvsp[-3]->get_name()+yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name()+"\n","");
                      string return_type = yyvsp[-5]->get_name();
					  string function_name = yyvsp[-4]->get_name();
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
 

					  current_parameter_list_name.clear();
					  current_parameter_list_type.clear();
				  }
#line 1655 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 339 "1605010.y"
                          {
					  yyval = new SymbolInfo(yyvsp[-4]->get_name()+" "+yyvsp[-3]->get_name()+yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name()+"\n","");
                    
					  string return_type = yyvsp[-4]->get_name();
					  string function_name = yyvsp[-3]->get_name();
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
 
					  current_parameter_list_name.clear();
					  current_parameter_list_type.clear();
				  }
#line 1687 "y.tab.c"
    break;

  case 10: /* $@1: %empty  */
#line 369 "1605010.y"
                  {
					  current_return_type = yyvsp[-4]->get_name();
					  string function_name = yyvsp[-3]->get_name();
					  SymbolInfo *temp = table->my_look_up(function_name);

					  current_func_name = yyvsp[-3]->name;

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
						  temp->is_defined_yet = 1;
					  }	  
				  }
#line 1716 "y.tab.c"
    break;

  case 11: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement  */
#line 394 "1605010.y"
                  {
					  yyval = new SymbolInfo(yyvsp[-6]->get_name()+" "+yyvsp[-5]->get_name()+yyvsp[-4]->get_name()+yyvsp[-3]->get_name()+yyvsp[-2]->get_name()+"\n"+yyvsp[0]->get_name(),"");
					  
                      string code = "";
					  
					  if(yyvsp[-5]->name == "main")
					  {
						  code += "MAIN PROC\nMOV AX,@DATA \nMOV DS,AX\n";
						
					  }
					  else
					  {
						   code  += (yyvsp[-5]->name + " PROC\n");

                           
						//    code += "PUSH AX\nPUSH BX \nPUSH CX\nPUSH DX\n";
						//    SymbolInfo *temp = table->my_look_up($2->name);
						//    vector<string>parameter = temp->parameter_list;
						//    for(int i=0;i<parameter.size();i++)
						//    {
						// 	   code += ("PUSH " + parameter[i] + "\n");
						//    }

					  }
                      code += yyvsp[0]->code;
					  code += ("FINISHED_"+ yyvsp[-5]->name + ":\n");
					  if(yyvsp[-5]->name == "main")
					  {
						  code += "MOV AH,4CH\nINT 21H\nMAIN ENDP\nEND MAIN\n";
					  }
					  else
					  {
						   
						//    SymbolInfo *temp = table->my_look_up($2->name);
						//    vector<string>parameter = temp->parameter_list;

						//    for(int i=parameter.size()-1;i>=0;i--)
						//    {
						// 	   code += ("POP " + parameter[i] + "\n");
						//    }

						//    code += "POP DX\nPOP CX \nPOP BX\nPOP AX\n";
						   code += "RET\n";
						   code += (yyvsp[-5]->name + " ENDP\n\n");
					  }

					  yyval->code = code;

					  
                    
				  }
#line 1772 "y.tab.c"
    break;

  case 12: /* $@2: %empty  */
#line 446 "1605010.y"
                          {

					  current_return_type = yyvsp[-3]->get_name();
					  string function_name = yyvsp[-2]->get_name();

					  
					  current_func_name = yyvsp[-2]->name;
 
                      
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
						  temp->is_defined_yet = 1; 
					  }	  

				  }
#line 1805 "y.tab.c"
    break;

  case 13: /* func_definition: type_specifier ID LPAREN RPAREN $@2 compound_statement  */
#line 475 "1605010.y"
                          {
					  yyval = new SymbolInfo(yyvsp[-5]->get_name()+" "+yyvsp[-4]->get_name()+yyvsp[-3]->get_name()+yyvsp[-2]->get_name()+"\n"+yyvsp[0]->get_name(),"");
                      
				 
                      string code = "";
					 

					  if(yyvsp[-4]->name == "main")
					  {
						  code += "MAIN PROC\nMOV AX,@DATA \nMOV DS,AX\n";
						
					  }
					  else
					  {
						   code  += (yyvsp[-4]->name + " PROC\n");
						   //code += "PUSH AX\nPUSH BX \nPUSH CX\nPUSH DX\n";
						    

					  }
                      code += yyvsp[0]->code;
					  code += ("FINISHED_"+ yyvsp[-4]->name + ":\n");
					  if(yyvsp[-4]->name == "main")
					  {
						  code += "MOV AH,4CH\nINT 21H\nMAIN ENDP\nEND MAIN\n";
					  }
					  else
					  {
						  // code += "POP DX\nPOP CX \nPOP BX\nPOP AX\n";
						   code += "RET\n";
						   code += (yyvsp[-4]->name + " ENDP\n\n");
					  }

					  yyval->code = code;
                     
				  }
#line 1845 "y.tab.c"
    break;

  case 14: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 512 "1605010.y"
                  {
					  yyval = new SymbolInfo(yyvsp[-3]->get_name()+yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+" "+yyvsp[0]->get_name(),"");

					  current_parameter_list_type.push_back(yyvsp[-1]->get_name());
					  current_parameter_list_name.push_back(yyvsp[0]->get_name());
 
				  }
#line 1857 "y.tab.c"
    break;

  case 15: /* parameter_list: parameter_list COMMA type_specifier  */
#line 520 "1605010.y"
                          {
					  yyval = new SymbolInfo(yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");
					  current_parameter_list_type.push_back(yyvsp[0]->get_name());
                       
				  }
#line 1867 "y.tab.c"
    break;

  case 16: /* parameter_list: type_specifier ID  */
#line 526 "1605010.y"
                          {
					  yyval = new SymbolInfo(yyvsp[-1]->get_name()+" "+yyvsp[0]->get_name(),"");
					  current_parameter_list_type.push_back(yyvsp[-1]->get_name());
					  current_parameter_list_name.push_back(yyvsp[0]->get_name());
 
				  }
#line 1878 "y.tab.c"
    break;

  case 17: /* parameter_list: type_specifier  */
#line 533 "1605010.y"
                          {
					  yyval = yyvsp[0];
					  current_parameter_list_type.push_back(yyvsp[0]->get_name());
				  }
#line 1887 "y.tab.c"
    break;

  case 18: /* $@3: %empty  */
#line 540 "1605010.y"
                  {
	                table->enter_scope();

					SymbolInfo *temp = table->my_look_up(current_func_name);

					
					 
					
					current_scope_table_id = table->current_scope_table->get_id();
					string temp_name = int_to_string(current_scope_table_id);
					
					for(int i=0;i<current_parameter_list_name.size();i++)
					{
						
						SymbolInfo rhs;
						rhs.name = current_parameter_list_name[i];
						rhs.type = "ID";
						rhs.sub_type = current_parameter_list_type[i];
						rhs.name_with_id = rhs.name + temp_name;
						temp->parameter_list.push_back(rhs.name_with_id);
						variables.push_back(rhs.name_with_id);
						table->my_insert(rhs);

						

					}

					current_parameter_list_name.clear();
					current_parameter_list_type.clear();
					  

				  }
#line 1924 "y.tab.c"
    break;

  case 19: /* compound_statement: LCURL $@3 statements RCURL  */
#line 572 "1605010.y"
                  {
					  yyval = new SymbolInfo("{\n"+yyvsp[-1]->get_name()+"\n}","");
					  yyval->code += yyvsp[-1]->code; 
                    
				 
					  table->exit_scope();
				  }
#line 1936 "y.tab.c"
    break;

  case 20: /* $@4: %empty  */
#line 580 "1605010.y"
                              {
					  table->enter_scope();

					  SymbolInfo *temp = table->my_look_up(current_func_name);
		 

					  if(current_parameter_list_name.size()!=0)
					  { 
						  current_scope_table_id = table->current_scope_table->get_id();
					      string temp_name = int_to_string(current_scope_table_id);
					 
						  for(int i=0;i<current_parameter_list_name.size();i++)
						  {
							  SymbolInfo rhs;
							  rhs.name = current_parameter_list_name[i];
							  rhs.type = "ID";
							  rhs.sub_type = current_parameter_list_type[i];
							  rhs.name_with_id = rhs.name + temp_name;
							  variables.push_back(rhs.name_with_id);
							  temp->parameter_list.push_back(rhs.name_with_id);
							  table->my_insert(rhs);

							


							  
							   

						  }
						  current_parameter_list_name.clear();
					      current_parameter_list_type.clear();
					  }
 

				  }
#line 1976 "y.tab.c"
    break;

  case 21: /* compound_statement: LCURL $@4 RCURL  */
#line 615 "1605010.y"
                              {
					  yyval = new SymbolInfo("{}","");
					  table->exit_scope();
				  }
#line 1985 "y.tab.c"
    break;

  case 22: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 622 "1605010.y"
                  {
					  yyval = new SymbolInfo(yyvsp[-2]->get_name()+" "+yyvsp[-1]->get_name()+yyvsp[0]->get_name()+"\n","");

					  
					  string str = yyvsp[-1]->get_name();
					  str = change_comma_to_space(str);
					  vector<string> tokens = tokenize(str);
					  current_scope_table_id = table->current_scope_table->get_id();
					  string temp_name = int_to_string(current_scope_table_id);
					  for(string s : tokens)
					  {
						  
						  pair<bool,int> res = check_if_array(s);
						  if(res.first == 0)
						  {
							  SymbolInfo rhs;
							  rhs.name = s;
							  rhs.type = "ID";
							  rhs.sub_type = yyvsp[-2]->get_name();

							  rhs.name_with_id = s + temp_name;
 
							  variables.push_back(rhs.name_with_id);

							  SymbolInfo *temp = table->my_look_up_current(rhs.name);
 
							  
							   
							  table->my_insert(rhs);
							  
						  }
						  else
						  {
							   
								SymbolInfo rhs;
								rhs.name = arr_tream(s);
								rhs.type = "ID";
								rhs.sub_type = yyvsp[-2]->get_name();
								rhs.is_array = 1;
								rhs.arr_size = res.second;
								rhs.name_with_id = rhs.name + temp_name;
								arrays.push_back(rhs.name_with_id);
								array_sizes.push_back(int_to_string(rhs.arr_size));
								SymbolInfo *temp = table->my_look_up_current(rhs.name);  
								table->my_insert(rhs);
							      
						  }
					  }
			 
				  }
#line 2040 "y.tab.c"
    break;

  case 23: /* type_specifier: INT  */
#line 675 "1605010.y"
                  {   
					  yyval = yyvsp[0];				   
				  }
#line 2048 "y.tab.c"
    break;

  case 24: /* type_specifier: FLOAT  */
#line 678 "1605010.y"
                          {
			          yyval = yyvsp[0];
			      }
#line 2056 "y.tab.c"
    break;

  case 25: /* type_specifier: VOID  */
#line 681 "1605010.y"
                          {
			          yyval = yyvsp[0];
			      }
#line 2064 "y.tab.c"
    break;

  case 26: /* declaration_list: declaration_list COMMA ID  */
#line 687 "1605010.y"
                  {
					  yyval = new SymbolInfo(yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name(),""); 
                     
				  }
#line 2073 "y.tab.c"
    break;

  case 27: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 692 "1605010.y"
                          {
					  yyval = new SymbolInfo(yyvsp[-5]->get_name()+yyvsp[-4]->get_name()+yyvsp[-3]->get_name()+yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");
                   
				  }
#line 2082 "y.tab.c"
    break;

  case 28: /* declaration_list: ID  */
#line 697 "1605010.y"
                          {
					  yyval = yyvsp[0];
				  }
#line 2090 "y.tab.c"
    break;

  case 29: /* declaration_list: ID LTHIRD CONST_INT RTHIRD  */
#line 701 "1605010.y"
                          {
					  yyval = new SymbolInfo(yyvsp[-3]->get_name()+yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");
                      
				  }
#line 2099 "y.tab.c"
    break;

  case 30: /* statements: statement  */
#line 708 "1605010.y"
                 {
					  yyval = yyvsp[0];					   
				 }
#line 2107 "y.tab.c"
    break;

  case 31: /* statements: statements statement  */
#line 712 "1605010.y"
                     {
					  yyval = new SymbolInfo(yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");
					  yyval->code += (yyvsp[-1]->code + yyvsp[0]->code);
					 
				 }
#line 2117 "y.tab.c"
    break;

  case 32: /* statement: var_declaration  */
#line 720 "1605010.y"
                 {
					  yyval = yyvsp[0];
                      
				 }
#line 2126 "y.tab.c"
    break;

  case 33: /* statement: expression_statement  */
#line 725 "1605010.y"
                     {
					  yyval = yyvsp[0];
                      
				 }
#line 2135 "y.tab.c"
    break;

  case 34: /* statement: compound_statement  */
#line 730 "1605010.y"
                     {
					  yyval = yyvsp[0];
                    
				 }
#line 2144 "y.tab.c"
    break;

  case 35: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 735 "1605010.y"
                     {
					  yyval = new SymbolInfo(yyvsp[-6]->get_name()+yyvsp[-5]->get_name()+yyvsp[-4]->get_name()+yyvsp[-3]->get_name()+yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");
					
					  string label1 = new_label();
					  string label2 = new_label();

					  

					  yyval->code += (yyvsp[-4]->code + "\n");

					  yyval->code += (label1 + ":\n");
					  yyval->code += (yyvsp[-3]->code + "\n");
                       
					  if(yyvsp[-3]->name_with_id != ""){
					  	yyval->code += ("CMP " + yyvsp[-3]->name_with_id + ",0\n");
					  	yyval->code += ("JE " + label2 + "\n");
					  }

					  yyval->code += (yyvsp[0]->code + "\n");
					  yyval->code += (yyvsp[-2]->code + "\n");
					  yyval->code += ("JMP " + label1 + "\n");
					  yyval->code += (label2 + ":\n");

                       
				 }
#line 2174 "y.tab.c"
    break;

  case 36: /* statement: IF LPAREN expression RPAREN statement  */
#line 761 "1605010.y"
                     {
					yyval = new SymbolInfo(yyvsp[-4]->get_name()+yyvsp[-3]->get_name()+yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");
					  
					string label = new_label();

					yyval->code += yyvsp[-2]->code;
					yyval->code += ("CMP " + yyvsp[-2]->name_with_id + ",0\n");
					yyval->code += ("JE " + label + "\n");
					yyval->code += (yyvsp[0]->code + "\n");
					yyval->code += (label + ":\n");

					 
					
                  
				 }
#line 2194 "y.tab.c"
    break;

  case 37: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 777 "1605010.y"
                     {
					yyval = new SymbolInfo(yyvsp[-6]->get_name()+yyvsp[-5]->get_name()+yyvsp[-4]->get_name()+yyvsp[-3]->get_name()+yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");
                      

					string label1 = new_label();
					string label2 = new_label();

					yyval->code += yyvsp[-4]->code;
					yyval->code += ("CMP " + yyvsp[-4]->name_with_id + ",0\n");
					yyval->code += ("JE " + label1 + "\n");
					yyval->code += (yyvsp[-2]->code + "\n");
					yyval->code += ("JMP " + label2 + "\n");
					yyval->code += (label1 + ":\n");
					yyval->code += (yyvsp[0]->code + "\n");
					yyval->code += (label2 + ":\n");
                      
				 }
#line 2216 "y.tab.c"
    break;

  case 38: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 795 "1605010.y"
                     {
					  yyval = new SymbolInfo(yyvsp[-4]->get_name()+yyvsp[-3]->get_name()+yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");
					 

					  string label1 = new_label();
					  string label2 = new_label();

					  yyval->code += (label1 + ":\n");
					  yyval->code += yyvsp[-2]->code;
					  yyval->code += ("CMP " + yyvsp[-2]->name_with_id + ",0\n");
					  yyval->code += ("JE " + label2 + "\n");
					  yyval->code += (yyvsp[0]->code + "\n");
					  yyval->code += ("JMP " + label1 + "\n");
					  yyval->code += (label2 + ":\n");


                       
				 }
#line 2239 "y.tab.c"
    break;

  case 39: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 814 "1605010.y"
                     {
					  yyval = new SymbolInfo(yyvsp[-4]->get_name()+yyvsp[-3]->get_name()+yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name()+"\n","");
                      SymbolInfo *temp = table->my_look_up(yyvsp[-2]->name);

					  yyval->code += ("MOV AX," + temp->name_with_id + "\n");
					  yyval->code += ("CALL PRINT\n");

                  
				 }
#line 2253 "y.tab.c"
    break;

  case 40: /* statement: RETURN expression SEMICOLON  */
#line 824 "1605010.y"
                     {
					  yyval = new SymbolInfo(yyvsp[-2]->get_name()+" "+yyvsp[-1]->get_name()+yyvsp[0]->get_name()+"\n","");

					  yyval->code += yyvsp[-1]->code;
					  yyval->code += ("MOV AX," + yyvsp[-1]->name_with_id + "\n");
					  yyval->code += ("MOV " + ret_var + ",AX\n");
					  yyval->code += ("JMP FINISHED_" + current_func_name + "\n");
					  
					  
					  
                    
				 }
#line 2270 "y.tab.c"
    break;

  case 41: /* expression_statement: SEMICOLON  */
#line 839 "1605010.y"
                {
					  yyval = yyvsp[0];
                   
				}
#line 2279 "y.tab.c"
    break;

  case 42: /* expression_statement: expression SEMICOLON  */
#line 844 "1605010.y"
                            { 
					  yyval = yyvsp[-1];
				}
#line 2287 "y.tab.c"
    break;

  case 43: /* variable: ID  */
#line 850 "1605010.y"
                {
					  SymbolInfo *temp = table->my_look_up(yyvsp[0]->get_name());
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
						 
                          yyval = temp;  
					  }

					   
 
				}
#line 2313 "y.tab.c"
    break;

  case 44: /* variable: ID LTHIRD expression RTHIRD  */
#line 872 "1605010.y"
                    {
					  yyval = new SymbolInfo(yyvsp[-3]->get_name()+yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");

					  SymbolInfo *temp = table->my_look_up(yyvsp[-3]->get_name());

					  if(temp == nullptr)
					  {
						  fprintf(error_out,"At line no : %d undeclared variable\n",line_count);
						  error_count++;
					  }
					  else
					  {
						
						  
							if(yyvsp[-1]->sub_type != "int")
							{
								fprintf(error_out,"At line no : %d array index should be int\n",line_count);
								error_count++;
							}
							else
							{
								int my_arr_size = atoi(yyvsp[-1]->name.c_str());
								int mx_arr_size = temp->arr_size;

								if(my_arr_size<0||my_arr_size>=mx_arr_size)
								{
									fprintf(error_out,"At line no : %d index out of bound\n",line_count);
									error_count++;
								}

							}

							yyval->sub_type = temp->sub_type;
							yyval->is_array = temp->is_array;
							yyval->arr_size = temp->arr_size;
							yyval->name_with_id = temp->name_with_id;
							yyval->code = yyvsp[-1]->code+"MOV BX, " +yyvsp[-1]->name_with_id +"\nADD BX, BX\n";

							 
					  }


                   
				}
#line 2362 "y.tab.c"
    break;

  case 45: /* expression: logic_expression  */
#line 919 "1605010.y"
                {
					  yyval = yyvsp[0];
					//  fprintf(asm_out,"%s\n",$$->code.c_str());
                       
				}
#line 2372 "y.tab.c"
    break;

  case 46: /* expression: variable ASSIGNOP logic_expression  */
#line 925 "1605010.y"
                    {
					  
					  

					  yyval = new SymbolInfo(yyvsp[-2]->name + yyvsp[-1]->code + yyvsp[0]->name,"");

				      yyval->code = yyvsp[0]->code+yyvsp[-2]->code;

				      yyval->code += "MOV AX, "+yyvsp[0]->name_with_id+"\n";

				      if(yyvsp[-2]->is_array)
					  { 
						  yyval->code += "MOV  "+yyvsp[-2]->name_with_id+"[BX], AX\n";
				      }
				      else
					  {
						  yyval->code += "MOV "+yyvsp[-2]->name_with_id+", AX\n";
				      }

					  

					//  fprintf(asm_out,"%s\n",$$->code.c_str());
   
                   
				}
#line 2402 "y.tab.c"
    break;

  case 47: /* logic_expression: rel_expression  */
#line 953 "1605010.y"
                {
					  yyval = yyvsp[0];
                    
				}
#line 2411 "y.tab.c"
    break;

  case 48: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 958 "1605010.y"
                        {
					  yyval = new SymbolInfo(yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");

					  if((yyvsp[-2]->sub_type != yyvsp[0]->sub_type)&&(yyvsp[-2]->sub_type != "int"))
					  {
						  fprintf(error_out,"At line no : %d type mismatch\n",line_count);
						  error_count++;
					  }

					yyval->sub_type = "int";

					yyval->code += yyvsp[-2]->code;
					yyval->code += yyvsp[0]->code;

					yyval->code += "MOV AX, " + yyvsp[-2]->name_with_id+"\n";
					yyval->code+="MOV BX, " + yyvsp[0]->name_with_id+"\n";

					string temp = new_temp();
					variables.push_back(temp);

					string label1 = new_label();
					string label2 = new_label();
 
					
					if(yyvsp[-1]->name=="&&")
					{
						yyval->code += ("CMP AX,0\n");
						yyval->code += ("JE " + label1 + "\n");
						yyval->code += ("CMP BX,0\n");
						yyval->code += ("JE " + label1 + "\n");
						yyval->code += ("MOV " + temp + ",1\n");
						yyval->code += ("JMP " + label2 + "\n");
						yyval->code += (label1 + ":\n");
						yyval->code += ("MOV " + temp + ",0\n");
						yyval->code += (label2 + ":\n");

						 
						 
					}
					else if(yyvsp[-1]->name=="||")
					{
						yyval->code += ("CMP AX,0\n");
						yyval->code += ("JNE " + label1 + "\n");
						yyval->code += ("CMP BX,0\n");
						yyval->code += ("JNE " + label1 + "\n");
						yyval->code += ("MOV " + temp + ",0\n");
						yyval->code += ("JMP " + label2 + "\n");
						yyval->code += (label1 + ":\n");
						yyval->code += ("MOV " + temp + ",1\n");
						yyval->code += (label2 + ":\n");
						 
						
					}

					yyval->name_with_id = temp;
					


                    
				}
#line 2476 "y.tab.c"
    break;

  case 49: /* rel_expression: simple_expression  */
#line 1021 "1605010.y"
                {
					  yyval = yyvsp[0];
				}
#line 2484 "y.tab.c"
    break;

  case 50: /* rel_expression: simple_expression RELOP simple_expression  */
#line 1025 "1605010.y"
                        {
					  yyval = new SymbolInfo(yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");

					  

					 
					  yyval->code += yyvsp[-2]->code;
					  yyval->code += yyvsp[0]->code;

					  yyval->code += "MOV AX, " + yyvsp[-2]->name_with_id+"\n";
					  yyval->code +="CMP AX, " + yyvsp[0]->name_with_id+"\n";

					  string temp = new_temp();
					  variables.push_back(temp);

					  string label1 = new_label();
				      string label2 = new_label();

					  if(yyvsp[-1]->name == "<")
					  {
							yyval->code+="JL " + label1+"\n";
					  }
					  else if(yyvsp[-1]->name=="<=")
					  {
						  yyval->code+="JLE " + label1+"\n";
					  }
					  else if(yyvsp[-1]->name==">")
					  {
						  yyval->code+="JG " + label1+"\n";
					  }
					  else if(yyvsp[-1]->name==">=")
					  {
						  yyval->code+="JGE " + label1+"\n";
					  }
					  else if(yyvsp[-1]->name=="==")
					  {
						  yyval->code+="JE " + label1+"\n";
					  }
					  else if(yyvsp[-1]->name == "!=")
					  {
						  yyval->code+="JNE " + label1+"\n";

					  }
						
					  yyval->code += "MOV "+ temp +", 0\n";
					  yyval->code += "JMP "+ label2 +"\n";

					  yyval->code += label1 + ":\n";
					  yyval->code += "MOV "+ temp +", 1\n";
					  yyval->code += label2+":\n";

					  yyval->name_with_id = temp;

					 



					  

					  
						



                     
				}
#line 2555 "y.tab.c"
    break;

  case 51: /* simple_expression: term  */
#line 1094 "1605010.y"
                {  
					  yyval = yyvsp[0];
                    
			    }
#line 2564 "y.tab.c"
    break;

  case 52: /* simple_expression: simple_expression ADDOP term  */
#line 1099 "1605010.y"
                        {
					  yyval = new SymbolInfo(yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");

					  if(yyvsp[-2]->sub_type == "void" || yyvsp[0]->sub_type == "void")
					  {
						  fprintf(error_out,"At line no : %d type mismatch\n",line_count);
						  error_count++;
					  }
					  else if(yyvsp[-2]->sub_type != yyvsp[0]->sub_type)
					  {
							yyval->sub_type = "float";  
					  }
					  else if(yyvsp[-2]->sub_type == yyvsp[0]->sub_type)
					  {
						  yyval->sub_type = yyvsp[-2]->sub_type;
					  }

					  yyval->code += yyvsp[-2]->code;
					  yyval->code += yyvsp[0]->code;

					  

					  yyval->code += "MOV AX, "+ yyvsp[-2]->name_with_id+"\n";

					 
					  yyval->code += "MOV BX, "+ yyvsp[0]->name_with_id +"\n";

					   

					  string temp = new_temp();
					  variables.push_back(temp);

					  if(yyvsp[-1]->name == "+")
					  {
							yyval->code += "ADD AX, BX\n";
							yyval->code += "MOV "+ temp + ", AX\n";
					  }
					  else if(yyvsp[-1]->name == "-")
					  {
							 
							yyval->code += ("SUB AX, BX\n");
							yyval->code += ("MOV " + temp + ", AX\n");
					 }
							  
					 yyval->name_with_id = temp; 

		 
                   
				}
#line 2618 "y.tab.c"
    break;

  case 53: /* term: unary_expression  */
#line 1151 "1605010.y"
                {
					  yyval = yyvsp[0];
                      
				}
#line 2627 "y.tab.c"
    break;

  case 54: /* term: term MULOP unary_expression  */
#line 1156 "1605010.y"
                    {
					yyval = new SymbolInfo(yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");
					yyval->sub_type = "int";

                      
					yyval->code += yyvsp[-2]->code;
					yyval->code += yyvsp[0]->code;

					yyval->code += "MOV AX, "+ yyvsp[-2]->name_with_id+"\n";
					yyval->code += "MOV BX, "+ yyvsp[0]->name_with_id +"\n";

					string temp = new_temp();
					variables.push_back(temp);

					if(yyvsp[-1]->name == "*")
					{
						yyval->code += "IMUL BX\n";
						yyval->code += "MOV "+ temp + ", AX\n";
					}
					else if(yyvsp[-1]->name == "/")
					{
					
						string label1 = new_label();
						string label2 = new_label();

						yyval->code += ("CMP AX,0\n");
						yyval->code += ("JGE " + label1 + "\n");
						yyval->code += ("MOV DX,-1\n");
						yyval->code += ("JMP " + label2+"\n");
						yyval->code += (label1 + ":\n"); 
						yyval->code += ("MOV DX,0\n");
						yyval->code += (label2 + ":\n");
						yyval->code += ("IDIV BX\n");
						yyval->code += ("MOV " + temp + ", AX\n");
					}
					else
					{

						string label1 = new_label();
						string label2 = new_label();

						yyval->code += ("CMP AX,0\n");
						yyval->code += ("JGE " + label1 + "\n");
						yyval->code += ("MOV DX,-1\n");
						yyval->code += ("JMP " + label2+"\n");
						yyval->code += (label1 + ":\n"); 
						yyval->code += ("MOV DX,0\n");
						yyval->code += (label2 + ":\n");
						yyval->code += ("IDIV BX\n");
						yyval->code += ("MOV " + temp + ", DX\n");
					}
					
					yyval->name_with_id = temp;  
			

				}
#line 2688 "y.tab.c"
    break;

  case 55: /* unary_expression: ADDOP unary_expression  */
#line 1214 "1605010.y"
                {
					  yyval = new SymbolInfo(yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");
					  yyval->code += yyvsp[0]->code;
					  if(yyvsp[-1]->name == "-")
					  {
						  string temp = new_temp();
					      variables.push_back(temp);

					      yyval->code += ("MOV AX, " + yyvsp[0]->name_with_id + "\n");
					      yyval->code += ("NEG AX\n");
					      yyval->code += ("MOV " + temp +", AX\n");
					      yyval->name_with_id = temp;
					  }
                 
				}
#line 2708 "y.tab.c"
    break;

  case 56: /* unary_expression: NOT unary_expression  */
#line 1230 "1605010.y"
                        {
					yyval = new SymbolInfo(yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");
					yyval->code += yyvsp[0]->code;
					string temp = new_temp();
					variables.push_back(temp);
					string label1 = new_label();
					string label2 = new_label();


					yyval->code += ("MOV AX, " + yyvsp[0]->name_with_id + "\n");
					yyval->code += ("CMP AX,0\n");
					yyval->code += ("JE" + label1 + "\n");
					yyval->code += ("MOV " + temp + ",0\n");
					yyval->code += ("JMP " + label2 + "\n");
					yyval->code += (label1 + ":\n");
					yyval->code += ("MOV "+ temp +", 1\n");
					yyval->code += (label2 + ":\n");


					yyval->name_with_id = temp;
			    }
#line 2734 "y.tab.c"
    break;

  case 57: /* unary_expression: factor  */
#line 1252 "1605010.y"
                        {
					  yyval = yyvsp[0];
                     
				}
#line 2743 "y.tab.c"
    break;

  case 58: /* factor: variable  */
#line 1259 "1605010.y"
                {
					  yyval = yyvsp[0];

					  if(yyval->is_array)
					  {

						  string temp= new_temp();
						  variables.push_back(temp);
						  
				          yyval->code += "MOV AX, " + yyvsp[0]->name_with_id + "[BX]\n";
				          yyval->code += "MOV " + temp + ", AX\n";
				          yyval->name_with_id = temp;
					  }
                 
				}
#line 2763 "y.tab.c"
    break;

  case 59: /* $@5: %empty  */
#line 1275 "1605010.y"
                    {
					 current_argument_list.push(vector<string>());
					 current_argument_name_with_id.push(vector<string>());
				}
#line 2772 "y.tab.c"
    break;

  case 60: /* factor: ID LPAREN $@5 argument_list RPAREN  */
#line 1279 "1605010.y"
                    {
					  yyval = new SymbolInfo(yyvsp[-4]->get_name()+yyvsp[-3]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");
					  SymbolInfo *temp = table->my_look_up(yyvsp[-4]->get_name());

					  vector<string>parameter = temp->parameter_list;

					  string code = yyvsp[-1]->code;

					  for(int i=0;i<parameter.size();i++)
					  {
						  code += ("MOV AX," + current_argument_name_with_id.top()[i] + "\n");
						  code += ("MOV " + parameter[i] + ",AX\n");
					  }

					   //code += "PUSH AX\nPUSH BX \nPUSH CX\nPUSH DX\n";
					   code += "PUSHA\n";
						    
					   for(int i=0;i<parameter.size();i++)
					   {
							code += ("PUSH " + parameter[i] + "\n");
					   }

					  code += ("CALL " + yyvsp[-4]->name + "\n");
 
					  for(int i=parameter.size()-1;i>=0;i--)
					  {
						   code += ("POP " + parameter[i] + "\n");
					  }

					  //code += "POP DX\nPOP CX \nPOP BX\nPOP AX\n";
					  code += "POPA\n";

					  string temp1 = new_temp();
					  variables.push_back(temp1);

					  code += ("MOV AX," +ret_var + "\n");
					  code += ("MOV " + temp1 + ",AX\n");

					  yyval->code = code;
					  yyval->name_with_id = temp1;
					  
					   
					  yyval->sub_type = temp->return_type;
					  current_argument_list.pop();


               
					  
				}
#line 2826 "y.tab.c"
    break;

  case 61: /* factor: LPAREN expression RPAREN  */
#line 1329 "1605010.y"
                    {
					  yyval = yyvsp[-1];
                   
				}
#line 2835 "y.tab.c"
    break;

  case 62: /* factor: CONST_INT  */
#line 1334 "1605010.y"
                    {
					  yyval = yyvsp[0];
					  string temp = new_temp();
					  variables.push_back(temp);
					  yyval->sub_type = "int";
					  yyval->name_with_id = temp;
					  yyval->code += ("MOV " + temp + "," + yyvsp[0]->name + "\n");
                   
				}
#line 2849 "y.tab.c"
    break;

  case 63: /* factor: CONST_FLOAT  */
#line 1344 "1605010.y"
                    {
					  yyval = yyvsp[0];
					  string temp = new_temp();
					  variables.push_back(temp);
					  yyval->sub_type = "float";
					  yyval->name_with_id = temp;

					  yyval->code += ("MOV " + temp + "," + yyvsp[0]->name + "\n");
                   
				}
#line 2864 "y.tab.c"
    break;

  case 64: /* factor: variable INCOP  */
#line 1355 "1605010.y"
                    {
					  yyval = new SymbolInfo(yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");
					  string temp = new_temp();
					  variables.push_back(temp);
					  if(yyvsp[-1]->is_array)
					  {
					      //$$->code += ("MOV " + temp + ", " + $1->name_with_id + "[BX]\n");
						  //$$->code += ("\nINC " + $1->name_with_id + "[BX]\n");

						  yyval->code += ("MOV AX," + yyvsp[-1]->name_with_id + "[BX]\n");
						  yyval->code += ("MOV " + temp + ", "+ "AX\n");
						  yyval->code += ("INC " + yyvsp[-1]->name_with_id + "[BX]\n");


					  }
					  else
					  {
						  yyval->code += ("MOV AX," + yyvsp[-1]->name_with_id + "\n");
						  yyval->code += ("MOV " + temp + ", "+ "AX\n");
						  yyval->code += ("INC " + yyvsp[-1]->name_with_id + "\n");

					  }

					  yyval->name_with_id = temp;
					  
                  
				}
#line 2896 "y.tab.c"
    break;

  case 65: /* factor: variable DECOP  */
#line 1383 "1605010.y"
                    {
					  yyval = new SymbolInfo(yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");
					  string temp = new_temp();
					  variables.push_back(temp);
					  if(yyvsp[-1]->is_array)
					  {
					      //$$->code += ("MOV " + temp + ", " + $1->name_with_id + "[BX]\n");
						  //$$->code += ("DEC " + $1->name_with_id + "[BX]\n");

						  yyval->code += ("MOV AX," + yyvsp[-1]->name_with_id + "[BX]\n");
						  yyval->code += ("MOV " + temp + ", "+ "AX\n");
						  yyval->code += ("DEC " + yyvsp[-1]->name_with_id + "[BX]\n");


					  }
					  else
					  {
						  yyval->code += ("MOV AX," + yyvsp[-1]->name_with_id + "\n");
						  yyval->code += ("MOV " + temp + ", "+ "AX\n");
						  yyval->code += ("DEC " + yyvsp[-1]->name_with_id + "\n");

					  }

					  yyval->name_with_id = temp;
					  
					  
                   
				}
#line 2929 "y.tab.c"
    break;

  case 66: /* argument_list: arguments  */
#line 1414 "1605010.y"
               {
					  yyval = yyvsp[0];
				 
			   }
#line 2938 "y.tab.c"
    break;

  case 67: /* argument_list: %empty  */
#line 1418 "1605010.y"
                            { yyval = new SymbolInfo();}
#line 2944 "y.tab.c"
    break;

  case 68: /* arguments: arguments COMMA logic_expression  */
#line 1422 "1605010.y"
               {
				      yyval = new SymbolInfo(yyvsp[-2]->get_name()+yyvsp[-1]->get_name()+yyvsp[0]->get_name(),"");
					  current_argument_list.top().push_back(yyvsp[0]->sub_type);
					  current_argument_name_with_id.top().push_back(yyvsp[0]->name_with_id);
					  yyval->code += (yyvsp[-2]->code + yyvsp[0]->code);

                    
			   }
#line 2957 "y.tab.c"
    break;

  case 69: /* arguments: logic_expression  */
#line 1431 "1605010.y"
                       {
				      yyval = yyvsp[0];
					  current_argument_list.top().push_back(yyvsp[0]->sub_type);
					  current_argument_name_with_id.top().push_back(yyvsp[0]->name_with_id);
					  
			   }
#line 2968 "y.tab.c"
    break;


#line 2972 "y.tab.c"

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

#line 1439 "1605010.y"

int main(int argc,char *argv[])
{
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	error_out = fopen("1605010_log.txt","w");
	asm_out = fopen("1605010_code.asm","w");


	yyin=fp;
	yyparse();

	fprintf(error_out,"Total number of error : %d",error_count);

	fclose(error_out);
	fclose(asm_out);


	string str_1,str_2,str_3,str_4;
	vector<string>token_1,token_2;

	vector<string>out,t_out;
	bool ok = 0;


	ifstream fin; 
	fin.open("1605010_code.asm");
	while(fin)
	{
		getline(fin,str_1);	
		if(str_1.size() != 0)
		{
			out.push_back(str_1);
		}
		
	}
	fin.close();
	 
	while(true)
	{
		 
		for(int i=0;i<out.size()-1;i++)
		{
			
			str_1 = out[i];
			str_2 = out[i+1];

			str_3 = change_comma_to_space(str_1);
			str_4 = change_comma_to_space(str_2);

			token_1 = tokenize(str_3);
			token_2 = tokenize(str_4);

			if(token_1[0] == "MOV" && token_2[0] == "MOV")
			{
				if(token_1[1] == token_2[2] && token_1[2] == token_2[1])
				{
					t_out.push_back(str_1);
					i++;
					ok = 1;
				}
				else
				{
					t_out.push_back(str_1);
				}
			}
			else
			{
				t_out.push_back(str_1);
			}
	
		}

		if(!ok)
		{
			break;
		}
		else
		{
			out.clear();
			for(int i=0;i<t_out.size();i++)
			{
				out.push_back(t_out[i]);
			}
			t_out.clear();
		}

		ok = 0;
	}

	ofstream fout;
	fout.open("1605010_Code.asm");
	for(int i=0;i<out.size();i++)
	{
		fout<<out[i]<<endl;
	}
	fout.close();
	out.clear();

		
	return 0;
}

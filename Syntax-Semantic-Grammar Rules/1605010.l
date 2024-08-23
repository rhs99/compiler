%{
#include<bits/stdc++.h>
#include "MySymbolTable.h"
#include "y.tab.h"


using namespace std;

extern YYSTYPE yylval;
extern SymbolTable *table;
void yyerror(char *);

int line_count=1;
int error=0;


%}



digit [0-9]
letter [A-Za-z]
delim [ \t\r\f\v]
newline \n
ws [delim]+
id (_|{letter})(_|{letter}|{digit})*
integer {digit}+
number {digit}*(\.{digit}+)?(E[+-]?{digit}+)?
ADDOP [+-] 
MULOP [*/%]

%%

{delim}+	{}
{newline} {line_count++;}

"if"        {
	            SymbolInfo *s = new SymbolInfo(yytext,"IF");
				yylval = s;
	            return IF;
			}
"else"      {
	            SymbolInfo *s = new SymbolInfo(yytext,"ELSE");
				yylval = s;
			    return ELSE;
			}
"for"       {
	            SymbolInfo *s = new SymbolInfo(yytext,"FOR");
				yylval = s;
	            return FOR;
			}
"while"     { 
	            SymbolInfo *s = new SymbolInfo(yytext,"WHILE");
				yylval = s;
				return WHILE;
			}
"int"       {
	            SymbolInfo *s = new SymbolInfo(yytext,"INT");
				yylval = s;
	        	return INT;
			}
"float"     {   
	            SymbolInfo *s = new SymbolInfo(yytext,"FLOAT");
				yylval = s;
	            return FLOAT;
			}
"double"    {
	            SymbolInfo *s = new SymbolInfo(yytext,"DOUBLE");
				yylval = s;
	            return DOUBLE;
			}
"char"      {
	            SymbolInfo *s = new SymbolInfo(yytext,"CHAR");
				yylval = s;
	            return CHAR;
			}
"return"    {
	            SymbolInfo *s = new SymbolInfo(yytext,"RETURN");
				yylval = s;
	            return RETURN;
			}
"void"      {  
	            SymbolInfo *s = new SymbolInfo(yytext,"VOID");
				yylval = s; 
	            return VOID;
			}

"println"	{   
	            SymbolInfo *s = new SymbolInfo(yytext,"PRINTLN");
				yylval = s;
	            return PRINTLN;
			}

{ADDOP} { 
			SymbolInfo *s= new  SymbolInfo(yytext,"ADDOP");
			yylval = s;
			return ADDOP;
		}



{MULOP}	{
			SymbolInfo *s= new  SymbolInfo(yytext,"MULOP");
			yylval = s;
			return MULOP;
		}


"=" 	{   
	        SymbolInfo *s = new SymbolInfo(yytext,"ASSIGNOP");
			yylval = s;
	        return ASSIGNOP;
		}

">" |
"<" |
">=" |
"<=" |
"==" |
"!=" {
		SymbolInfo *s= new  SymbolInfo(yytext,"RELOP");
		yylval = s;
		return RELOP;
	}

"&&"	|
"||"	{
			SymbolInfo *s= new  SymbolInfo(yytext,"LOGICOP");
			yylval = s;
			return LOGICOP;
		}
"!"		{	
	        SymbolInfo *s = new SymbolInfo(yytext,"FLOAT");
			yylval = s;
			return NOT; 
		}


";" 	{ 
	        SymbolInfo *s = new SymbolInfo(yytext,"FLOAT");
			yylval = s;
	        return SEMICOLON;
		}
"," 	{
	        SymbolInfo *s = new SymbolInfo(yytext,"COMMA");
			yylval = s;
	        return COMMA;
		}
"(" 	{
	        SymbolInfo *s = new SymbolInfo(yytext,"LPAREN");
			yylval = s;
	        return LPAREN;
		}
")" 	{
	        SymbolInfo *s = new SymbolInfo(yytext,"RPAREN");
			yylval = s;
	        return RPAREN;
		}
"{" 	{
	        SymbolInfo *s = new SymbolInfo(yytext,"LCURL");
			yylval = s;
	        return LCURL;
		}
"}" 	{
	        SymbolInfo *s = new SymbolInfo(yytext,"RCURL");
			yylval = s;
	        return RCURL;
		}
"[" 	{
	        SymbolInfo *s = new SymbolInfo(yytext,"LTHIRD");
			yylval = s;
	        return LTHIRD;
		}
"]" 	{    
	        SymbolInfo *s = new SymbolInfo(yytext,"RTHIRD");
			yylval = s;
	        return RTHIRD;
		}
"++" 	{
	        SymbolInfo *s = new SymbolInfo(yytext,"INCOP");
			yylval = s;
	        return INCOP;
		}
"--" 	{
	        SymbolInfo *s = new SymbolInfo(yytext,"DECOP");
			yylval = s;
	        return DECOP;
		}



{integer}	{
				SymbolInfo *s= new  SymbolInfo(yytext,"CONST_INT");
				yylval = s;
				return CONST_INT;
			}
{number} 	{	
				SymbolInfo *s= new  SymbolInfo(yytext,"CONST_FLOAT");
				yylval = s;
				return CONST_FLOAT; 
			}
{id} 		{	 		
				SymbolInfo* s = new SymbolInfo(yytext,"ID");
				yylval = s;
				return ID;
			}


%%

int yywrap(void)
{
	return 1;
}
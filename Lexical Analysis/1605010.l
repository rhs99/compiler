%option noyywrap
%x COMMENT 
%x SCOMMENT
%x STRING
%x C_CHAR

%{
#include<bits/stdc++.h>
using namespace std;

#include "MySymbolTable.h"

int line_count = 1;
int error_count = 0;
string str = "";

SymbolTable symbol_table;

 
FILE *logout;
FILE *tokenout;

void flex_insert(string type,string name)
{
        SymbolInfo rhs;
        rhs.set_name(name);
        rhs.set_type(type);
        symbol_table.my_insert(rhs);
        symbol_table.print_current_scope_table(logout);
}

void flex_char_print(string s)
{
    if(s.size() == 1)
    {
        if(s[0] == '\\')
        {
            error_count++;
            string temp = "'"+s+"'";
            fprintf(logout,"error::At Line no %d UNFINISHED CHARACTER CONSTANT %s found\n",line_count,temp.c_str());
        }
        else{ 
        string temp = "'"+s+"'";
        fprintf(tokenout,"<CONST_CHAR,%s>",temp.c_str());
        fprintf(logout,"Line no %d: TOKENn <CONST_CHAR> Lexeme %s found\n",line_count,temp.c_str());
        flex_insert("CONST_CHAR",temp);
        }
    }
    else if(s.size() == 2)
    {
        string temp ;
        if(s[0]=='\\')
        {
            if(s[1] == 'n')
            {
                temp = "\n";
            }
            else if(s[1] == 't')
            {
                temp = "\t";
            }
            else if(s[1] == '\\')
            {
                temp = "\\";
            }
            else if(s[1] == '\"')
            {
                temp = "\"";

            }
            else if(s[1] == 'a')
            {
                temp = "\a";
            }
            else if(s[1] == 'f')
            {
                temp = "\f";
            }
            else if(s[1] == 'r')
            {
                temp = "\r";

            }
            else if(s[1] == 'b')
            {
                temp = "\b";

            }
            else if(s[1] == 'v')
            {
                temp = "\v";
            }
            else if(s[1] == '0')
            {
                temp = "\0";

            }

            fprintf(tokenout,"<CONST_CHAR,%s>",temp.c_str());
            fprintf(logout,"Line no %d: TOKEN <CONST_CHAR> Lexeme %s found\n",line_count,temp.c_str());
            flex_insert("CONST_CHAR",temp);

        }
        else
        {
            error_count++;
            string temp = "'"+s+"'";
            fprintf(logout,"error::At Line no %d MULTI CHARACTER CONSTANT %s found\n",line_count,temp.c_str());

        }

    }
    else if(s.size()>2)
    {
        error_count++;
        string temp = "'"+s+"'";
        fprintf(logout,"error::At Line no %d MULTI CHARACTER CONSTANT %s found\n",line_count,temp.c_str());
    }

}







%}

WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z]
DIGIT [0-9]
NEWLINE \n


%%






\'                   { BEGIN C_CHAR;}

<C_CHAR>\'           {
                       flex_char_print(str);
                       str = "";
                       BEGIN INITIAL;
                     }

<C_CHAR>[^\n\']+   { string s = yytext; str += s;}

<C_CHAR><<EOF>>  {   
                     if(str.size()>0){
                     error_count++; 
                     string temp = "'"+str;
                     fprintf(logout,"error::UNFINISHED CHARACTER %s found\n",temp.c_str());
                     str = "";
                     }
                     BEGIN INITIAL;
                     return 0;
                     }

<C_CHAR>\n           {
                     string temp = "'"+str;
                     fprintf(logout,"error::At Line no %d UNFINISHED CHARACTER %s found\n",line_count,temp.c_str());
                     line_count++;
                     error_count++; 
                     str = "";
                     BEGIN INITIAL;
                     }


"/*"                 {BEGIN COMMENT;}
<COMMENT>[^*\n]*     {}
<COMMENT>"*"+/[^/]   {}
<COMMENT>"\n"        {line_count++;}
<COMMENT><<EOF>>     {
                     error_count++; 
                     fprintf(logout,"error::UNFINISHED COMMENT found\n");
                     return 0;
                     }
<COMMENT>"*"+[/]     { BEGIN INITIAL;}



"//"                  {BEGIN SCOMMENT;}
<SCOMMENT>[^\n\\]+    {}
<SCOMMENT>"\\"+"\n"   {line_count++;}
<SCOMMENT>"\\"+       {}
<SCOMMENT>"\n"        {
                       line_count++;
                       BEGIN INITIAL;
                      }



\"                  {BEGIN STRING;}
<STRING>\\n  {str += '\n';}
<STRING>\\t  {str += '\t';}
<STRING>\\r  {str += '\r';}
<STRING>\\b  {str += '\b';}
<STRING>\\f  {str += '\f';}


<STRING>[^\"\n\\]+  {
                       string s = yytext;
                       str += s;

                       
                    }
<STRING>"\\"+"\n"   {line_count++;}
<STRING>\"          { 
                       str = "\""+str+"\"";
                       fprintf(logout,"TOKEN <STRINNG> Lexeme %s found\n",str.c_str());
                       fprintf(tokenout,"<STRING,%s>",str.c_str());
                       str = "";
                       BEGIN INITIAL;
                    }

<STRING>\n          {
                     line_count++;
                     str = "";
                     BEGIN INITIAL;
                     error_count++;
                     fprintf(logout,"error::UNFINISHED STRING found\n");
                    }

"if"	            {
			fprintf(tokenout,"<IF>");
			fprintf(logout,"Line no %d: TOKEN <IF> Lexeme %s found\n",line_count,yytext);
		    }
		
"else"	            {
			fprintf(tokenout,"<ELSE>");
			fprintf(logout,"Line no %d: TOKEN <ELSE> Lexeme %s found\n",line_count,yytext);
		    }

"for"	            {
			fprintf(tokenout,"<FOR>");
			fprintf(logout,"Line no %d: TOKEN <FOR> Lexeme %s found\n",line_count,yytext);
		    }
"while"	            {
			fprintf(tokenout,"<WHILE>");
			fprintf(logout,"Line no %d: TOKEN <WHILE> Lexeme %s found\n",line_count,yytext);
		    }
"do"	            {
			fprintf(tokenout,"<DO>");
			fprintf(logout,"Line no %d: TOKEN <DO> Lexeme %s found\n",line_count,yytext);
		    }
"break"	            {
			fprintf(tokenout,"<BREAK>");
			fprintf(logout,"Line no %d: TOKEN <BREAK> Lexeme %s found\n",line_count,yytext);
		    }

"int"	            {
			fprintf(tokenout,"<INT>");
			fprintf(logout,"Line no %d: TOKEN <INT> Lexeme %s found\n",line_count,yytext);
		    }

"char"	            {
			fprintf(tokenout,"<CHAR>");
			fprintf(logout,"Line no %d: TOKEN <CHAR> Lexeme %s found\n",line_count,yytext);
		    }
"float"	            {
			fprintf(tokenout,"<FLOAT>");
			fprintf(logout,"Line no %d: TOKEN <FLOAT> Lexeme %s found\n",line_count,yytext);
		    }
"double"	    {
			fprintf(tokenout,"<DOUBLE>");
			fprintf(logout,"Line no %d: TOKEN <DOUBLE> Lexeme %s found\n",line_count,yytext);
		    }
"void"	            {
			fprintf(tokenout,"<VOID>");
			fprintf(logout,"Line no %d: TOKEN <VOID> Lexeme %s found\n",line_count,yytext);
		    }
"return"	    {
			fprintf(tokenout,"<RETURN>");
			fprintf(logout,"Line no %d: TOKEN <RETURN> Lexeme %s found\n",line_count,yytext);
		    }
"switch"	    {
			fprintf(tokenout,"<SWITCH>");
			fprintf(logout,"Line no %d: TOKEN <SWITCH> Lexeme %s found\n",line_count,yytext);
		    }
"case"	            {
			fprintf(tokenout,"<CASE>");
			fprintf(logout,"Line no %d: TOKEN <CASE> Lexeme %s found\n",line_count,yytext);
		    }
"default"	    {
			fprintf(tokenout,"<DEFAULT>");
			fprintf(logout,"Line no %d: TOKEN <DEFAULT> Lexeme %s found\n",line_count,yytext);
		    }
"continue"	    {
			fprintf(tokenout,"<CONTINUE>");
			fprintf(logout,"Line no %d: TOKEN <CONTINUE> Lexeme %s found\n",line_count,yytext);
		    }


 






[[:alpha:]_][[:alnum:]_]*   {
				fprintf(tokenout,"<ID,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <ID> Lexeme %s found\n",line_count,yytext);
                                flex_insert("ID",yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
		             }




"+"|"-" 	    {
			fprintf(tokenout,"<ADDOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <ADDOP> Lexeme %s found\n",line_count,yytext);
                        flex_insert("ADDOP",yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		    }

"*"|"/"|"%"	    {
			fprintf(tokenout,"<MULOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <MULOP> Lexeme %s found\n",line_count,yytext);
                        flex_insert("MULOP",yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		    }

"++"|"--" 	            {
			fprintf(tokenout,"<INCOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <INCOP> Lexeme %s found\n",line_count,yytext);
                        flex_insert("INCOP",yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		    }
"<"|"<="|">"|">="|"=="|"!=" {
			fprintf(tokenout,"<RELOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <RELOP> Lexeme %s found\n",line_count,yytext);
                        flex_insert("RELOP",yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		        }

"=" 	            {
			fprintf(tokenout,"<ASSIGNOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <ASSIGNOP> Lexeme %s found\n",line_count,yytext);
                        flex_insert("ASSIGNOP",yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		    }

"&&"|"||" 	     {
			fprintf(tokenout,"<LOGICOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <LOGICOP> Lexeme %s found\n",line_count,yytext);
                        flex_insert("LOGICOP",yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		    }


"&"|"|"|"^"|"<<"|">>" {
			fprintf(tokenout,"<BITOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <BITOP> Lexeme %s found\n",line_count,yytext);
                        flex_insert("BITOP",yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		    }

"!"	            {
			fprintf(tokenout,"<NOT,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <NOT> Lexeme %s found\n",line_count,yytext);
                        flex_insert("NOT",yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		    }


"("	            {
			fprintf(tokenout,"<LPAREN,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <LPAREN> Lexeme %s found\n",line_count,yytext);
                        flex_insert("LPAREN",yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		    }


")" 	            {
			fprintf(tokenout,"<RPAREN,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <RPAREN> Lexeme %s found\n",line_count,yytext);
                        flex_insert("RPAREN",yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		    }

"{"	            {
			fprintf(tokenout,"<LCURL,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <LCURL> Lexeme %s found\n",line_count,yytext);
                        flex_insert("LCURL",yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		    }


"}" 	            {
			fprintf(tokenout,"<RCURL,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <RCURL> Lexeme %s found\n",line_count,yytext);
                        flex_insert("RCURL",yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		    }

"["	            {
			fprintf(tokenout,"<LTHIRD,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <LTHIRD> Lexeme %s found\n",line_count,yytext);
                        flex_insert("LTHIRD",yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		    }


"]" 	            {
			fprintf(tokenout,"<RTHIRD,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <RTHIRD> Lexeme %s found\n",line_count,yytext);
                        flex_insert("RTHIRD",yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		    }

","	            {
			fprintf(tokenout,"<COMMA,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <COMMA> Lexeme %s found\n",line_count,yytext);
                        flex_insert("COMMA",yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		    }


";" 	            {
			fprintf(tokenout,"<SEMICOLON,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <SEMICOLON> Lexeme %s found\n",line_count,yytext);
                        flex_insert("SEMICOLON",yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		    }


		
{DIGIT}+ 	     {
                                string str = yytext;
				fprintf(tokenout,"<CONST_INT,%s>",str.c_str());
				fprintf(logout,"Line no %d: TOKEN <CONST_INT> Lexeme %s found\n",line_count,str.c_str());
                                flex_insert("CONST_INT",str);
				//insert in symbol table and print symbol table content(only non empty buckets)
		     }

([0-9]*\.?[0-9]+|[0-9]+\.)(E[-+]?[0-9]+)?  {
                                                        
                                                     fprintf(tokenout,"<CONST_FLOAT,%s>",yytext);
				                     fprintf(logout,"Line no %d: TOKEN <CONST_FLOAT> Lexeme %s found\n",line_count,yytext);
                                                     flex_insert("CONST_FLOAT",yytext);
				                     //insert in symbol table and print symbol table content(only non empty buckets)

                                                 }
[0-9]*\.[0-9]*\..*             {
                                error_count++;
                                fprintf(logout,"Line no %d:error: TOO MANY DECIMAL POINT Lexeme %s found\n",line_count,yytext);
                               }

([0-9]*\.?[0-9]+|[0-9]+\.)(E[-+]?[0-9]*\.[0-9]*)?  {
                                                  error_count++;
                                                 fprintf(logout,"Line no %d:error:ILL FORMED NUMBER Lexeme %s found\n",line_count,yytext);
                                                 }

([0-9])+([[:alnum:]])+             {
                                   error_count++;
                                   fprintf(logout,"Line no %d:error: INVALID INDETIFIRE Lexeme %s found\n",line_count,yytext);
                                   }


{NEWLINE}           {
                        line_count++;
                    }

{WHITESPACE}        {}
 
.                   { error_count++;
                      fprintf(logout,"Line no %d:error: UNRECOGNIZED CHARACTER Lexeme %s found\n",line_count,yytext);
                    }



 
	

%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}

        tokenout= fopen("1605010_token.txt","w");
	logout= fopen("1605010_log.txt","w");
	

	yyin= fin;
	yylex();
        
        fprintf(logout,"Total line : %d\n",line_count);
        fprintf(logout,"Total error : %d\n",error_count);

	fclose(yyin);
	fclose(tokenout);
	fclose(logout);
	return 0;
}

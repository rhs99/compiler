
%{
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


%}
%start start
%define api.value.type{SymbolInfo*}
%token IF ELSE FOR WHILE INT FLOAT DOUBLE CHAR RETURN VOID
PRINTLN ADDOP MULOP ASSIGNOP RELOP LOGICOP NOT SEMICOLON COMMA 
LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD INCOP DECOP CONST_INT CONST_FLOAT ID

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
start:          program
	             {
					  $$ = $1;
		              fprintf(log_out,"At line no : %d start : program\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
	             }
	;
program:         program unit 
                  {
					  $$ = new SymbolInfo($1->get_name()+"\n"+$2->get_name(),"");
					  fprintf(log_out,"At line no : %d program : program unit\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
	|             unit
	              {
					  $$ = $1;
                      fprintf(log_out,"At line no : %d program : unit\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
	;
	
unit:            var_declaration
                  {
					  $$ = $1;
                      fprintf(log_out,"At line no : %d unit : var_declaration\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
     |            func_declaration
	              {
					  $$ = $1;
                      fprintf(log_out,"At line no : %d unit : func_declaration\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
     |            func_definition
	              { 
					  $$ = $1;
                      fprintf(log_out,"At line no : %d unit : func_definition\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
     ;
     
func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
                  {
					  $$ = new SymbolInfo($1->get_name()+" "+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name()+$6->get_name()+"\n","");
                      string return_type = $1->get_name();
					  string function_name = $2->get_name();
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
					  fprintf(log_out,"%s\n",$$->get_name().c_str());

					  current_parameter_list_name.clear();
					  current_parameter_list_type.clear();
				  }
		|         type_specifier ID LPAREN RPAREN SEMICOLON
		          {
					  $$ = new SymbolInfo($1->get_name()+" "+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name()+"\n","");
                    
					  string return_type = $1->get_name();
					  string function_name = $2->get_name();
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
					  fprintf(log_out,"%s\n",$$->get_name().c_str());

					  current_parameter_list_name.clear();
					  current_parameter_list_type.clear();
				  }
		;
		 
func_definition: type_specifier ID LPAREN parameter_list RPAREN
                  {
					  current_return_type = $1->get_name();
					  string function_name = $2->get_name();
                      
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
				  compound_statement
                  {
					  $$ = new SymbolInfo($1->get_name()+" "+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name()+"\n"+$7->get_name(),"");

                      fprintf(log_out,"At line no : %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
		|         type_specifier ID LPAREN RPAREN 
		          {

					  current_return_type = $1->get_name();
					  string function_name = $2->get_name();
                      
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
		          compound_statement
		          {
					  $$ = new SymbolInfo($1->get_name()+" "+$2->get_name()+$3->get_name()+$4->get_name()+"\n"+$6->get_name(),"");
                      
                      fprintf(log_out,"At line no : %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
 		;				
parameter_list: parameter_list COMMA type_specifier ID
                  {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+" "+$4->get_name(),"");

					  


					  current_parameter_list_type.push_back($3->get_name());
					  current_parameter_list_name.push_back($4->get_name());

                      fprintf(log_out,"At line no : %d parameter_list  : parameter_list COMMA type_specifier ID\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
		|         parameter_list COMMA type_specifier
		          {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),"");

					  

					  current_parameter_list_type.push_back($3->get_name());


                      fprintf(log_out,"At line no : %d parameter_list  :  parameter_list COMMA type_specifier\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
 		|         type_specifier ID
		          {
					  $$ = new SymbolInfo($1->get_name()+" "+$2->get_name(),"");

					  

					  current_parameter_list_type.push_back($1->get_name());
					  current_parameter_list_name.push_back($2->get_name());

                      fprintf(log_out,"At line no : %d parameter_list : type_specifier ID\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
		|         type_specifier
		          {
					  $$ = $1;

					  current_parameter_list_type.push_back($1->get_name());

				

                      fprintf(log_out,"At line no : %d parameter_list : type_specifier\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
 		;
 		
compound_statement: LCURL 
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

				  } statements RCURL
                  {
					  $$ = new SymbolInfo("{\n"+$3->get_name()+"\n}","");
                      fprintf(log_out,"At line no : %d compound_statement : LCURL statements RCURL\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
					  table->print_all_scope_table(log_out);
					  fprintf(log_out,"ScopeTable with id %d removed\n",table->current_scope_table->get_id());
					  table->exit_scope();
				  }
 		    |     LCURL 
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
 

				  } RCURL
			      {
					  $$ = new SymbolInfo("{}","");
                      fprintf(log_out,"At line no : %d compound_statement : LCURL RCURL\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
					  table->print_all_scope_table(log_out);
					  fprintf(log_out,"ScopeTable with id %d removed\n",table->current_scope_table->get_id());
					  table->exit_scope();
				  }
 		    ;
 		    
var_declaration: type_specifier declaration_list SEMICOLON
                  {
					  $$ = new SymbolInfo($1->get_name()+" "+$2->get_name()+$3->get_name()+"\n","");

					  if($1->name == "void")
					  {
						  fprintf(error_out,"At linr no : %d variable type cannot be void\n",line_count);
						  error_count++;
					  }
					
					  string str = $2->get_name();

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
							  rhs.sub_type = $1->get_name();

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
							      rhs.sub_type = $1->get_name();
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
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
 		 ;
 		 
type_specifier: INT
                  {   
					  $$ = $1;

				  	  fprintf(log_out,"At line no : %d type_specifier : INT\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
 		| FLOAT   {
			          $$ = $1;
					 
			 		  fprintf(log_out,"At line no : %d type_specifier : FLOAT\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());	
				 
			      }
 		| VOID    {
			          $$ = $1;

			 		  fprintf(log_out,"At line no : %d type_specifier : VOID\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());	
			      }
 		;
 		
declaration_list: declaration_list COMMA ID
                  {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),""); 
                      fprintf(log_out,"At line no : %d declaration_list : declaration_list COMMA ID\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
 		  |       declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
		          {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name()+$6->get_name(),"");
                      fprintf(log_out,"At line no : %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n",line_count);
					  fprintf(log_out,"%s\n\n",$5->get_name().c_str());
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
 		  |       ID
		          {
					  $$ = $1;
					  
                      fprintf(log_out,"At line no : %d declaration_list : ID\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
 		  |       ID LTHIRD CONST_INT RTHIRD
		          {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+$4->get_name(),"");
                      fprintf(log_out,"At line no : %d declaration_list : ID LTHIRD CONST_INT RTHIRD\n",line_count);
					  fprintf(log_out,"%s\n\n",$3->get_name().c_str());
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				  }
 		  ;
 		  
statements:     statement  
                 {
					  $$ = $1;
					  fprintf(log_out,"At line no : %d statements : statement\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				 }
	   |         statements statement
	             {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name(),"");
					  fprintf(log_out,"At line no : %d statements : statements statement\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				 }
	   ;
	   
statement:      var_declaration
                 {
					  $$ = $1;
                      fprintf(log_out,"At line no : %d statement : var_declaration\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				 }
	  |          expression_statement
	             {
					  $$ = $1;
                      fprintf(log_out,"At line no : %d statement : expression_statement\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				 }
	  |          compound_statement
	             {
					  $$ = $1;
                      fprintf(log_out,"At line no : %d statement : compound_statement\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				 }
	  |          FOR LPAREN expression_statement expression_statement expression RPAREN statement
	             {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name()+$6->get_name()+$7->get_name(),"");
					  if($4->sub_type == "void"||$5->sub_type=="void")
					  {
						  fprintf(error_out,"At line no : %d expression evaluates void\n",line_count);
						  error_count++;
					  }
                      fprintf(log_out,"At line no : %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				 }
	  |          IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
	             {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name(),"");
					  if($3->sub_type == "void")
					  {
						  fprintf(error_out,"At line no : %d expression evaluates void\n",line_count);
						  error_count++;
					  }
                      fprintf(log_out,"At line no : %d statement : IF LPAREN expression RPAREN statement\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				 }
	  |          IF LPAREN expression RPAREN statement ELSE statement
	             {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name()+$6->get_name()+$7->get_name(),"");
                      if($3->sub_type == "void")
					  {
						  fprintf(error_out,"At line no : %d expression evaluates void\n",line_count);
						  error_count++;
					  }
                      fprintf(log_out,"At line no : %d statement : IF LPAREN expression RPAREN statement ELSE statement\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				 }
	  |          WHILE LPAREN expression RPAREN statement
	             {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name(),"");
					  if($3->sub_type == "void")
					  {
						  fprintf(error_out,"At line no : %d expression evaluates void\n",line_count);
						  error_count++;
					  }
                      fprintf(log_out,"At line no : %d statement : WHILE LPAREN expression RPAREN statement\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				 }
	  |          PRINTLN LPAREN ID RPAREN SEMICOLON
	             {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name()+"\n","");
                      fprintf(log_out,"At line no : %d statement :  PRINTLN LPAREN ID RPAREN SEMICOLON\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				 }
	  |          RETURN expression SEMICOLON
	             {
					  $$ = new SymbolInfo($1->get_name()+" "+$2->get_name()+$3->get_name()+"\n","");
					  if($2->sub_type != current_return_type)
					  {
						  fprintf(error_out,"At line no : %d return type mismatch\n",line_count);
						  error_count++;
					  }
                      fprintf(log_out,"At line no : %d statement : RETURN expression SEMICOLON\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				 }
	  ;
	  
expression_statement: SEMICOLON	
                {
					  $$ = $1;
                      fprintf(log_out,"At line no : %d expression_statement : SEMICOLON\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}		
			|         expression SEMICOLON 
			    { 
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+"\n","");
					  
                      fprintf(log_out,"At line no : %d expression_statement : expression SEMICOLON\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
			;
	  
variable:      ID
                {
					  SymbolInfo *temp = table->my_look_up($1->get_name());

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
						 
                          $$ = temp;
					  }


					   

                      fprintf(log_out,"At line no : %d variable : ID\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
	 |          ID LTHIRD expression RTHIRD 
	            {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+$4->get_name(),"");
					 

					  SymbolInfo *temp = table->my_look_up($1->get_name());

					  if(temp == nullptr)
					  {
						  fprintf(error_out,"At line no : %d undeclared variable\n",line_count);
						  error_count++;
					  }
					  else
					  {
						
						  
							if($3->sub_type != "int")
							{
								fprintf(error_out,"At line no : %d array index should be int\n",line_count);
								error_count++;
							}
							else
							{
								int my_arr_size = atoi($3->name.c_str());
								int mx_arr_size = temp->arr_size;

							

								if(my_arr_size<0||my_arr_size>=mx_arr_size)
								{
									fprintf(error_out,"At line no : %d index out of bound\n",line_count);
									error_count++;
								}

							}

							$$->sub_type = temp->sub_type;
							$$->is_array = temp->is_array;
							$$->arr_size = temp->arr_size;
					 
					  }


                      fprintf(log_out,"At line no : %d variable : ID LTHIRD expression RTHIRD\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
	 ;
	 
 expression:    logic_expression
                {
					  $$ = $1;
                      fprintf(log_out,"At line no : %d expression : logic_expression\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}	
	   |        variable ASSIGNOP logic_expression
	            {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),"");

					  if($1->sub_type != $3->sub_type)
					  {
						  fprintf(error_out,"At line no : %d type mismatch\n",line_count);
						  error_count++;
					  }

					  $$->sub_type = $1->sub_type;
					  
                      fprintf(log_out,"At line no : %d expression : variable ASSIGNOP logic_expression\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
	   ;
			
logic_expression: rel_expression 
                {
					  $$ = $1;
                      fprintf(log_out,"At line no : %d logic_expression : rel_expression\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}	
		 |      rel_expression LOGICOP rel_expression 	
		        {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),"");

					  if(($1->sub_type != $3->sub_type)&&($1->sub_type != "int"))
					  {
						  fprintf(error_out,"At line no : %d type mismatch\n",line_count);
						  error_count++;
					  }

					  $$->sub_type = "int";


                      fprintf(log_out,"At line no : %d logic_expression : rel_expression LOGICOP rel_expression \n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
		 ;
			
rel_expression: simple_expression 
                {
					  $$ = $1;
                      fprintf(log_out,"At line no : %d rel_expression : simple_expression \n",line_count); 
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
		|       simple_expression RELOP simple_expression	
		        {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),"");

					  if($1->sub_type == "void" || $3->sub_type == "void")
					  {
						  fprintf(error_out,"At line no : %d type mismatch\n",line_count);
						  error_count++;
					  }

					  $$->sub_type = "int";



                      fprintf(log_out,"At line no : %d rel_expression : simple_expression RELOP simple_expression\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
		;
				
simple_expression: term 
                {  
					  $$ = $1;
                      fprintf(log_out,"At line no : %d simple_expression : term\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
			    }
		  |     simple_expression ADDOP term 
		        {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),"");

					  if($1->sub_type == "void" || $3->sub_type == "void")
					  {
						  fprintf(error_out,"At line no : %d type mismatch\n",line_count);
						  error_count++;
					  }
					  else if($1->sub_type != $3->sub_type)
					  {
						   
							
							$$->sub_type = "float";  
					  }
					  else if($1->sub_type == $3->sub_type)
					  {
						  $$->sub_type = $1->sub_type;
					  }

					  


                      fprintf(log_out,"At line no : %d simple_expression : simple_expression ADDOP term\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
		  ;
					
term:	        unary_expression
                {
					  $$ = $1;
                      fprintf(log_out,"At line no : %d term : unary_expression \n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
     |          term MULOP unary_expression
	            {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),"");

                      if($1->sub_type == "void" || $3->sub_type == "void")
					  {
						  fprintf(error_out,"At line no : %d type mismatch\n",line_count);
						  error_count++;
					  }
					  else
					  {
						  if($2->name == "%")
						  {
							  if($1->sub_type == "float"||$3->sub_type == "float")
							  {
								  fprintf(error_out,"At line no : %d modulus operator cannot have float operand\n",line_count);
								  error_count++;
							  }
							  $$->sub_type = "int";
						  }	
						  else
						  {
							  if($1->sub_type == "float"||$3->sub_type == "float")
							  {
								  $$->sub_type = "float";
								   
							  }
							  else
							  {
								  $$->sub_type = "int";

							  }
							  
						  }					   
						 
					  }
					   



                      fprintf(log_out,"At line no : %d term : term MULOP unary_expression\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
     ;
unary_expression: ADDOP unary_expression  
                {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name(),"");
					  $$->sub_type = $2->sub_type;
                      fprintf(log_out,"At line no : %d unary_expression : ADDOP unary_expression\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
		 |      NOT unary_expression 
		        {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name(),"");
					  $$->sub_type = $2->sub_type;
                      fprintf(log_out,"At line no : %d unary_expression : NOT unary_expression\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
			    }
		 |      factor 
		        {
					  $$ = $1;
                      fprintf(log_out,"At line no : %d unary_expression : factor\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
		 ;
	
factor:         variable 
                {
					  $$ = $1;
                      fprintf(log_out,"At line no : %d factor : variable \n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
	|           ID LPAREN { current_argument_list.push(vector<string>()); } argument_list RPAREN
	            {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$4->get_name()+$5->get_name(),"");

					  SymbolInfo *temp = table->my_look_up($1->get_name());

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

						  $$->sub_type = temp->return_type;
					  }

					  current_argument_list.pop();


                      fprintf(log_out,"At line no : %d factor : ID LPAREN argument_list RPAREN\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
					  
				}
	|           LPAREN expression RPAREN
	            {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),"");
					  $$->sub_type = $2->sub_type;
                      fprintf(log_out,"At line no : %d factor : LPAREN expression RPAREN\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
	|           CONST_INT 
	            {
					  $$ = $1;
					  $$->sub_type = "int";
                      fprintf(log_out,"At line no : %d factor : CONST_INT\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
	|           CONST_FLOAT
	            {
					  $$ = $1;
					  $$->sub_type = "float";
                      fprintf(log_out,"At line no : %d factor : CONST_FLOAT\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
	|           variable INCOP
	            {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name(),"");
					  $$->sub_type = $1->sub_type;
                      fprintf(log_out,"At line no : %d factor : variable INCOP\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				} 
	|           variable DECOP
	            {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name(),"");
					  $$->sub_type = $1->sub_type;
                      fprintf(log_out,"At line no : %d factor : variable DECOP\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
	;
	
argument_list: arguments
                {
					  $$ = $1;
					  
                      fprintf(log_out,"At line no : %d argument_list : arguments\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
				}
			  | {$$ = new SymbolInfo();}
			  ;
	
arguments:    arguments COMMA logic_expression
               {
				      $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),"");

					  current_argument_list.top().push_back($3->sub_type);

                      fprintf(log_out,"At line no : %d arguments : arguments COMMA logic_expression \n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
			   }
	      |    logic_expression
		       {
				      $$ = $1;

					  current_argument_list.top().push_back($1->sub_type);
					  
					   
                      fprintf(log_out,"At line no : %d arguments : logic_expression\n",line_count);
					  fprintf(log_out,"%s\n",$$->get_name().c_str());
			   }
	      ;
 
%%
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
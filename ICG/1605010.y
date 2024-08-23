
%{
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
						 
						  fprintf(asm_out,$$->code.c_str());
 




					  }
					  else
					  {
						  fprintf(error_out,"Total number of errors : %d\n",line_count);

					  }
		           
	             }
	;
program:         program unit 
                  {
					  $$ = new SymbolInfo($1->get_name()+"\n"+$2->get_name(),"");
					  $$->code += ($1->code + $2->code);
				 
				  }
	|             unit
	              {
					  $$ = $1;
                    
				  }
	;
	
unit:            var_declaration
                  {
					  $$ = $1;
                      
				  }
     |            func_declaration
	              {
					  $$ = $1;
                     
				  }
     |            func_definition
	              { 
					  $$ = $1;
					  
                      
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
 
					  current_parameter_list_name.clear();
					  current_parameter_list_type.clear();
				  }
		;
		 
func_definition: type_specifier ID LPAREN parameter_list RPAREN
                  {
					  current_return_type = $1->get_name();
					  string function_name = $2->get_name();
					  SymbolInfo *temp = table->my_look_up(function_name);

					  current_func_name = $2->name;

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
				  compound_statement
                  {
					  $$ = new SymbolInfo($1->get_name()+" "+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name()+"\n"+$7->get_name(),"");
					  
                      string code = "";
					  
					  if($2->name == "main")
					  {
						  code += "MAIN PROC\nMOV AX,@DATA \nMOV DS,AX\n";
						
					  }
					  else
					  {
						   code  += ($2->name + " PROC\n");

                           
						//    code += "PUSH AX\nPUSH BX \nPUSH CX\nPUSH DX\n";
						//    SymbolInfo *temp = table->my_look_up($2->name);
						//    vector<string>parameter = temp->parameter_list;
						//    for(int i=0;i<parameter.size();i++)
						//    {
						// 	   code += ("PUSH " + parameter[i] + "\n");
						//    }

					  }
                      code += $7->code;
					  code += ("FINISHED_"+ $2->name + ":\n");
					  if($2->name == "main")
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
						   code += ($2->name + " ENDP\n\n");
					  }

					  $$->code = code;

					  
                    
				  }
		|         type_specifier ID LPAREN RPAREN 
		          {

					  current_return_type = $1->get_name();
					  string function_name = $2->get_name();

					  
					  current_func_name = $2->name;
 
                      
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
		          compound_statement
		          {
					  $$ = new SymbolInfo($1->get_name()+" "+$2->get_name()+$3->get_name()+$4->get_name()+"\n"+$6->get_name(),"");
                      
				 
                      string code = "";
					 

					  if($2->name == "main")
					  {
						  code += "MAIN PROC\nMOV AX,@DATA \nMOV DS,AX\n";
						
					  }
					  else
					  {
						   code  += ($2->name + " PROC\n");
						   //code += "PUSH AX\nPUSH BX \nPUSH CX\nPUSH DX\n";
						    

					  }
                      code += $6->code;
					  code += ("FINISHED_"+ $2->name + ":\n");
					  if($2->name == "main")
					  {
						  code += "MOV AH,4CH\nINT 21H\nMAIN ENDP\nEND MAIN\n";
					  }
					  else
					  {
						  // code += "POP DX\nPOP CX \nPOP BX\nPOP AX\n";
						   code += "RET\n";
						   code += ($2->name + " ENDP\n\n");
					  }

					  $$->code = code;
                     
				  }
 		;				
parameter_list: parameter_list COMMA type_specifier ID
                  {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+" "+$4->get_name(),"");

					  current_parameter_list_type.push_back($3->get_name());
					  current_parameter_list_name.push_back($4->get_name());
 
				  }
		|         parameter_list COMMA type_specifier
		          {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),"");
					  current_parameter_list_type.push_back($3->get_name());
                       
				  }
 		|         type_specifier ID
		          {
					  $$ = new SymbolInfo($1->get_name()+" "+$2->get_name(),"");
					  current_parameter_list_type.push_back($1->get_name());
					  current_parameter_list_name.push_back($2->get_name());
 
				  }
		|         type_specifier
		          {
					  $$ = $1;
					  current_parameter_list_type.push_back($1->get_name());
				  }
 		;
 		
compound_statement: LCURL 
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
					  

				  } statements RCURL
                  {
					  $$ = new SymbolInfo("{\n"+$3->get_name()+"\n}","");
					  $$->code += $3->code; 
                    
				 
					  table->exit_scope();
				  }
 		    |     LCURL 
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
 

				  } RCURL
			      {
					  $$ = new SymbolInfo("{}","");
					  table->exit_scope();
				  }
 		    ;
 		    
var_declaration: type_specifier declaration_list SEMICOLON
                  {
					  $$ = new SymbolInfo($1->get_name()+" "+$2->get_name()+$3->get_name()+"\n","");

					  
					  string str = $2->get_name();
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
							  rhs.sub_type = $1->get_name();

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
								rhs.sub_type = $1->get_name();
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
 		 ;
 		 
type_specifier: INT
                  {   
					  $$ = $1;				   
				  }
 		| FLOAT   {
			          $$ = $1;
			      }
 		| VOID    {
			          $$ = $1;
			      }
 		;
 		
declaration_list: declaration_list COMMA ID
                  {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),""); 
                     
				  }
 		  |       declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
		          {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name()+$6->get_name(),"");
                   
				  }
 		  |       ID
		          {
					  $$ = $1;
				  }
 		  |       ID LTHIRD CONST_INT RTHIRD
		          {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+$4->get_name(),"");
                      
				  }
 		  ;
 		  
statements:     statement  
                 {
					  $$ = $1;					   
				 }
	   |         statements statement
	             {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name(),"");
					  $$->code += ($1->code + $2->code);
					 
				 }
	   ;
	   
statement:      var_declaration
                 {
					  $$ = $1;
                      
				 }
	  |          expression_statement
	             {
					  $$ = $1;
                      
				 }
	  |          compound_statement
	             {
					  $$ = $1;
                    
				 }
	  |          FOR LPAREN expression_statement expression_statement expression RPAREN statement
	             {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name()+$6->get_name()+$7->get_name(),"");
					
					  string label1 = new_label();
					  string label2 = new_label();

					  

					  $$->code += ($3->code + "\n");

					  $$->code += (label1 + ":\n");
					  $$->code += ($4->code + "\n");
                       
					  if($4->name_with_id != ""){
					  	$$->code += ("CMP " + $4->name_with_id + ",0\n");
					  	$$->code += ("JE " + label2 + "\n");
					  }

					  $$->code += ($7->code + "\n");
					  $$->code += ($5->code + "\n");
					  $$->code += ("JMP " + label1 + "\n");
					  $$->code += (label2 + ":\n");

                       
				 }
	  |          IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
	             {
					$$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name(),"");
					  
					string label = new_label();

					$$->code += $3->code;
					$$->code += ("CMP " + $3->name_with_id + ",0\n");
					$$->code += ("JE " + label + "\n");
					$$->code += ($5->code + "\n");
					$$->code += (label + ":\n");

					 
					
                  
				 }
	  |          IF LPAREN expression RPAREN statement ELSE statement
	             {
					$$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name()+$6->get_name()+$7->get_name(),"");
                      

					string label1 = new_label();
					string label2 = new_label();

					$$->code += $3->code;
					$$->code += ("CMP " + $3->name_with_id + ",0\n");
					$$->code += ("JE " + label1 + "\n");
					$$->code += ($5->code + "\n");
					$$->code += ("JMP " + label2 + "\n");
					$$->code += (label1 + ":\n");
					$$->code += ($7->code + "\n");
					$$->code += (label2 + ":\n");
                      
				 }
	  |          WHILE LPAREN expression RPAREN statement
	             {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name(),"");
					 

					  string label1 = new_label();
					  string label2 = new_label();

					  $$->code += (label1 + ":\n");
					  $$->code += $3->code;
					  $$->code += ("CMP " + $3->name_with_id + ",0\n");
					  $$->code += ("JE " + label2 + "\n");
					  $$->code += ($5->code + "\n");
					  $$->code += ("JMP " + label1 + "\n");
					  $$->code += (label2 + ":\n");


                       
				 }
	  |          PRINTLN LPAREN ID RPAREN SEMICOLON
	             {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name()+"\n","");
                      SymbolInfo *temp = table->my_look_up($3->name);

					  $$->code += ("MOV AX," + temp->name_with_id + "\n");
					  $$->code += ("CALL PRINT\n");

                  
				 }
	  |          RETURN expression SEMICOLON
	             {
					  $$ = new SymbolInfo($1->get_name()+" "+$2->get_name()+$3->get_name()+"\n","");

					  $$->code += $2->code;
					  $$->code += ("MOV AX," + $2->name_with_id + "\n");
					  $$->code += ("MOV " + ret_var + ",AX\n");
					  $$->code += ("JMP FINISHED_" + current_func_name + "\n");
					  
					  
					  
                    
				 }
	  ;
	  
expression_statement: SEMICOLON	
                {
					  $$ = $1;
                   
				}		
			|         expression SEMICOLON 
			    { 
					  $$ = $1;
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
							$$->name_with_id = temp->name_with_id;
							$$->code = $3->code+"MOV BX, " +$3->name_with_id +"\nADD BX, BX\n";

							 
					  }


                   
				}
	 ;
	 
 expression:    logic_expression
                {
					  $$ = $1;
					//  fprintf(asm_out,"%s\n",$$->code.c_str());
                       
				}	
	   |        variable ASSIGNOP logic_expression
	            {
					  
					  

					  $$ = new SymbolInfo($1->name + $2->code + $3->name,"");

				      $$->code = $3->code+$1->code;

				      $$->code += "MOV AX, "+$3->name_with_id+"\n";

				      if($1->is_array)
					  { 
						  $$->code += "MOV  "+$1->name_with_id+"[BX], AX\n";
				      }
				      else
					  {
						  $$->code += "MOV "+$1->name_with_id+", AX\n";
				      }

					  

					//  fprintf(asm_out,"%s\n",$$->code.c_str());
   
                   
				}
	   ;
			
logic_expression: rel_expression 
                {
					  $$ = $1;
                    
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

					$$->code += $1->code;
					$$->code += $3->code;

					$$->code += "MOV AX, " + $1->name_with_id+"\n";
					$$->code+="MOV BX, " + $3->name_with_id+"\n";

					string temp = new_temp();
					variables.push_back(temp);

					string label1 = new_label();
					string label2 = new_label();
 
					
					if($2->name=="&&")
					{
						$$->code += ("CMP AX,0\n");
						$$->code += ("JE " + label1 + "\n");
						$$->code += ("CMP BX,0\n");
						$$->code += ("JE " + label1 + "\n");
						$$->code += ("MOV " + temp + ",1\n");
						$$->code += ("JMP " + label2 + "\n");
						$$->code += (label1 + ":\n");
						$$->code += ("MOV " + temp + ",0\n");
						$$->code += (label2 + ":\n");

						 
						 
					}
					else if($2->name=="||")
					{
						$$->code += ("CMP AX,0\n");
						$$->code += ("JNE " + label1 + "\n");
						$$->code += ("CMP BX,0\n");
						$$->code += ("JNE " + label1 + "\n");
						$$->code += ("MOV " + temp + ",0\n");
						$$->code += ("JMP " + label2 + "\n");
						$$->code += (label1 + ":\n");
						$$->code += ("MOV " + temp + ",1\n");
						$$->code += (label2 + ":\n");
						 
						
					}

					$$->name_with_id = temp;
					


                    
				}
		 ;
			
rel_expression: simple_expression 
                {
					  $$ = $1;
				}
		|       simple_expression RELOP simple_expression	
		        {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),"");

					  

					 
					  $$->code += $1->code;
					  $$->code += $3->code;

					  $$->code += "MOV AX, " + $1->name_with_id+"\n";
					  $$->code +="CMP AX, " + $3->name_with_id+"\n";

					  string temp = new_temp();
					  variables.push_back(temp);

					  string label1 = new_label();
				      string label2 = new_label();

					  if($2->name == "<")
					  {
							$$->code+="JL " + label1+"\n";
					  }
					  else if($2->name=="<=")
					  {
						  $$->code+="JLE " + label1+"\n";
					  }
					  else if($2->name==">")
					  {
						  $$->code+="JG " + label1+"\n";
					  }
					  else if($2->name==">=")
					  {
						  $$->code+="JGE " + label1+"\n";
					  }
					  else if($2->name=="==")
					  {
						  $$->code+="JE " + label1+"\n";
					  }
					  else if($2->name == "!=")
					  {
						  $$->code+="JNE " + label1+"\n";

					  }
						
					  $$->code += "MOV "+ temp +", 0\n";
					  $$->code += "JMP "+ label2 +"\n";

					  $$->code += label1 + ":\n";
					  $$->code += "MOV "+ temp +", 1\n";
					  $$->code += label2+":\n";

					  $$->name_with_id = temp;

					 



					  

					  
						



                     
				}
		;
				
simple_expression: term 
                {  
					  $$ = $1;
                    
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

					  $$->code += $1->code;
					  $$->code += $3->code;

					  

					  $$->code += "MOV AX, "+ $1->name_with_id+"\n";

					 
					  $$->code += "MOV BX, "+ $3->name_with_id +"\n";

					   

					  string temp = new_temp();
					  variables.push_back(temp);

					  if($2->name == "+")
					  {
							$$->code += "ADD AX, BX\n";
							$$->code += "MOV "+ temp + ", AX\n";
					  }
					  else if($2->name == "-")
					  {
							 
							$$->code += ("SUB AX, BX\n");
							$$->code += ("MOV " + temp + ", AX\n");
					 }
							  
					 $$->name_with_id = temp; 

		 
                   
				}
		  ;
					
term:	        unary_expression
                {
					  $$ = $1;
                      
				}
     |          term MULOP unary_expression
	            {
					$$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),"");
					$$->sub_type = "int";

                      
					$$->code += $1->code;
					$$->code += $3->code;

					$$->code += "MOV AX, "+ $1->name_with_id+"\n";
					$$->code += "MOV BX, "+ $3->name_with_id +"\n";

					string temp = new_temp();
					variables.push_back(temp);

					if($2->name == "*")
					{
						$$->code += "IMUL BX\n";
						$$->code += "MOV "+ temp + ", AX\n";
					}
					else if($2->name == "/")
					{
					
						string label1 = new_label();
						string label2 = new_label();

						$$->code += ("CMP AX,0\n");
						$$->code += ("JGE " + label1 + "\n");
						$$->code += ("MOV DX,-1\n");
						$$->code += ("JMP " + label2+"\n");
						$$->code += (label1 + ":\n"); 
						$$->code += ("MOV DX,0\n");
						$$->code += (label2 + ":\n");
						$$->code += ("IDIV BX\n");
						$$->code += ("MOV " + temp + ", AX\n");
					}
					else
					{

						string label1 = new_label();
						string label2 = new_label();

						$$->code += ("CMP AX,0\n");
						$$->code += ("JGE " + label1 + "\n");
						$$->code += ("MOV DX,-1\n");
						$$->code += ("JMP " + label2+"\n");
						$$->code += (label1 + ":\n"); 
						$$->code += ("MOV DX,0\n");
						$$->code += (label2 + ":\n");
						$$->code += ("IDIV BX\n");
						$$->code += ("MOV " + temp + ", DX\n");
					}
					
					$$->name_with_id = temp;  
			

				}
     ;
unary_expression: ADDOP unary_expression  
                {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name(),"");
					  $$->code += $2->code;
					  if($1->name == "-")
					  {
						  string temp = new_temp();
					      variables.push_back(temp);

					      $$->code += ("MOV AX, " + $2->name_with_id + "\n");
					      $$->code += ("NEG AX\n");
					      $$->code += ("MOV " + temp +", AX\n");
					      $$->name_with_id = temp;
					  }
                 
				}
		 |      NOT unary_expression 
		        {
					$$ = new SymbolInfo($1->get_name()+$2->get_name(),"");
					$$->code += $2->code;
					string temp = new_temp();
					variables.push_back(temp);
					string label1 = new_label();
					string label2 = new_label();


					$$->code += ("MOV AX, " + $2->name_with_id + "\n");
					$$->code += ("CMP AX,0\n");
					$$->code += ("JE" + label1 + "\n");
					$$->code += ("MOV " + temp + ",0\n");
					$$->code += ("JMP " + label2 + "\n");
					$$->code += (label1 + ":\n");
					$$->code += ("MOV "+ temp +", 1\n");
					$$->code += (label2 + ":\n");


					$$->name_with_id = temp;
			    }
		 |      factor 
		        {
					  $$ = $1;
                     
				}
		 ;
	
factor:         variable 
                {
					  $$ = $1;

					  if($$->is_array)
					  {

						  string temp= new_temp();
						  variables.push_back(temp);
						  
				          $$->code += "MOV AX, " + $1->name_with_id + "[BX]\n";
				          $$->code += "MOV " + temp + ", AX\n";
				          $$->name_with_id = temp;
					  }
                 
				}
	|           ID LPAREN 
	            {
					 current_argument_list.push(vector<string>());
					 current_argument_name_with_id.push(vector<string>());
				} argument_list RPAREN
	            {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name()+$4->get_name()+$5->get_name(),"");
					  SymbolInfo *temp = table->my_look_up($1->get_name());

					  vector<string>parameter = temp->parameter_list;

					  string code = $4->code;

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

					  code += ("CALL " + $1->name + "\n");
 
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

					  $$->code = code;
					  $$->name_with_id = temp1;
					  
					   
					  $$->sub_type = temp->return_type;
					  current_argument_list.pop();


               
					  
				}
	|           LPAREN expression RPAREN
	            {
					  $$ = $2;
                   
				}
	|           CONST_INT 
	            {
					  $$ = $1;
					  string temp = new_temp();
					  variables.push_back(temp);
					  $$->sub_type = "int";
					  $$->name_with_id = temp;
					  $$->code += ("MOV " + temp + "," + $1->name + "\n");
                   
				}
	|           CONST_FLOAT
	            {
					  $$ = $1;
					  string temp = new_temp();
					  variables.push_back(temp);
					  $$->sub_type = "float";
					  $$->name_with_id = temp;

					  $$->code += ("MOV " + temp + "," + $1->name + "\n");
                   
				}
	|           variable INCOP
	            {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name(),"");
					  string temp = new_temp();
					  variables.push_back(temp);
					  if($1->is_array)
					  {
					      //$$->code += ("MOV " + temp + ", " + $1->name_with_id + "[BX]\n");
						  //$$->code += ("\nINC " + $1->name_with_id + "[BX]\n");

						  $$->code += ("MOV AX," + $1->name_with_id + "[BX]\n");
						  $$->code += ("MOV " + temp + ", "+ "AX\n");
						  $$->code += ("INC " + $1->name_with_id + "[BX]\n");


					  }
					  else
					  {
						  $$->code += ("MOV AX," + $1->name_with_id + "\n");
						  $$->code += ("MOV " + temp + ", "+ "AX\n");
						  $$->code += ("INC " + $1->name_with_id + "\n");

					  }

					  $$->name_with_id = temp;
					  
                  
				} 
	|           variable DECOP
	            {
					  $$ = new SymbolInfo($1->get_name()+$2->get_name(),"");
					  string temp = new_temp();
					  variables.push_back(temp);
					  if($1->is_array)
					  {
					      //$$->code += ("MOV " + temp + ", " + $1->name_with_id + "[BX]\n");
						  //$$->code += ("DEC " + $1->name_with_id + "[BX]\n");

						  $$->code += ("MOV AX," + $1->name_with_id + "[BX]\n");
						  $$->code += ("MOV " + temp + ", "+ "AX\n");
						  $$->code += ("DEC " + $1->name_with_id + "[BX]\n");


					  }
					  else
					  {
						  $$->code += ("MOV AX," + $1->name_with_id + "\n");
						  $$->code += ("MOV " + temp + ", "+ "AX\n");
						  $$->code += ("DEC " + $1->name_with_id + "\n");

					  }

					  $$->name_with_id = temp;
					  
					  
                   
				}
	;
	
argument_list: arguments
               {
					  $$ = $1;
				 
			   }
			  | { $$ = new SymbolInfo();}
			  ;
	
arguments:    arguments COMMA logic_expression
               {
				      $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),"");
					  current_argument_list.top().push_back($3->sub_type);
					  current_argument_name_with_id.top().push_back($3->name_with_id);
					  $$->code += ($1->code + $3->code);

                    
			   }
	      |    logic_expression
		       {
				      $$ = $1;
					  current_argument_list.top().push_back($1->sub_type);
					  current_argument_name_with_id.top().push_back($1->name_with_id);
					  
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
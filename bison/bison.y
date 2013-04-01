%{
#include <stdio.h>
#include <string.h>
 
void yyerror(const char *str)
{
        fprintf(stderr,"������: %s\n",str);
}
 
int yywrap()
{
        return 1;
} 
  
main()
{
        yyparse();
} 

%}

%token IMPORT FUNCTION WHILE VAR_BEGIN IF ELSE FOR ARRAY_INITIALIZATION 
%token IDENTIFIER NUMBER STRING_DEFINITION END_OF_THE_INSTRUCTION ARG_SPLITTER 
%token PLUS MINUS DIVIDE MULTIPLY ASSIGN MORE LESS MORE_OR_EQUAL LESS_OR_EQUAL EQUAL NOT_EQUAL
%token OPEN_BLOCK CLOSE_BLOCK OPEN_BRACKET CLOSE_BRACKET STRING_CONCETATE RETURN

%%
commands: /* empty */
        | commands command
        ;	
		
variable:
		VAR_BEGIN IDENTIFIER
		;
		
arguments: /* empty */
        | variable arguments
        ;
		
any_variable:
		IDENTIFIER 
		| 
		function_call 
		| 
		variable 
		| 
		STRING_DEFINITION
		;
		
string_variable:
		STRING_DEFINITION 
		| 
		variable
		;

command:
        function_declaration
        |
        function_call
		|
		assign_value
		|
		string_concetate
		|
		return_value
        ;



function_declaration:
		FUNCTION IDENTIFIER OPEN_BRACKET arguments CLOSE_BRACKET
        {
                printf("������� %s\n", $2);
        }
        ;
function_call:
		IDENTIFIER OPEN_BRACKET arguments CLOSE_BRACKET END_OF_THE_INSTRUCTION
        {
                printf("����� ������� %s\n", $1);
        }
        ;
assign_value:
		VAR_BEGIN IDENTIFIER ASSIGN any_variable
        {
                printf("\n");
        }
        ;
string_concetate:
		variable STRING_CONCETATE string_variable
        {
                printf("\n");
        }
        ;
return_value:
		RETURN any_variable
        {
                printf("\n");
        }
        ;
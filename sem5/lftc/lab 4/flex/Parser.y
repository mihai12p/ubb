%{
#include <stdio.h>
#include <stdlib.h>

#define YYDEBUG 1

extern int yylex();
extern int current_line;
void yyerror(const char* s);
extern int yydebug;
%}

%token INCLUDE LIBRARY MAIN RETURN CONST INT DOUBLE STRUCT TIPSPECIAL
%token IF ELSE WHILE SWITCH CASE DEFAULT BREAK STD CIN COUT
%token LBRACE RBRACE SEMICOLON COLON LPAREN RPAREN COMMA QUOTE
%token PERCENT ADD SUB MUL DIV LT GT SHL SHR ASSIGN NEQ AND OR EQ LE GE
%token NUMBER ID STRING_LITERAL

%%
program:
    includes main_function
    ;

includes:
    INCLUDE LT LIBRARY GT
    |
    ;

main_function:
    INT MAIN LPAREN RPAREN LBRACE statements RBRACE
    ;

statements:
    | statements statement
    ;

statement:
    RETURN expression SEMICOLON
    | declaration SEMICOLON
    | expression SEMICOLON
    | cin_statement SEMICOLON
    | cout_statement SEMICOLON
    | compound_statement
    | while_statement
    ;

while_statement:
    WHILE LPAREN expression RPAREN compound_statement
    ;

cin_statement:
    STD COLON COLON CIN rightshift_id_list
    ;

cout_statement:
    STD COLON COLON COUT leftshift_id_list
    ;

leftshift_id_list:
    SHL expression
    | leftshift_id_list SHL expression
    ;

rightshift_id_list:
    SHR ID
    | rightshift_id_list SHR ID
    ;

compound_statement:
    LBRACE statements RBRACE
    ;

declaration:
    type declaration_list
    | CONST type declaration_list
    ;

declaration_list:
    single_declaration
    | declaration_list COMMA single_declaration
    ;

single_declaration:
    ID
    | ID ASSIGN expression
    ;

type:
    INT
    | DOUBLE
    ;

expression:
    ID ASSIGN expression
    | expression ADD expression
    | expression SUB expression
    | expression MUL expression
    | expression DIV expression
    | expression NEQ expression
    | expression LT expression
    | expression GT expression
    | expression PERCENT expression
    | LPAREN expression RPAREN
    | NUMBER
    | ID
    | STRING_LITERAL
    ;

%%

void yyerror(const char* s)
{
    fprintf(stderr, "Eroare la linia %d: %s\n", current_line - 1, s);
}
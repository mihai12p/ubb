%{
#include "Parser.tab.h"
#include <stdio.h>
#include <stdlib.h>

int current_line = 1;
%}

%option noyywrap

DIGIT   [0-9]
NUMBER  (0[xX][0-9A-Fa-f]+)|(0[0-7]+)|({DIGIT}+(\.{DIGIT}+)?)
ID      [a-zA-Z][a-zA-Z0-9]{0,7}

%%

\n                          { ++current_line; }
"#include"                  { return INCLUDE; }
"<iostream>"                { return LIBRARY; }
"main"                      { return MAIN; }
"return"                    { return RETURN; }
"int"                       { return INT; }
"std"                       { return STD; }
"cin"                       { return CIN; }
"cout"                      { return COUT; }
"endl"                      { return ENDL; }
"{"                         { return LBRACE; }
"}"                         { return RBRACE; }
";"                         { return SEMICOLON; }
":"                         { return COLON; }
"("                         { return LPAREN; }
")"                         { return RPAREN; }
","                         { return COMMA; }
"+"                         { return ADD; }
"-"                         { return SUB; }
"/"                         { return DIV; }
"*"                         { return MUL; }
"<<"                        { return SHL; }
">>"                        { return SHR; }
"="                         { return ASSIGN; }
{NUMBER}                    { yylval.intval = atoi(yytext); return NUMBER; }
[a-zA-Z][a-zA-Z0-9]{8,}     { printf("Error: '%s' is too long, line %d\n", yytext, current_line); exit(EXIT_FAILURE); }
{ID}                        { strcpy(yylval.strval, yytext); return ID; }
\"[^\"]*\"                  { return STRING_LITERAL; }
[ \t\r]+                    { /* ignora spatiile */ }
.                           { printf("Error: Unknown '%s' on line %d\n", yytext, current_line); exit(EXIT_FAILURE); }

%%
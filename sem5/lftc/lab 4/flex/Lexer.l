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
"iostream"                  { return LIBRARY; }
"main"                      { return MAIN; }
"return"                    { return RETURN; }
"const"                     { return CONST; }
"int"                       { return INT; }
"double"                    { return DOUBLE; }
"struct"                    { return STRUCT; }
"TipSpecial"                { return TIPSPECIAL; }
"if"                        { return IF; }
"else"                      { return ELSE; }
"while"                     { return WHILE; }
"switch"                    { return SWITCH; }
"case"                      { return CASE; }
"default"                   { return DEFAULT; }
"break"                     { return BREAK; }
"std"                       { return STD; }
"cin"                       { return CIN; }
"cout"                      { return COUT; }
"{"                         { return LBRACE; }
"}"                         { return RBRACE; }
";"                         { return SEMICOLON; }
":"                         { return COLON; }
"("                         { return LPAREN; }
")"                         { return RPAREN; }
","                         { return COMMA; }
"\""                        { return QUOTE; }
"%"                         { return PERCENT; }
"+"                         { return ADD; }
"-"                         { return SUB; }
"/"                         { return DIV; }
"*"                         { return MUL; }
"<"                         { return LT; }
">"                         { return GT; }
"<<"                        { return SHL; }
">>"                        { return SHR; }
"="                         { return ASSIGN; }
"!="                        { return NEQ; }
"&&"                        { return AND; }
"||"                        { return OR; }
"=="                        { return EQ; }
"<="                        { return LE; }
">="                        { return GE; }
{NUMBER}                    { return NUMBER; }
[a-zA-Z][a-zA-Z0-9]{8,}     { printf("Error: '%s' is too long, line %d\n", yytext, current_line); exit(EXIT_FAILURE); }
{ID}                        { return ID; }
\"[^\"]*\"                  { return STRING_LITERAL; }
[ \t\r]+                    { /* ignora spatiile */ }
.                           { printf("Error: Unknown '%s' on line %d\n", yytext, current_line); exit(EXIT_FAILURE); }

%%
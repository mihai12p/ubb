%{
#include "LexiTable.h"

int current_line = 1;
PSYMBOL gSymbolTable = NULL;
PSYMBOL gInternalTable = NULL;
%}

%option noyywrap

DIGIT   [0-9]
NUMBER  {DIGIT}+(\.{DIGIT}+)?
ID      [a-zA-Z][a-zA-Z0-9]{0,7}

%%

\n                          { ++current_line; }
"#include"                  { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: #include\n"); }
"iostream"                  { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: iostream\n"); }
"main"                      { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: main\n"); }
"return"                    { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: return\n"); }
"const"                     { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: const\n"); }
"int"                       { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: int\n"); }
"double"                    { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: double\n"); }
"struct"                    { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: struct\n"); }
"TipSpecial"                { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: TipSpecial\n"); }
"if"                        { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: if\n"); }
"else"                      { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: else\n"); }
"while"                     { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: while\n"); }
"switch"                    { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: switch\n"); }
"case"                      { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: case\n"); }
"default"                   { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: default\n"); }
"break"                     { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: break\n"); }
"std"                       { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: std\n"); }
"cin"                       { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: cin\n"); }
"cout"                      { InsertSymbol(&gInternalTable, yytext, 0); printf("KEYWORD: cout\n"); }
"{"                         { InsertSymbol(&gInternalTable, yytext, 0); printf("SYMBOL: {\n"); }
"}"                         { InsertSymbol(&gInternalTable, yytext, 0); printf("SYMBOL: }\n"); }
";"                         { InsertSymbol(&gInternalTable, yytext, 0); printf("SYMBOL: ;\n"); }
":"                         { InsertSymbol(&gInternalTable, yytext, 0); printf("SYMBOL: :\n"); }
"("                         { InsertSymbol(&gInternalTable, yytext, 0); printf("SYMBOL: (\n"); }
")"                         { InsertSymbol(&gInternalTable, yytext, 0); printf("SYMBOL: )\n"); }
","                         { InsertSymbol(&gInternalTable, yytext, 0); printf("SYMBOL: ,\n"); }
"\""                        { InsertSymbol(&gInternalTable, yytext, 0); printf("SYMBOL: \"\n"); }
"%"                         { InsertSymbol(&gInternalTable, yytext, 0); printf("OPERATOR: %s\n", yytext); }
"+" | "-" | "/"             { InsertSymbol(&gInternalTable, yytext, 0); printf("OPERATOR: %s\n", yytext); }
"*"                         { InsertSymbol(&gInternalTable, yytext, 0); printf("OPERATOR: %s\n", yytext); }
"<"                         { InsertSymbol(&gInternalTable, yytext, 0); printf("OPERATOR: %s\n", yytext); }
">"                         { InsertSymbol(&gInternalTable, yytext, 0); printf("OPERATOR: %s\n", yytext); }
"<<"                        { InsertSymbol(&gInternalTable, yytext, 0); printf("OPERATOR: %s\n", yytext); }
">>"                        { InsertSymbol(&gInternalTable, yytext, 0); printf("OPERATOR: %s\n", yytext); }
"="                         { InsertSymbol(&gInternalTable, yytext, 0); printf("OPERATOR: %s\n", yytext); }
"!="                        { InsertSymbol(&gInternalTable, yytext, 0); printf("OPERATOR: %s\n", yytext); }
"&&" | "||" | "=="          { InsertSymbol(&gInternalTable, yytext, 0); printf("OPERATOR: %s\n", yytext); }
"<=" | ">="                 { InsertSymbol(&gInternalTable, yytext, 0); printf("OPERATOR: %s\n", yytext); }
{NUMBER}                    { InsertSymbolInOrder(&gSymbolTable, yytext); InsertSymbol(&gInternalTable, yytext, 2); printf("CONSTANT: %s\n", yytext); }
[a-zA-Z][a-zA-Z0-9]{8,}     { printf("Error: '%s' is too long, line %d\n", yytext, current_line); exit(EXIT_FAILURE); }
{ID}                        { InsertSymbolInOrder(&gSymbolTable, yytext); InsertSymbol(&gInternalTable, yytext, 1); printf("IDENTIFIER: %s\n", yytext); }
[ \t\r]+                    { /* ignora spatiile */ }
.                           { printf("Error: Unknown '%s' on line %d\n", yytext, current_line); exit(EXIT_FAILURE); }

%%
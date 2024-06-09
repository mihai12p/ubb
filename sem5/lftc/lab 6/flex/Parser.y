%{
#include <stdio.h>
#include <stdlib.h>

#define YYDEBUG 1

extern int yylex();
extern int current_line;
void yyerror(const char* s);
extern int yydebug;

char gInstrux[4096] = { 0 };
char gDeclarations[64][64] = { 0 };
int gVariablesCount = 0;

void Add2Code(const char* Str)
{
    strcat(gInstrux, Str);
}

void NewDeclaration(char* Declaration)
{
    strcpy(gDeclarations[gVariablesCount], Declaration);
    ++gVariablesCount;
}

void AddOperation()
{
    Add2Code("\n\tpop  ebx\n");
    Add2Code("\tpop  eax\n");
    Add2Code("\tadd  eax, ebx\n");
    Add2Code("\tpush eax\n");
}

void SubOperation()
{
    Add2Code("\n\tpop  ebx\n");
    Add2Code("\tpop  eax\n");
    Add2Code("\tsub  eax, ebx\n");
    Add2Code("\tpush eax\n");
}

void MulOperation()
{
    Add2Code("\n\tpop  ebx\n");
    Add2Code("\tpop  eax\n");
    Add2Code("\timul ebx\n");
    Add2Code("\tpush eax\n");
}

void DivOperation()
{
    Add2Code("\n\tpop  ebx\n");
    Add2Code("\tpop  eax\n");
    Add2Code("\txor  edx, edx\n");
    Add2Code("\tidiv ebx\n");
    Add2Code("\tpush eax\n");
}

void PrintAsm()
{
    FILE* file = fopen("output.asm", "w");
    if (!file)
    {
        return;
    }

    fprintf(file, "bits 32\n");
    fprintf(file, "global start\n\n");
    fprintf(file, "extern exit, printf, scanf\n");
    fprintf(file, "import exit msvcrt.dll\n");
    fprintf(file, "import scanf msvcrt.dll\n");
    fprintf(file, "import printf msvcrt.dll\n");

    fprintf(file, "\nsegment data use32 class=data\n");
    fprintf(file, "\tformat_d db \"%%d\", 0\n");
    fprintf(file, "\tnewline db 10, 0\n");
    for (int i = 0; i < gVariablesCount; ++i)
    {
        fprintf(file, "\t%s dd 0\n", gDeclarations[i]);
    }

    fprintf(file, "\nsegment code use32 class=code\n");
    fprintf(file, "start:");
    fprintf(file, "%s", gInstrux);
    
    fclose(file);
}

%}

%token INCLUDE LIBRARY MAIN RETURN INT
%token STD CIN COUT ENDL
%token LBRACE RBRACE SEMICOLON COLON LPAREN RPAREN COMMA
%token ASSIGN SHL SHR
%token STRING_LITERAL

%left ADD SUB
%left MUL DIV
%right ASSIGN
%nonassoc LPAREN RPAREN

%union {
    char strval[64];
    int  intval;
}

%token<strval> ID
%token<intval> NUMBER

%type<strval> expression declaration_list term factor

%%
program:
    INCLUDE LIBRARY INT MAIN LPAREN RPAREN LBRACE statements RBRACE
    ;

statements:
    | statements statement
    ;

statement:
    RETURN NUMBER SEMICOLON {
        char buffer[64] = { 0 };
        sprintf(buffer, "\n\tpush %d\n", $2);
        Add2Code(buffer);
        Add2Code("\tcall [exit]");
    }
    | declaration SEMICOLON
    | instr_attr SEMICOLON
    | cin_statement SEMICOLON
    | cout_statement SEMICOLON
    ;

instr_attr:
    ID ASSIGN expression {
        Add2Code("\n\tpop  eax\n");
        char buffer[64] = { 0 };
        sprintf(buffer, "\tmov  [%s], eax\n", $1);
        Add2Code(buffer);
    }
    ;

cin_statement:
    STD COLON COLON CIN rightshift_id_list
    ;

cout_statement:
    STD COLON COLON COUT leftshift_id_list
    ;

leftshift_id_list:
    SHL ID {
        Add2Code("\n\tpush DWORD [");
        Add2Code($2);
        Add2Code("]");
        Add2Code("\n\tpush format_d");
        Add2Code("\n\tcall [printf]");
        Add2Code("\n\tadd  esp, 4 * 2\n");
    }
    | SHL STD COLON COLON ENDL {
        Add2Code("\n\tpush newline");
        Add2Code("\n\tcall [printf]");
        Add2Code("\n\tadd  esp, 4 * 1\n");
    }
    ;

rightshift_id_list:
    SHR ID {
        Add2Code("\n\tpush ");
        Add2Code($2);
        Add2Code("\n\tpush format_d");
        Add2Code("\n\tcall [scanf]");
        Add2Code("\n\tadd  esp, 4 * 2\n");
    }
    ;

declaration:
    INT declaration_list
    ;

declaration_list:
    ID {
        strcpy($$, $1);
        NewDeclaration($1);
    }
    | ID COMMA declaration_list {
        strcpy($$, $1);
        NewDeclaration($1);
    }
    ;

expression:
    expression ADD term {
        AddOperation();
    }
    | expression SUB term {
        SubOperation();
    }
    | term
    ;

term:
    term MUL factor {
        MulOperation();
    }
    | term DIV factor {
        DivOperation();
    }
    | factor
    ;

factor:
    NUMBER {
        char buffer[64] = { 0 };
        sprintf(buffer, "\n\tpush %d\n", $1);
        Add2Code(buffer);
    }
    | ID {
        printf("**************************************************************\n%s\n**************************************************************", $1);
        char buffer[64] = { 0 };
        sprintf(buffer, "\n\tmov  eax, [%s]\n", $1);
        Add2Code(buffer);
        Add2Code("\tpush eax\n");
    }
    ;

%%

void yyerror(const char* s)
{
    fprintf(stderr, "Eroare la linia %d: %s\n", current_line - 1, s);
}
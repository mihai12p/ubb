#include "LexiTable.h"

extern "C" int yylex();
extern "C" FILE* yyin;
extern "C" PSYMBOL gSymbolTable;
extern "C" PSYMBOL gInternalTable;

#define FILE "PATH"

int main(int argc, char** argv)
{
    yyin = fopen(FILE, "r");
    yylex();
    PrintProgramInternalTable(gInternalTable, gSymbolTable);
    printf("\n");
    PrintSymbolTable(gSymbolTable);

    FreeTable(gInternalTable);
    FreeTable(gSymbolTable);
    return 0;
}
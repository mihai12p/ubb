#include <stdio.h>
#include <string>

extern "C" int yyparse();
extern "C" FILE* yyin;
extern "C" int yydebug;
extern "C" void PrintAsm();

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Use flex.exe file.txt\n");
        exit(EXIT_FAILURE);
    }

    yydebug = 1;

    std::string filePath = "d:\\facultate-repo\\sem5\\lftc\\lab6\\";
    filePath += argv[1];

    yyin = fopen(filePath.c_str(), "r");
    if (!yyin)
    {
        fprintf(stderr, "Eroare la deschiderea fisierului '%s'.\n", filePath.c_str());
        return 1;
    }

    int status = yyparse();
    if (!status)
    {
        PrintAsm();
        printf("\nParsing reusit!\n");
    }
    else
    {
        printf("Eroare la parsing.\n");
    }

    fclose(yyin);
    return 0;
}
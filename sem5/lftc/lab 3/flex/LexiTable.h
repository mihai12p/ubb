#ifndef _LEXI_TABLE_H_
#define _LEXI_TABLE_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int gIndex = 2;

typedef struct _SYMBOL
{
    char*           literal;
    int             index;
    struct _SYMBOL* next;
} SYMBOL, * PSYMBOL;

void InsertSymbolInOrder(PSYMBOL* Root, char* Literal)
{
    PSYMBOL current = *Root;
    while (current != NULL)
    {
        if (!strcmp(current->literal, Literal))
        {
            return;
        }
        current = current->next;
    }

    PSYMBOL newNode = (PSYMBOL)malloc(sizeof(SYMBOL));
    newNode->literal = strdup(Literal);
    newNode->next = NULL;

    if (*Root == NULL || strcmp((*Root)->literal, Literal) > 0)
    {
        newNode->next = *Root;
        *Root = newNode;
    }
    else
    {
        PSYMBOL current = *Root;
        while (current->next != NULL && strcmp(current->next->literal, Literal) < 0)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    return;
}

void InsertSymbol(PSYMBOL* Root, char* Literal, int Type)
{
    int alreadyInserted = 0;

    PSYMBOL current = *Root;
    while (current != NULL)
    {
        if (!strcmp(current->literal, Literal))
        {
            alreadyInserted = 1;
            break;
        }
        current = current->next;
    }

    PSYMBOL newNode = (PSYMBOL)malloc(sizeof(SYMBOL));
    newNode->literal = strdup(Literal);
    if (Type)
    {
        newNode->index = Type - 1;
    }
    else
    {
        newNode->index = alreadyInserted ? current->index : gIndex++;
    }
    newNode->next = NULL;

    if (*Root == NULL)
    {
        newNode->next = *Root;
        *Root = newNode;
    }
    else
    {
        PSYMBOL current = *Root;
        while (current->next != NULL)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    return;
}

void PrintProgramInternalTable(PSYMBOL Root, PSYMBOL SymbolTableRoot)
{
    PSYMBOL current = Root;
    printf("Forma interna a programului\n");
    printf("%4s %24s\n", "Cod", "Pozitie in TS");
    while (current != NULL)
    {
        if (current->index < 2)
        {
            int index = 0;
            PSYMBOL symbolTableCurrent = SymbolTableRoot;
            while (symbolTableCurrent != NULL)
            {
                ++index;
                if (!strcmp(symbolTableCurrent->literal, current->literal))
                {
                    break;
                }
                symbolTableCurrent = symbolTableCurrent->next;
            }

            printf("%4d %24d\n", current->index, index);
        }
        else
        {
            printf("%4d\n", current->index);
        }
        current = current->next;
    }
}

void PrintSymbolTable(PSYMBOL Root)
{
    int index = 0;
    PSYMBOL current = Root;
    printf("Tabela de simboluri\n");
    printf("%4s %24s\n", "Pozitie", "Atom lexical");
    while (current != NULL)
    {
        printf("%4d %24s\n", ++index, current->literal);
        current = current->next;
    }
}

void FreeTable(PSYMBOL Root)
{
    while (Root != NULL)
    {
        PSYMBOL temp = Root;
        Root = Root->next;
        free(temp->literal);
        free(temp);
    }
}

#endif//_LEXI_TABLE_H_
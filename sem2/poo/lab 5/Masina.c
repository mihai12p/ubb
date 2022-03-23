#include "Masina.h"
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>

Masina *creeazaMasina(char *numarInmatriculare, char *model, char *categorie) 
{
    Masina *masinaNoua = (Masina*)malloc(sizeof(Masina));

    masinaNoua->numarInmatriculare = (char*) malloc(strlen(numarInmatriculare) * sizeof(char)+1);
    strcpy_s(masinaNoua->numarInmatriculare, strlen(numarInmatriculare) + 1, numarInmatriculare);

    masinaNoua->model = (char*) malloc(strlen(model) * sizeof(char)+1);
    strcpy_s(masinaNoua->model, strlen(model) + 1, model);

    masinaNoua->categorie = (char*) malloc(strlen(categorie) * sizeof(char)+1);
    strcpy_s(masinaNoua->categorie, strlen(categorie) + 1, categorie);

    masinaNoua->inchiriata = 0;

    return masinaNoua;
}

void stergeMasina(Masina *masina) 
{
    free(masina->numarInmatriculare);
    free(masina->model);
    free(masina->categorie);
    free(masina);
}

#include "Validator.h"
#include "MasiniService.h"
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>

int adaugareMasinaService(MasinaRepository *masinaRepository, char *numarInmatriculare, char *model, char *categorie) 
{
    /*
     * Primeste informatiile despre o masina , o valideaza, verifica si adauga in repo
     */
    if (!validareMasina(numarInmatriculare, model, categorie)) 
        return 0;

    Masina *masinaNoua = creeazaMasina(numarInmatriculare, model, categorie);
    if (adaugaMasinaRepository(masinaRepository, masinaNoua)) 
        return 1;

    stergeMasina(masinaNoua);
    return 0;
}

int modificareMasinaService(MasinaRepository *masinaRepository, char *numarInmatriculare, char *model, char *categorie) 
{
    /*
     * Primeste informatiile despre o masina o cauta in repo si daca o gaseste apeleaza modificarea acesteia
     */
    Masina *masinaDeModificat = cautaMasina(masinaRepository, numarInmatriculare);
    if (masinaDeModificat == NULL) 
        return 0;

    //Daca campurile sunt lasate goale inseamna ca nu trebuie modificate
    if (strlen(model) == 0) model = masinaDeModificat->model;
    if (strlen(categorie) == 0) categorie = masinaDeModificat->categorie;

    Masina *masinaNoua = creeazaMasina(numarInmatriculare, model, categorie);
    modificareMasina(masinaRepository, masinaNoua);

    return 1;
}


int inchiriereMasina(MasinaRepository *masinaRepository, char *numarDeInmatriculare) 
{
    /*
     * Seteaza atributul de inchiriat 1 la o masina cu un numar de inmatriculare dat
     */
    int ok = -1, good = 0;
    for (int i = 0; ok == -1 && i < masinaRepository->dimensiune; i++) 
        if (strcmp(masinaRepository->listaMasini[i]->numarInmatriculare, numarDeInmatriculare) == 0) 
        {
            good = 1;
            if (masinaRepository->listaMasini[i]->inchiriata == 0)
                masinaRepository->listaMasini[i]->inchiriata = ok = 1;
            else
                ok = 0;
        }
     
    return (good) ? ok : 0;
}

int returnareMasina(MasinaRepository *masinaRepository, char *numarDeInmatriculare) {
    /*
     * Seteaza atributul de inchiriat 0 la o masina cu un numar de inmatriculare dat
     */
    int ok = -1, good = 0;
    for (int i = 0; ok == -1 && i < masinaRepository->dimensiune; i++) 
        if (strcmp(masinaRepository->listaMasini[i]->numarInmatriculare, numarDeInmatriculare) == 0) 
        {
            good = 1;
            if (masinaRepository->listaMasini[i]->inchiriata == 1)
            {
                masinaRepository->listaMasini[i]->inchiriata = 0;
                ok = 1;
            }
            else
                ok = 0;
        }

    return (good) ? ok : 0;
}

Masina **listaMasiniDupaCategorie(MasinaRepository *masinaRepository, int *dimensiuneListaReturnata, char *categorieDeCautat) 
{
    /*
     * Creaza un pointer catre lista noua cu toate masinile care au categoria data si o returneaza
     */
    Masina **listaMasiniDeCautat = malloc(sizeof(Masina*) * masinaRepository->dimensiune);

    for (int i = 0; i < masinaRepository->dimensiune; i++) 
        if (strcmp(categorieDeCautat, masinaRepository->listaMasini[i]->categorie) == 0) 
            listaMasiniDeCautat[(*dimensiuneListaReturnata)++] = masinaRepository->listaMasini[i];

    return listaMasiniDeCautat;
}

Masina **listaMasiniDupaModel(MasinaRepository *masinaRepository, int *dimensiuneListaReturnata, char *modelDeCautat) 
{
    /*
     * Creaza un pointer catre lista noua cu toate masinile care au model data si o returneaza
     */
    Masina **listaMasiniDeCautat = malloc(sizeof(Masina*) * masinaRepository->dimensiune);

    for (int i = 0; i < masinaRepository->dimensiune; i++)
        if (strcmp(modelDeCautat, masinaRepository->listaMasini[i]->model) == 0)
            listaMasiniDeCautat[(*dimensiuneListaReturnata)++] = masinaRepository->listaMasini[i];

    return listaMasiniDeCautat;
}

int comparareMasiniDupaModel(Masina *masina1, Masina *masina2, int crescator) 
{
    /*
     * Returneaza o valoare de adevar prin compararea modelului a doua masini in ordine cresc or decresc
     */
    if (crescator == 1) 
        return (strcmp(masina1->model, masina2->model) > 0 ? 1 : 0);
    else 
        return (strcmp(masina2->model, masina1->model) > 0 ? 1 : 0);
}

Masina **sortareMasiniDupaModel(MasinaRepository *masinaRepository, int crescator) 
{
    /*
     *  creaza un pointer la o lista noua unde va copia toate masinile si va aplica bubble sort
     */
    Masina **listaMasiniSortata = malloc(sizeof(Masina*) * masinaRepository->dimensiune);
    //Copiere masini in lista
    for (int i = 0; i < masinaRepository->dimensiune; i++) 
        listaMasiniSortata[i] = masinaRepository->listaMasini[i];

    //Sortare
    int listaSortata = 0;
    while (!listaSortata) 
    {
        listaSortata = 1;
        for (int i = 0; i < masinaRepository->dimensiune-1; i++) 
            if (comparareMasiniDupaModel(listaMasiniSortata[i], listaMasiniSortata[i+1], crescator)) 
            {
                listaSortata = 0;
                Masina *aux = listaMasiniSortata[i];
                listaMasiniSortata[i] = listaMasiniSortata[i+1];
                listaMasiniSortata[i+1] = aux;
            }
    }
    return listaMasiniSortata;
}

int comparareMasiniDupaCategorie(Masina *masina1, Masina *masina2, int crescator) 
{
    /*
     * Returneaza o valoare de adevar prin compararea categoriile a doua masini in ordine cresc or decresc
     */
    if (crescator == 1) 
        return (strcmp(masina1->categorie, masina2->categorie) > 0 ? 1 : 0);
    else 
        return (strcmp(masina2->categorie, masina1->categorie) > 0 ? 1 : 0);
}

Masina **sortareMasiniDupaCategorie(MasinaRepository *masinaRepository, int crescator) 
{
    /*
     *  creaza un pointer la o lista noua unde va copia toate masinile si va aplica bubble sort
     */
    Masina **listaMasiniSortata = malloc(sizeof(Masina*) * masinaRepository->dimensiune);
    //Copiere masini in lista
    for (int i = 0; i < masinaRepository->dimensiune; i++) 
        listaMasiniSortata[i] = masinaRepository->listaMasini[i];

    //Sortare
    int listaSortata = 0;
    while (!listaSortata) 
    {
        listaSortata = 1;
        for (int i = 0; i < masinaRepository->dimensiune-1; i++) 
            if (comparareMasiniDupaCategorie(listaMasiniSortata[i], listaMasiniSortata[i+1], crescator)) 
            {
                listaSortata = 0;
                Masina *aux = listaMasiniSortata[i];
                listaMasiniSortata[i] = listaMasiniSortata[i+1];
                listaMasiniSortata[i+1] = aux;
            }
    }
    return listaMasiniSortata;
}

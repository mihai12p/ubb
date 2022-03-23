#include "MasiniRepository.h"
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>

MasinaRepository *creeazaMasinaRepository() 
{
    /*
     * creaza un repo gol format din (capacitate/dimensiune/lista_masini)
     */
    MasinaRepository *masinaRepository = (MasinaRepository*)malloc(sizeof(MasinaRepository));
    masinaRepository->capacitate = 1;
    masinaRepository->dimensiune = 0;
    masinaRepository->listaMasini = malloc(sizeof(Masina*));
    return masinaRepository;
}

void redimensionareRepository(MasinaRepository *masinaRepository) 
{
    /*
     * Daca capacitatea va fi egala cu dimensiunea se va apela aceasta functie si se va realoca o lista de 2 ori mai mare
     */
    Masina **listaNouaMasini = malloc(2*masinaRepository->capacitate*sizeof(Masina*));
    masinaRepository->capacitate *= 2;
    for (int i = 0; i < masinaRepository->capacitate; i++)
        listaNouaMasini[i] = masinaRepository->listaMasini[i];

    free(masinaRepository->listaMasini);
    masinaRepository->listaMasini = listaNouaMasini;
}

int adaugaMasinaRepository(MasinaRepository *masinaRepository, Masina *masina) 
{
    /*
     * adauga o masina in repo daca nu exista o masina cu numar de inmatriculare dat
     */

    for (int i = 0; i < masinaRepository->dimensiune; i++) 
        if (strcmp(masina->numarInmatriculare, masinaRepository->listaMasini[i]->numarInmatriculare) == 0) 
            return 0; //Deja exista o masina cu acelasi numar de inmatriculare

    //Daca se ajunge aici inseamna ca masina poate fi adaugata
    if (masinaRepository->dimensiune == masinaRepository->capacitate)
        redimensionareRepository(masinaRepository);

    masinaRepository->listaMasini[masinaRepository->dimensiune++] = masina;
    return 1;
}

int modificareMasina(MasinaRepository *masinaRepository, Masina *masinaDeModificat) 
{
    /*
     * cauta masina cu acelasi numar de inmatriculare si o schimba
     */
    for (int i = 0; i < masinaRepository->dimensiune; i++) {
        if (strcmp(masinaRepository->listaMasini[i]->numarInmatriculare, masinaDeModificat->numarInmatriculare) == 0) 
        {
            stergeMasina(masinaRepository->listaMasini[i]);
            masinaRepository->listaMasini[i] = masinaDeModificat;
            return 1;
        }
    }
    return 0;
}

Masina *cautaMasina(MasinaRepository *masinaRepository, char *numarInmatriculare) 
{
    /*
     *cauta o masina in repo si returneaza masina daca o gaseste sau NULL in cazul inexistentei
     */
    for (int i = 0; i < masinaRepository->dimensiune; i++)
        if (strcmp(masinaRepository->listaMasini[i]->numarInmatriculare, numarInmatriculare) == 0) 
            return masinaRepository->listaMasini[i];

    return NULL;
}

void stergeMasinaRepository(MasinaRepository *masinaRepository) 
{
    /*
     * sterge masinile din repository dupa care dealoca lista si repo ul in sine
     */
    for (int i = 0; i < masinaRepository->dimensiune; i++)
        stergeMasina(masinaRepository->listaMasini[i]);

    free(masinaRepository->listaMasini);
    free(masinaRepository);
}

#ifndef UNTITLED_MASINISERVICE_H
#define UNTITLED_MASINISERVICE_H
#include "MasiniRepository.h"

typedef struct
{
	lista_masini* toateMasini;
	lista_masini* listaUndo;
} MasinaRepository;

int undo(MasinaRepository* masinaRepository);

int adaugareMasinaService(MasinaRepository *masinaRepository, char *numarInmatriculare, char *model, char *categorie);

int modificareMasinaService(MasinaRepository *masinaRepository, char *numarInmatriculare, char *model, char *categorie);

int inchiriereMasina(MasinaRepository *masinaRepository, char *numarDeInmatriculare);

int returnareMasina(MasinaRepository *masinaRepository, char *numarDeInmatriculare);

ElemType* listaMasiniDupaCategorie(MasinaRepository *masinaRepository, int *dimensiuneListaReturnata, char *categorieDeCautat);

ElemType* listaMasiniDupaModel(MasinaRepository *masinaRepository, int *dimensiuneListaReturnata, char *modelDeCautat);

typedef int(*functie)(ElemType e1, ElemType e2, int order);
ElemType* sortareMasiniDupaFunctie(MasinaRepository* masinaRepository, functie func, int order);

#endif //UNTITLED_MASINISERVICE_H

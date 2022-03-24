#ifndef UNTITLED_MASINIREPOSITORY_H
#define UNTITLED_MASINIREPOSITORY_H

#include "Masina.h"
#include "string.h"

typedef void* ElemType;
typedef void(*DestroyFct)(ElemType);
typedef ElemType(*CopyFct)(ElemType);

typedef struct 
{
	ElemType* listaMasini;
	int capacitate;
	int dimensiune;
	DestroyFct dfunc;
} lista_masini;

int comparareMasiniDupaModel(Masina* masina1, Masina* masina2, int crescator);
int comparareMasiniDupaCategorie(Masina* masina1, Masina* masina2, int crescator);

ElemType set(lista_masini* masinaRepository, int poz, ElemType masina);
ElemType get(lista_masini* masinaRepository, int poz);

lista_masini* creeazaMasinaRepository(DestroyFct func);

int adaugaMasinaRepository(lista_masini* masinaRepository, ElemType masina);

int modificareMasina(lista_masini* masinaRepository, ElemType masinaDeModificat);

ElemType cautaMasina(lista_masini* masinaRepository, char *numarInmatriculare);

int size(lista_masini* masinaRepository);
lista_masini* copiazaLista(lista_masini* lista, CopyFct func);
void stergeLista(lista_masini* lista);
ElemType stergeUltim(lista_masini* lista);

#endif //UNTITLED_MASINIREPOSITORY_H

#include "Validator.h"
#include "MasiniService.h"
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>

int undo(MasinaRepository* masinaRepository)
{
	if (masinaRepository->listaUndo->dimensiune == 0)
		return 1; // nu mai putem face undo

	lista_masini* listaFaraUltimulElem = stergeUltim(masinaRepository->listaUndo);
	stergeLista(masinaRepository->toateMasini);
	masinaRepository->toateMasini = listaFaraUltimulElem;
	return 0;
}

int adaugareMasinaService(MasinaRepository *masinaRepository, char *numarInmatriculare, char *model, char *categorie) 
{
	/*
	 * Primeste informatiile despre o masina , o valideaza, verifica si adauga in repo
	 */
	if (!validareMasina(numarInmatriculare, model, categorie)) 
		return 0;

	for (int i = 0; i < masinaRepository->toateMasini->dimensiune; i++)
	{
		Masina* rez = get(masinaRepository->toateMasini, i);
		if (strcmp(numarInmatriculare, rez->numarInmatriculare) == 0)
			return 0; //Deja exista o masina cu acelasi numar de inmatriculare
	}

	Masina* masinaNoua = creeazaMasina(numarInmatriculare, model, categorie, 0);
	lista_masini* undoList = copiazaLista(masinaRepository->toateMasini, copiazaMasina);
	adaugaMasinaRepository(masinaRepository->toateMasini, masinaNoua);
	adaugaMasinaRepository(masinaRepository->listaUndo, undoList);

	return 1;
}

int modificareMasinaService(MasinaRepository *masinaRepository, char *numarInmatriculare, char *model, char *categorie) 
{
	/*
	 * Primeste informatiile despre o masina o cauta in repo si daca o gaseste apeleaza modificarea acesteia
	 */
	Masina* masinaDeModificat = cautaMasina(masinaRepository->toateMasini, numarInmatriculare);
	if (masinaDeModificat == NULL) 
		return 0;

	//Daca campurile sunt lasate goale inseamna ca nu trebuie modificate
	if (strlen(model) == 0) model = masinaDeModificat->model;
	if (strlen(categorie) == 0) categorie = masinaDeModificat->categorie;

	Masina* masinaNoua = creeazaMasina(numarInmatriculare, model, categorie, masinaDeModificat->inchiriata);
	lista_masini* undoList = copiazaLista(masinaRepository->toateMasini, copiazaMasina);
	modificareMasina(masinaRepository->toateMasini, masinaNoua);
	adaugaMasinaRepository(masinaRepository->listaUndo, undoList);

	return 1;
}

int inchiriereMasina(MasinaRepository *masinaRepository, char *numarDeInmatriculare) 
{
	/*
	 * Seteaza atributul de inchiriat 1 la o masina cu un numar de inmatriculare dat
	 */
	int ok = -1, good = 0;
	for (int i = 0; ok == -1 && i < masinaRepository->toateMasini->dimensiune; i++)
	{
		Masina* rez = get(masinaRepository->toateMasini, i);
		if (strcmp(rez->numarInmatriculare, numarDeInmatriculare) == 0)
		{
			good = 1;
			if (rez->inchiriata == 0)
			{
				lista_masini* undoList = copiazaLista(masinaRepository->toateMasini, copiazaMasina);
				adaugaMasinaRepository(masinaRepository->listaUndo, undoList);

				ok = rez->inchiriata = 1;
			}
			else
				ok = 0;
		}
	}
	 
	return (good) ? ok : 0;
}

int returnareMasina(MasinaRepository *masinaRepository, char *numarDeInmatriculare) 
{
	/*
	 * Seteaza atributul de inchiriat 0 la o masina cu un numar de inmatriculare dat
	 */
	int ok = -1, good = 0;
	for (int i = 0; ok == -1 && i < masinaRepository->toateMasini->dimensiune; i++)
	{
		Masina* rez = get(masinaRepository->toateMasini, i);
		if (strcmp(rez->numarInmatriculare, numarDeInmatriculare) == 0)
		{
			good = 1;
			if (rez->inchiriata == 1)
			{
				lista_masini* undoList = copiazaLista(masinaRepository->toateMasini, copiazaMasina);
				adaugaMasinaRepository(masinaRepository->listaUndo, undoList);

				rez->inchiriata = 0;
				ok = 1;
			}
			else
				ok = 0;
		}
	}

	return (good) ? ok : 0;
}

ElemType* listaMasiniDupaCategorie(MasinaRepository *masinaRepository, int *dimensiuneListaReturnata, char *categorieDeCautat) 
{
	/*
	 * Creaza un pointer catre lista noua cu toate masinile care au categoria data si o returneaza
	 */
	ElemType* listaMasiniDeCautat = (ElemType*)malloc(sizeof(ElemType) * masinaRepository->toateMasini->dimensiune);

	for (int i = 0; i < masinaRepository->toateMasini->dimensiune; i++)
	{
		Masina* rez = get(masinaRepository->toateMasini, i);
		if (strcmp(categorieDeCautat, rez->categorie) == 0)
			listaMasiniDeCautat[(*dimensiuneListaReturnata)++] = rez;
	}

	return listaMasiniDeCautat;
}

ElemType* listaMasiniDupaModel(MasinaRepository *masinaRepository, int *dimensiuneListaReturnata, char *modelDeCautat) 
{
	/*
	 * Creaza un pointer catre lista noua cu toate masinile care au model data si o returneaza
	 */
	ElemType* listaMasiniDeCautat = (ElemType*)malloc(sizeof(ElemType) * masinaRepository->toateMasini->dimensiune);

	for (int i = 0; i < masinaRepository->toateMasini->dimensiune; i++)
	{
		Masina* rez = get(masinaRepository->toateMasini, i);
		if (strcmp(modelDeCautat, rez->model) == 0)
			listaMasiniDeCautat[(*dimensiuneListaReturnata)++] = rez;
	}

	return listaMasiniDeCautat;
}

ElemType* sortareMasiniDupaFunctie(MasinaRepository* masinaRepository, functie func, int order)
{
	/*
	 *  creaza un pointer la o lista noua unde va copia toate masinile si va aplica bubble sort
	 */
	ElemType* listaMasiniSortata = (ElemType*)malloc(sizeof(ElemType) * masinaRepository->toateMasini->dimensiune);
	//Copiere masini in lista
	for (int i = 0; i < masinaRepository->toateMasini->dimensiune; i++)
		listaMasiniSortata[i] = masinaRepository->toateMasini->listaMasini[i];

	//Sortare
	int listaSortata = 0;
	while (!listaSortata)
	{
		listaSortata = 1;
		for (int i = 0; i < masinaRepository->toateMasini->dimensiune - 1; i++)
			if (func(listaMasiniSortata[i], listaMasiniSortata[i + 1], order) > 0)
			{
				listaSortata = 0;
				ElemType aux = listaMasiniSortata[i];
				listaMasiniSortata[i] = listaMasiniSortata[i + 1];
				listaMasiniSortata[i + 1] = aux;
			}
	}
	return listaMasiniSortata;
}

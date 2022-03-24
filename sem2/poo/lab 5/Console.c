#include "Console.h"
#include "MasiniService.h"
#include "Validator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>

void printOptions() 
{
	printf("\n");
	printf("1 - Adaugare masina\n");
	printf("2 - Modificare masina existenta\n");
	printf("3 - Inchiriere masina\n");
	printf("4 - Returnare masina\n");
	printf("5 - Filtrare masini\n");
	printf("6 - Sortare masini\n");
	printf("7 - Undo operatie\n");
	printf("8 - Afisare lista masini\n");
	printf("0 - Exit\n");
	printf("\n");
}

void adaugareMasina_UI(MasinaRepository *masinaRepository) 
{
	char numarDeInmatriculareNou[100], modelNou[100], categorieNoua[100];
	fseek(stdin, 0, SEEK_END); //golire buffer
	printf("Numar de inmatriculare:");
	fgets(numarDeInmatriculareNou, 100, stdin);
	numarDeInmatriculareNou[strlen(numarDeInmatriculareNou) - 1] = '\0';
	printf("Model:");
	fgets(modelNou, 100, stdin);
	modelNou[strlen(modelNou) - 1] = '\0';
	printf("Categorie:");
	fgets(categorieNoua, 100, stdin);
	categorieNoua[strlen(categorieNoua) - 1] = '\0';
	if (adaugareMasinaService(masinaRepository, numarDeInmatriculareNou, modelNou, categorieNoua) == 1)
		printf("Adaugare reusita!\n");
	else
		printf("Adaugare esuata!\n");
}

void modificareMasina_UI(MasinaRepository *masinaRepository) 
{
	char numarDeInmatriculareNou[100], modelNou[100], categorieNoua[100];
	fseek(stdin, 0, SEEK_END); //golire buffer
	printf("Numar de inmatriculare:");
	fgets(numarDeInmatriculareNou, 100, stdin);
	numarDeInmatriculareNou[strlen(numarDeInmatriculareNou) - 1] = '\0';
	printf("Model (sau '' pentru nemodificare):");
	fgets(modelNou, 100, stdin);
	modelNou[strlen(modelNou) - 1] = '\0';
	printf("Categorie(sau '' pentru nemodificare):");
	fgets(categorieNoua, 100, stdin);
	categorieNoua[strlen(categorieNoua) - 1] = '\0';
	if (modificareMasinaService(masinaRepository, numarDeInmatriculareNou, modelNou, categorieNoua) == 1)
		printf("Modificare reusita!\n");
	else
		printf("Modificare esuata!\n");
}

void inchiriereMasina_UI(MasinaRepository *masinaRepository) 
{
	char numarDeInmatriculare[100];
	fseek(stdin, 0, SEEK_END); //golire buffer
	printf("Numar de inmatriculare:");
	fgets(numarDeInmatriculare, 100, stdin);
	numarDeInmatriculare[strlen(numarDeInmatriculare) - 1] = '\0';
	if (inchiriereMasina(masinaRepository, numarDeInmatriculare) == 1)
		printf("Inchiriere reusita!\n");
	else
		printf("Inchiriere esuata!\n");
}

void returnareMasina_UI(MasinaRepository *masinaRepository) 
{
	char numarDeInmatriculare[100];
	fseek(stdin, 0, SEEK_END); //golire buffer
	printf("Numar de inmatriculare: ");
	fgets(numarDeInmatriculare, 100, stdin);
	numarDeInmatriculare[strlen(numarDeInmatriculare) - 1] = '\0';
	if (returnareMasina(masinaRepository, numarDeInmatriculare) == 1)
		printf("Returnare reusita!\n");
	else
		printf("Returnare esuata!\n");
}

void filtrareMasini_UI(MasinaRepository *masinaRepository) 
{
	char criteriu[20] = { 0 }, filtru[20] = { 0 };
	printf("Introduceti criteriul (categorie/model):");
	scanf_s("%19s", criteriu, _countof(criteriu));
	if (strcmp(criteriu, "categorie") == 0) 
	{
		printf("Categorie:");
		scanf_s("%19s", filtru, _countof(filtru));
		printf("Rezultate:\n");

		int dimensiuneListaMasini = 0;
		ElemType* listaMasiniDeCautat = listaMasiniDupaCategorie(masinaRepository, &dimensiuneListaMasini, filtru);

		//Afisare masini
		for (int i = 0; i < dimensiuneListaMasini; i++)
		{
			Masina* rez = listaMasiniDeCautat[i];
			printf("Numar inmatriculare: %s | Model: %s | Categorie: %s | Inchiriata: %s\n", rez->numarInmatriculare, rez->model, rez->categorie, rez->inchiriata == 0 ? "False" : "True");
		}

		free(listaMasiniDeCautat);
	} 
	else if (strcmp(criteriu, "model") == 0)
	{
		printf("Model:");
		scanf_s("%19s", filtru, _countof(filtru));
		printf("Rezultate:\n");
		int dimensiuneListaMasini = 0;
		ElemType* listaMasiniDeCautat = listaMasiniDupaModel(masinaRepository, &dimensiuneListaMasini, filtru);

		//Afisare masini
		for (int i = 0; i < dimensiuneListaMasini; i++)
		{
			Masina* rez = listaMasiniDeCautat[i];
			printf("Numar inmatriculare: %s | Model: %s | Categorie: %s | Inchiriata: %s\n", rez->numarInmatriculare, rez->model, rez->categorie, rez->inchiriata == 0 ? "False" : "True");
		}

		free(listaMasiniDeCautat);
	} 
	else
		printf("Criteriu invalid!\n");
}

void afisareMasini_UI(MasinaRepository *masinaRepository) 
{
	for (int i = 0; i < masinaRepository->toateMasini->dimensiune; i++)
	{
		Masina* rez = get(masinaRepository->toateMasini, i);
		printf("Numar inmatriculare: %s | Model: %s | Categorie: %s | Inchiriata: %s\n", rez->numarInmatriculare, rez->model, rez->categorie, rez->inchiriata == 0 ? "False" : "True");
	}
}

void afisareMasiniSortate_UI(MasinaRepository *masinaRepository) 
{
	printf("Sortare dupa: model/categorie?");
	char criteriuSortare[30] = { 0 };
	scanf_s("%29s", criteriuSortare, _countof(criteriuSortare));
	if (strcmp(criteriuSortare, "model") == 0)
	{
		printf("crescator / descrescator?");
		char ordineDeSortare[20] = { 0 };
		scanf_s("%19s", ordineDeSortare, _countof(ordineDeSortare));
		if (strcmp(ordineDeSortare, "crescator") == 0 || strcmp(ordineDeSortare, "descrescator") == 0)
		{
			//Sortare dupa model, crescator
			printf("Rezultat: \n");
			ElemType* listaSortataMasini = sortareMasiniDupaFunctie(masinaRepository, comparareMasiniDupaModel, !strcmp(ordineDeSortare, "crescator"));
			for (int i = 0; i < masinaRepository->toateMasini->dimensiune; i++)
			{
				Masina* rez = listaSortataMasini[i];
				printf("Numar inmatriculare: %s | Model: %s | Categorie: %s | Inchiriata: %s\n", rez->numarInmatriculare, rez->model, rez->categorie, rez->inchiriata == 0 ? "False" : "True");
			}

			free(listaSortataMasini);
		}
		else
			printf("Ordine invalida!\n");
	} 
	else if (strcmp(criteriuSortare, "categorie") == 0)
	{
		printf("crescator / descrescator?");
		char ordineDeSortare[20] = { 0 };
		scanf_s("%19s", ordineDeSortare, _countof(ordineDeSortare));
		if (strcmp(ordineDeSortare, "crescator") == 0 || strcmp(ordineDeSortare, "descrescator") == 0)
		{
			//Sortare dupa categorie, crescator
			printf("Rezultat: \n");
			ElemType* listaSortataMasini = sortareMasiniDupaFunctie(masinaRepository, comparareMasiniDupaCategorie, !strcmp(ordineDeSortare, "crescator"));
			for (int i = 0; i < masinaRepository->toateMasini->dimensiune; i++)
			{
				Masina* rez = listaSortataMasini[i];
				printf("Numar inmatriculare: %s | Model: %s | Categorie: %s | Inchiriata: %s\n", rez->numarInmatriculare, rez->model, rez->categorie, rez->inchiriata == 0 ? "False" : "True");
			}

			free(listaSortataMasini);
		} 
		else 
			printf("Ordine invalida!\n");
	} 
	else 
		printf("Criteriu invalid!\n");
}

void undoOperatie_UI(MasinaRepository* masinaRepository)
{
	if (undo(masinaRepository) == 0)
		printf("Undo efectuat cu succes!\n");
	else
		printf("Nu se mai poate face undo!\n");
}

void runConsoleApplication() 
{
	int rulareProgram = 1;
	int comandaDeExecutat;
	MasinaRepository masini;
	masini.toateMasini = creeazaMasinaRepository(stergeMasina);
	masini.listaUndo = creeazaMasinaRepository(stergeLista);

	while (rulareProgram) 
	{
		printOptions();
		printf(">>>");
		scanf_s("%d", &comandaDeExecutat);
		if (comandaDeExecutat == 0)
		{
			stergeLista(masini.toateMasini);
			stergeLista(masini.listaUndo);
			rulareProgram = 0;
		}
		else if (comandaDeExecutat == 1)
			//Adauga masina
			adaugareMasina_UI(&masini);
		else if (comandaDeExecutat == 2)
			//Modifica masina existenta
			modificareMasina_UI(&masini);
		else if (comandaDeExecutat == 3)
			//Inchiriere masina
			inchiriereMasina_UI(&masini);
		else if (comandaDeExecutat == 4)
			//Returnare masina
			returnareMasina_UI(&masini);
		else if (comandaDeExecutat == 5)
			//Filtrare masini
			filtrareMasini_UI(&masini);
		else if (comandaDeExecutat == 6)
			//Sortare masini
			afisareMasiniSortate_UI(&masini);
		else if (comandaDeExecutat == 7)
			//Undo ultima operatie
			undoOperatie_UI(&masini);
		else if (comandaDeExecutat == 8) 
			//Afisare masini
			afisareMasini_UI(&masini);
	}
}

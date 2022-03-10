#include <stdio.h>
#include "operatii.h"

/*
	desc: afiseaza toti concurentii actuali
	param: repo pentru gestiunea participantilor
*/
void printall(repository* repo)
{
	printf("\n" ANSI_COLOR_GREEN("Lista participanti: \n"));
	for (int i = 0; i < repo->len; ++i)
	{
		printf("\t" ANSI_COLOR_BLUE("%d") ". %s %s | ", i + 1, repo->user[i].nume, repo->user[i].prenume);
		for (int j = 0; j < 10; ++j)
			printf("%d ", repo->user[i].scor[j]);
		printf("\n");
	}
	printf("\n");
}

/*
	desc: interfata cu utilizatorul pentru a adauga un nou concurent
	param: repo pentru gestiunea participantilor
*/
void adaugaUi(repository* repo)
{
	char nume[23] = { 0 }, prenume[23] = { 0 };
	printf("Introduceti numele, prenumele si scorul noului participant: \n");
	printf("\tNume si prenume: ");
	scanf_s("%23s %23s", nume, sizeof(nume), prenume, sizeof(prenume));

	if (cauta(repo, nume, prenume) != NULL)
	{
		printf(ANSI_COLOR_RED("\tExista deja un participant cu acest nume si prenume.\n"));
		return;
	}

	int scor[10] = { 0 };
	printf("\tScor: ");
	for (int i = 0; i < 10; ++i)
		scanf_s("%d", &scor[i]);

	if (adauga(repo, nume, prenume, scor) != NULL)
		printf(ANSI_COLOR_GREEN("\tParticipantul a fost adaugat cu succes.\n"));
	else
		printf(ANSI_COLOR_RED("\tFiecare problema poate avea intre 1-10 puncte.\n"));
}

/*
	desc: interfata cu utilizatorul pentru a actualiza detaliile unui concurent existent
	param: repo pentru gestiunea participantilor
*/
void actualizeazaUi(repository* repo)
{
	char nume[23] = { 0 }, prenume[23] = { 0 };
	printf("Introduceti numele si prenumele unui participant existent: \n");
	printf("\tNume si prenume: ");
	scanf_s("%23s %23s", nume, sizeof(nume), prenume, sizeof(prenume));

	participant* cautat = cauta(repo, nume, prenume);
	if (cautat == NULL)
	{
		printf(ANSI_COLOR_RED("\tNu a fost gasit un astfel de participant.\n"));
		return;
	}

	printf("\t" ANSI_COLOR_GREEN("Participant gasit: ") "%s %s | ", cautat->nume, cautat->prenume);
	for (int i = 0; i < 10; ++i)
		printf("%d ", cautat->scor[i]);
	printf("\n");

	printf("\tIntroduceti noile date pentru acest participant: \n");
	printf("\t\tNume si prenume noi: ");
	scanf_s("%23s %23s", nume, sizeof(nume), prenume, sizeof(prenume));

	if (cauta(repo, nume, prenume) != NULL)
	{
		printf(ANSI_COLOR_RED("\tExista deja un participant cu acest nume si prenume.\n"));
		return;
	}

	int scor[10] = { 0 };
	printf("\t\tScor nou: ");
	for (int i = 0; i < 10; ++i)
		scanf_s("%d", &scor[i]);

	if (actualizeaza(cautat, nume, prenume, scor) != NULL)
		printf(ANSI_COLOR_GREEN("\tParticipantul a fost modificat cu succes.\n"));
	else
		printf(ANSI_COLOR_RED("\tFiecare problema poate avea intre 1-10 puncte.\n"));
}

/*
	desc: interfata cu utilizatorul pentru a elimina un concurent
	param: repo pentru gestiunea participantilor
*/
void stergeUi(repository* repo)
{
	char nume[23] = { 0 }, prenume[23] = { 0 };
	printf("Introduceti numele si prenumele unui participant existent: \n");
	printf("\tNume si prenume: ");
	scanf_s("%23s %23s", nume, sizeof(nume), prenume, sizeof(prenume));

	participant* cautat = cauta(repo, nume, prenume);
	if (cautat == NULL)
	{
		printf(ANSI_COLOR_RED("\tNu a fost gasit un astfel de participant.\n"));
		return;
	}

	printf("\t" ANSI_COLOR_GREEN("Participant gasit: ") "%s %s | ", cautat->nume, cautat->prenume);
	for (int i = 0; i < 10; ++i)
		printf("%d ", cautat->scor[i]);
	printf("\n");

	printf("\t" ANSI_COLOR_RED("Sunteti sigur ca vreti sa stergeti acest participant: \n"));
	printf("\t\t" ANSI_COLOR_GREEN("1") " - absolut sigur\n");
	printf("\t\t" ANSI_COLOR_GREEN("2") " - nu\n");
	printf("\t" ANSI_COLOR_YELLOW("Introduceti optiunea dorita: "));

	int del = 0;
	if (scanf_s("%d", &del) == 1 && del == 1 && sterge(repo, &cautat) != NULL)
		printf("\t" ANSI_COLOR_GREEN("Participantul a fost eliminat cu succes.\n"));
	else
		printf("\t" ANSI_COLOR_RED("Participantul nu a fost eliminat.\n"));
}

/*
	functie utila pentru testarea aplicatiei
	desc: adauga participanti in lista
	param: repo pentru gestiunea participantilor
*/
void participanti_predefiniti(repository* repo)
{
	int scor[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	adauga(repo, "Mihai", "Panduru", scor);

	int scor2[10] = { 1, 2, 2, 3, 1, 1, 1, 1, 10, 5 };
	adauga(repo, "Alexandru", "Nedelcu", scor2);

	int scor3[10] = { 10, 2, 3, 1, 5, 10, 2, 1, 10, 10 };
	adauga(repo, "Ion", "Tiriac", scor3);

	int scor4[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	adauga(repo, "Vladimir", "Putin", scor4);

	int scor5[10] = { 2, 8, 3, 4, 3, 8, 2, 8, 8, 9 };
	adauga(repo, "Dani", "Mocanu", scor5);

	int scor6[10] = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };
	adauga(repo, "Stefan", "Nastasa", scor6);

	int scor7[10] = { 1, 2, 3, 4, 5, 3, 3, 2, 2, 10 };
	adauga(repo, "Mihai", "Bendeac", scor7);

	int scor8[10] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
	adauga(repo, "Volodymyr", "Zelenskyy", scor8);

	int scor9[10] = { 2, 2, 10, 2, 2, 10, 2, 2, 10, 10 };
	adauga(repo, "Florin", "Salam", scor9);

	int scor10[10] = { 7, 7, 7, 4, 5, 7, 2, 7, 4, 6 };
	adauga(repo, "Andrea", "Bocelli", scor10);

	int scor11[10] = { 4, 2, 4, 2, 4, 2, 4, 2, 4, 2 };
	adauga(repo, "Snoop", "Dogg", scor11);

	int scor12[10] = { 6, 3, 5, 9, 7, 2, 1, 5, 6, 9 };
	adauga(repo, "Chester", "Bennington", scor12);
}

/*
	desc: interfata generala cu utilizatorul
	param: repo pentru gestiunea participantilor
	return vals: 0 daca programul trebuie sa continue
				-1 daca programul trebuie sa se opreasca
*/
int consola(repository* repo)
{
	printf(ANSI_COLOR_CYAN("Optiuni disponibile: \n"));
	printf("\t" ANSI_COLOR_GREEN("1") " - adauga participanti\n");
	printf("\t" ANSI_COLOR_GREEN("2") " - actualizeaza participant existent\n");
	printf("\t" ANSI_COLOR_GREEN("3") " - sterge participanti\n");
	printf("\t" ANSI_COLOR_GREEN("4") " - filtreaza participanti\n");
	printf("\t" ANSI_COLOR_GREEN("5") " - sorteaza participanti\n");
	printf("\t" ANSI_COLOR_GREEN("6") " - iesire\n");
	printf(ANSI_COLOR_YELLOW("Introduceti optiunea dorita: "));

	int option;
	if (scanf_s("%d", &option) != 1) return -1; // incheiem executia programului daca nu se introduce un numar

	switch (option)
	{
		case 1:
			adaugaUi(repo);
			break;

		case 2:
			actualizeazaUi(repo);
			break;

		case 3:
			stergeUi(repo);
			break;

		case 4:
		case 5:
			break;

		case 6:
			printf(ANSI_COLOR_MAGENTA("Ciau!\n"));
			return -1;

		default:
			printf(ANSI_COLOR_RED("Optiune invalida."));
	}

	printall(repo);
	printf("\n");

	return 0;
}

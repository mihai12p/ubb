#include <stdio.h>
#include "operatii.h"
#include "valid.h"

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
	participant user;
	printf("Introduceti numele, prenumele si scorul noului participant: \n");
	printf("\tNume si prenume: ");
	scanf_s("%23s %23s", user.nume, sizeof(user.nume), user.prenume, sizeof(user.prenume));

	printf("\tScor: ");
	for (int i = 0; i < 10; ++i)
		scanf_s("%d", user.scor + i);

	if (valid(user.scor) == 0)
	{
		adauga(repo, user);
		printf(ANSI_COLOR_GREEN("\tParticipantul a fost adaugat cu succes.\n"));
	}
	else
		printf(ANSI_COLOR_RED("\tFiecare problema poate avea intre 1-10 puncte.\n"));
}

/*
	desc: interfata cu utilizatorul pentru a actualiza detaliile unui concurent existent
	param: repo pentru gestiunea participantilor
*/
void actualizeazaUi(repository* repo)
{
	participant user;
	printf("Introduceti numele si prenumele unui participant existent: \n");
	printf("\tNume si prenume: ");
	scanf_s("%23s %23s", user.nume, sizeof(user.nume), user.prenume, sizeof(user.prenume));

	int poz = cauta(repo, user);
	if (poz == -1)
	{
		printf(ANSI_COLOR_RED("\tNu a fost gasit un astfel de participant.\n"));
		return;
	}

	printf("\t" ANSI_COLOR_GREEN("Participant gasit: ") "%s %s | ", user.nume, user.prenume);
	for (int i = 0; i < 10; ++i)
		printf("%d ", repo->user[poz].scor[i]);
	printf("\n");

	printf("\tIntroduceti noile date pentru acest participant: \n");
	printf("\t\tNume si prenume noi: ");
	scanf_s("%23s %23s", user.nume, sizeof(user.nume), user.prenume, sizeof(user.prenume));

	printf("\t\tScor nou: ");
	for (int i = 0; i < 10; ++i)
		scanf_s("%d", user.scor + i);

	if (valid(user.scor) == 0)
	{
		actualizeaza(repo, user, poz);
		printf(ANSI_COLOR_GREEN("\tParticipantul a fost modificat cu succes.\n"));
	}
	else
		printf(ANSI_COLOR_RED("\tFiecare problema poate avea intre 1-10 puncte.\n"));
}

/*
	desc: interfata cu utilizatorul pentru a elimina un concurent
	param: repo pentru gestiunea participantilor
*/
void stergeUi(repository* repo)
{
	participant user;
	printf("Introduceti numele si prenumele unui participant existent: \n");
	printf("\tNume si prenume: ");
	scanf_s("%23s %23s", user.nume, sizeof(user.nume), user.prenume, sizeof(user.prenume));

	int poz = cauta(repo, user);
	if (poz == -1)
	{
		printf(ANSI_COLOR_RED("\tNu a fost gasit un astfel de participant.\n"));
		return;
	}

	printf("\t" ANSI_COLOR_GREEN("Participant gasit: ") "%s %s | ", user.nume, user.prenume);
	for (int i = 0; i < 10; ++i)
		printf("%d ", repo->user[poz].scor[i]);
	printf("\n");

	printf("\t" ANSI_COLOR_RED("Sunteti sigur ca vreti sa stergeti acest participant: \n"));
	printf("\t\t" ANSI_COLOR_GREEN("1") " - da\n");
	printf("\t\t" ANSI_COLOR_GREEN("2") " - nu\n");
	printf("\t" ANSI_COLOR_YELLOW("Introduceti optiunea dorita: "));

	int del = 0;
	if (scanf_s("%d", &del) == 1 && del == 1)
	{
		sterge(repo, poz);
		printf("\t" ANSI_COLOR_GREEN("Participantul a fost eliminat cu succes.\n"));
	}
	else
		printf("\t" ANSI_COLOR_RED("Participantul nu a fost eliminat.\n"));
}

/*
	desc: interfata generala cu utilizatorul
	param: repo pentru gestiunea participantilor
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

#include <string.h>
#include <assert.h>
#include "service.h"
#include "valid.h"

/*
	desc: adauga un nou participant in concurs
	param: repo pentru gestiunea participantilor, numele, prenumele si scorul noului participant
	return vals: adresa noului participant adaugat
			     NULL daca scorul sau datele de intrare sunt invalide
*/
participant* adauga(repository* repo, char* nume, char* prenume, int* scor)
{
	if (repo == NULL || nume == NULL || prenume == NULL || scor == NULL)
		return NULL;

	if (valid(scor) == -1)
		return NULL;

	participant participantNou;
	strcpy_s(participantNou.nume, sizeof(participantNou.nume), nume);
	strcpy_s(participantNou.prenume, sizeof(participantNou.prenume), prenume);
	for (int i = 0; i < 10; ++i)
		participantNou.scor[i] = scor[i];

	return adaugaRepo(repo, participantNou);
}

/*
	desc: verifica daca un participant este inscris in concurs
	param: repo pentru gestiunea participantilor, numele si prenumele participantului cautat
	return vals: returneaza adresa participantului daca acesta este inscris adica daca este concurent
							NULL daca participantul nu este inscris adica nu este concurent sau datele de intrare sunt invalide
*/
participant* cauta(repository* repo, char* nume, char* prenume)
{
	if (repo == NULL || nume == NULL || prenume == NULL)
		return NULL;

	return cautaRepo(repo, nume, prenume);
}

/*
	desc: actualizeaza detaliile pentru un concurent
	param: cautat pentru identificarea participantului, numele, prenumele si scorul pentru participantului modificat
	return vals: returneaza adresa participantului modificat
							NULL daca scorul sau datele de intrare sunt invalide
*/
participant* actualizeaza(participant* cautat, char* nume, char* prenume, int* scor)
{
	if (cautat == NULL || nume == NULL || prenume == NULL || scor == NULL)
		return NULL;

	if (valid(scor) == -1)
		return NULL;

	return actualizeazaRepo(cautat, nume, prenume, scor);
}

/*
	desc: elimina un concurent
	param: repo pentru gestiunea participantilor, cautat pentru identificarea participantului
	return vals: returneaza un pointer catre adresa 1
							NULL daca datele de intrare sunt invalide
*/
void* sterge(repository* repo, participant* cautat)
{
	if (repo == NULL || cautat == NULL)
		return NULL;

	for (int i = 0; i < repo->len; ++i)
		if (!strcmp(repo->user[i].nume, cautat->nume) && !strcmp(repo->user[i].prenume, cautat->prenume))
		{
			stergeRepo(repo, i);
			break;
		}

	return (void*)1;
}

void test_adauga()
{
	repository repo;
	reset(&repo);

	int scor[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	adauga(&repo, "Mihai", "Panduru", scor);
	assert(repo.len == 1);

	int scorGresit[10] = { 1, 2, 3, 0, 5, 6, 7, 8, 9, 10 };
	participant* neadaugat = adauga(&repo, "Vladimir", "Putin", scorGresit);
	assert(repo.len == 1);
	assert(neadaugat == NULL);

	participant* neadaugat2 = adauga(&repo, "Vladimir", NULL, scor);
	assert(repo.len == 1);
	assert(neadaugat2 == NULL);

	int scor2[10] = { 2, 8, 3, 4, 3, 8, 2, 8, 8, 9 };
	participant* adaugat = adauga(&repo, "Dani", "Mocanu", scor2);
	assert(repo.len == 2);
	assert(adaugat != NULL);
	assert(strcmp(adaugat->nume, "Dani") == 0);
	assert(strcmp(adaugat->prenume, "Mocanu") == 0);
	assert(adaugat->scor[5] == 8);
}

void test_reset()
{
	repository repo;
	reset(&repo);
	assert(repo.len == 0);

	int scor[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	participant* adaugat = adauga(&repo, "Mihai", "Panduru", scor);
	assert(repo.len == 1);

	int scor2[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	participant* adaugat2 = adauga(&repo, "Vladimir", "Putin", scor2);
	assert(repo.len == 2);

	reset(&repo);
	assert(repo.len == 0);
	assert(adaugat != NULL);
	assert(strlen(adaugat->nume) == 0);
	assert(strlen(adaugat->prenume) == 0);
	assert(adaugat2 != NULL);
	assert(adaugat2->scor[5] == 0);
}

void test_cauta()
{
	repository repo;
	reset(&repo);

	int scor[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	participant* adaugat = adauga(&repo, "Mihai", "Panduru", scor);
	participant* cautat = cauta(&repo, "Mihai", "Panduru");
	assert(cautat != NULL);
	assert(adaugat == cautat);

	assert(cauta(&repo, "Vladimir", "Putin") == NULL);
	assert(cauta(&repo, "Vladimir", NULL) == NULL);
}

void test_actualizeaza()
{
	repository repo;
	reset(&repo);

	int scor[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	adauga(&repo, "Mihai", "Panduru", scor);
	participant* cautat = cauta(&repo, "Mihai", "Panduru");
	assert(cautat != NULL);

	int scorGresit[10] = { 1, 2, 3, 0, 5, 6, 7, 8, 9, 10 };
	participant* nemodificat = actualizeaza(cautat, "Vladimir", "Putin", scorGresit);
	assert(nemodificat == NULL);
	assert(strcmp(cautat->nume, "Mihai") == 0);
	assert(strcmp(cautat->prenume, "Panduru") == 0);

	participant* nemodificat2 = actualizeaza(NULL, "Vladimir", "Putin", scor);
	assert(nemodificat2 == NULL);

	int scorNou[10] = { 5, 2, 5, 4, 5, 6, 7, 8, 9, 10 };
	participant* modificat = actualizeaza(cautat, "Alberto", "Zimbran", scorNou);
	assert(repo.len == 1);
	assert(modificat != NULL);
	assert(modificat == cautat);
	assert(strcmp(modificat->nume, "Alberto") == 0);
	assert(strcmp(modificat->prenume, "Zimbran") == 0);
	assert(modificat->scor[2] == 5);
}

void test_sterge()
{
	repository repo;
	reset(&repo);

	int scor[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	adauga(&repo, "Mihai", "Panduru", scor);

	int scor2[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	participant* adaugat = adauga(&repo, "Vladimir", "Putin", scor2);

	int scor3[10] = { 2, 8, 3, 4, 3, 8, 2, 8, 8, 9 };
	adauga(&repo, "Dani", "Mocanu", scor3);
	assert(repo.len == 3);

	void* nesters = sterge(&repo, NULL);
	assert(nesters == NULL);

	void* ret = sterge(&repo, adaugat);
	assert(ret != NULL);
	assert(repo.len == 2);
	assert(cauta(&repo, "Vladimir", "Putin") == NULL);
	assert(adaugat != NULL);
}

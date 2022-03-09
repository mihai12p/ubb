#include <string.h>
#include "concurs.h"

/*
	desc: adauga un nou participant in concurs
	param: repo pentru gestiunea participantilor, newUser pentru noul participant
	return vals: adresa noului participant adaugat
*/
participant* adaugaRepo(repository* repo, participant newUser)
{
	repo->user[repo->len++] = newUser;
	return &repo->user[repo->len - 1];
}

/*
	desc: reseteaza lista de concurenti
	param: repo pentru gestiunea participantilor
*/
void reset(repository* repo)
{
	memset(repo, 0, sizeof(*repo));
}

/*
	desc: verifica daca un participant este inscris in concurs
	param: repo pentru gestiunea participantilor, numele si prenumele participantului cautat
	return vals: returneaza adresa participantului daca acesta este inscris adica daca este concurent
							NULL daca participantul nu este inscris adica nu este concurent
*/
participant* cautaRepo(repository* repo, char* nume, char* prenume)
{
	for (int i = 0; i < repo->len; ++i)
		if (!strcmp(repo->user[i].nume, nume) && !strcmp(repo->user[i].prenume, prenume))
			return &repo->user[i];

	return NULL;
}

/*
	desc: actualizeaza detaliile pentru un concurent
	param: modifiedUser pentru identificarea participantului, numele, prenumele si scorul pentru participantului modificat
	return vals: returneaza adresa participantului modificat
*/
participant* actualizeazaRepo(participant* modifiedUser, char* nume, char* prenume, int* scor)
{
	strcpy_s(modifiedUser->nume, sizeof(modifiedUser->nume), nume);
	strcpy_s(modifiedUser->prenume, sizeof(modifiedUser->prenume), prenume);
	for (int i = 0; i < 10; ++i)
		modifiedUser->scor[i] = scor[i];

	return modifiedUser;
}

/*
	desc: elimina un concurent
	param: repo pentru gestiunea participantilor, poz pentru pozitia concurentului in lista
*/
void stergeRepo(repository* repo, int poz)
{
	for (int i = poz; i < repo->len - 1; ++i)
		repo->user[i] = repo->user[i + 1];

	memset(&repo->user[repo->len - 1], 0, sizeof(repo->user[repo->len - 1]));
	--repo->len;
}

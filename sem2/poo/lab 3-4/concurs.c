#include <string.h>
#include "concurs.h"

/*
	desc: adauga un nou participant in concurs
	param: repo pentru gestiunea participantilor, newUser pentru noul participant
*/
void adauga(repository* repo, participant newUser)
{
	repo->user[repo->len] = newUser;
	++repo->len;
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
	param: repo pentru gestiunea participantilor, existingUser pentru participantul cautat
	return vals: returneaza pozitia participantului in lista daca acesta este inscris adica daca este concurent
							-1 daca participantul nu este inscris adica nu este concurent
*/
int cauta(repository* repo, participant existingUser)
{
	for (int i = 0; i < repo->len; ++i)
		if (!strcmp(repo->user[i].nume, existingUser.nume) && !strcmp(repo->user[i].prenume, existingUser.prenume))
			return i;

	return -1;
}

/*
	desc: actualizeaza detaliile pentru un concurent
	param: repo pentru gestiunea participantilor, modifiedUser pentru concurentul modificat, poz pentru pozitia concurentului in lista
*/
void actualizeaza(repository* repo, participant modifiedUser, int poz)
{
	repo->user[poz] = modifiedUser;
}

/*
	desc: elimina un concurent
	param: repo pentru gestiunea participantilor, poz pentru pozitia concurentului in lista
*/
void sterge(repository* repo, int poz)
{
	for (int i = poz; i < repo->len - 1; ++i)
		repo->user[i] = repo->user[i + 1];

	memset(&repo->user[repo->len - 1], 0, sizeof(repo->user[repo->len - 1]));
	--repo->len;
}

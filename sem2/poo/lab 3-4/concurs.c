#include <string.h>
#include <assert.h>
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

void test_adauga()
{
	repository repo;
	reset(&repo);

	adauga(&repo, (participant) { "Mihai", "Panduru", { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } });
	assert(repo.len == 1);

	adauga(&repo, (participant) { "Vladimir", "Putin", { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } });
	assert(repo.len == 2);

	adauga(&repo, (participant) { "Dani", "Mocanu", { 2, 8, 3, 4, 3, 8, 2, 8, 8, 9 } });
	assert(repo.len == 3);
	assert(strcmp(repo.user[2].nume, "Dani") == 0);
	assert(strcmp(repo.user[2].prenume, "Mocanu") == 0);
	assert(repo.user[2].scor[5] == 8);
}

void test_reset()
{
	repository repo;
	reset(&repo);
	assert(repo.len == 0);

	adauga(&repo, (participant) { "Mihai", "Panduru", { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } });
	assert(repo.len == 1);

	adauga(&repo, (participant) { "Vladimir", "Putin", { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } });
	assert(repo.len == 2);

	reset(&repo);
	assert(repo.len == 0);
	assert(strlen(repo.user[0].nume) == 0);
	assert(strlen(repo.user[0].prenume) == 0);
	assert(repo.user[1].scor[5] == 0);
}

void test_cauta()
{
	repository repo;
	reset(&repo);

	adauga(&repo, (participant) { "Mihai", "Panduru", { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } });
	assert(cauta(&repo, (participant) { "Mihai", "Panduru", { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } }) == 0);

	adauga(&repo, (participant) { "Volodymyr", "Zelenskyy", { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 } });
	assert(cauta(&repo, (participant) { "Volodymyr", "Zelenskyy", { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 } }) == 1);

	assert(cauta(&repo, (participant) { "Vladimir", "Putin", { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } }) == -1);
}

void test_actualizeaza()
{
	repository repo;
	reset(&repo);

	adauga(&repo, (participant) { "Mihai", "Panduru", { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } });
	int poz = cauta(&repo, (participant) { "Mihai", "Panduru", { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } });

	actualizeaza(&repo, (participant) { "Alberto", "Zimbran", { 5, 2, 5, 4, 5, 6, 7, 8, 9, 10 } }, poz);
	assert(repo.len == 1);
	assert(strcmp(repo.user[poz].nume, "Alberto") == 0);
	assert(strcmp(repo.user[poz].prenume, "Zimbran") == 0);
	assert(repo.user[poz].scor[2] == 5);
}

void test_sterge()
{
	repository repo;
	reset(&repo);

	adauga(&repo, (participant) { "Mihai", "Panduru", { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } });
	adauga(&repo, (participant) { "Vladimir", "Putin", { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } });
	adauga(&repo, (participant) { "Dani", "Mocanu", { 2, 8, 3, 4, 3, 8, 2, 8, 8, 9 } });
	assert(repo.len == 3);

	sterge(&repo, cauta(&repo, (participant) { "Vladimir", "Putin", { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } }));
	assert(repo.len == 2);
	assert(cauta(&repo, (participant) { "Vladimir", "Putin", { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } }) == -1);
}

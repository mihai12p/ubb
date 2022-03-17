#include <assert.h>
#include <string.h>
#include "service.h"

/*
	desc: validam scorul
	param: concurentul ce trebuie validat
	return vals: returneaza 0 daca concurentul este valid
							1 daca numele este invalid, 2 daca prenumele este invalid sau 3 daca scorul este invalid
*/
int isValid(participant concurent)
{
	if (strlen(concurent.nume) == 0)
		return 1;
	
	if (strlen(concurent.prenume) == 0)
		return 2;

	for (int i = 0; i < 10; ++i)
		if (concurent.scor[i] < 1 || concurent.scor[i] > 10)
			return 3;

	return 0;
}

void test_isValid()
{
	int scor[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	participant newParticipant = createParticipant("", "Putin", scor);
	assert(isValid(newParticipant) == 1);
	destroyParticipant(&newParticipant);

	newParticipant = createParticipant("Vladimir", "", scor);
	assert(isValid(newParticipant) == 2);
	destroyParticipant(&newParticipant);

	int scor2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	newParticipant = createParticipant("Vladimir", "Putin", scor2);
	assert(isValid(newParticipant) == 0);
	destroyParticipant(&newParticipant);

	int scor3[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	newParticipant = createParticipant("Vladimir", "Putin", scor3);
	assert(isValid(newParticipant) == 3);
	destroyParticipant(&newParticipant);
}

/*
	desc: adauga un nou participant in concurs
	param: repo pentru gestiunea participantilor, numele, prenumele si scorul noului participant
	return vals: 0 daca totul este in regula
			     cod de eroare altfel
*/
int adauga(repository* repo, char* nume, char* prenume, int* scor)
{
	if (repo == NULL || nume == NULL || prenume == NULL || scor == NULL)
		return -1;

	participant newParticipant = createParticipant(nume, prenume, scor);
	int errCode = isValid(newParticipant);
	if (errCode != 0)
	{
		destroyParticipant(&newParticipant);
		return errCode;
	}

	adaugaRepo(repo, newParticipant);
	return 0;
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
	return vals: 0 daca totul este in regula
				 cod de eroare altfel
*/
int actualizeaza(participant* cautat, char* nume, char* prenume, int* scor)
{
	if (cautat == NULL || nume == NULL || prenume == NULL || scor == NULL)
		return -1;

	participant newParticipant = createParticipant(nume, prenume, scor);
	int errCode = isValid(newParticipant);
	if (errCode != 0)
	{
		destroyParticipant(&newParticipant);
		return errCode;
	}

	destroyParticipant(cautat);
	*cautat = newParticipant;

	return 0;
}

/*
	desc: elimina un concurent
	param: repo pentru gestiunea participantilor, cautat pentru identificarea participantului
	return vals: pointer la adresa 1 daca totul este in regula
				 NULL daca datele de intrare sunt invalide
*/
void* sterge(repository* repo, participant* cautat)
{
	if (repo == NULL || cautat == NULL || cautat == NULL)
		return NULL;

	for (int i = 0; i < repo->len; ++i)
		if (!strcmp(repo->concurent[i].nume, cautat->nume) && !strcmp(repo->concurent[i].prenume, cautat->prenume))
		{
			destroyParticipant(cautat);
			stergeRepo(repo, i);

			break;
		}

	return (void*)1;
}

/*
	desc: filtreaza concurentii
	param: repo pentru gestiunea participantilor, mod de filtrare si valori de comparatie
	return vals: noua lista filtrata
*/
repository filter(repository* repo, int mode, char val)
{
	repository filteredList = createEmpty();
	for (int i = 0; i < size(repo); ++i)
	{
		participant concurent = get(repo, i);
		if (mode == 1 && getScore(concurent) < val)
			adaugaRepo(&filteredList, copyParticipant(&concurent));
		else if (mode == 2 && concurent.nume[0] == val)
			adaugaRepo(&filteredList, copyParticipant(&concurent));
	}
	return filteredList;
}

int byNameCresc(participant* p1, participant* p2) { return strcmp(p1->nume, p2->nume) > 0; }
int byNameDescr(participant* p1, participant* p2) { return strcmp(p1->nume, p2->nume) <= 0; }
int byScoreCresc(participant* p1, participant* p2) { return getScore(*p1) > getScore(*p2); }
int byScoreDescr(participant* p1, participant* p2) { return getScore(*p1) <= getScore(*p2); }

/*
	desc: sorteaza concurentii
	param: repo pentru gestiunea participantilor, ord pentru crescator/descrescator
	return vals: noua lista filtrata
*/
repository sortBy(repository* repo, int byWhat, int ord)
{
	repository sortedRepo = copyList(repo);

	function func = byNameCresc;
	if (byWhat == 1 && ord == 2)
		func = byNameDescr;
	else if (byWhat == 2 && ord == 1)
		func = byScoreCresc;
	else if (byWhat == 2 && ord == 2)
		func = byScoreDescr;
		
	sort(&sortedRepo, func);

	return sortedRepo;
}

void test_adauga()
{
	repository repo = createEmpty();

	int scor[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int ret = adauga(&repo, "Mihai", "Panduru", scor);
	assert(ret == 0);
	assert(repo.len == 1);

	int scorGresit[10] = { 1, 2, 3, 0, 5, 6, 7, 8, 9, 10 };
	ret = adauga(&repo, "Vladimir", "Putin", scorGresit);
	assert(ret != 0);
	assert(repo.len == 1);

	ret = adauga(&repo, "Vladimir", NULL, scor);
	assert(ret != 0);
	assert(repo.len == 1);

	int scor2[10] = { 2, 8, 3, 4, 3, 8, 2, 8, 8, 9 };
	ret = adauga(&repo, "Dani", "Mocanu", scor2);
	assert(ret == 0);
	assert(repo.len == 2);
	assert(strcmp(get(&repo, repo.len - 1).nume, "Dani") == 0);
	assert(strcmp(get(&repo, repo.len - 1).prenume, "Mocanu") == 0);
	assert(get(&repo, repo.len - 1).scor[5] == 8);

	destroy(&repo);
}

void test_cauta()
{
	repository repo = createEmpty();

	int scor[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int ret = adauga(&repo, "Mihai", "Panduru", scor);
	participant* cautat = cauta(&repo, "Mihai", "Panduru");
	assert(ret == 0);
	assert(cauta(&repo, "Mihai", "Panduru") != NULL);
	assert(cauta(&repo, "Vladimir", "Putin") == NULL);
	assert(cauta(&repo, "Vladimir", NULL) == NULL);

	destroy(&repo);
}

void test_actualizeaza()
{
	repository repo = createEmpty();

	int scor[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	adauga(&repo, "Mihai", "Panduru", scor);
	participant* cautat = cauta(&repo, "Mihai", "Panduru");
	assert(cautat != NULL);

	int scorGresit[10] = { 1, 2, 3, 0, 5, 6, 7, 8, 9, 10 };
	int ret = actualizeaza(cautat, "Vladimir", "Putin", scorGresit);
	assert(ret != 0);
	assert(strcmp(cautat->nume, "Mihai") == 0);
	assert(strcmp(cautat->prenume, "Panduru") == 0);

	ret = actualizeaza(NULL, "Vladimir", "Putin", scor);
	assert(ret != 0);

	int scorNou[10] = { 5, 2, 5, 4, 5, 6, 7, 8, 9, 10 };
	ret = actualizeaza(cautat, "Alberto", "Zimbran", scorNou);
	assert(repo.len == 1);
	assert(ret == 0);
	assert(strcmp(cautat->nume, "Alberto") == 0);
	assert(strcmp(cautat->prenume, "Zimbran") == 0);
	assert(cautat->scor[2] == 5);

	destroy(&repo);
}

void test_sterge()
{
	repository repo = createEmpty();

	int scor[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	adauga(&repo, "Mihai", "Panduru", scor);

	int scor2[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	adauga(&repo, "Vladimir", "Putin", scor2);

	int scor3[10] = { 2, 8, 3, 4, 3, 8, 2, 8, 8, 9 };
	adauga(&repo, "Dani", "Mocanu", scor3);
	assert(repo.len == 3);

	void* nesters = sterge(&repo, NULL);
	assert(nesters == NULL);

	participant* cautat = cauta(&repo, "Vladimir", "Putin");

	void* ret = sterge(&repo, cautat);
	assert(ret != NULL);
	assert(repo.len == 2);
	assert(cauta(&repo, "Vladimir", "Putin") == NULL);

	destroy(&repo);
}

void test_filter()
{
	repository repo = createEmpty();

	int scor[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	adauga(&repo, "Mihai", "Panduru", scor);

	int scor2[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	adauga(&repo, "Vladimir", "Putin", scor2);

	int scor3[10] = { 2, 8, 3, 4, 3, 8, 2, 8, 8, 9 };
	adauga(&repo, "Dani", "Mocanu", scor3);

	repository filteredRepo = filter(&repo, 1, 2);
	assert(size(&filteredRepo) == 1);
	assert(getScore(*filteredRepo.concurent) == 1);
	destroy(&filteredRepo);

	filteredRepo = filter(&repo, 2, 'v');
	assert(size(&filteredRepo) == 0);
	destroy(&filteredRepo);

	filteredRepo = filter(&repo, 2, 'V');
	assert(size(&filteredRepo) == 1);
	destroy(&filteredRepo);

	destroy(&repo);
}

void test_sort()
{
	repository repo = createEmpty();

	int scor[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	adauga(&repo, "Mihai", "Panduru", scor);

	int scor2[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	adauga(&repo, "Vladimir", "Putin", scor2);

	int scor3[10] = { 2, 8, 3, 4, 3, 8, 2, 8, 8, 9 };
	adauga(&repo, "Dani", "Mocanu", scor3);

	repository sortedRepo = sortBy(&repo, 1, 1);
	assert(size(&sortedRepo) == 3);
	assert(strcmp(sortedRepo.concurent[0].nume, "Dani") == 0);
	destroy(&sortedRepo);

	sortedRepo = sortBy(&repo, 1, 2);
	assert(size(&sortedRepo) == 3);
	assert(strcmp(sortedRepo.concurent[0].nume, "Vladimir") == 0);
	destroy(&sortedRepo);

	sortedRepo = sortBy(&repo, 2, 1);
	assert(size(&sortedRepo) == 3);
	assert(strcmp(sortedRepo.concurent[0].nume, "Vladimir") == 0);
	destroy(&sortedRepo);

	sortedRepo = sortBy(&repo, 2, 2);
	assert(size(&sortedRepo) == 3);
	assert(strcmp(sortedRepo.concurent[0].nume, "Dani") == 0);
	destroy(&sortedRepo);

	destroy(&repo);
}

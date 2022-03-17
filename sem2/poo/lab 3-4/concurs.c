#include <string.h>
#include <stdlib.h>
#include "concurs.h"

/*
	desc: creeaza un repo pentru participanti
	return vals: repo-ul creat
*/
repository createEmpty()
{
	repository repo;
	repo.len = 0;
	repo.capacity = 1;
	repo.concurent = (participant*)malloc(sizeof(participant) * repo.capacity);
	return repo;
}

/*
	desc: distruge un repo si detaliile acestuia
*/
void destroy(repository* repo)
{
	for (int i = 0; i < repo->len; ++i)
		destroyParticipant(&repo->concurent[i]);
	free(repo->concurent);
	repo->concurent = NULL;
	repo->len = 0;
}

participant get(repository* repo, int poz)
{
	return repo->concurent[poz];
}

participant set(repository* repo, int poz, participant nou)
{
	participant vechi = repo->concurent[poz];
	repo->concurent[poz] = nou;

	return vechi;
}

int size(repository* repo)
{
	return repo->len;
}

/*
	desc: ne asiguram ca vectorul dinamic este intotdeauna pregatit pentru un nou participant
*/
void ensureCapacity(repository* repo)
{
	if (repo->len < repo->capacity)
		return;

	int newCapacity = repo->capacity * 2;
	participant* nou = (participant*)malloc(sizeof(participant) * newCapacity);
	for (int i = 0; i < repo->len; ++i)
		nou[i] = repo->concurent[i];
	free(repo->concurent);
	repo->concurent = nou;
	repo->capacity = newCapacity;
}

/*
	desc: adauga un nou participant in concurs
	param: repo pentru gestiunea participantilor, newUser pentru noul participant
	return vals: adresa noului participant adaugat
*/
participant* adaugaRepo(repository* repo, participant newUser)
{
	ensureCapacity(repo);
	set(repo, repo->len++, newUser);

	return &repo->concurent[repo->len - 1];
}

/*
	desc: face o copie a listei de participanti
	param: lista de participanti de copiat
	return vals: lista de participanti copiata
*/
repository copyList(repository* repo)
{
	repository newCopy = createEmpty();
	for (int i = 0; i < size(repo); ++i)
	{
		participant user = get(repo, i);
		adaugaRepo(&newCopy, copyParticipant(&user));
	}
	return newCopy;
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
		if (!strcmp(repo->concurent[i].nume, nume) && !strcmp(repo->concurent[i].prenume, prenume))
			return &repo->concurent[i];

	return NULL;
}

/*
	desc: elimina un concurent
	param: repo pentru gestiunea participantilor, poz pentru pozitia concurentului in lista
*/
void stergeRepo(repository* repo, int poz)
{
	for (int i = poz; i < repo->len - 1; ++i)
		set(repo, i, repo->concurent[i + 1]);

	memset(&repo->concurent[repo->len - 1], 0, sizeof(repo->concurent[repo->len - 1]));
	--repo->len;
}

/*
	desc: sorteaza o lista de participanti dupa un anumit criteriu
	param: lista de participanti de sortat si functia (criteriul)
*/
void sort(repository* repo, function cmp)
{
	for (int i = 0; i < size(repo) - 1; ++i)
		for (int j = i + 1; j < size(repo); ++j)
		{
			participant p1 = get(repo, i);
			participant p2 = get(repo, j);
			if (cmp(&p1, &p2) > 0)
			{
				set(repo, i, p2);
				set(repo, j, p1);
			}
		}
}

#pragma once

#include "participant.h"

typedef struct
{
	participant* concurent;
	int len;
	int capacity;
} repository; // un nou tip de data pentru gestiunea participantilor sub forma de vector dinamic

participant* adaugaRepo(repository* repo, participant user); // adauga un nou participant in concurs
participant* cautaRepo(repository* repo, char* nume, char* prenume); // verifica daca un participant este inscris in concurs
void stergeRepo(repository* repo, int poz); // elimina un concurent

repository createEmpty();
void destroy(repository* repo);
participant get(repository* repo, int poz);
participant set(repository* repo, int poz, participant nou);
int size(repository* repo);
repository copyList(repository* repo);

typedef int (*function)(participant* p1, participant* p2);
void sort(repository* repo, function cmp);

#pragma once

#define MAX_PARTICIPANTI	20 // numarul maxim de participanti

typedef struct
{
	char nume[23 + 1];
	char prenume[23 + 1];
	int scor[10];
} participant; // un nou tip de data ce defineste un participant
// un participant este unic prin nume si prenume

typedef struct
{
	participant user[MAX_PARTICIPANTI];
	int len;
} repository; // un nou tip de data pentru gestiunea participantilor sub forma de lista

void adauga(repository* repo, participant user); // adauga un nou participant in concurs
void reset(repository* repo); // reseteaza lista de concurenti
int cauta(repository* repo, participant existingUser); // verifica daca un participant este inscris in concurs
void actualizeaza(repository* repo, participant modifiedUser, int poz); // actualizeaza detaliile pentru un concurent
void sterge(repository* repo, int poz); // elimina un concurent

void test_adauga();
void test_reset();
void test_cauta();
void test_actualizeaza();
void test_sterge();

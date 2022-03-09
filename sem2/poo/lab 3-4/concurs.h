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

participant* adaugaRepo(repository* repo, participant user); // adauga un nou participant in concurs
void reset(repository* repo); // reseteaza lista de concurenti
participant* cautaRepo(repository* repo, char* nume, char* prenume); // verifica daca un participant este inscris in concurs
participant* actualizeazaRepo(participant* modifiedUser, char* nume, char* prenume, int* scor); // actualizeaza detaliile pentru un concurent
void stergeRepo(repository* repo, int poz); // elimina un concurent

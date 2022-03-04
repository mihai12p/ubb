#pragma once

#define MAX_PARTICIPANTI	20

typedef struct
{
	char nume[23 + 1];
	char prenume[23 + 1];
	int scor[10];
} participant;

typedef struct
{
	participant user[MAX_PARTICIPANTI];
	int len;
} repository;

void adauga(repository* repo, participant user);
void reset(repository* repo);
int cauta(repository* repo, participant existingUser);
void actualizeaza(repository* repo, participant newUser, int poz);
void sterge(repository* repo, int poz);

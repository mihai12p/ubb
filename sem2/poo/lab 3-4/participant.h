#pragma once

typedef struct
{
	char* nume;
	char* prenume;
	int* scor;
} participant; // un nou tip de data ce defineste un participant
// un participant este unic prin nume si prenume

participant createParticipant(char* nume, char* prenume, int* scor);
void destroyParticipant(participant* user);
participant copyParticipant(participant* toBeCopied);
int getScore(participant concurent);

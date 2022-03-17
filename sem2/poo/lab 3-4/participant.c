#include <string.h>
#include <stdlib.h>
#include "participant.h"

/*
	desc: creeaza un participant
	param: nume, prenume si scor
	return vals: noul participant creat
*/
participant createParticipant(char* nume, char* prenume, int* scor)
{
	participant newParticipant;
	newParticipant.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy_s(newParticipant.nume, strlen(nume) + 1, nume);
	newParticipant.prenume = (char*)malloc(sizeof(char) * (strlen(prenume) + 1));
	strcpy_s(newParticipant.prenume, strlen(prenume) + 1, prenume);
	newParticipant.scor = (int*)malloc(sizeof(int) * 10);
	for (int i = 0; i < 10; ++i)
		newParticipant.scor[i] = scor[i];
	return newParticipant;
}

/*
	desc: distruge detaliile unui participant
	param: participantul de eliminat
*/
void destroyParticipant(participant* user)
{
	free(user->nume);
	user->nume = NULL;

	free(user->prenume);
	user->prenume = NULL;

	free(user->scor);
	user->scor = NULL;
}

/*
	desc: copiaza un participant
	param: participantul de copiat
*/
participant copyParticipant(participant* toBeCopied)
{
	return createParticipant(toBeCopied->nume, toBeCopied->prenume, toBeCopied->scor);
}

/*
	desc: calculeaza media celor 10 note
	param: participantul pentru care se doreste calcularea mediei
	return vals: partea intreaga a mediei rotunjite
*/
int getScore(participant concurent)
{
	int sum = 0;
	for (int i = 0; i < 10; ++i)
		sum += concurent.scor[i];
	return (int)((sum / 10.0) + 0.5);
}

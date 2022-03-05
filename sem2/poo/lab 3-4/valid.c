#include "valid.h"

/*
	desc: validam scorul
	param: pointer scor catre scorul ce trebuie validat
	return vals: returneaza 0 daca toate notele la cele 10 probe sunt numere cuprinse intre 1-10
							-1 altfel
*/
int valid(int* scor)
{
	for (int i = 0; i < 10; ++i)
		if (scor[i] < 1 || scor[i] > 10)
			return -1;

	return 0;
}

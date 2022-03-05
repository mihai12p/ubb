#include <assert.h>
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

void test_valid()
{
	int scor[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	assert(valid(scor) == 0);

	int scor2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // 9 note in loc de 10
	assert(valid(scor2) == -1);

	int scor3[] = { 10, 1, 2, 3, 11, 5, 6, 7, 8, 9 }; // nota 11
	assert(valid(scor3) == -1);

	int scor4[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // nota 0
	assert(valid(scor4) == -1);
}

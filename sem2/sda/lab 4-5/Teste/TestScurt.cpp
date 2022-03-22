#include "TestScurt.h"
#include <assert.h>
#include "../Matrice.h"
#include <iostream>

using namespace std;

void testAll() { //apelam fiecare functie sa vedem daca exista
	Matrice m(4,4);
	assert(m.nrLinii() == 4);
	assert(m.nrColoane() == 4);
	//adaug niste elemente
	m.modifica(1,1,5);
	assert(m.element(1,1) == 5);
	m.modifica(1,1,6);
	assert(m.element(1,2) == NULL_TELEMENT);
}

void test_suma()
{
	Matrice m(4, 4);
	for (int i = 0; i < m.nrLinii(); ++i)
		for (int j = 0; j < m.nrColoane(); ++j)
			m.modifica(i, j, i + j);

	assert(m.suma(3) == 18); // 3 + 4 + 5 + 6
	assert(m.suma(2) == 14);
	assert(m.suma(1) == 10);
	assert(m.suma(0) == 6); // 0 + 1 + 2 + 3

	Matrice z(3, 3);
	assert(z.suma(2) == 0);
	try
	{
		z.suma(3);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
}

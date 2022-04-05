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

void testSumaDiagonalaPrincipala()
{
	Matrice z(3, 3);
	assert(z.sumaDiagonalaPrincipala() == 0);

	Matrice m(4, 4);
	for (int i = 0; i < m.nrLinii(); ++i)
		for (int j = 0; j < m.nrColoane(); ++j)
			m.modifica(i, j, i);

	assert(m.sumaDiagonalaPrincipala() == 6); // 0 + 1 + 2 + 3 = 6
}

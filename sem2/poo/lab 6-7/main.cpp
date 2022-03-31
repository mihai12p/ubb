#include <iostream>
#include "Teste.hpp"
#include "Consola.hpp"

//#define OPEN_CPP_COVERAGE

void teste()
{
	testAdauga();
	testSterge();
	testModifica();
	testCauta();
}

int main()
{
	teste();

#ifndef OPEN_CPP_COVERAGE
	Filme repo;
	Valid validator;
	Service srv{ repo, validator };
	Consola consola{ srv };
	consola.adaugaCateva();
	consola.start();
#endif

	return 0;
}
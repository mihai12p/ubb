#include "Teste.hpp"
#include "Consola.hpp"

//#define OPEN_CPP_COVERAGE
#define CHECK_MEMORY_LEAKS
#ifdef CHECK_MEMORY_LEAKS
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif

void teste()
{
	testAdauga();
	testSterge();
	testModifica();
	testCauta();
}

void init()
{
	Filme repo;
	Valid validator;
	Service srv{ repo, validator };
	Consola consola{ srv };
	consola.adaugaCateva();
	consola.start();
}

int main()
{
	teste();
#ifndef OPEN_CPP_COVERAGE
	init();
#endif

#ifdef CHECK_MEMORY_LEAKS
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
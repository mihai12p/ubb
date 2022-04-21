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
	testFiltrare();
	testSortare();
	testAdaugaCos();
	testGolesteCos();
	testRaport();
	testSaveToFile();
	testUndo();
}

void adaugaCateva(Service& srv)
{
	srv.adaugaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");
	srv.adaugaFilm("Miami Bici", "Amuzzament", 2020, "Codin Maticiuc");
	srv.adaugaFilm("Moartea", "Documentar", 2022, "Ion Iliescu");
	srv.adaugaFilm("Soacra mea e o scorpie", "Romance", 2005, "Jane Fonda");
}

void init()
{
	Filme repo;
	Valid validator;
	Service srv{ repo, validator };
	adaugaCateva(srv);

	Consola consola{ srv };
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
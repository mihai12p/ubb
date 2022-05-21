#include "teste.h"
#include "service.h"
#include <assert.h>
#include <fstream>

void testAdauga()
{
	repo r;
	service srv{ r };
	assert(srv.getAll().size() == 10); // lista populata din fisier de constructor

	srv.adauga(1, "Metin2", 2, "PC", 16);
	assert(srv.getAll().size() == 11);

	srv.adauga(2, "League of Legends", 2, "PC", 12);
	assert(srv.getAll().size() == 12);
}

void testSortare()
{
	repo r;
	service srv{ r };
	assert(srv.getAll().size() == 10); // lista populata din fisier de constructor

	const auto& listaSortata = srv.sortare();
	auto it = listaSortata.begin();
	for (auto it2 = it + 1; it2 != listaSortata.end(); ++it2)
	{
		assert(it->getPret() <= it2->getPret());
		it = it2;
	}
}

void testFiltrare()
{
	repo r;
	service srv{ r };
	assert(srv.getAll().size() == 10); // lista populata din fisier de constructor

	const auto& listaSortata = srv.filtrare();
	for (const auto& game : listaSortata)
		assert(game.getPegi() < 12);
}

void testAll()
{
	testAdauga();
	testSortare();
	testFiltrare();
}

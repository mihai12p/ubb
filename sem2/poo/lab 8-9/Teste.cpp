#include <fstream>
#include <cassert>
#include <sstream>
#include <algorithm>
#include "Service.hpp"
#include "Valid.hpp"

void testAdauga()
{
	Filme repo;
	Valid validator;
	Service srv{ repo, validator };

	srv.adaugaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");
	assert(srv.getAll().size() == 1);

	srv.adaugaFilm("Miami Bici", "Amuzzament", 2020, "Codin Maticiuc");
	assert(srv.getAll().size() == 2);

	try
	{
		srv.adaugaFilm("Miami Bici", "Amuzzament", 2020, "Codin Maticiuc");
		assert(false);
	}
	catch (const FilmeException& ex)
	{
		assert(true);

		std::stringstream out;
		out << ex;
		assert(out.str() == "Exista deja un astfel de film.");
	}

	try
	{
		srv.adaugaFilm("", "", NULL, "");
		assert(false);
	}
	catch (const ValidateException& ex)
	{
		assert(true);

		std::stringstream out;
		out << ex;
		assert(out.str() == "Titlu inexistent. Gen inexistent. An inexistent. Actor inexistent. ");
	}

	try
	{
		srv.adaugaFilm("Elodia", "Crime", NULL, "Cristian Cioaca");
		assert(false);
	}
	catch (const ValidateException& ex)
	{
		assert(true);

		std::stringstream out;
		out << ex;
		assert(out.str() == "An inexistent. ");
	}
}

void testSterge()
{
	Filme repo;
	Valid validator;
	Service srv{ repo, validator };

	srv.adaugaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");
	srv.adaugaFilm("Miami Bici", "Amuzzament", 2020, "Codin Maticiuc");

	srv.stergeFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");
	assert(srv.getAll().size() == 1);

	try
	{
		srv.stergeFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");
		assert(false);
	}
	catch (const FilmeException& ex)
	{
		assert(true);

		std::stringstream out;
		out << ex;
		assert(out.str() == "Nu exista un astfel de film.");
	}

	try
	{
		srv.stergeFilm("Elodia", "Crime", 2007, "Cristian Cioaca");
		assert(false);
	}
	catch (const FilmeException& ex)
	{
		assert(true);

		std::stringstream out;
		out << ex;
		assert(out.str() == "Nu exista un astfel de film.");
	}

	try
	{
		srv.stergeFilm("", "", NULL, "");
		assert(false);
	}
	catch (const ValidateException& ex)
	{
		assert(true);

		std::stringstream out;
		out << ex;
		assert(out.str() == "Titlu inexistent. Gen inexistent. An inexistent. Actor inexistent. ");
	}
}

void testModifica()
{
	Filme repo;
	Valid validator;
	Service srv{ repo, validator };

	srv.adaugaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");
	srv.adaugaFilm("Miami Bici", "Amuzzament", 2020, "Codin Maticiuc");

	size_t poz = srv.modificaFilm("Tom si Jerry", "Soacra mea e o scorpie", "Romance", 2005, "Jane Fonda");
	assert(repo.getAll().at(poz).getTitlu() == "Soacra mea e o scorpie");
	assert(repo.getAll().at(poz).getGen() == "Romance");
	assert(repo.getAll().at(poz).getAn() == 2005);
	assert(repo.getAll().at(poz).getActor() == "Jane Fonda");

	try
	{
		srv.modificaFilm("Tom si Jerry", "Moartea", "Documentar", 2022, "Ion Iliescu");
		assert(false);
	}
	catch (const FilmeException& ex)
	{
		assert(true);

		std::stringstream out;
		out << ex;
		assert(out.str() == "Nu exista un astfel de film.");
	}

	try
	{
		srv.modificaFilm("Miami Bici", "Miami Bici", "Amuzzament", 2020, "Codin Maticiuc");
		assert(false);
	}
	catch (const FilmeException& ex)
	{
		assert(true);

		std::stringstream out;
		out << ex;
		assert(out.str() == "Exista deja un astfel de film.");
	}

	try
	{
		srv.modificaFilm("Tom si Jerry", "Moartea", "Documentar", NULL, "Ion Iliescu");
		assert(false);
	}
	catch (const ValidateException& ex)
	{
		assert(true);

		std::stringstream out;
		out << ex;
		assert(out.str() == "An inexistent. ");
	}
}

void testCauta()
{
	Filme repo;
	Valid validator;
	Service srv{ repo, validator };

	srv.adaugaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");
	srv.adaugaFilm("Miami Bici", "Amuzzament", 2020, "Codin Maticiuc");

	std::unique_ptr<Film> filmCautat = srv.cautaFilm("Tom si Jerry");
	const Film* filmPointer = filmCautat.get();
	assert(filmPointer != nullptr);
	assert(filmPointer && filmPointer->getActor() == "Jerry");

	try
	{
		srv.cautaFilm("Moartea");
		assert(false);
	}
	catch (const FilmeException& ex)
	{
		assert(true);

		std::stringstream out;
		out << ex;
		assert(out.str() == "Nu exista un astfel de film.");
	}

	try
	{
		srv.cautaFilm("");
		assert(false);
	}
	catch (const ValidateException& ex)
	{
		assert(true);

		std::stringstream out;
		out << ex;
		assert(out.str() == "Titlu inexistent. ");
	}
}

void testFiltrare()
{
	Filme repo;
	Valid validator;
	Service srv{ repo, validator };

	srv.adaugaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");
	srv.adaugaFilm("Miami Bici", "Amuzzament", 2020, "Codin Maticiuc");

	std::vector<Film> filmeFiltrate = srv.filtrare("Tom si Jerry", 2020);
	assert(filmeFiltrate.size() == 2);

	filmeFiltrate = srv.filtrare("Tom si Jerry", 2022);
	assert(filmeFiltrate.size() == 1);
}

void testSortare()
{
	Filme repo;
	Valid validator;
	Service srv{ repo, validator };

	srv.adaugaFilm("Miami Bici", "Amuzament", 2020, "Codin Maticiuc");
	srv.adaugaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");

	std::vector<Film> filmeSortate = srv.sortare(1);
	assert(filmeSortate.at(0).getTitlu() == "Miami Bici");

	filmeSortate = srv.sortare(2);
	assert(filmeSortate.at(0).getGen() == "Amuzament");

	filmeSortate = srv.sortare(3);
	assert(filmeSortate.at(0).getAn() == 1940);
}

void testAdaugaCos()
{
	Filme repo;
	Valid validator;
	Service srv{ repo, validator };
	assert(srv.getAll().size() == 0);

	srv.adaugaFilm("Miami Bici", "Amuzament", 2020, "Codin Maticiuc");
	srv.adaugaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");
	assert(srv.getAll().size() == 2);

	srv.inchiriazaFilm("Miami Bici");
	assert(srv.getAll().size() == 2);
	assert(srv.getCos() == 1);
}

void testGolesteCos()
{
	Filme repo;
	Valid validator;
	Service srv{ repo, validator };
	assert(srv.getAll().size() == 0);

	srv.adaugaFilm("Miami Bici", "Amuzament", 2020, "Codin Maticiuc");
	srv.adaugaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");
	assert(srv.getAll().size() == 2);

	srv.inchiriazaFilm("Miami Bici");
	
	srv.golesteCos();
	assert(srv.getAll().size() == 2);
	assert(srv.getCos() == 0);
}

void testRaport()
{
	Filme repo;
	Valid validator;
	Service srv{ repo, validator };
	assert(srv.getAll().size() == 0);

	srv.adaugaFilm("Miami Bici", "Amuzament", 2020, "Codin Maticiuc");
	srv.adaugaFilm("Elodia", "Crime", 2020, "Cristian Cioaca");
	srv.adaugaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");
	assert(srv.getAll().size() == 3);

	srv.inchiriazaFilm("Miami Bici");
	srv.inchiriazaFilm("Miami Bici");
	srv.inchiriazaFilm("Elodia");
	srv.inchiriazaFilm("Tom si Jerry");
	assert(srv.raport().at(1940) == 1);
	assert(srv.raport().at(2020) == 3);

	srv.golesteCos();
	assert(srv.raport().at(1940) == 0);
	assert(srv.raport().at(2020) == 0);
}

void testSaveToFile()
{
	Filme repo;
	Valid validator;
	Service srv{ repo, validator };

	srv.adaugaFilm("Miami Bici", "Amuzament", 2020, "Codin Maticiuc");
	srv.adaugaFilm("Elodia", "Crime", 2020, "Cristian Cioaca");
	srv.adaugaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");
	assert(srv.getAll().size() == 3);

	srv.inchiriazaFilm("Miami Bici");
	srv.saveToFile("test.cvs");

	std::ifstream createdFile("test.cvs");
	assert(createdFile.good() == true);
	assert(createdFile.is_open() == true);
	createdFile.close();
	assert(createdFile.is_open() == false);
	assert(remove("test.cvs") == 0);
}

void testUndo()
{
	Filme repo;
	Valid validator;
	Service srv{ repo, validator };

	srv.adaugaFilm("Elodia", "Crime", 2020, "Cristian Cioaca");
	srv.adaugaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");
	assert(srv.getAll().size() == 2);

	srv.undoLast();
	assert(srv.getAll().size() == 1);

	srv.stergeFilm("Elodia", "Crime", 2020, "Cristian Cioaca");
	assert(srv.getAll().size() == 0);

	srv.undoLast();
	assert(srv.getAll().size() == 1);

	srv.modificaFilm("Elodia", "Alexandra Macesanu", "Crime", 2019, "Gheorghe Dinca");
	assert(srv.getAll().at(0).getActor() == "Gheorghe Dinca");

	srv.undoLast();
	assert(srv.getAll().at(0).getActor() == "Cristian Cioaca");

	srv.undoLast();
	try
	{
		srv.undoLast();
		assert(false);
	}
	catch (const FilmeException& ex)
	{
		assert(true);

		std::stringstream out;
		out << ex;
		assert(out.str() == "Nu mai exista operatii.");
	}
}

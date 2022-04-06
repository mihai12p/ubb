#include <cassert>
#include <sstream>
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

	size_t poz = srv.modificaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry", "Soacra mea e o scorpie", "Romance", 2005, "Jane Fonda");
	assert(repo.getAll().at(poz).getTitlu() == "Soacra mea e o scorpie");
	assert(repo.getAll().at(poz).getGen() == "Romance");
	assert(repo.getAll().at(poz).getAn() == 2005);
	assert(repo.getAll().at(poz).getActor() == "Jane Fonda");

	try
	{
		srv.modificaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry", "Moartea", "Documentar", 2022, "Ion Iliescu");
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
		srv.modificaFilm("Miami Bici", "Amuzzament", 2020, "Codin Maticiuc", "Miami Bici", "Amuzzament", 2020, "Codin Maticiuc");
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
		srv.modificaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry", "Moartea", "Documentar", NULL, "Ion Iliescu");
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

	const Film& filmCautat = srv.cautaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");
	assert(filmCautat.getActor() == "Jerry");

	try
	{
		srv.cautaFilm("Moartea", "Documentar", 2022, "Ion Iliescu");
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
		srv.cautaFilm("Moartea", "Documentar", NULL, "Ion Iliescu");
		assert(false);
	}
	catch (const ValidateException& ex)
	{
		assert(true);

		std::stringstream out;
		out << ex;
		assert(out.str() == "An inexistent. ");
	}

	try
	{
		srv.cautaFilm("", "", NULL, "");
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

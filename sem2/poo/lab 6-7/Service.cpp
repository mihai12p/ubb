#include "Service.hpp"

void Service::adaugaFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor)
{
	Film film{ titlu, gen, an, actor };
	valid.validate(film);
	repo.adauga(film);
}

void Service::stergeFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor)
{
	Film film{ titlu, gen, an, actor };
	valid.validate(film);
	repo.sterge(film);
}

const size_t Service::modificaFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor, const std::string& titluNou, const std::string& genNou, const int anNou, const std::string& actorNou)
{
	Film filmDeModificat{ titlu, gen, an, actor };
	valid.validate(filmDeModificat);

	Film filmDupaModificare{ titluNou, genNou, anNou, actorNou };
	valid.validate(filmDupaModificare);
	return repo.modifica(filmDeModificat, filmDupaModificare);
}

const Film& Service::cautaFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor) const
{
	Film filmCautat{ titlu, gen, an, actor };
	valid.validate(filmCautat);
	return repo.cauta(titlu, gen, an, actor);
}

const MyDynaVec<Film> Service::filtrare(const std::string& titlu, const int an)
{
	MyDynaVec<Film> listaNoua = this->getAll();

	for (int i = this->getAll().size() - 1; i >= 0; --i)
		if (listaNoua.at(i).getTitlu() != titlu && listaNoua.at(i).getAn() != an)
			listaNoua.erase(i);

	return listaNoua;
}

int dupaTitlu(Film f1, Film f2) { return strcmp(f1.getTitlu().c_str(), f2.getTitlu().c_str()); }
int dupaAnGen(Film f1, Film f2) { return f1.getAn() == f2.getAn() ? strcmp(f1.getGen().c_str(), f2.getGen().c_str()) : f1.getAn() > f2.getAn(); }
int dupaActor(Film f1, Film f2) { return strcmp(f1.getActor().c_str(), f2.getActor().c_str()); }

typedef int(*functie)(Film f1, Film f2);
functie myFuncs[] = { dupaTitlu, dupaActor, dupaAnGen };

const MyDynaVec<Film> Service::sortare(int criteriu)
{
	MyDynaVec<Film> listaNoua = this->getAll();

	bool listaSortata = false;
	while (!listaSortata)
	{
		listaSortata = true;
		for (int i = 0; i < listaNoua.size() - 1; ++i)
		{
			if (myFuncs[criteriu - 1](listaNoua.at(i), listaNoua.at(i + 1)) > 0)
			{
				listaSortata = false;
				std::swap(listaNoua.at(i), listaNoua.at(i + 1));
			}
		}
	}

	return listaNoua;
}

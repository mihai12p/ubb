#include <algorithm>
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

const std::unique_ptr<Film> Service::cautaFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor) const
{
	Film filmCautat{ titlu, gen, an, actor };
	valid.validate(filmCautat);

	return repo.cauta(titlu, gen, an, actor);
}

const std::vector<Film> Service::filtrare(const std::string& titlu, const int an)
{
	std::vector<Film> listaNoua;
	std::copy_if(this->getAll().begin(), this->getAll().end(), std::back_inserter(listaNoua), [&](const Film& film) { return film.getTitlu() == titlu || film.getAn() == an; });
	
	return listaNoua;
}

const bool dupaTitlu(const Film& f1, const Film& f2) { return f1.getTitlu().compare(f2.getTitlu()) < 0; }
const bool dupaActor(const Film& f1, const Film& f2) { return f1.getActor().compare(f2.getActor()) < 0; }
const bool dupaGenAn(const Film& f1, const Film& f2) { return f1.getAn() == f2.getAn() ? f1.getGen().compare(f2.getGen()) < 0 : f1.getAn() < f2.getAn(); }
const std::vector<Film> Service::sortare(int criteriu)
{
	const std::vector<functie>& myVec = { dupaTitlu, dupaActor, dupaGenAn };

	std::vector<Film> listaNoua = this->getAll();
	std::sort(listaNoua.begin(), listaNoua.end(), myVec.at(criteriu - 1));

	return listaNoua;
}

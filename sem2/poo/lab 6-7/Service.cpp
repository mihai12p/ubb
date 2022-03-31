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

#pragma once

#include "Repo.hpp"
#include "Valid.hpp"

class Service
{
	Filme& repo;
	Valid& valid;

	typedef const bool(*functie)(const Film& f1, const Film& f2);

	public:
		Service(Filme& repo, Valid& valid) noexcept : repo{ repo }, valid{ valid } { }
		Service(const Service& other) = delete;

		const std::vector<Film>& getAll() const noexcept { return repo.getAll(); }

		void adaugaFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor);
		void stergeFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor);
		const size_t modificaFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor, const std::string& titluNou, const std::string& genNou, const int anNou, const std::string& actorNou);
		const std::unique_ptr<Film> cautaFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor) const;
		const std::vector<Film> filtrare(const std::string& titlu, const int an);
		const std::vector<Film> sortare(int criteriu);
};

#pragma once

#include "Repo.hpp"
#include "Valid.hpp"

class Service
{
	Filme& repo;
	Valid& valid;

	public:
		Service(Filme& repo, Valid& valid) noexcept : repo{ repo }, valid{ valid } { }
		Service(const Service& other) = delete;

		const std::vector<Film>& getAll() const noexcept { return repo.getAll(); }

		void adaugaFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor);
		void stergeFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor);
		const size_t modificaFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor, const std::string& titluNou, const std::string& genNou, const int anNou, const std::string& actorNou);
		const Film& cautaFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor) const;
};

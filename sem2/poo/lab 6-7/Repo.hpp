#pragma once

#include <vector>
#include <ostream>
#include "Film.hpp"

class Filme
{
	std::vector<Film> all;

	bool exist(const Film& film) const;

	public:
		Filme() = default;
		Filme(const Filme& other) = delete;

		const std::vector<Film>& getAll() const noexcept { return this->all; };

		void adauga(const Film& film);
		void sterge(const Film& film);
		size_t modifica(Film& filmDeModificat, Film& filmDupaModificare);
		const Film& cauta(const std::string& titlu, const std::string& gen, const int an, const std::string& actor) const;
};

class FilmeException
{
	std::string msg;

	public:
		FilmeException(const std::string& msg) : msg{ msg } { }

		friend std::ostream& operator<<(std::ostream& out, const FilmeException& ex);
};

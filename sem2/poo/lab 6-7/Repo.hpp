#pragma once

#include <ostream>
#include "MyDynaVec.hpp"
#include "Film.hpp"

class Filme
{
	MyDynaVec<Film> all;

	bool exist(const Film& film) const;

	public:
		Filme() noexcept = default;
		Filme(const Filme& other) = delete;

		const MyDynaVec<Film>& getAll() const noexcept { return this->all; };

		void adauga(const Film& film);
		void sterge(const Film& film);
		size_t modifica(const Film& filmDeModificat, const Film& filmDupaModificare);
		const Film& cauta(const std::string& titlu, const std::string& gen, const int an, const std::string& actor) const;
};

class FilmeException
{
	std::string msg;

	public:
		FilmeException(const std::string& msg) : msg{ msg } { }

		friend std::ostream& operator<<(std::ostream& out, const FilmeException& ex);
};

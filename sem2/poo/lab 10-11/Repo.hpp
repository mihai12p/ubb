#pragma once

#include <ostream>
#include <vector>
#include <algorithm>
#include "Film.hpp"

class Filme
{
	std::vector<Film> all;

	bool exist(const Film& film) const;

	public:
		Filme() noexcept { }

		Filme(const Filme& other) = delete;

		const std::vector<Film>& getAll() const noexcept { return this->all; };
		const int getCos() const noexcept;

		void adauga(const Film& film);
		void sterge(const Film& film);
		size_t modifica(const Film& filmDeModificat, Film& filmDupaModificare);
		const std::unique_ptr<Film> cauta(const std::string& titlu) const;

		void inchiriaza(Film& film, int val = 1) noexcept;
		void golesteCos() noexcept;
};

class FilmeException : public std::exception
{
	std::string msg;

	public:
		FilmeException(const std::string& msg) : std::exception(), msg{ msg } { }

		const std::string& getMsg() const noexcept { return msg; };

		friend std::ostream& operator<<(std::ostream& out, const FilmeException& ex);
};

#pragma once

#include <iostream>
#include <string>

class Film
{
	std::string titlu;
	std::string gen;
	int an = NULL;
	std::string actor;

	public:
		Film() noexcept { };
		~Film() { };

		Film(const std::string titlu, const std::string gen, const int an, const std::string actor) : titlu{ titlu }, gen{ gen }, an{ an }, actor{ actor } { }
		
		Film(const Film& other) = delete; // constructor de copiere
		Film& operator=(const Film& other); // assignment operator
		Film(const Film&& other) = delete; // move constructor
		Film& operator=(const Film&& other) = delete; // move assignment

		const std::string getTitlu() const { return this->titlu; }
		const std::string getGen() const { return this->gen; }
		const int getAn() const noexcept { return this->an; }
		const std::string getActor() const { return this->actor; }

		const bool operator==(const Film& film) const noexcept { return this->titlu == film.titlu && this->gen == film.gen && this->an == film.an && this->actor == film.actor; }
};

#pragma once

#include <string>

class Film
{
	std::string titlu;
	std::string gen;
	int an;
	std::string actor;

	public:
		Film(const std::string titlu, const std::string gen, const int an, const std::string actor) : titlu{ titlu }, gen{ gen }, an{ an }, actor{ actor } { }

		const std::string getTitlu() const { return this->titlu; }
		const std::string getGen() const { return this->gen; }
		const int getAn() const noexcept { return this->an; }
		const std::string getActor() const { return this->actor; }

		const bool operator==(const Film& film) { return this->titlu == film.titlu && this->gen == film.gen && this->an == film.an && this->actor == film.actor; }
};

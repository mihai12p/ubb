#pragma once

#include <string>

class Film
{
	std::string titlu = "";
	std::string gen = "";
	int an = NULL;
	std::string actor = "";
	int inchiriat = NULL;

	public:
		Film() noexcept { };
		~Film() { };

		Film(const std::string titlu, const std::string gen, const int an, const std::string actor, const int inchiriat = NULL) : titlu{ titlu }, gen{ gen }, an{ an }, actor{ actor }, inchiriat{ inchiriat } { }
		
		Film(const Film& other); // constructor de copiere
		Film& operator=(const Film& other); // assignment operator
		Film(Film&& other) noexcept; // move constructor
		Film& operator=(Film&& other) noexcept; // move assignment

		const std::string getTitlu() const { return this->titlu; }
		const std::string getGen() const { return this->gen; }
		const int getAn() const noexcept { return this->an; }
		const std::string getActor() const { return this->actor; }
		const int getInchiriat() const noexcept { return this->inchiriat; }

		void inchiriaza(const int val) noexcept { this->inchiriat += val; }

		const bool operator==(const Film& film) const noexcept { return this->titlu == film.titlu && this->gen == film.gen && this->an == film.an && this->actor == film.actor; }
};

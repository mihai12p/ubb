#include "Film.hpp"

Film::Film(const Film& other) : titlu{ other.titlu }, gen{ other.gen }, an{ other.an }, actor{ other.actor }, inchiriat{ other.inchiriat } { }

Film& Film::operator=(const Film& other)
{
	this->titlu = other.titlu;
	this->gen = other.gen;
	this->an = other.an;
	this->actor = other.actor;
	this->inchiriat = other.inchiriat;

	return *this;
}

Film::Film(Film&& other) noexcept : titlu{ other.titlu }, gen{ other.gen }, an{ other.an }, actor{ other.actor }, inchiriat{ other.inchiriat }
{
	other.titlu = "";
	other.gen = "";
	other.an = NULL;
	other.actor = "";
	other.inchiriat = NULL;
}

Film& Film::operator=(Film&& other) noexcept
{
	if (this == &other)
		return *this;

	this->titlu = other.titlu;
	this->gen = other.gen;
	this->an = other.an;
	this->actor = other.actor;
	this->inchiriat = other.inchiriat;

	other.titlu = "";
	other.gen = "";
	other.an = NULL;
	other.actor = "";
	other.inchiriat = NULL;

	return *this;
}

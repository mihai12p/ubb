#include "Film.hpp"

Film& Film::operator=(const Film& other)
{
	this->titlu = other.titlu;
	this->gen = other.gen;
	this->an = other.an;
	this->actor = other.actor;

	return *this;
}

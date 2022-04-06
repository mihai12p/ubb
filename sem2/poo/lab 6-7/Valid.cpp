#include "Valid.hpp"

/*
valideaza un film
param: referinta catre filmul de validat
arunca exceptie daca detaliile unui film sunt invalide
*/
void Valid::validate(const Film& film)
{
	MyDynaVec<std::string> msg;
	if (film.getTitlu().size() <= 0)
		msg.push_back("Titlu inexistent.");
	if (film.getGen().size() <= 0)
		msg.push_back("Gen inexistent.");
	if (film.getAn() == NULL)
		msg.push_back("An inexistent.");
	if (film.getActor().size() <= 0)
		msg.push_back("Actor inexistent.");

	if (msg.size() >= 1)
		throw ValidateException(msg);
}

std::ostream& operator<<(std::ostream& out, const ValidateException& ex) 
{
	for (const auto& msg : ex.msg)
		out << msg << ' ';

	return out;
}

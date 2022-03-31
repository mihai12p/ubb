#include "Valid.hpp"

void Valid::validate(const Film& film)
{
	std::vector<std::string> msg;
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

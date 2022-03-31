#include "Repo.hpp"

bool Filme::exist(const Film& film) const
{
	try
	{
		this->cauta(film.getTitlu(), film.getGen(), film.getAn(), film.getActor());
		return true;
	}
	catch (FilmeException&)
	{
		return false;
	}
}

void Filme::adauga(const Film& film)
{
	if (this->exist(film))
		throw FilmeException("Exista deja un astfel de film.");

	this->all.push_back(film);
}

void Filme::sterge(const Film& film)
{
	if (this->exist(film) == false)
		throw FilmeException("Nu exista un astfel de film.");

	this->all.erase(std::find(this->all.begin(), this->all.end(), film));
}

size_t Filme::modifica(Film& filmDeModificat, Film& filmDupaModificare)
{
	if (this->exist(filmDeModificat) == false)
		throw FilmeException("Nu exista un astfel de film.");

	if (this->exist(filmDupaModificare))
		throw FilmeException("Exista deja un astfel de film.");

	size_t poz = std::find(this->all.begin(), this->all.end(), filmDeModificat) - this->all.begin();
	this->all[poz] = filmDupaModificare;

	return poz;
}

const Film& Filme::cauta(const std::string& titlu, const std::string& gen, const int an, const std::string& actor) const
{
	for (const Film& film : this->all)
		if (film.getTitlu() == titlu && film.getGen() == gen && film.getAn() == an && film.getActor() == actor)
			return film;

	throw FilmeException("Nu exista un astfel de film.");
}

std::ostream& operator<<(std::ostream& out, const FilmeException& ex)
{
	out << ex.msg;
	return out;
}

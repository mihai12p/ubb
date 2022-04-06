#include "Repo.hpp"

/*
verifica daca exista un film in lista
param: referinta catre film
return: true sau false
*/
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

/*
adauga un nou film daca nu exista un astfel de film deja sau arunca exceptie daca filmul exista deja
param: referinta catre film
*/
void Filme::adauga(const Film& film)
{
	if (this->exist(film))
		throw FilmeException("Exista deja un astfel de film.");

	this->all.push_back(film);
}

/*
sterge un film deja existent sau arunca exceptie daca nu exista un astfel de film
param: referinta catre film
*/
void Filme::sterge(const Film& film)
{
	if (this->exist(film) == false)
		throw FilmeException("Nu exista un astfel de film.");

	int poz = -1;
	for (const Film& filmIt : this->getAll())
	{
		++poz;
		if (filmIt == film)
		{
			this->all.erase(poz);
			break;
		}
	}
}

/*
modifica un film
param: referinta catre filmul de modificat si filmul dupa modificare
return: pozitia filmului ce a fost modificat
*/
size_t Filme::modifica(const Film& filmDeModificat, const Film& filmDupaModificare)
{
	if (this->exist(filmDeModificat) == false)
		throw FilmeException("Nu exista un astfel de film.");

	if (this->exist(filmDupaModificare))
		throw FilmeException("Exista deja un astfel de film.");

	int poz = -1;
	for (const Film& filmIt : this->getAll())
	{
		++poz;
		if (filmIt == filmDeModificat)
		{
			this->all.at(poz) = filmDupaModificare;
			break;
		}
	}

	return poz;
}

/*
cauta un film
param: titlu, gen, an, actor pentru a cauta un film
return: referinta catre filmul cautat
*/
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

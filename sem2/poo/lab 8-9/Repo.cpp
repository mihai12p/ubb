#include <algorithm>
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

	auto it = std::find_if(this->getAll().begin(), this->getAll().end(), [&film](const Film& filmIt) noexcept { return filmIt == film; });
	if (it != this->getAll().end())
		this->all.erase(it);
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

	auto it = std::find_if(this->getAll().begin(), this->getAll().end(), [&filmDeModificat](const Film& filmIt) noexcept { return filmIt == filmDeModificat; });
	if (it != this->getAll().end())
		this->all.at(it - this->getAll().begin()) = filmDupaModificare;

	return it - this->getAll().begin();
}

/*
cauta un film
param: titlu, gen, an, actor pentru a cauta un film
return: referinta catre filmul cautat
*/
const std::unique_ptr<Film> Filme::cauta(const std::string& titlu, const std::string& gen, const int an, const std::string& actor) const
{
	auto it = std::find_if(this->all.begin(), this->all.end(), [&](const Film& film) { return (film.getTitlu() == titlu && film.getGen() == gen && film.getAn() == an && film.getActor() == actor); });
	if (&it == nullptr || it == this->all.end())
		throw FilmeException("Nu exista un astfel de film.");

	return std::make_unique<Film>(*it);
}

std::ostream& operator<<(std::ostream& out, const FilmeException& ex)
{
	out << ex.msg;
	return out;
}

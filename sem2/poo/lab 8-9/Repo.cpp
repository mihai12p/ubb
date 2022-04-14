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
		this->cauta(film.getTitlu());
		return true;
	}
	catch (FilmeException&)
	{
		return false;
	}
}

const int Filme::getCos() const noexcept
{
	int i = 0; 
	std::for_each(this->getAll().begin(), this->getAll().end(), [&](const Film& film) noexcept { i += film.getInchiriat(); });
	return i;
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

	const auto& it = std::find_if(this->getAll().begin(), this->getAll().end(), [&film](const Film& filmIt) noexcept { return filmIt == film; });
	if (it != this->getAll().end())
		this->all.erase(it);
}

/*
modifica un film
param: referinta catre filmul de modificat si filmul dupa modificare
return: pozitia filmului ce a fost modificat
*/
size_t Filme::modifica(const Film& filmDeModificat, Film& filmDupaModificare)
{
	if (this->exist(filmDupaModificare))
		throw FilmeException("Exista deja un astfel de film.");

	filmDupaModificare.inchiriaza(filmDeModificat.getInchiriat());

	const auto& it = std::find_if(this->getAll().begin(), this->getAll().end(), [&filmDeModificat](const Film& filmIt) noexcept { return filmIt == filmDeModificat; });
	if (it != this->getAll().end())
		this->all.at(it - this->getAll().begin()) = filmDupaModificare;

	return it - this->getAll().begin();
}

/*
cauta un film
param: titlu, gen, an, actor pentru a cauta un film
return: referinta catre filmul cautat
*/
const std::unique_ptr<Film> Filme::cauta(const std::string& titlu) const
{
	const auto& it = std::find_if(this->getAll().begin(), this->getAll().end(), [&](const Film& film) { return (film.getTitlu() == titlu); });
	if (&it == nullptr || it == this->getAll().end())
		throw FilmeException("Nu exista un astfel de film.");

	return std::make_unique<Film>(*it);
}

void Filme::inchiriaza(Film& film, int val) noexcept
{
	const auto& it = std::find_if(this->getAll().begin(), this->getAll().end(), [&](const Film& filmIt) noexcept { return filmIt == film; });
	
	if (val == 0)
		val = -film.getInchiriat();

	this->all.at(it - this->getAll().begin()).inchiriaza(val);
}

void Filme::golesteCos() noexcept
{
	std::for_each(this->all.begin(), this->all.end(), [&](Film& film) noexcept { if (this) inchiriaza(film, 0); });
}

std::ostream& operator<<(std::ostream& out, const FilmeException& ex)
{
	out << ex.msg;
	return out;
}

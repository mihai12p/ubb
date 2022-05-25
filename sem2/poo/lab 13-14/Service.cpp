#include <array>
#include <random>
#include <algorithm>
#include <fstream>
#include "Service.hpp"

void Service::adaugaFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor)
{
	Film film{ titlu, gen, an, actor };
	valid.validate(film);
	repo.adauga(film);
	undo.push_back(std::make_unique<UndoAdauga>(UndoAdauga{ repo, film }));
}

void Service::stergeFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor)
{
	Film film{ titlu, gen, an, actor };
	valid.validate(film);
	repo.sterge(film);
	undo.push_back(std::make_unique<UndoSterge>(UndoSterge{ repo, film }));

	notifica();
}

const size_t Service::modificaFilm(const std::string& titlu, const std::string& titluNou, const std::string& genNou, const int anNou, const std::string& actorNou)
{
	Film filmDupaModificare{ titluNou, genNou, anNou, actorNou };
	valid.validate(filmDupaModificare);
	std::unique_ptr<Film> filmDeModificat = repo.cauta(titlu);
	const size_t ret = repo.modifica(*filmDeModificat, filmDupaModificare);
	undo.push_back(std::make_unique<UndoModifica>(UndoModifica{ repo, filmDupaModificare, *filmDeModificat }));

	notifica();

	return ret;
}

const std::unique_ptr<Film> Service::cautaFilm(const std::string& titlu) const
{
	valid.validate(Film{ titlu, "Gen", 2022, "Actor" });
	return repo.cauta(titlu);
}

const std::vector<Film> Service::filtrare(const std::string& titlu, const int an)
{
	std::vector<Film> listaNoua;
	std::copy_if(this->getAll().begin(), this->getAll().end(), std::back_inserter(listaNoua), [&](const Film& film) { return film.getTitlu() == titlu || film.getAn() == an; });
	
	return listaNoua;
}

const bool dupaTitlu(const Film& f1, const Film& f2) { return f1.getTitlu().compare(f2.getTitlu()) < 0; }
const bool dupaActor(const Film& f1, const Film& f2) { return f1.getActor().compare(f2.getActor()) < 0; }
const bool dupaGenAn(const Film& f1, const Film& f2) { return f1.getAn() == f2.getAn() ? f1.getGen().compare(f2.getGen()) < 0 : f1.getAn() < f2.getAn(); }
const std::vector<Film> Service::sortare(int criteriu)
{
	std::array<functie, 3> criterii = { dupaTitlu, dupaActor, dupaGenAn };
	std::vector<Film> listaNoua = this->getAll();
	std::sort(listaNoua.begin(), listaNoua.end(), criterii.at(criteriu - 1));

	return listaNoua;
}

void Service::inchiriazaFilm(const std::string& titlu)
{
	const std::unique_ptr<Film> filmCautat = cautaFilm(titlu);
	Film* film = filmCautat.get();
	if (film)
		repo.inchiriaza(*film);

	notifica();
}

void Service::golesteCos() noexcept
{
	repo.golesteCos();

	notifica();
}

void Service::genereaza(int cate)
{
	srand(time(NULL));

	std::mt19937 mt{ std::random_device{}() };
	const std::uniform_int_distribution<> dist(0, int(getAll().size()) - 1);

	int nr = (cate == 0) ? rand() % getAll().size() * 2 + 1 : cate;
	while (nr--)
	{
		const int rndNr = dist(mt);
		inchiriazaFilm(getAll().at(rndNr).getTitlu());
	}
}

const std::unordered_map<int, int> Service::raport() const noexcept
{
	std::unordered_map<int, int> map;
	std::for_each(this->getAll().begin(), this->getAll().end(), [&](const Film& film) 
	{ 
		if (map.find(film.getAn()) == map.end()) 
			map.insert({ film.getAn(), film.getInchiriat() }); 
		else 
			map.at(film.getAn()) += film.getInchiriat(); 
	});
	return map;
}

void Service::saveToFile(const std::string& fileName)
{
	std::ofstream fout(fileName);
	std::for_each(this->getAll().begin(), this->getAll().end(), [&](const Film& film)
	{
		if (film.getInchiriat())
			fout << film.getTitlu() << ';' << film.getGen() << ';' << film.getAn() << ';' << film.getActor() << '\n';
	});
	fout.close();
}

void Service::undoLast()
{
	if (this->undo.empty())
		throw FilmeException("Nu mai exista operatii.");

	const std::unique_ptr<ActiuneUndo> last(std::move(this->undo.back()));
	ActiuneUndo* result = last.get();
	if (result)
		result->doUndo();
	this->undo.pop_back();

	notifica();
}

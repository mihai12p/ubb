#include "service.h"
#include <fstream>
#include <algorithm>

/*
param: idx (int), titlu (string), pret (int), platforma (string), pegi (int)
Adauga un joc nou il lista
*/
void service::adauga(const int idx, const std::string& titlu, const int pret, const std::string& platf, const int pegi)
{
	joc nou{ idx, titlu, pret, platf, pegi };
	r.adauga(nou);
}

/*
return: o noua lista cu toate jocurile sortate crescator dupa pret
Sorteaza jocurile existente in lista crescator dupa pret
*/
std::vector<joc> service::sortare()
{
	std::vector<joc> listaNouaSortata = this->getAll();
	std::sort(listaNouaSortata.begin(), listaNouaSortata.end(), [](const joc& game1, const joc& game2) { return game1.getPret() < game2.getPret(); });
	return listaNouaSortata;
}

/*
return: o noua lista cu toate jocurile filtrate dupa conditia PEGI < 12
Filtreaza jocurile existente in lista alegandu-le doar pe cele cu varsta minima strict mai mica ca 12
*/
std::vector<joc> service::filtrare()
{
	std::vector<joc> listaNouaFiltrata;
	for_each(this->getAll().begin(), this->getAll().end(), [&](const joc& game) 
	{
		if (game.getPegi() < 12)
			listaNouaFiltrata.push_back(game); 
	});
	return listaNouaFiltrata;
}

/*
param: fileName (string) -> nume fisier
Incarca jocurile dintr-un fisier in lista repository
*** Fiecare data a jocului trebuie sa fie pe o linie separata
*/
void service::loadFromFile(const std::string& fileName)
{
	std::ifstream fin(fileName);
	std::string line;
	int i = 0;

	int idx;
	std::string titlu = "";
	int pret = -1;
	std::string platf = "";
	int pegi = -1;
	while (std::getline(fin, line))
	{
		++i;

		if (i == 1)
			idx = stoi(line);
		else if (i == 2)
			titlu = line;
		else if (i == 3)
			pret = stoi(line);
		else if (i == 4)
			platf = line;
		else if (i == 5)
		{
			pegi = stoi(line);
			i = 0;

			this->adauga(idx, titlu, pret, platf, pegi);
		}
	}
}

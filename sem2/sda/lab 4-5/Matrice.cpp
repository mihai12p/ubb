#include "Matrice.h"

#include <exception>

using namespace std;

Matrice::Matrice(int m, int n) // theta(1)
{
	if (m <= 0 || n <= 0)
		throw std::exception();

	this->linii = m;
	this->coloane = n;
}

Matrice::~Matrice() // theta(n)
{
	lsi* nod = this->prim;
	while (nod)
	{
		lsi* urmator = nod->urm;
		delete nod;
		nod = urmator;
	}
}

int Matrice::nrLinii() const // theta(1)
{
	return this->linii;
}

int Matrice::nrColoane() const // theta(1)
{
	return this->coloane;
}

TElem Matrice::element(int i, int j) const // O(n)
{
	if (i >= this->nrLinii() || j >= this->nrColoane() || i < 0 || j < 0)
		throw std::exception();

	lsi* nod = this->prim;
	while (nod)
	{
		if (nod->elem.first.first > i || (nod->elem.first.first == i && nod->elem.first.second > j))
			break;

		if (nod->elem.first == std::make_pair(i, j))
			return nod->elem.second;

		nod = nod->urm;
	}

	return NULL_TELEMENT;
}

TElem Matrice::modifica(int i, int j, TElem e) // O(n) + O(n) = O(n)
{
	if (i >= this->nrLinii() || j >= this->nrColoane() || i < 0 || j < 0)
		throw std::exception();

	lsi* nod = this->prim;
	while (nod)
	{
		if (nod->elem.first.first > i || (nod->elem.first.first == i && nod->elem.first.second > j))
			break;

		if (nod->elem.first == std::make_pair(i,j))
		{
			TElem vecheaVal = nod->elem.second;
			nod->elem.second = e;
			return vecheaVal;
		}
		nod = nod->urm;
	}

	lsi* nodNou = new lsi;
	nodNou->elem.first = std::make_pair(i, j);
	nodNou->elem.second = e;
	nodNou->urm = nullptr;

	if (this->prim == nullptr) // lista vida
		this->prim = nodNou;
	else
	{
		lsi* nod = this->prim;
		while (nod->urm && (nod->urm->elem.first.first < i || (nod->urm->elem.first.first == i && nod->urm->elem.first.second < j)))
			nod = nod->urm;

		if (nod->urm) // daca mai exista vreun nod dupa el deci nu e final trebuie sa il intercalez sau sa il adaug la inceput
		{
			if (nod->elem.first.first > i) // daca vreau sa adaug un nod ce are numarul liniilor mai mic decat al tuturor celorlalte
			{							   // trebuie sa il adaug la inceput de tot de lista
				nodNou->urm = nod;
				this->prim = nodNou;
			}
			else // altfel il intercalez intre nodul curent si cel urmator deci in loc de [nod nodUrm] voi avea [nod inter NodUrm]
			{
				lsi* inter = nod->urm;
				nod->urm = nodNou;
				nodNou->urm = inter;
			}
		}
		else // daca nodul este ultimul atunci inseamna ca pot adauga noul nod ca fiind ultimul
			nod->urm = nodNou;
	}

	return NULL_TELEMENT;
}

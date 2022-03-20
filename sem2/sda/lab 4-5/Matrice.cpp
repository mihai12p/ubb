#include "Matrice.h"

#include <exception>

using namespace std;

Matrice::Matrice(int m, int n) 
{
	if (m <= 0 || n <= 0)
		throw std::exception();

	this->linii = m;
	this->coloane = n;
}

Matrice::~Matrice()
{
	lsi* nod = this->prim;
	while (nod)
	{
		lsi* urmator = nod->urm;
		delete nod;
		nod = urmator;
	}
}

int Matrice::nrLinii() const
{
	return this->linii;
}

int Matrice::nrColoane() const
{
	return this->coloane;
}

TElem Matrice::element(int i, int j) const
{
	if (i >= this->nrLinii() || j >= this->nrColoane() || i < 0 || j < 0)
		throw std::exception();

	lsi* nod = this->prim;
	while (nod)
	{
		if (nod->elem.first == std::make_pair(i, j))
			return nod->elem.second;

		nod = nod->urm;
	}

	return NULL_TELEMENT;
}

TElem Matrice::modifica(int i, int j, TElem e) 
{
	if (i >= this->nrLinii() || j >= this->nrColoane() || i < 0 || j < 0)
		throw std::exception();

	lsi* nod = this->prim;
	while (nod)
	{
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
		while (nod->urm)
			nod = nod->urm;

		nod->urm = nodNou;
	}

	return NULL_TELEMENT;
}

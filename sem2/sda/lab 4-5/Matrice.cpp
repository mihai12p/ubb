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
		//if (nod->elem.first.first > i || (nod->elem.first.first == i && nod->elem.first.second > j))
		//	break;

		if (nod->elem.first == std::make_pair(i, j))
			return nod->elem.second;

		nod = nod->urm;
	}

	return NULL_TELEMENT;
}
#include <cstdio>
TElem Matrice::modifica(int i, int j, TElem e) 
{
	if (i >= this->nrLinii() || j >= this->nrColoane() || i < 0 || j < 0)
		throw std::exception();

	lsi* nod = this->prim;
	while (nod)
	{
		//if (nod->elem.first.first > i || (nod->elem.first.first == i && nod->elem.first.second > j))
		//	break;

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
		/*lsi* print = this->prim;
		while (print)
		{
			printf("%d %d %d\n", print->elem.first.first, print->elem.first.second, print->elem.second);
			print = print->urm;
		}printf("\n\n");*/

		lsi* nod = this->prim;
		while (nod->urm && nod->urm->elem.first.first < i)
			nod = nod->urm;

		if (nod->urm)
		{
			if (nod->elem.first.first > i)
			{
				nodNou->urm = nod;
				this->prim = nodNou;
			}
			else
			{
				lsi* inter = nod->urm;
				nod->urm = nodNou;
				nodNou->urm = inter;
			}
		}
		else
			nod->urm = nodNou;
	}

	return NULL_TELEMENT;
}

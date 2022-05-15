#include "Matrice.h"

#include <exception>
#include <functional>

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
	std::function<void(nod*)> distrugRecursiv = [&](nod* curent)
	{ 
		if (curent == nullptr)
			return;

		distrugRecursiv(curent->st);
		distrugRecursiv(curent->dr);
		delete curent;
	};
	distrugRecursiv(this->rad);
}

int Matrice::nrLinii() const // theta(1)
{
	return this->linii;
}

int Matrice::nrColoane() const // theta(1)
{
	return this->coloane;
}

TElem Matrice::element(int i, int j) const // O(h)
{
	if (i >= this->nrLinii() || j >= this->nrColoane() || i < 0 || j < 0)
		throw std::exception();

	nod* curent = this->rad;
	while (curent)
	{
		if (curent->elem.first == std::make_pair(i, j))
			return curent->elem.second;

		curent = (curent->elem.first.first > i || (curent->elem.first.first == i && curent->elem.first.second > j)) ? curent->st : curent->dr;
	}

	return NULL_TELEMENT;
}

void Matrice::adaugaNod(nod* nodDeLegat) // O(h)
{
	nod* curent = this->rad;
	while (curent)
	{
		if (curent->elem.first.first > nodDeLegat->elem.first.first || (curent->elem.first.first == nodDeLegat->elem.first.first && curent->elem.first.second > nodDeLegat->elem.first.second))
		{
			if (curent->st == nullptr)
			{
				curent->st = nodDeLegat;
				break;
			}
			else
				curent = curent->st;
		}
		else
		{
			if (curent->dr == nullptr)
			{
				curent->dr = nodDeLegat;
				break;
			}
			else
				curent = curent->dr;
		}
	}
}

TElem Matrice::modifica(int i, int j, TElem e) // O(h) + O(h) = O(h)
{
	if (i >= this->nrLinii() || j >= this->nrColoane() || i < 0 || j < 0)
		throw std::exception();

	nod* prev = nullptr;
	nod* curent = this->rad;
	while (curent)
	{
		if (curent->elem.first == std::make_pair(i, j))
		{
			TElem vecheaVal = curent->elem.second;
			if (e == NULL_TELEMENT)
			{
				nod* subarboreStangDeMutat = curent->st;
				nod* subarboreDreptDeMutat = curent->dr;
				if (prev == nullptr)
					this->rad = (subarboreStangDeMutat != nullptr) ? subarboreStangDeMutat : subarboreDreptDeMutat;
				else
				{
					if (prev->st == curent)
						prev->st = nullptr;
					else
						prev->dr = nullptr;
				}
				delete curent;

				if (subarboreStangDeMutat != nullptr && this->rad != subarboreStangDeMutat)
					this->adaugaNod(subarboreStangDeMutat);

				if (subarboreDreptDeMutat != nullptr && this->rad != subarboreDreptDeMutat)
					this->adaugaNod(subarboreDreptDeMutat);
			}
			else
				curent->elem.second = e;

			return vecheaVal;
		}

		prev = curent;
		curent = (curent->elem.first.first > i || (curent->elem.first.first == i && curent->elem.first.second > j)) ? curent->st : curent->dr;
	}

	if (e == NULL_TELEMENT)
		return NULL_TELEMENT;

	nod* nou = new nod;
	nou->elem.first = std::make_pair(i, j);
	nou->elem.second = e;
	nou->st = nou->dr = nullptr;

	if (this->rad == nullptr)
		this->rad = nou;
	else
		this->adaugaNod(nou);

	return NULL_TELEMENT;
}

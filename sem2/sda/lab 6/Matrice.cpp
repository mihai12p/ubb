#include "Matrice.h"

#include <exception>

using namespace std;

Matrice::Matrice(int m, int n) // theta(1)
{
	if (m <= 0 || n <= 0)
		throw std::exception();

	this->linii = m;
	this->coloane = n;

	this->len = 0;
	this->cap = 1;

	this->elem = new std::pair<std::pair<int, int>, TElem>[this->cap];
	this->elem[this->cap - 1] = std::make_pair(std::make_pair(0, 0), 0);

	this->urm = new int[this->cap];
	this->urm[this->cap - 1] = -1;

	this->prim = -1;
	this->primLiber = 0;
}

Matrice::~Matrice() // theta(n)
{
	if (this->elem)
		delete[] this->elem;

	if (this->urm)
		delete[] this->urm;
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

	int index = this->prim;
	while (index != -1)
	{
		if (this->elem[index].first.first > i || (this->elem[index].first.first == i && this->elem[index].first.second > j))
			break;

		if (this->elem[index].first == std::make_pair(i, j))
			return this->elem[index].second;

		index = this->urm[index];
	}

	return NULL_TELEMENT;
}
#include <iostream>
TElem Matrice::modifica(int i, int j, TElem e) // O(n) + O(n) = O(n)
{
	if (i >= this->nrLinii() || j >= this->nrColoane() || i < 0 || j < 0)
		throw std::exception();

	int index = this->prim;
	while (index != -1)
	{
		if (this->elem[index].first.first > i || (this->elem[index].first.first == i && this->elem[index].first.second > j))
			break;

		if (this->elem[index].first == std::make_pair(i, j))
		{
			TElem vecheaVal = this->elem[index].second;
			this->elem[index].second = e;
			return vecheaVal;
		}
		index = this->urm[index];
	}

	if (this->primLiber == -1) // nu exista spatiu liber in lista => redimensionare
	{
		this->cap *= 2;

		std::pair<std::pair<int, int>, TElem>* newVec = new std::pair<std::pair<int, int>, TElem>[this->cap];
		for (int i = 0; i < this->len; ++i)
			newVec[i] = this->elem[i];

		if (this->elem)
			delete[] this->elem;
		this->elem = newVec;


		int* newUrm = new int[this->cap];
		for (int i = 0; i < this->len; ++i)
			newUrm[i] = this->urm[i];

		if (this->urm)
			delete[] this->urm;
		this->urm = newUrm;

		for (int i = this->len; i < this->cap - 1; ++i)
			this->urm[i] = i + 1;
		this->urm[this->cap - 1] = -1;
		this->primLiber = this->len;
	}

	if (e != 0)
	{
		this->elem[this->primLiber] = std::make_pair(std::make_pair(i, j), e);
		++this->len;

		if (this->prim == -1) // lista vida
		{
			this->prim = this->primLiber; // prim devine noul nod adaugat deoarece adaugam la inceput
			this->urm[this->primLiber] = -1;
		}
		else
		{
			int curent = this->prim, prev = this->prim, next = this->urm[curent];
			while (next != -1 && (this->elem[next].first.first < i || (this->elem[next].first.first == i && this->elem[next].first.second < j)))
				prev = curent, curent = next, next = this->urm[next];

			/*if (next == -1) // e ultimul nod deci noul nod trebuie adaugat fix la sfarsit
			{
				if (this->elem[curent].first.first < i || (this->elem[curent].first.first == i && this->elem[curent].first.second < j))
				{
					this->urm[curent] = this->primLiber;
					this->urm[this->primLiber] = -1;
				}
				else
				{
					this->urm[prev] = this->primLiber;
					this->urm[this->primLiber] = curent;
					this->urm[curent] = -1;
					if (this->prim == prev)
						this->prim = this->primLiber;
				}
			}
			else // intercalam in fata sau in spate
			*/{
				if (this->elem[curent].first.first < i || (this->elem[curent].first.first == i && this->elem[curent].first.second < j))
				{
					int ret = this->urm[curent];
					this->urm[curent] = this->primLiber;
					this->urm[this->primLiber] = ret;
				}
				else
				{
					this->urm[this->primLiber] = curent;
					this->prim = this->primLiber;
				}
			}
		}

		int x;
		for (x = this->cap - 1; x >= 0 && this->elem[x].second != 0; --x);
		this->primLiber = x;
	}
	else
		this->elem[this->primLiber] = std::make_pair(std::make_pair(0, 0), 0);

	///
	/*std::cout << "Index\t";
	for (int q = 0; q < this->cap; ++q)
		std::cout << q << '\t';
	std::cout << "\nElem\t";
	for (int q = 0; q < this->cap; ++q)
		std::cout << this->elem[q].first.first << ',' << this->elem[q].first.second << ',' << this->elem[q].second << '\t';
	std::cout << "\nUrm\t";
	for (int q = 0; q < this->cap; ++q)
		std::cout << this->urm[q] << '\t';
	std::cout << "\nPrim\t" << this->prim << "\nPrimLiber\t" << this->primLiber;
	std::cout << "\n\n";*/
	///

	return NULL_TELEMENT;
}

#include "Iterator.h"
#include "DO.h"
#include <iostream>

using namespace std;

void DO::actualizarePrimLiber() // O(cap)
{
	int liber = 0;
	while (this->elem[liber] != std::make_pair(-INT_MAX, -INT_MAX))
		if (++liber == this->capacity)
		{
			std::cout << "TABELA E PLINA!\n";
			break;
		}

	this->primLiber = liber;
}

DO::DO(Relatie r) // theta(cap)
{
	this->len = 0;
	this->capacity = MAX;
	for (int i = 0; i < this->capacity; ++i)
	{
		this->elem[i] = { -INT_MAX, -INT_MAX };
		this->prev[i] = -1;
		this->urm[i] = -1;
	}
	this->primLiber = 0;
	this->indexUltim = -1;
	this->rel = r;
	this->indexMin = 0, this->indexMax = this->capacity - 1;
	this->keyMin = INT_MAX, this->keyMax = INT_MIN;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) // O(cap)
{
	int index = this->d(c);
	while (index != -1)
	{
		if (!this->rel(this->elem[index].first, c))
			break;

		if (this->elem[index].first == c)
		{
			TValoare vecheaVal = this->elem[index].second;
			this->elem[index].second = v;
			return vecheaVal;
		}

		index = this->urm[index];
	}

	index = this->d(c);
	if (this->elem[index] == std::make_pair(-INT_MAX, -INT_MAX))
	{
		++this->len;
		this->elem[index] = { c, v };

		if (this->keyMin > c)
		{
			this->keyMin = c;
			this->indexMin = index;
		}

		if (this->keyMax < c)
		{
			this->keyMax = c;
			this->indexMax = index;
		}

		this->indexUltim = std::max(this->indexUltim, index);
		if (this->primLiber == index)
			this->actualizarePrimLiber();

		return NULL_TVALOARE;
	}

	if (this->primLiber >= this->capacity)
		throw std::exception();

	while (this->prev[index] != -1)
		index = this->prev[index];

	while (this->urm[index] != -1 && this->rel(this->elem[this->urm[index]].first, c))
		index = this->urm[index];

	++this->len;
	this->elem[this->primLiber] = { c, v };
	if (this->rel(this->elem[index].first, c)) // adaugaDupa
	{
		this->prev[this->primLiber] = index;
		if (this->urm[index] != -1)
			this->prev[this->urm[index]] = this->primLiber;
		this->urm[this->primLiber] = this->urm[index];
		this->urm[index] = this->primLiber;
	}
	else // adaugaInainte
	{
		this->urm[this->primLiber] = index;
		if (this->prev[index] != -1)
			this->urm[this->prev[index]] = this->primLiber;
		this->prev[this->primLiber] = this->prev[index];
		this->prev[index] = this->primLiber;
	}

	if (this->keyMin > c)
	{
		this->keyMin = c;
		this->indexMin = this->primLiber;
	}

	if (this->keyMax < c)
	{
		this->keyMax = c;
		this->indexMax = this->primLiber;
	}

	this->indexUltim = std::max(this->indexUltim, this->primLiber);
	this->actualizarePrimLiber();

	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const // O(n)
{
	int index = this->d(c);
	while (this->prev[index] != -1)
		index = this->prev[index];

	while (index != -1)
	{
		if (!this->rel(this->elem[index].first, c))
			break;

		if (this->elem[index].first == c)
			return this->elem[index].second;

		index = this->urm[index];
	}

	return NULL_TVALOARE;	
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) // O(n)
{
	int index = this->d(c);
	while (this->prev[index] != -1)
		index = this->prev[index];

	while (index != -1)
	{
		if (!this->rel(this->elem[index].first, c))
			break;

		if (this->elem[index].first == c)
		{
			const TValoare valStearsa = this->elem[index].second;
			if (this->primLiber > index)
				this->primLiber = index;
			--this->len;
			this->elem[index] = { -INT_MAX, -INT_MAX };
			if (this->prev[index] != -1)
				this->urm[this->prev[index]] = this->urm[index];
			if (this->urm[index] != -1)
				this->prev[this->urm[index]] = this->prev[index];

			if (this->indexUltim == index)
				while (this->elem[this->indexUltim] == std::make_pair(-INT_MAX, -INT_MAX))
					if (--this->indexUltim == -1)
						break;

			if (this->keyMin == c)
			{
				TCheie min = INT_MAX;
				for (int i = 0; i <= this->indexUltim; ++i)
					if (this->elem[i] != std::make_pair(-INT_MAX, -INT_MAX) && min > this->elem[i].first)
					{
						this->keyMin = min = this->elem[i].first;
						this->indexMin = i;
					}
			}

			if (this->keyMax == c)
			{
				TCheie max = INT_MIN;
				for (int i = 0; i <= this->indexUltim; ++i)
					if (this->elem[i] != std::make_pair(-INT_MAX, -INT_MAX) && max < this->elem[i].first)
					{
						this->keyMin = max = this->elem[i].first;
						this->indexMax = i;
					}
			}

			return valStearsa;
		}

		index = this->urm[index];
	}

	return NULL_TVALOARE;
}

/*
Complexitati:
	- caz favorabil: cheia si valoarea cautate se alfa in dictionar deci se inlocuieste valoarea => se executa O(n) pasi
	- caz defavorabil: cheia si valoarea cautate nu se alfa in dictionar => se executa O(n) pasi
	- caz total: deoarece CF = CD (mereu vor trebui parcurse toate cele n elemente), CT = O(n), unde n este numarul de elemente
																								dispersate la d(cheie)
Pseudocod:
	Subalgoritm inlocuieste()
		{pre: k : TCheie, valoareVeche : TValoare, valoareNoua : TValoare}
		{post: se inlocuieste valoareVeche cu valoareNoua in dictionar}

		index <- [this].d(k)
		cat timp [this].prev[index] != -1 executa
			index <- [this].prev[index]
		sfarsit_cat_timp

		cat timp index != -1 executa
			daca (![this].rel([this].elem[index].first, k)) atunci
				@break
			sfarsit_daca

			daca ([this].elem[index] = @pereche(k, valoareVeche)) atunci
				[this].elem[index].second <- valoareNoua
			sfarsit_daca

			index <- [this].urm[index]
		sfarsit_cat_timp
	Sfarsit_subalg
*/
void DO::inlocuieste(TCheie k, TValoare valoareVeche, TValoare valoareNoua)
{
	int index = this->d(k);
	while (this->prev[index] != -1)
		index = this->prev[index];

	while (index != -1)
	{
		if (!this->rel(this->elem[index].first, k))
			break;

		if (this->elem[index] == std::make_pair(k, valoareVeche))
			this->elem[index].second = valoareNoua;

		index = this->urm[index];
	}
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const // theta(1)
{
	return this->len;
}

//verifica daca dictionarul e vid
bool DO::vid() const // theta(1)
{
	return this->len == 0;
}

Iterator DO::iterator() const // theta(1)
{
	return Iterator(*this);
}

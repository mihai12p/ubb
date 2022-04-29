#include "Iterator.h"
#include "DO.h"
#include <iostream>

using namespace std;

void DO::actualizarePrimLiber()
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

DO::DO(Relatie r) 
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
	this->rel = r;
	this->indexMin = 0;
	this->keyMin = INT_MAX;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) 
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
		if (this->primLiber == index)
			this->actualizarePrimLiber();

		if (this->keyMin > c)
		{
			this->keyMin = c;
			this->indexMin = index;
		}

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

	this->actualizarePrimLiber();

	if (this->keyMin > c)
	{
		this->keyMin = c;
		this->indexMin = index;
	}

	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const 
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
TValoare DO::sterge(TCheie c) 
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
			TValoare valStearsa = this->elem[index].second;
			if (this->primLiber > index)
				this->primLiber = index;
			--this->len;
			this->elem[index] = { -INT_MAX, -INT_MAX };
			if (this->prev[index] != -1)
				this->urm[this->prev[index]] = this->urm[index];
			if (this->urm[index] != -1)
				this->prev[this->urm[index]] = this->prev[index];

			if (this->keyMin == c)
			{
				TCheie min = INT_MAX;
				for (int i = 0; i < this->capacity; ++i)
					if (this->elem[i] != std::make_pair(-INT_MAX, -INT_MAX) && min > this->elem[i].first)
					{
						this->keyMin = min = this->elem[i].first;
						this->indexMin = i;
					}
			}

			return valStearsa;
		}

		index = this->urm[index];
	}

	return NULL_TVALOARE;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const 
{
	return this->len;
}

//verifica daca dictionarul e vid
bool DO::vid() const 
{
	return this->len == 0;
}

Iterator DO::iterator() const 
{
	return Iterator(*this);
}

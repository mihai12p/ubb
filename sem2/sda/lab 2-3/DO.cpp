#include "Iterator.h"
#include "DO.h"
#include <iostream>

using namespace std;

DO::DO(Relatie r) 
{
	this->len = 0;
	this->capacity = 1;
	this->MyDynaVec = new TElem[this->capacity];
	this->rel = r;
}

DO::~DO() 
{
	if (this->MyDynaVec)
		delete[] this->MyDynaVec;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) 
{
	for (int i = 0; i < this->len; ++i)
		if (this->MyDynaVec[i].first == c)
		{
			TValoare vecheaVal = this->MyDynaVec[i].second;
			this->MyDynaVec[i].second = v;
			return vecheaVal;
		}

	if (this->len == this->capacity)
	{
		this->capacity *= 2;

		TElem* newDynaVec = new TElem[this->capacity];
		std::copy(this->MyDynaVec, this->MyDynaVec + this->len, newDynaVec);
		if (this->MyDynaVec)
			delete[] this->MyDynaVec;
		this->MyDynaVec = newDynaVec;
	}

	this->MyDynaVec[this->len++] = TElem(c, v);

	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const 
{
	for (int i = 0; i < this->len; ++i)
		if (this->MyDynaVec[i].first == c)
			return this->MyDynaVec[i].second;

	return NULL_TVALOARE;	
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) 
{
	for (int i = 0; i < this->len; ++i)
		if (this->MyDynaVec[i].first == c)
		{
			TValoare valStearsa = this->MyDynaVec[i].second;

			std::copy(this->MyDynaVec + i + 1, this->MyDynaVec + this->len, this->MyDynaVec + i);
			--this->len;

			return valStearsa;
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

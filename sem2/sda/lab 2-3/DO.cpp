#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
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
	int i = 0;
	while (i < this->len && this->rel(c, this->MyDynaVec[i].first))
	{
		if (this->MyDynaVec[i].first == c)
		{
			TValoare vecheaVal = this->MyDynaVec[i].second;
			this->MyDynaVec[i].second = v;
			return vecheaVal;
		}
		++i;
	}

	if (this->len == this->capacity)
	{
		this->capacity *= 2;

		TElem* copyVec = new TElem[this->capacity];
		std::copy(this->MyDynaVec, this->MyDynaVec + this->len, copyVec);
		if (this->MyDynaVec)
			delete[] this->MyDynaVec;
		this->MyDynaVec = copyVec;
	}

	this->MyDynaVec[this->len] = TElem(c, v);
	this->len++;

	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const 
{
	/* de adaugat */
	return NULL_TVALOARE;	
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) 
{
	/* de adaugat */
	return NULL_TVALOARE;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const 
{
	/* de adaugat */
	return 0;
}

//verifica daca dictionarul e vid
bool DO::vid() const 
{
	/* de adaugat */
	return true;
}

Iterator DO::iterator() const 
{
	return Iterator(*this);
}

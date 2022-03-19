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
	for (int i = 0; i < this->len && this->rel(c, this->MyDynaVec[i].first); ++i)
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
		for (int i = 0; i < this->len; ++i)
			newDynaVec[i] = this->MyDynaVec[i];

		if (this->MyDynaVec)
			delete[] this->MyDynaVec;

		this->MyDynaVec = newDynaVec;
	}

	int i;
	for (i = 0; i < this->len; ++i)
		if (!this->rel(c, this->MyDynaVec[i].first)) // i = pozitia primului element care nu mai e in relatie cu cel pe care vreau sa il adaug
			break;									 // deci trebuie sa ii fac loc intre i - 1 si i

	for (int j = this->len - 1; j >= i; --j)
		this->MyDynaVec[j + 1] = this->MyDynaVec[j]; // trag toate elementele incepand cu pozitia i cu o pozitie mai in fata
	++this->len;

	this->MyDynaVec[i] = TElem(c, v); // inserez pe pozitia i noul element si va fi in relatie cu toate cele [0..i-1] elemente

	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const 
{
	for (int i = 0; i < this->len && this->rel(c, this->MyDynaVec[i].first); ++i)
		if (this->MyDynaVec[i].first == c)
			return this->MyDynaVec[i].second;

	return NULL_TVALOARE;	
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) 
{
	for (int i = 0; i < this->len && this->rel(c, this->MyDynaVec[i].first); ++i)
		if (this->MyDynaVec[i].first == c)
		{
			TValoare valStearsa = this->MyDynaVec[i].second;

			for (int j = i; j < this->len - 1; ++j)
				this->MyDynaVec[j] = this->MyDynaVec[j + 1];
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

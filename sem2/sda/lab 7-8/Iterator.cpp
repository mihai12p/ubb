#include "Iterator.h"
#include "DO.h"

#include <exception>
using namespace std;

Iterator::Iterator(const DO& d) : dict(d) // theta(1)
{
	this->pozCurenta = 0;
}

void Iterator::prim() // theta(1)
{
	this->pozCurenta = dict.indexMin;
}

void Iterator::ultim() // theta(1)
{
	this->pozCurenta = dict.indexMax;
}

/*
Complexitati:
	- caz favorabil: lista contine 1 element => se executa theta(1) pasi
	- caz defavorabil: lista contine n elemente => se executa theta(n) pasi
	- caz total: deoarece CF = CD (mereu vor trebui parcurse toate cele n elemente), CT = theta(n)
Pseudocod:
	Subalgoritm anterior()
		{pre: pozCurenta sa fie pozitie valida}
		{post: pozCurenta: noua pozitie anterioara celeilalte}

		daca ![this].valid() atunci
			@arunca exceptie
		sfarsit_daca

		actualElem <- [this].element()
		max <- INT_MIN
		pentru i <- 0, dict.indexUltim executa
			daca dict.elem[i] este liber || dict.elem[i] = actualElem atunci
				continua
			sfarsit_daca

			daca max < dict.elem[i].first && !dict.rel(actualElem.first, dict.elem[i].first) atunci
				max <- dict.elem[i].first
				[this].pozCurenta <- i
			sfarsit_daca
		sfarsit_pentru

		daca max = INT_MIN atunci
			[this].pozCurenta <- dict.indexUltim + 1
		sfarsit_daca
	Sfarsit_subalg
*/
void Iterator::anterior()
{
	if (!this->valid())
		throw std::exception();

	const TElem& actualElem = this->element();
	TCheie max = INT_MIN;
	for (int i = 0; i <= dict.indexUltim; ++i)
	{
		if (dict.elem[i] == std::make_pair(-INT_MAX, -INT_MAX) || dict.elem[i] == actualElem)
			continue;

		if (max < dict.elem[i].first && !dict.rel(actualElem.first, dict.elem[i].first))
		{
			max = dict.elem[i].first;
			this->pozCurenta = i;
		}
	}

	if (max == INT_MIN)
		this->pozCurenta = dict.indexUltim + 1;
}

void Iterator::urmator() // theta(n)
{
	if (!this->valid())
		throw std::exception();

	const TElem& actualElem = this->element();
	TCheie min = INT_MAX;
	for (int i = 0; i <= dict.indexUltim; ++i)
	{
		if (dict.elem[i] == std::make_pair(-INT_MAX, -INT_MAX) || dict.elem[i] == actualElem)
			continue;

		if (min > dict.elem[i].first && dict.rel(actualElem.first, dict.elem[i].first))
		{
			min = dict.elem[i].first;
			this->pozCurenta = i;
		}
	}

	if (min == INT_MAX)
		this->pozCurenta = dict.indexUltim + 1;
}

bool Iterator::valid() const // theta(1)
{
	return this->pozCurenta <= dict.indexUltim;
}

TElem Iterator::element() const // theta(1)
{
	if (this->valid())
		return dict.elem[this->pozCurenta];
	else
		throw std::exception();
}

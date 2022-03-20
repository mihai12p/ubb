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
	this->pozCurenta = 0;
}

void Iterator::urmator() // theta(1) amortizata
{
	if (!this->valid())
		return;

	TCheie actualKey = this->element().first;
	while (true)
	{
		++this->pozCurenta;
		if (!this->valid())
			break;

		TCheie nextKey = dict.MyDynaVec[this->pozCurenta].first;
		if (dict.rel(actualKey, nextKey))
			break;
	}
}

bool Iterator::valid() const // theta(1)
{
	return this->pozCurenta < dict.dim();
}

TElem Iterator::element() const // theta(1)
{
	if (this->valid())
		return dict.MyDynaVec[this->pozCurenta];
	else
		throw std::exception();
}

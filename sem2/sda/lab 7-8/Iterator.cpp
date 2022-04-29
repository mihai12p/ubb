#include "Iterator.h"
#include "DO.h"

#include <exception>
using namespace std;

Iterator::Iterator(const DO& d) : dict(d)
{
	this->pozCurenta = 0;
}

void Iterator::prim()
{
	this->pozCurenta = dict.indexMin;
}

void Iterator::urmator()
{
	if (!this->valid())
		return;

	TElem actualElem = this->element();
	TCheie min = INT_MAX;
	for (int i = 0; i < dict.capacity; ++i)
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
		this->pozCurenta = dict.dim();
}

bool Iterator::valid() const
{
	return this->pozCurenta < dict.dim();
}

TElem Iterator::element() const
{
	if (this->valid())
		return dict.elem[this->pozCurenta];
	else
		throw std::exception();
}

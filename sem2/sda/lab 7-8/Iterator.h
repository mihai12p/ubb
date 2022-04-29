#pragma once

#include "DO.h"

class Iterator
{
	friend class DO;

	private:
		//constructorul primeste o referinta catre Container
		//iteratorul va referi primul element din container
		Iterator(const DO& dictionar);

		//contine o referinta catre containerul pe care il itereaza
		const DO& dict;

		int pozCurenta;

	public:
		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		//reseteaza pozitia iteratorului la sfarsitul containerului
		void ultim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void anterior();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element() const;
};

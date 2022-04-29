#pragma once

#define MAX 6002

typedef int TCheie;
typedef int TValoare;

#define NULL_TVALOARE -1

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Iterator;

typedef bool(*Relatie)(TCheie, TCheie);

class DO 
{
	friend class Iterator;

	private:
		int len;
		int capacity;
		TElem elem[MAX];
		int urm[MAX];
		int prev[MAX];
		int primLiber;
		int indexUltim;
		Relatie rel;

		int indexMin, indexMax;
		TCheie keyMin, keyMax;

		void actualizarePrimLiber();
		const int hashCode(TCheie e) const { return abs(e); }
		//functia de dispersie
		const int d(TCheie e) const { return hashCode(e) % capacity; }

	public:
		DO(Relatie r);

		// adauga o pereche (cheie, valoare) in dictionar
		//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
		// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
		TValoare adauga(TCheie c, TValoare v);

		//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
		TValoare cauta(TCheie c) const;

		//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
		TValoare sterge(TCheie c);

		//returneaza numarul de perechi (cheie, valoare) din dictionar
		int dim() const;

		//verifica daca dictionarul e vid
		bool vid() const;

		// se returneaza iterator pe dictionar
		// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
		Iterator iterator() const;
};

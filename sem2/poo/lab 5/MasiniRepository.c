#include "MasiniRepository.h"
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>

int comparareMasiniDupaModel(Masina* masina1, Masina* masina2, int crescator) { return (crescator) ? (strcmp(masina1->model, masina2->model) > 0 ? 1 : 0) : (strcmp(masina2->model, masina1->model) > 0 ? 1 : 0); }
int comparareMasiniDupaCategorie(Masina* masina1, Masina* masina2, int crescator) { return (crescator) ? (strcmp(masina1->categorie, masina2->categorie) > 0 ? 1 : 0) : (strcmp(masina2->categorie, masina1->categorie) > 0 ? 1 : 0); }

ElemType set(lista_masini* masinaRepository, int poz, ElemType masina)
{
	ElemType rez = masinaRepository->listaMasini[poz];
	masinaRepository->listaMasini[poz] = masina;
	return rez;
}

ElemType get(lista_masini* masinaRepository, int poz)
{
	return masinaRepository->listaMasini[poz];
}

lista_masini* creeazaMasinaRepository(DestroyFct func)
{
	/*
	 * creaza un repo gol format din (capacitate/dimensiune/lista_masini)
	 */
	lista_masini* masinaRepository = (lista_masini*)malloc(sizeof(lista_masini));
	masinaRepository->capacitate = 1;
	masinaRepository->dimensiune = 0;
	masinaRepository->listaMasini = malloc(sizeof(ElemType)*masinaRepository->capacitate);
	masinaRepository->dfunc = func;
	return masinaRepository;
}

void redimensionareRepository(lista_masini* masinaRepository)
{
	/*
	 * Daca capacitatea va fi egala cu dimensiunea se va apela aceasta functie si se va realoca o lista de 2 ori mai mare
	 */
	masinaRepository->capacitate *= 2;
	ElemType* listaNouaMasini = malloc(sizeof(ElemType)*masinaRepository->capacitate);
	for (int i = 0; i < masinaRepository->dimensiune; i++)
		listaNouaMasini[i] = masinaRepository->listaMasini[i];

	free(masinaRepository->listaMasini);
	masinaRepository->listaMasini = listaNouaMasini;
}

int adaugaMasinaRepository(lista_masini* masinaRepository, ElemType masina)
{
	/*
	 * adauga o masina in repo daca nu exista o masina cu numar de inmatriculare dat
	 */

	//Daca se ajunge aici inseamna ca masina poate fi adaugata
	if (masinaRepository->dimensiune == masinaRepository->capacitate)
		redimensionareRepository(masinaRepository);

	set(masinaRepository, masinaRepository->dimensiune, masina);
	++masinaRepository->dimensiune;
	
	return 1;
}

int modificareMasina(lista_masini* masinaRepository, ElemType masinaDeModificat)
{
	/*
	 * cauta masina cu acelasi numar de inmatriculare si o schimba
	 */
	for (int i = 0; i < masinaRepository->dimensiune; i++) 
	{
		Masina* rez = get(masinaRepository, i);
		if (strcmp(rez->numarInmatriculare, ((Masina*)masinaDeModificat)->numarInmatriculare) == 0)
		{
			stergeMasina(masinaRepository->listaMasini[i]);
			set(masinaRepository, i, masinaDeModificat);

			return 1;
		}
	}
	return 0;
}

ElemType cautaMasina(lista_masini* masinaRepository, char *numarInmatriculare)
{
	/*
	 *cauta o masina in repo si returneaza masina daca o gaseste sau NULL in cazul inexistentei
	 */
	for (int i = 0; i < masinaRepository->dimensiune; i++)
	{
		Masina* rez = get(masinaRepository, i);
		if (strcmp(rez->numarInmatriculare, numarInmatriculare) == 0)
			return masinaRepository->listaMasini[i];
	}

	return NULL;
}

int size(lista_masini* masinaRepository)
{
	/*
	returneaza numarul de elemente ale unei liste
	*/
	return masinaRepository->dimensiune;
}

lista_masini* copiazaLista(lista_masini* lista, CopyFct func)
{
	/*
	copiaza o lista intr-o alta lista noua independenta de acelasi fel (dupa functia func)
	*/
	lista_masini* rez = creeazaMasinaRepository(lista->dfunc);
	for (int i = 0; i < lista->dimensiune; ++i)
	{
		ElemType el = get(lista, i);
		adaugaMasinaRepository(rez, func(el));
	}
	return rez;
}

void stergeLista(lista_masini* lista)
{
	/*
	 * sterge masinile din repository dupa care dealoca lista si repo ul in sine
	 */
	for (int i = 0; i < lista->dimensiune; i++)
		lista->dfunc(lista->listaMasini[i]);

	free(lista->listaMasini);
	free(lista);
}

ElemType stergeUltim(lista_masini* lista)
{
	/*
	returneaza ultimul element din lista FARA SA IL STEARGA
	*/
	ElemType elem = lista->listaMasini[lista->dimensiune - 1];
	--lista->dimensiune;
	return elem;
}

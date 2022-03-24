#include "Testing.h"
#include "Validator.h"
#include "MasiniService.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>

void testValidare() 
{
	char numeInmatriculareValid[] = "CJ 11 BER";
	char modelValid[] = "Porsche";
	char categorieValida[] = "Sport";

	char numeInmatriculareInvalid[] = "";
	char modelInvalid[] = "";
	char categorieInvalida[] = "";

	assert(validareMasina(numeInmatriculareValid, modelValid, categorieValida) == 1);
	assert(validareMasina(numeInmatriculareInvalid, modelValid, categorieValida) == 0);
	assert(validareMasina(numeInmatriculareValid, modelInvalid, categorieValida) == 0);
	assert(validareMasina(numeInmatriculareValid, modelValid, categorieInvalida) == 0);
}

void testAdaugareMasiniRepository() 
{
	MasinaRepository masinaRepository;
	masinaRepository.toateMasini = creeazaMasinaRepository(stergeMasina);

	assert(masinaRepository.toateMasini->dimensiune == 0);
	assert(masinaRepository.toateMasini->capacitate == 1);
	Masina* masina1 = creeazaMasina("CJ 35 ASI", "VW", "POLO", 0);
	Masina* masina2 = creeazaMasina("B 101 AAA", "BMW", "M5", 0);
	Masina* masina3 = creeazaMasina("BR 10 ABC", "BMW", "M3", 0);
	assert(adaugaMasinaRepository(masinaRepository.toateMasini, masina1) == 1);
	assert(adaugaMasinaRepository(masinaRepository.toateMasini, masina2) == 1);
	assert(masinaRepository.toateMasini->dimensiune == 2);
	assert(adaugaMasinaRepository(masinaRepository.toateMasini, masina3) == 1);
	stergeLista(masinaRepository.toateMasini);
}

void testModificareMasinaRepository() 
{
	MasinaRepository masinaRepository;
	masinaRepository.toateMasini = creeazaMasinaRepository(stergeMasina);

	Masina* masina1 = creeazaMasina("CJ 35 ASI", "VW", "POLO", 0);
	Masina* masina2 = creeazaMasina("B 101 AAA", "BMW", "M5", 0);
	Masina* masina3 = creeazaMasina("BR 10 ABC", "BMW", "M3", 0);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina1);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina2);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina3);

	Masina* masina1Modificata = creeazaMasina("CJ 35 ASI", "BMW", "M5 Pachet", 0);
	Masina* masina2Modificata = creeazaMasina("B 101 AAA", "Volvo", "Mini", 0);
	Masina* masinaNegasita = creeazaMasina("Invalid", "VV", "SS", 0);
	
	assert(modificareMasina(masinaRepository.toateMasini, masina1Modificata) == 1);
	assert(modificareMasina(masinaRepository.toateMasini, masina2Modificata) == 1);

	Masina* rez = get(masinaRepository.toateMasini, 1);
	assert(strcmp("Volvo", rez->model) == 0);
	rez = get(masinaRepository.toateMasini, 0);
	assert(strcmp("M5 Pachet", rez->categorie) == 0);

	assert(modificareMasina(masinaRepository.toateMasini, masinaNegasita) == 0);
	stergeMasina(masinaNegasita);
	stergeLista(masinaRepository.toateMasini);
}

void testCautareMasina() 
{
	MasinaRepository masinaRepository;
	masinaRepository.toateMasini = creeazaMasinaRepository(stergeMasina);

	Masina* masina1 = creeazaMasina("CJ 35 ASI", "VW", "POLO", 0);
	Masina* masina2 = creeazaMasina("B 101 AAA", "BMW", "M5", 0);
	Masina* masina3 = creeazaMasina("BR 10 ABC", "BMW", "M3", 0);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina1);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina2);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina3);

	assert(cautaMasina(masinaRepository.toateMasini, "C") == NULL);
	assert(cautaMasina(masinaRepository.toateMasini, "CJ 35 ASI") == masina1);
	stergeLista(masinaRepository.toateMasini);
}

void testAdaugareMasinaService() 
{
	MasinaRepository masinaRepository;
	masinaRepository.toateMasini = creeazaMasinaRepository(stergeMasina);
	masinaRepository.listaUndo = creeazaMasinaRepository(stergeLista);

	assert(adaugareMasinaService(&masinaRepository, "CJ 35 ASI", "VW", "POLO") == 1);
	assert(adaugareMasinaService(&masinaRepository, "", "", "") == 0);
	assert(adaugareMasinaService(&masinaRepository, "CJ 35 ASI", "VW", "CCC") != 1);

	stergeLista(masinaRepository.toateMasini);
	stergeLista(masinaRepository.listaUndo);
}

void testModificareMasinaService() 
{
	MasinaRepository masinaRepository;
	masinaRepository.toateMasini = creeazaMasinaRepository(stergeMasina);
	masinaRepository.listaUndo = creeazaMasinaRepository(stergeLista);

	Masina* masina1 = creeazaMasina("CJ 35 ASI", "VW", "POLO", 0);
	Masina* masina2 = creeazaMasina("B 101 AAA", "BMW", "M5", 0);
	Masina* masina3 = creeazaMasina("BR 10 ABC", "BMW", "M3", 0);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina1);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina2);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina3);

	assert(modificareMasinaService(&masinaRepository, "CJ 35 ASI", "VWDD", "PLL") == 1);
	Masina* rez = get(masinaRepository.toateMasini, 0);
	assert(strcmp("PLL", rez->categorie) == 0);
	assert(modificareMasinaService(&masinaRepository, "CC", "C", "") == 0);
	assert(modificareMasinaService(&masinaRepository, "B 101 AAA", "", "M8") == 1);
	rez = get(masinaRepository.toateMasini, 1);
	assert(strcmp("M8", rez->categorie) == 0);
	stergeLista(masinaRepository.toateMasini);
	stergeLista(masinaRepository.listaUndo);
}

void testInchiriereMasina() 
{
	MasinaRepository masinaRepository;
	masinaRepository.toateMasini = creeazaMasinaRepository(stergeMasina);
	masinaRepository.listaUndo = creeazaMasinaRepository(stergeLista);

	Masina* masina1 = creeazaMasina("CJ 35 ASI", "VW", "POLO", 0);
	Masina* masina2 = creeazaMasina("B 101 AAA", "BMW", "M5", 0);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina1);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina2);

	assert(inchiriereMasina(&masinaRepository, "CJ 35 ASI") == 1);
	Masina* rez = get(masinaRepository.toateMasini, 0);
	assert(rez->inchiriata == 1);
	assert(inchiriereMasina(&masinaRepository, "CJ 35 ASI") == 0);
	assert(inchiriereMasina(&masinaRepository, "BR 10 ABC") == 0);
	stergeLista(masinaRepository.toateMasini);
	stergeLista(masinaRepository.listaUndo);
}

void testReturnareMasina() 
{
	MasinaRepository masinaRepository;
	masinaRepository.toateMasini = creeazaMasinaRepository(stergeMasina);
	masinaRepository.listaUndo = creeazaMasinaRepository(stergeLista);

	Masina* masina1 = creeazaMasina("CJ 35 ASI", "VW", "POLO", 0);
	Masina* masina2 = creeazaMasina("B 101 AAA", "BMW", "M5", 0);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina1);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina2);

	assert(returnareMasina(&masinaRepository, "CJ 35 ASI") == 0);

	inchiriereMasina(&masinaRepository, "CJ 35 ASI");
	assert(returnareMasina(&masinaRepository, "CJ 35 ASI") == 1);
	stergeLista(masinaRepository.toateMasini);
	stergeLista(masinaRepository.listaUndo);
}

void testMasiniDupaCategorie() 
{
	MasinaRepository masinaRepository;
	masinaRepository.toateMasini = creeazaMasinaRepository(stergeMasina);
	masinaRepository.listaUndo = creeazaMasinaRepository(stergeLista);

	Masina* masina1 = creeazaMasina("CJ 35 ASI", "VW", "Mini", 0);
	Masina* masina2 = creeazaMasina("CJ 35 AAA", "BMW", "Mini", 0);
	Masina* masina3 = creeazaMasina("CJ 35 ABC", "VW", "Mini", 0);
	Masina* masina4 = creeazaMasina("CJ 35 ABD", "BMW", "SUV", 0);

	adaugaMasinaRepository(masinaRepository.toateMasini, masina1);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina2);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina3);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina4);
	int dimensiuneListaDeCautat = 0;
	ElemType* listaMasini = listaMasiniDupaCategorie(&masinaRepository, &dimensiuneListaDeCautat, "Mini");
	assert(dimensiuneListaDeCautat == 3);
	free(listaMasini);
	stergeLista(masinaRepository.toateMasini);
	stergeLista(masinaRepository.listaUndo);
}

void testMasiniDupaModel() 
{
	MasinaRepository masinaRepository;
	masinaRepository.toateMasini = creeazaMasinaRepository(stergeMasina);
	masinaRepository.listaUndo = creeazaMasinaRepository(stergeLista);

	Masina* masina1 = creeazaMasina("CJ 35 ASI", "VW", "Mini", 0);
	Masina* masina2 = creeazaMasina("CJ 35 AAA", "BMW", "Mini", 0);
	Masina* masina3 = creeazaMasina("CJ 35 ABC", "VW", "Mini", 0);
	Masina* masina4 = creeazaMasina("CJ 35 ABD", "BMW", "SUV", 0);

	adaugaMasinaRepository(masinaRepository.toateMasini, masina1);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina2);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina3);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina4);

	int dimensiuneListaDeCautat = 0;
	ElemType* listaMasini = listaMasiniDupaModel(&masinaRepository, &dimensiuneListaDeCautat, "BMW");
	assert(dimensiuneListaDeCautat == 2);
	free(listaMasini);
	stergeLista(masinaRepository.toateMasini);
	stergeLista(masinaRepository.listaUndo);
}

void testSortareMasiniDupaModel() 
{
	MasinaRepository masinaRepository;
	masinaRepository.toateMasini = creeazaMasinaRepository(stergeMasina);
	masinaRepository.listaUndo = creeazaMasinaRepository(stergeLista);

	Masina* masina1 = creeazaMasina("CJ 35 ASI", "a", "Mini", 0);
	Masina* masina2 = creeazaMasina("CJ 35 AAA", "c", "Mini", 0);
	Masina* masina3 = creeazaMasina("CJ 35 ABC", "d", "Mini", 0);
	Masina* masina4 = creeazaMasina("CJ 35 ABD", "b", "SUV", 0);

	adaugaMasinaRepository(masinaRepository.toateMasini, masina1);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina2);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina3);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina4);

	ElemType* listaMasiniSortata = sortareMasiniDupaFunctie(&masinaRepository, comparareMasiniDupaModel, 1);

	assert(strcmp(((Masina*)listaMasiniSortata[0])->model, "a") == 0);
	assert(strcmp(((Masina*)listaMasiniSortata[2])->model, "c") == 0);

	ElemType* listaMasiniSortata2 = sortareMasiniDupaFunctie(&masinaRepository, comparareMasiniDupaModel, 0);

	assert(strcmp(((Masina*)listaMasiniSortata2[0])->model, "d") == 0);
	assert(strcmp(((Masina*)listaMasiniSortata2[2])->model, "b") == 0);

	free(listaMasiniSortata);
	free(listaMasiniSortata2);
	stergeLista(masinaRepository.toateMasini);
	stergeLista(masinaRepository.listaUndo);
}

void testSortareMasiniDupaCategorie() 
{
	MasinaRepository masinaRepository;
	masinaRepository.toateMasini = creeazaMasinaRepository(stergeMasina);
	masinaRepository.listaUndo = creeazaMasinaRepository(stergeLista);

	Masina* masina1 = creeazaMasina("CJ 35 ASI", "a", "1", 0);
	Masina* masina2 = creeazaMasina("CJ 35 AAA", "c", "2", 0);
	Masina* masina3 = creeazaMasina("CJ 35 ABC", "d", "3", 0);
	Masina* masina4 = creeazaMasina("CJ 35 ABD", "b", "4", 0);

	adaugaMasinaRepository(masinaRepository.toateMasini, masina1);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina2);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina3);
	adaugaMasinaRepository(masinaRepository.toateMasini, masina4);

	ElemType* listaMasiniSortata = sortareMasiniDupaFunctie(&masinaRepository, comparareMasiniDupaCategorie, 0);

	assert(strcmp(((Masina*)listaMasiniSortata[0])->categorie, "4") == 0);
	assert(strcmp(((Masina*)listaMasiniSortata[2])->categorie, "2") == 0);

	ElemType* listaMasiniSortata2 = sortareMasiniDupaFunctie(&masinaRepository, comparareMasiniDupaCategorie, 1);

	assert(strcmp(((Masina*)listaMasiniSortata2[0])->categorie, "1") == 0);
	assert(strcmp(((Masina*)listaMasiniSortata2[2])->categorie, "3") == 0);

	free(listaMasiniSortata);
	free(listaMasiniSortata2);
	stergeLista(masinaRepository.toateMasini);
	stergeLista(masinaRepository.listaUndo);
}

void testUndo()
{
	MasinaRepository masinaRepository;
	masinaRepository.toateMasini = creeazaMasinaRepository(stergeMasina);
	masinaRepository.listaUndo = creeazaMasinaRepository(stergeLista);


	assert(adaugareMasinaService(&masinaRepository, "CJ 35 ASI", "VW", "POLO") == 1);
	assert(adaugareMasinaService(&masinaRepository, "CJ 35 AAA", "VW", "LAMBO") == 1);

	assert(undo(&masinaRepository) == 0);
	assert(size(masinaRepository.toateMasini) == 1);

	assert(undo(&masinaRepository) == 0);
	assert(size(masinaRepository.toateMasini) == 0);

	assert(undo(&masinaRepository) == 1);

	stergeLista(masinaRepository.toateMasini);
	stergeLista(masinaRepository.listaUndo);
}

void testAllFunctions() 
{
	testValidare();
	testAdaugareMasiniRepository();
	testModificareMasinaRepository();
	testInchiriereMasina();
	testInchiriereMasina();
	testReturnareMasina();
	testCautareMasina();
	testAdaugareMasinaService();
	testModificareMasinaService();
	testMasiniDupaCategorie();
	testMasiniDupaModel();
	testSortareMasiniDupaModel();
	testSortareMasiniDupaCategorie();
	testUndo();
}

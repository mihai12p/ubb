#include "Testing.h"
#include "Validator.h"
#include "MasiniRepository.h"
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
    MasinaRepository *masinaRepository = creeazaMasinaRepository();
    assert(masinaRepository->dimensiune == 0);
    assert(masinaRepository->capacitate == 1);
    Masina *masina1 = creeazaMasina("CJ 35 ASI", "VW", "POLO");
    Masina *masina2 = creeazaMasina("B 101 AAA", "BMW", "M5");
    Masina *masina3 = creeazaMasina("BR 10 ABC", "BMW", "M3");
    assert(adaugaMasinaRepository(masinaRepository, masina1) == 1);
    assert(adaugaMasinaRepository(masinaRepository, masina2) == 1);
    assert(adaugaMasinaRepository(masinaRepository, masina2) == 0);
    assert(masinaRepository->dimensiune == 2);
    assert(adaugaMasinaRepository(masinaRepository, masina3) == 1);
    stergeMasinaRepository(masinaRepository);
}

void testModificareMasinaRepository() 
{
    MasinaRepository *masinaRepository = creeazaMasinaRepository();
    Masina *masina1 = creeazaMasina("CJ 35 ASI", "VW", "POLO");
    Masina *masina2 = creeazaMasina("B 101 AAA", "BMW", "M5");
    Masina *masina3 = creeazaMasina("BR 10 ABC", "BMW", "M3");
    adaugaMasinaRepository(masinaRepository, masina1);
    adaugaMasinaRepository(masinaRepository, masina2);
    adaugaMasinaRepository(masinaRepository, masina3);

    Masina *masina1Modificata = creeazaMasina("CJ 35 ASI", "BMW", "M5 Pachet");
    Masina *masina2Modificata = creeazaMasina("B 101 AAA", "Volvo", "Mini");
    Masina *masinaNegasita = creeazaMasina("Invalid", "VV", "SS");
    

    assert(modificareMasina(masinaRepository, masina1Modificata) == 1);
    assert(modificareMasina(masinaRepository, masina2Modificata) == 1);

    assert(strcmp("Volvo", masinaRepository->listaMasini[1]->model) == 0);
    assert(strcmp("M5 Pachet", masinaRepository->listaMasini[0]->categorie) == 0);

    assert(modificareMasina(masinaRepository, masinaNegasita) == 0);
    stergeMasina(masinaNegasita);
    stergeMasinaRepository(masinaRepository);
}

void testCautareMasina() 
{
    MasinaRepository *masinaRepository = creeazaMasinaRepository();
    Masina *masina1 = creeazaMasina("CJ 35 ASI", "VW", "POLO");
    Masina *masina2 = creeazaMasina("B 101 AAA", "BMW", "M5");
    Masina *masina3 = creeazaMasina("BR 10 ABC", "BMW", "M3");
    adaugaMasinaRepository(masinaRepository, masina1);
    adaugaMasinaRepository(masinaRepository, masina2);
    adaugaMasinaRepository(masinaRepository, masina3);

    assert(cautaMasina(masinaRepository, "C") == NULL);
    assert(cautaMasina(masinaRepository, "CJ 35 ASI") == masina1);
    stergeMasinaRepository(masinaRepository);
}

void testAdaugareMasinaService() 
{
    MasinaRepository *masinaRepository = creeazaMasinaRepository();
    assert(adaugareMasinaService(masinaRepository, "CJ 35 ASI", "VW", "POLO") == 1);
    assert(adaugareMasinaService(masinaRepository, "", "", "") == 0);
    assert(adaugareMasinaService(masinaRepository, "CJ 35 ASI", "VW", "CCC") != 1);

    stergeMasinaRepository(masinaRepository);
}

void testModificareMasinaService() 
{
    MasinaRepository *masinaRepository = creeazaMasinaRepository();
    Masina *masina1 = creeazaMasina("CJ 35 ASI", "VW", "POLO");
    Masina *masina2 = creeazaMasina("B 101 AAA", "BMW", "M5");
    Masina *masina3 = creeazaMasina("BR 10 ABC", "BMW", "M3");
    adaugaMasinaRepository(masinaRepository, masina1);
    adaugaMasinaRepository(masinaRepository, masina2);
    adaugaMasinaRepository(masinaRepository, masina3);


    assert(modificareMasinaService(masinaRepository, "CJ 35 ASI", "VWDD", "PLL") == 1);
    assert(strcmp("PLL", masinaRepository->listaMasini[0]->categorie) == 0);
    assert(modificareMasinaService(masinaRepository, "CC", "C", "") == 0);
    assert(modificareMasinaService(masinaRepository, "B 101 AAA", "", "M8") == 1);
    assert(strcmp("M8", masinaRepository->listaMasini[1]->categorie) == 0);
    stergeMasinaRepository(masinaRepository);
}

void testInchiriereMasina() 
{
    MasinaRepository *masinaRepository = creeazaMasinaRepository();
    Masina *masina1 = creeazaMasina("CJ 35 ASI", "VW", "POLO");
    Masina *masina2 = creeazaMasina("B 101 AAA", "BMW", "M5");
    adaugaMasinaRepository(masinaRepository, masina1);
    adaugaMasinaRepository(masinaRepository, masina2);

    assert(inchiriereMasina(masinaRepository, "CJ 35 ASI") == 1);
    assert(masinaRepository->listaMasini[0]->inchiriata == 1);
    assert(inchiriereMasina(masinaRepository, "CJ 35 ASI") == 0);
    assert(inchiriereMasina(masinaRepository, "BR 10 ABC") == 0);
    stergeMasinaRepository(masinaRepository);
}

void testReturnareMasina() 
{
    MasinaRepository *masinaRepository = creeazaMasinaRepository();
    Masina *masina1 = creeazaMasina("CJ 35 ASI", "VW", "POLO");
    Masina *masina2 = creeazaMasina("B 101 AAA", "BMW", "M5");
    adaugaMasinaRepository(masinaRepository, masina1);
    adaugaMasinaRepository(masinaRepository, masina2);

    assert(returnareMasina(masinaRepository, "CJ 35 ASI") == 0);

    inchiriereMasina(masinaRepository, "CJ 35 ASI");
    assert(returnareMasina(masinaRepository, "CJ 35 ASI") == 1);
    stergeMasinaRepository(masinaRepository);
}

void testMasiniDupaCategorie() 
{
    MasinaRepository *masinaRepository = creeazaMasinaRepository();
    Masina *masina1 = creeazaMasina("CJ 35 ASI", "VW", "Mini");
    Masina *masina2 = creeazaMasina("CJ 35 AAA", "BMW", "Mini");
    Masina *masina3 = creeazaMasina("CJ 35 ABC", "VW", "Mini");
    Masina *masina4 = creeazaMasina("CJ 35 ABD", "BMW", "SUV");

    adaugaMasinaRepository(masinaRepository, masina1);
    adaugaMasinaRepository(masinaRepository, masina2);
    adaugaMasinaRepository(masinaRepository, masina3);
    adaugaMasinaRepository(masinaRepository, masina4);
    int dimensiuneListaDeCautat = 0;
    Masina **listaMasini = listaMasiniDupaCategorie(masinaRepository, &dimensiuneListaDeCautat, "Mini");
    assert(dimensiuneListaDeCautat == 3);
    free(listaMasini);
    stergeMasinaRepository(masinaRepository);
}

void testMasiniDupaModel() 
{
    MasinaRepository *masinaRepository = creeazaMasinaRepository();
    Masina *masina1 = creeazaMasina("CJ 35 ASI", "VW", "Mini");
    Masina *masina2 = creeazaMasina("CJ 35 AAA", "BMW", "Mini");
    Masina *masina3 = creeazaMasina("CJ 35 ABC", "VW", "Mini");
    Masina *masina4 = creeazaMasina("CJ 35 ABD", "BMW", "SUV");

    adaugaMasinaRepository(masinaRepository, masina1);
    adaugaMasinaRepository(masinaRepository, masina2);
    adaugaMasinaRepository(masinaRepository, masina3);
    adaugaMasinaRepository(masinaRepository, masina4);

    int dimensiuneListaDeCautat = 0;
    Masina **listaMasini = listaMasiniDupaModel(masinaRepository, &dimensiuneListaDeCautat, "BMW");
    assert(dimensiuneListaDeCautat == 2);
    free(listaMasini);
    stergeMasinaRepository(masinaRepository);
}

void testSortareMasiniDupaModel() 
{
    MasinaRepository *masinaRepository = creeazaMasinaRepository();
    Masina *masina1 = creeazaMasina("CJ 35 ASI", "a", "Mini");
    Masina *masina2 = creeazaMasina("CJ 35 AAA", "c", "Mini");
    Masina *masina3 = creeazaMasina("CJ 35 ABC", "d", "Mini");
    Masina *masina4 = creeazaMasina("CJ 35 ABD", "b", "SUV");

    adaugaMasinaRepository(masinaRepository, masina1);
    adaugaMasinaRepository(masinaRepository, masina2);
    adaugaMasinaRepository(masinaRepository, masina3);
    adaugaMasinaRepository(masinaRepository, masina4);

    Masina **listaMasiniSortata = sortareMasiniDupaModel(masinaRepository, 1);

    assert(strcmp(listaMasiniSortata[0]->model, "a") == 0);
    assert(strcmp(listaMasiniSortata[2]->model, "c") == 0);

    free(listaMasiniSortata);
    stergeMasinaRepository(masinaRepository);
}

void testSortareMasiniDupaCategorie() 
{
    MasinaRepository *masinaRepository = creeazaMasinaRepository();
    Masina *masina1 = creeazaMasina("CJ 35 ASI", "a", "1");
    Masina *masina2 = creeazaMasina("CJ 35 AAA", "c", "2");
    Masina *masina3 = creeazaMasina("CJ 35 ABC", "d", "3");
    Masina *masina4 = creeazaMasina("CJ 35 ABD", "b", "4");

    adaugaMasinaRepository(masinaRepository, masina1);
    adaugaMasinaRepository(masinaRepository, masina2);
    adaugaMasinaRepository(masinaRepository, masina3);
    adaugaMasinaRepository(masinaRepository, masina4);

    Masina **listaMasiniSortata = sortareMasiniDupaCategorie(masinaRepository, 0);

    assert(strcmp(listaMasiniSortata[0]->categorie, "4") == 0);
    assert(strcmp(listaMasiniSortata[2]->categorie, "2") == 0);

    free(listaMasiniSortata);
    stergeMasinaRepository(masinaRepository);
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
}
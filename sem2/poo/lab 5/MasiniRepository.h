#ifndef UNTITLED_MASINIREPOSITORY_H
#define UNTITLED_MASINIREPOSITORY_H

#include "Masina.h"

typedef struct 
{
    Masina ** listaMasini;
    int capacitate;
    int dimensiune;
} MasinaRepository;

MasinaRepository *creeazaMasinaRepository();

int adaugaMasinaRepository(MasinaRepository *masinaRepository, Masina *masina);

int modificareMasina(MasinaRepository *masinaRepository, Masina *masinaDeModificat);

Masina *cautaMasina(MasinaRepository *masinaRepository, char *numarInmatriculare);

void stergeMasinaRepository(MasinaRepository *masinaRepository);

#endif //UNTITLED_MASINIREPOSITORY_H

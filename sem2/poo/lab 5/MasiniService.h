#ifndef UNTITLED_MASINISERVICE_H
#define UNTITLED_MASINISERVICE_H
#include "MasiniRepository.h"

int adaugareMasinaService(MasinaRepository *masinaRepository, char *numarInmatriculare, char *model, char *categorie);

int modificareMasinaService(MasinaRepository *masinaRepository, char *numarInmatriculare, char *model, char *categorie);

int inchiriereMasina(MasinaRepository *masinaRepository, char *numarDeInmatriculare);

int returnareMasina(MasinaRepository *masinaRepository, char *numarDeInmatriculare);

Masina **listaMasiniDupaCategorie(MasinaRepository *masinaRepository, int *dimensiuneListaReturnata, char *categorieDeCautat);

Masina **listaMasiniDupaModel(MasinaRepository *masinaRepository, int *dimensiuneListaReturnata, char *modelDeCautat);

Masina **sortareMasiniDupaModel(MasinaRepository *masinaRepository, int crescator);

Masina **sortareMasiniDupaCategorie(MasinaRepository *masinaRepository, int crescator);

#endif //UNTITLED_MASINISERVICE_H

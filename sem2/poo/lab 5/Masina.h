#ifndef UNTITLED_MASINA_H
#define UNTITLED_MASINA_H

typedef struct 
{
	char *numarInmatriculare;
	char *model;
	char *categorie;
	int inchiriata;
} Masina;

Masina* creeazaMasina(char* numarInmatriculare, char* model, char* categorie, int inchiriata);
Masina* copiazaMasina(Masina* masina);
void stergeMasina(Masina* masina);

#endif //UNTITLED_MASINA_H

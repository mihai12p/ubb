#include "Validator.h"
#include <string.h>
#include <crtdbg.h>

int validareMasina(char *numarInmatriculareMasina, char *modelMasina, char *categorieMasina) 
{
	//toate campurile trebuie sa nu fie vide
	if (strlen(numarInmatriculareMasina) == 0 || strlen(modelMasina) == 0 || strlen(categorieMasina) == 0)
		return 0;

	return 1;
}

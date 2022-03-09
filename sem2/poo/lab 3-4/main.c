#include "service.h"
#include "operatii.h"
#include "valid.h"

#define PARTICIPANTI_PREDEFINITI // activeaza o lista cu pariticipanti predefiniti utila pentru teste

int main()
{
	test_valid();
	test_adauga();
	test_reset();
	test_cauta();
	test_actualizeaza();
	test_sterge();

	repository repo; // lista cu participanti alocata static
	reset(&repo); // resetam continutul listei la 0

#ifdef PARTICIPANTI_PREDEFINITI
	participanti_predefiniti(&repo);
#endif

	while (consola(&repo) != -1);

	return 0;
}

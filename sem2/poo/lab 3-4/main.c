#include "service.h"
#include "operatii.h"
#include "valid.h"

#define TEST_APP // activeaza testarea aplicatiei
#ifndef TEST_APP
	#define PARTICIPANTI_PREDEFINITI // activeaza o lista cu pariticipanti predefiniti utila pentru teste
#endif

int main()
{
#ifdef TEST_APP
	test_valid();
	test_adauga();
	test_reset();
	test_cauta();
	test_actualizeaza();
	test_sterge();
#else
	repository repo; // lista cu participanti alocata static
	reset(&repo); // resetam continutul listei la 0

#ifdef PARTICIPANTI_PREDEFINITI
	participanti_predefiniti(&repo);
#endif

	while (consola(&repo) != -1);
#endif
	return 0;
}

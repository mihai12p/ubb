#include "operatii.h"

//#define OPEN_CPP_COVERAGE
#define CHECK_MEMORY_LEAKS
#ifdef CHECK_MEMORY_LEAKS
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

void test_all()
{
	test_isValid();
	test_adauga();
	test_cauta();
	test_actualizeaza();
	test_sterge();
	test_filter();
	test_sort();
}

int main()
{
	test_all();
#ifndef OPEN_CPP_COVERAGE
	repository repo = createEmpty();

	participanti_predefiniti(&repo);
	while (consola(&repo) != -1);

	destroy(&repo);
#endif

#ifdef CHECK_MEMORY_LEAKS
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}

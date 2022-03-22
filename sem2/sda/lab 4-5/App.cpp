#include <iostream>

#include "Teste/TestScurt.h"
#include "Teste/TestExtins.h"

#define CHECK_MEMORY_LEAKS
#ifdef CHECK_MEMORY_LEAKS
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

int main() 
{
	testAll();
	testAllExtins();
	test_suma();
	std::cout << "Finished Tests!" << std::endl;

#ifdef CHECK_MEMORY_LEAKS
	_CrtDumpMemoryLeaks();
#endif
}

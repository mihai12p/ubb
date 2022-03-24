#include "Console.h"
#include "Testing.h"
#include <crtdbg.h>

//#define OPEN_CPP_COVERAGE
#define CHECK_MEMORY_LEAKS
#ifdef CHECK_MEMORY_LEAKS
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif

int main() 
{
	testAllFunctions();
#ifndef OPEN_CPP_COVERAGE
	runConsoleApplication();
#endif

#ifdef CHECK_MEMORY_LEAKS
	_CrtDumpMemoryLeaks();
#endif
}

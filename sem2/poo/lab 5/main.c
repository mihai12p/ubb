#include "Console.h"
#include "Testing.h"
#include <crtdbg.h>

int main() 
{
    testAllFunctions();
    runConsoleApplication();
    _CrtDumpMemoryLeaks();
}

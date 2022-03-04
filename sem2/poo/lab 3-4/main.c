#include "operatii.h"

int main()
{
	repository repo;
	reset(&repo);

	while (consola(&repo) != -1);

	return 0;
}

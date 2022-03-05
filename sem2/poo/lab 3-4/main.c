#include "operatii.h"

int main()
{
	repository repo; // lista cu participanti alocata static
	reset(&repo); // resetam continutul listei la 0

	while (consola(&repo) != -1); // se executa pana cand userul doreste sa inchida executia programului, consola(...) returnand -1

	return 0;
}

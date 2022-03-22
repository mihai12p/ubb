#include <fstream>
#include <iostream>

const int inf = INT_MAX / 2;
#define elems 10

void floyd_warshall(unsigned graf[][elems], unsigned noduri)
{
	for (unsigned k = 0; k < noduri; ++k)
		for (unsigned i = 0; i < noduri; ++i)
			for (unsigned j = 0; j < noduri; ++j)
				if (graf[i][j] > graf[i][k] + graf[k][j] && graf[i][k] != inf && graf[k][j] != inf)
					graf[i][j] = graf[i][k] + graf[k][j];
}

int main()
{
	unsigned noduri;
	unsigned graf[elems][elems];

	std::ifstream fin("graf.txt");
	fin >> noduri;

	for (unsigned i = 0; i < noduri; ++i)
		for (unsigned j = i; j < noduri; ++j)
		{
			graf[i][j] = graf[j][i] = inf;
			graf[i][i] = 1;
		}

	unsigned x, y;
	while (fin >> x >> y)
		graf[x][y] = 1;

	floyd_warshall(graf, noduri);

	std::cout << "Inchiderea tranzitiva a grafului este: \n";
	for (unsigned i = 0; i < noduri; ++i)
	{
		for (unsigned j = 0; j < noduri; ++j)
		{
			if (graf[i][j] != inf)
				std::cout << "1 ";
			else
				std::cout << "0 ";
		}
		std::cout << '\n';
	}

	return 0;
}

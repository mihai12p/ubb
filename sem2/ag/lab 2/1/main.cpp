#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

const int inf = INT_MAX / 2;
#define elems 100

void moore(std::vector<unsigned>* G, unsigned nod, unsigned* drum, unsigned* parinte, unsigned noduri)
{
	bool visited[elems];
	memset(visited, false, sizeof(visited));

	for (unsigned i = 0; i < noduri; ++i)
		drum[i] = inf;
	drum[nod] = 0;

	std::queue<unsigned> Q;
	Q.push(nod);
	while (!Q.empty())
	{
		unsigned nodCurent = Q.front();
		Q.pop();
		visited[nodCurent] = true;

		for (unsigned i = 0; i < G[nodCurent].size(); ++i)
			if (drum[G[nodCurent][i]] > drum[nodCurent] + 1)
			{
				parinte[G[nodCurent][i]] = nodCurent;
				drum[G[nodCurent][i]] = drum[nodCurent] + 1;
				if (!visited[G[nodCurent][i]])
					Q.push(G[nodCurent][i]);
			}
	}
}

int main()
{
	unsigned noduri;
	std::vector<unsigned> graf[elems];
	std::ifstream fin("graf.txt");
	fin >> noduri;

	unsigned x, y;
	while (fin >> x >> y)
	{
		graf[x].push_back(y);
		graf[y].push_back(x);
	}

	unsigned drum[elems], parinte[elems];
	memset(drum, 0, sizeof(drum));
	memset(parinte, 0, sizeof(parinte));

	unsigned varf_sursa;
	std::cout << "Introduceti varful sursa: ";
	std::cin >> varf_sursa;

	moore(graf, varf_sursa, drum, parinte, noduri);

	std::cout << "Lantul cel mai scurt este: ";
	for (unsigned i = 0; i < noduri; ++i)
		if (drum[i] != inf)
			std::cout << drum[i] << ' ';
		else
			std::cout << "inf ";

	return 0;
}

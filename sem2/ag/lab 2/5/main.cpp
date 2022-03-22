#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>

#define noduri_max 25

bool viz[noduri_max];
void dfs(std::vector<int>* muchii, int nod)
{
	viz[nod] = true;
	std::cout << nod << ' ';

	for (size_t k = 0; k < muchii[nod].size(); ++k)
	{
		int vecin = muchii[nod][k];
		if (!viz[vecin])
			dfs(muchii, vecin);
	}
}

int main()
{
	int noduri;
	std::vector<int> muchii[311];
	std::ifstream fin("graf.txt");
	fin >> noduri;

	int x, y;
	while (fin >> x >> y)
	{
		muchii[x].push_back(y);
		muchii[y].push_back(x);
	}

	for (int i = 0; i < noduri; ++i)
	{
		std::cout << "Nodurile accesibile din " << i << " sunt: ";
		memset(viz, false, sizeof(viz));
		dfs(muchii, i);
		std::cout << '\n';
	}

	return 0;
}

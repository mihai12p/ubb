#include <fstream>
#include <iostream>
#include <queue>

#define noduri_max 25

void bfs(std::vector<int>* muchii, int nodStart)
{
	int dist[noduri_max] = { 0 };
	bool viz[noduri_max] = { false };
	std::queue<int> Q;
	Q.push(nodStart);
	viz[nodStart] = true;
	dist[nodStart] = 0;

	std::cout << "Nodurile accesibile din " << nodStart << " sunt: \n";

	while (!Q.empty())
	{
		int nod = Q.front();
		Q.pop();
		for (size_t k = 0; k < muchii[nod].size(); ++k)
		{
			int vecin = muchii[nod][k];
			if (!viz[vecin])
			{
				dist[vecin] = dist[nod] + 1;
				viz[vecin] = true;
				Q.push(vecin);
				std::cout << vecin << " (dist: " << dist[vecin] << ")\n";
			}
		}
	}
}

int main()
{
	std::vector<int> muchii[311];
	std::ifstream fin("graf.txt");

	int x, y;
	while (fin >> x >> y)
	{
		muchii[x].push_back(y);
		muchii[y].push_back(x);
	}

	int start;
	std::cout << "Introduceti varful de start: ";
	std::cin >> start;

	bfs(muchii, start);

	return 0;
}

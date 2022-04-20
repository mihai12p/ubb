#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

const int INF = 0x3f3f3f3f;

void prim(std::vector<std::pair<int, int>>* graf, const int radacina, const int noduri, std::ofstream* fout)
{
	int costMinim = 0, nr_muchii = -1;

	typedef std::pair<int, int> iPair;
	std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> PQ; // min-heap

	std::vector<int> key(noduri, INF);
	std::vector<int> parinte(noduri, -1);
	std::vector<bool> inMST(noduri, false);

	PQ.push({ 0, radacina });
	key[radacina] = 0;
	
	while (!PQ.empty())
	{
		int nodCurent = PQ.top().second; PQ.pop();
		if (inMST[nodCurent])
			continue;
		inMST[nodCurent] = true;
		++nr_muchii;

		for (const auto& k : graf[nodCurent])
		{
			const int vecin = k.first;
			const int cost = k.second;
			if (key[vecin] > cost && !inMST[vecin])
			{
				key[vecin] = cost;
				PQ.push({ key[vecin], vecin });
				parinte[vecin] = nodCurent;
			}
		}
	}

	for (int i = 0; i < noduri; ++i)
		costMinim += key[i];
	*fout << costMinim << '\n' << nr_muchii << '\n';
	for (int i = 0; i < noduri; ++i)
		if (inMST[i] && i != radacina)
		{
			if (i < parinte[i])
				*fout << i << ' ' << parinte[i] << '\n';
			else
				*fout << parinte[i] << ' ' << i << '\n';
		}
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cout << "Syntax: .exe input output";
		return -1;
	}

	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);

	int noduri, arce;
	fin >> noduri >> arce;
	std::vector<std::pair<int, int>>* graf = new std::vector<std::pair<int, int>>[noduri];
	for (int i = 0; i < arce; ++i)
	{
		int x, y, cost;
		fin >> x >> y >> cost;
		graf[x].push_back({ y, cost });
		graf[y].push_back({ x, cost });
	}

	prim(graf, 0, noduri, &fout);

	fout.close();
	fin.close();
	return 0;
}

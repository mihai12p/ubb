#include <iostream>
#include <fstream>
#include <queue>

bool BFS(int** grafRezidual, const int sursa, const int destinatie, int* parinte, const int noduri)
{
	bool* viz = new bool[noduri] { };

	std::queue<int> Q;
	Q.push(sursa);
	viz[sursa] = true;
	parinte[sursa] = -1;

	while (!Q.empty() && !viz[destinatie])
	{
		int nodCurent = Q.front();
		Q.pop();

		for (int i = 0; i < noduri && !viz[destinatie]; ++i)
		{
			int cost = grafRezidual[nodCurent][i];
			if (!viz[i] && cost > 0)
			{
				Q.push(i);
				viz[i] = true;
				parinte[i] = nodCurent;
			}
		}
	}

	bool ret = viz[destinatie];
	delete[] viz;

	return ret;
}

int edmons_karp(int** grafRezidual, const int sursa, const int destinatie, const int noduri)
{
	int fluxMaxim = 0;

	int* parinte = new int[noduri] { };
	while (BFS(grafRezidual, sursa, destinatie, parinte, noduri))
	{
		int capacitateMin = INT_MAX;
		for (int v = destinatie; v != sursa; v = parinte[v])
		{
			int u = parinte[v];
			capacitateMin = std::min(capacitateMin, grafRezidual[u][v]);
		}

		for (int v = destinatie; v != sursa; v = parinte[v])
		{
			int u = parinte[v];
			grafRezidual[u][v] -= capacitateMin;
			grafRezidual[v][u] += capacitateMin;
		}

		// la fiecare drum s - t gasit se satureaza arcul cu costul minim deci data viitoare
		// sigur se va gasi un alt drum s - t

		fluxMaxim += capacitateMin;
	}

	delete[] parinte;

	return fluxMaxim;
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
	int** grafRezidual = new int* [noduri];
	for (int i = 0; i < noduri; ++i)
		grafRezidual[i] = new int[noduri] {};
	for (int i = 0; i < arce; ++i)
	{
		int x, y, cost;
		fin >> x >> y >> cost;
		grafRezidual[x][y] = cost;
	}

	fout << edmons_karp(grafRezidual, 0, noduri - 1, noduri);

	for (int i = 0; i < noduri; ++i)
		delete[] grafRezidual[i];
	delete[] grafRezidual;
	fout.close();
	fin.close();
	return 0;
}

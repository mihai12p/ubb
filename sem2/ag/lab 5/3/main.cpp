#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <unordered_set>

void hierholzer(std::unordered_set<int>* G, const int start, std::vector<int>& eulerCircuit, std::ofstream& fout)
{
	std::stack<int> path;
	path.push(start);

	while (!path.empty())
	{
		const int u = path.top();
		if (G[u].size()) // cat timp mai avem muchii care au pe u ca extremitate
		{
			const int v = *G[u].begin();
			
			//stergem muchia u - v din graf
			G[u].erase(G[u].begin());
			G[v].erase(u);

			//continuam cu vecinul lui u adica v
			path.push(v);
			continue;
		}

		path.pop();
		eulerCircuit.push_back(u);
	}

	eulerCircuit.pop_back();
	for (const auto& n : eulerCircuit)
		fout << n << ' ';
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

	std::vector<int> eulerCircuit;

	int noduri, muchii;
	fin >> noduri >> muchii;
	std::unordered_set<int>* G = new std::unordered_set<int>[noduri];
	for (int i = 0; i < muchii; ++i)
	{
		int x, y;
		fin >> x >> y;
		G[x].insert(y);
		G[y].insert(x);
	}

	hierholzer(G, 0, eulerCircuit, fout);

	delete[] G;
	fout.close();
	fin.close();
	return 0;
}

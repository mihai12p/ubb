#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

const int INF = 0x3f3f3f3f;

void dijkstra(const std::vector<std::pair<int, int>>* graf, std::vector<int>& dist, const int start)
{
	typedef std::pair<int, int> iPair;
	std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> PQ; // min-heap
	PQ.push({ 0, start });
	dist[start] = 0;

	while (!PQ.empty())
	{
		int nodCurent = PQ.top().second; PQ.pop();
		for (const auto& i : graf[nodCurent])
		{
			int vecin = i.first;
			int cost = i.second;
			if (dist[vecin] > dist[nodCurent] + cost)
			{
				dist[vecin] = dist[nodCurent] + cost;
				PQ.push({ dist[vecin], vecin });
			}
		}
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

	int noduri, arce, start;
	fin >> noduri >> arce >> start;
	std::vector<std::pair<int, int>>* graf = new std::vector<std::pair<int, int>>[noduri];
	for (int i = 0; i < arce; ++i)
	{
		int x, y, cost;
		fin >> x >> y >> cost;
		graf[x].push_back({ y, cost });
	}

	std::vector<int> dist(noduri, INF);
	dijkstra(graf, dist, start);
	for (int i = 0; i < noduri; ++i)
	{
		if (dist[i] == INF)
			fout << "INF ";
		else
			fout << dist[i] << ' ';
	}

	delete[] graf;
	fout.close();
	fin.close();
	return 0;
}

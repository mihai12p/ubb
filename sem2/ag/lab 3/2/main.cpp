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
			const int vecin = i.first;
			const int cost = i.second;
			if (dist[vecin] > dist[nodCurent] + cost)
			{
				dist[vecin] = dist[nodCurent] + cost;
				PQ.push({ dist[vecin], vecin });
			}
		}
	}
}

bool bellman_ford(const std::vector<std::pair<int, int>>* graf, std::vector<int>& dist, const int start)
{
	dist[start] = 0;
	for (int i = 0; i < start - 1; ++i)
		for (int k = 0; k < start; ++k)
			for (const auto& j : graf[k])
			{
				const int vecin = j.first;
				const int cost = j.second;
				if (dist[vecin] > dist[k] + cost)
					dist[vecin] = dist[k] + cost;
			}
	for (int k = 0; k < start; ++k)
		for (const auto& j : graf[k])
		{
			const int vecin = j.first;
			const int cost = j.second;
			if (dist[vecin] > dist[k] + cost)
				return false; // ciclu negativ
		}

	return true;
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
	std::vector<std::pair<int, int>>* graf = new std::vector<std::pair<int, int>>[noduri + 1];
	for (int i = 0; i < arce; ++i)
	{
		int x, y, cost;
		fin >> x >> y >> cost;
		graf[x].push_back({ y, cost });
	}
	for (int i = 0; i < noduri; ++i)
		graf[noduri].push_back({ i, 0 }); // adaug noul nod (index = int(noduri)) si il leg de varfuri cu cost 0

	std::vector<int> dist(noduri + 1, INF);
	if (bellman_ford(graf, dist, noduri) == false)
		fout << -1;
	else
	{
		for (int i = 0; i < noduri; ++i)
		{
			graf[noduri].pop_back(); // elimin nodul adaugat
			for (auto& j : graf[i])
			{
				const int vecin = j.first;
				int& cost = j.second;
				cost += dist[i] - dist[vecin]; // reponderez graful
				fout << i << ' ' << vecin << ' ' << cost << '\n';
			}
		}
		for (int i = 0; i < noduri; ++i)
		{
			std::vector<int> distNoi(noduri, INF);
			dijkstra(graf, distNoi, i); // Dijkstra pentru fiecare nod in noul graf reponderat
			for (int j = 0; j < noduri; ++j)
			{
				if (distNoi[j] == INF)
					fout << "INF ";
				else
					fout << distNoi[j] - dist[i] + dist[j] << ' ';
			}
			fout << '\n';
		}
	}

	delete[] graf;
	fout.close();
	fin.close();
	return 0;
}

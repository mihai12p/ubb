#include <iostream>
#include <fstream>
#include <set>

struct nod
{
	int grad;
	int parinte;
};

void codare_prufer(nod* noduri, int* K, const int N, std::set<int>& frunze)
{
	for (int i = 0, frunzaMin; i < N - 1; ++i)
	{
		frunzaMin = *frunze.begin();
		frunze.erase(frunze.begin());

		K[i] = noduri[frunzaMin].parinte;
		--noduri[frunzaMin].grad;
		if (noduri[noduri[frunzaMin].parinte].parinte != -1 && --noduri[noduri[frunzaMin].parinte].grad == 1)
			frunze.insert(noduri[frunzaMin].parinte);
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

	int N;
	fin >> N;
	nod* noduri = new nod[N] { };
	for (int i = 0; i < N; ++i)
	{
		fin >> noduri[i].parinte;
		if (noduri[i].parinte != -1)
			++noduri[i].grad, ++noduri[noduri[i].parinte].grad;
	}

	std::set<int> frunze;
	for (int i = 0; i < N; ++i)
		if (noduri[i].grad == 1 && noduri[i].parinte != -1) // daca e frunza si nu e radacina
			frunze.insert(i);

	int* K = new int[N - 1];
	codare_prufer(noduri, K, N, frunze);
	fout << N - 1 << '\n';
	for (int i = 0; i < N - 1; ++i)
		fout << K[i] << ' ';

	delete[] K;
	delete[] noduri;
	fout.close();
	fin.close();
	return 0;
}

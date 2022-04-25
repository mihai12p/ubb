#include <iostream>
#include <fstream>
#include <list>
#include <set>

void decodare_prufer(std::list<int>& parinti, int* T, const int N, std::set<int>& min, int* grad)
{
	for (int i = 0, minim; i < N; ++i)
	{
		minim = *min.begin();
		min.erase(min.begin());

		T[minim] = parinti.front();
		if (--grad[parinti.front()] == 0)
			min.insert(parinti.front());
		parinti.erase(parinti.begin());
	}

	T[*min.begin()] = -1;
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
	int* grad = new int[N + 1] { };
	std::set<int> min;
	for (int i = 0; i < N + 1; ++i)
		min.insert(i);

	std::list<int> parinti;
	for (int i = 0, x; i < N; ++i)
	{
		fin >> x;
		++grad[x];
		parinti.push_back(x);
		min.erase(x);
	}

	int* T = new int[N + 1] { };
	decodare_prufer(parinti, T, N, min, grad);
	fout << N + 1 << '\n';
	for (int i = 0; i < N + 1; ++i)
		fout << T[i] << ' ';

	delete[] T;
	delete[] grad;
	fout.close();
	fin.close();
	return 0;
}

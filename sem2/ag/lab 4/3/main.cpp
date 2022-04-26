#include <iostream>
#include <fstream>
#include <string>
#include <map>

void codare_huffman(const std::string& sir, std::ofstream& fout)
{
	typedef std::pair<int, char> iPair;
	std::multimap<iPair, std::string> PQ;

	int fr[256] { }, count = 0;
	for (const auto& i : sir)
		if (++fr[i] == 1)
			++count;
	fout << count << '\n';
	for (int i = 0; i < 256; ++i)
		if (fr[i])
		{
			fout << char(i) << ' ' << fr[i] << '\n';
			PQ.insert({ { fr[i], i }, std::string(1, i) });
		}

	std::string cod[256] { };
	typedef std::pair<iPair, std::string> mPair;
	while (--count)
	{
		const mPair& x = *PQ.begin();
		for (const auto& c : x.second)
			cod[c] = "0" + cod[c];
		PQ.erase(PQ.begin());

		const mPair& y = *PQ.begin();
		for (const auto& c : y.second)
			cod[c] = "1" + cod[c];
		PQ.erase(PQ.begin());

		PQ.insert({ { x.first.first + y.first.first, std::min(x.first.second, y.first.second) }, x.second + y.second });
		count = PQ.size();
	}
	for (const auto& i : sir)
		fout << cod[i];
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

	std::string sir;
	std::getline(fin, sir);

	codare_huffman(sir, fout);

	fout.close();
	fin.close();
	return 0;
}

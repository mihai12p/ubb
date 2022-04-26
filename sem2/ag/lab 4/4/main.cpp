#include <iostream>
#include <fstream>
#include <string>
#include <map>

typedef std::pair<int, char> iPair;
void codare_huffman(int& count, std::multimap<iPair, std::string>& PQ, std::map<std::string, char>& coduri)
{
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

	for (int i = 0; i < 256; ++i)
		if (cod[i] != "")
			coduri.insert({ cod[i], i });
}

void decodare_huffman(int& count, std::multimap<iPair, std::string>& PQ, std::string& sir, int* fr, std::ofstream& fout)
{
	std::string sirNou = "";

	std::map<std::string, char> coduri;
	codare_huffman(count, PQ, coduri);

	int lastPos = 0, lenSubsir = 0;
	std::string previous = "", previousChar = "";
	while (coduri.size() > 1)
	{
		std::string untilNow = sir.substr(lastPos, ++lenSubsir);
		const auto& cauta = coduri.find(untilNow);
		if (cauta != coduri.end())
		{
			previous = untilNow;
			previousChar = cauta->second;
		}
		else if (cauta == coduri.end() && previous != "")
		{
			sirNou.append(previousChar);

			if (--fr[previousChar[0]] == 0)
				coduri.erase(previous);

			lastPos += previous.size();
			lenSubsir = 0;
			previous = previousChar = "";
		}
	}

	if (coduri.size() == 1)
		sirNou.append(std::string(1, coduri.begin()->second));

	fout << sirNou;
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

	std::multimap<iPair, std::string> PQ;

	int count, fr[256] { };
	fin >> count;
	fin.get();
	for (int i = 0; i < count; ++i)
	{
		std::string s;
		std::getline(fin, s);
		char c = s[0];
		fr[c] = std::stoi(s.substr(2));
		PQ.insert({ { fr[c], c }, std::string(1, c) });
	}
	std::string sir;
	std::getline(fin, sir);

	decodare_huffman(count, PQ, sir, fr, fout);

	fout.close();
	fin.close();
	return 0;
}

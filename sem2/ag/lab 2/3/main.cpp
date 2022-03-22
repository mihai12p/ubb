#include <fstream>
#include <iostream>
#include <string>
#include <queue>

#define linii_max 53
#define coloane_max 104

struct nod 
{
	int lin, col;
} st, fn;

int di[] = { 0, 1, 0, -1 };
int dj[] = { 1, 0, -1, 0 };

void Lee(int graf[][coloane_max], nod start, nod final, int linii, int coloane)
{
	std::queue<std::pair<int, int>> Q;
	Q.push(std::make_pair(start.lin, start.col));
	graf[start.lin][start.col] = 1;

	while (!Q.empty() && graf[final.lin][final.col] == 0)
	{
		int i = Q.front().first, j = Q.front().second;
		Q.pop();
		for (int k = 0; k < 4; ++k)
		{
			nod vec = { i + di[k], j + dj[k] };
			if (vec.lin >= 0 && vec.lin < linii && vec.col >= 0 && vec.col < coloane && graf[vec.lin][vec.col] == 0)
			{
				graf[vec.lin][vec.col] = graf[i][j] + 1;
				Q.push(std::make_pair(vec.lin, vec.col));
			}
		}
	}
}

void traseu(int graf[][coloane_max], nod start, nod final, int linii, int coloane)
{
	int drum[linii_max][coloane_max] { };

	nod actualPos = { final.lin, final.col };
	drum[actualPos.lin][actualPos.col] = 1;

	while (!(actualPos.lin == start.lin && actualPos.col == start.col))
	{
		for (int k = 0; k < 4; ++k)
		{
			nod vec = { actualPos.lin + di[k], actualPos.col + dj[k] };
			if (graf[actualPos.lin][actualPos.col] == graf[vec.lin][vec.col] + 1)
			{
				actualPos.lin += di[k], actualPos.col += dj[k];
				break;
			}
		}
		drum[actualPos.lin][actualPos.col] = 1;
	}

	for (int i = 0; i < linii; ++i)
	{
		for (int j = 0; j < coloane; ++j)
		{
			if (drum[i][j])
				std::cout << drum[i][j] << ' ';
			else
				std::cout << "  ";
		}

		std::cout << '\n';
	}
}

int main()
{
	int graf[linii_max][coloane_max];

	std::ifstream fin("labirint_1.txt");

	int linie = 0;
	std::string tp;
	while (getline(fin, tp))
	{
		for (size_t i = 0; i < tp.size(); ++i)
		{
			if (tp[i] == '1')
				graf[linie][i] = -1;
			else
			{
				if (tp[i] == 'S')
					st = { linie, (int)i };
				else if (tp[i] == 'F')
					fn = { linie, (int)i };

				graf[linie][i] = 0;
			}
		}
		++linie;
	}

	int coloane = tp.size();

	Lee(graf, st, fn, linie, coloane);
	traseu(graf, st, fn, linie, coloane);

	return 0;
}

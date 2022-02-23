#include <fstream>
#include <iostream>
#include <vector>

int main()
{
    std::ifstream fin("in.txt");
    int nr_varfuri, nr_muchii = 0;
    fin >> nr_varfuri;

    /* Fisier -> Matrice de adiacenta */
    bool graf[nr_varfuri][nr_varfuri] { };

    int x, y;
    while (fin >> x >> y)
        graf[x - 1][y - 1] = graf[y - 1][x - 1] = true, ++nr_muchii;

    std::cout << "Matricea de adiacenta este: \n";
    for (int i = 0; i < nr_varfuri; ++i)
    {
        for (int j = 0; j < nr_varfuri; ++j)
            std::cout << graf[i][j] << ' ';
        std::cout << '\n';
    }

    /* Matrice de adiacenta -> Liste de adiacenta */
    std::vector<int> lista[nr_varfuri];

    for (int i = 0; i < nr_varfuri; ++i)
        for (int j = 0; j < nr_varfuri; ++j)
            if (graf[i][j])
                lista[i].push_back(j + 1);

    std::cout << "\nLista de adiacenta este: \n";
    for (int i = 0; i < nr_varfuri; ++i)
    {
        std::cout << "Varf " << i + 1 << ": ";
        for (int j = 0; j < lista[i].size(); ++j)
            std::cout << lista[i][j] << ' ';
        std::cout << '\n';
    }

    /* Liste de adiacenta -> Matrice de incidenta */
    bool inc[nr_varfuri][nr_muchii] { };
    
    for (int j = 0, muchie = -1; j < nr_varfuri; ++j)
        for (int k = lista[j].size() - 1; k >= 0 && lista[j][k] > j + 1; --k)
            ++muchie, inc[j][muchie] = inc[lista[j][k] - 1][muchie] = true;

    std::cout << "\nMatricea de incidenta este: \n";
    for (int i = 0; i < nr_varfuri; ++i)
    {
        for (int j = 0; j < nr_muchii; ++j)
            std::cout << inc[i][j] << ' ';
        std::cout << '\n';
    }

    /* Matrice de incidenta -> Matrice de adiacenta */
    bool adiac[nr_varfuri][nr_varfuri] { };

    for (int i = 0; i < nr_muchii; ++i)
        for (int j = 0, first = -1, second = -1; j < nr_varfuri && (first == -1 || second == -1); ++j)
            if (inc[j][i])
            {
                if (first != -1)
                    second = j, adiac[first][second] = adiac[second][first] = true;
                else
                    first = j;
            }

    std::cout << "\nMatricea de adiacenta este: \n";
    for (int i = 0; i < nr_varfuri; ++i)
    {
        for (int j = 0; j < nr_varfuri; ++j)
            std::cout << adiac[i][j] << ' ';
        std::cout << '\n';
    }

    /* Verificam daca e ca la inceput */
    try
    {
        for (int i = 0; i < nr_varfuri; ++i)
            for (int j = 0; j < nr_varfuri; ++j)
                if (adiac[i][j] != graf[i][j])
                    throw "\nCele 2 matrici de adiacenta sunt diferite.";

        std::cout << "\nCele 2 matrici de adiacenta sunt identice.";
    }
    catch (const char * msg)
    {
        std::cout << msg;
    }

    return 0;
}
#include <fstream>
#include <iostream>

#define inf 300

int nr_varfuri, nr_muchii;
bool graf[inf][inf];
int dist[inf][inf];
bool vizitat[inf];

void dfs(int varf);

int main()
{
    std::ifstream fin("fis2.txt");
    fin >> nr_varfuri >> nr_muchii;

    for (int i = 0, x, y; i < nr_muchii; ++i)
    {
        fin >> x >> y;
        graf[x - 1][y - 1] = graf[y - 1][x - 1] = true;
        dist[x - 1][y - 1] = dist[y - 1][x - 1] = 1;
    }

    /* Determinam varfurile izolate */
    int grad[nr_varfuri] { };

    for (int i = 0; i < nr_varfuri; ++i)
        for (int j = 0; j < nr_varfuri; ++j)
            if (graf[i][j])
                ++grad[i];

    std::cout << "Varfurile izolate sunt: ";
    for (int i = 0; i < nr_varfuri; ++i)
        if (grad[i] == 0)
            std::cout << i + 1 << ' ';

    /* Verificam daca graful e regular */
    try
    {
        for (int i = 1; i < nr_varfuri; ++i)
            if (grad[i - 1] != grad[i])
                throw "\n\nGraful nu este regular.\n";

        std::cout << "\n\nGraful este regular.\n";
    }
    catch (const char * msg)
    {
        std::cout << msg;
    }

    /* Determinam matricea distantelor (algoritm: Roy-Floyd) */
    for (int i = 0; i < nr_varfuri; ++i)
        for (int j = 0; j < nr_varfuri; ++j)
            if (!dist[i][j] && i != j)
                dist[i][j] = inf;

    for (int k = 0; k < nr_varfuri; ++k)
        for (int i = 0; i < nr_varfuri; ++i)
            for (int j = 0; j < nr_varfuri; ++j)
                dist[i][j] = std::min(dist[i][k] + dist[k][j], dist[i][j]);

    std::cout << "\nMatricea distantelor: \n";
    for (int i = 0; i < nr_varfuri; ++i)
    {
        for (int j = 0; j < nr_varfuri; ++j)
            if (dist[i][j] != inf)
                std::cout << dist[i][j] << ' ';
            else
                std::cout << "inf ";
        std::cout << '\n';
    }
    
    /* Verificam daca graful e conex */
    dfs(0);
    try
    {
        for (int i = 0; i < nr_varfuri; ++i)
            if (!vizitat[i])
                throw "\nGraful nu este conex.";

        std::cout << "\nGraful este conex.";
    }
    catch (const char * msg)
    {
        std::cout << msg;
    }

    return 0;
}

void dfs(int varf)
{
    vizitat[varf] = true;
    for (int i = 0; i < nr_varfuri; ++i)
        if (graf[i][varf] && !vizitat[i])
            dfs(i); 
}
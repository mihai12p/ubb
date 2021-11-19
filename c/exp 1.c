#include <stdio.h>

void afisare(int d, int (*sir)[d])
{
    for (int i = 0; i < d; ++i)
    {
        for (int j = 0; j < d; ++j)
            printf("%d ", *(*(sir + i) + j));
        printf("\n");
    }
}

int main()
{
    int d = 2;
    int sir[d][d];
    for (int i = 0; i < d; ++i)
        for (int j = 0; j < d; ++j)
            scanf("%d", *(sir + i) + j);

    afisare(d, sir);

    return 0;
}
#include <stdio.h>

void afisare(int d, int (*mat)[d])
{
    for (int i = 0; i < d; ++i)
    {
        for (int j = 0; j < d; ++j)
            printf("%d ", *(*(mat + i) + j));
        printf("\n");
    }
}

int main()
{
    int d = 2;
    int mat[d][d];
    for (int i = 0; i < d; ++i)
        for (int j = 0; j < d; ++j)
            scanf("%d", *(mat + i) + j);

    afisare(d, mat);

    return 0;
}

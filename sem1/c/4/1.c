#include <stdio.h>
#include <stdlib.h>

// 1.Using dynamic memory allocation where is the case, solve the following:
// Multiply 2 matrices of integers.

#define X 2
#define Y 3
/*
EXEMPLU PENTRU XY DE MAI SUS
[ 1 0 2    [3 1    [5 1
 -1 3 1] x  2 1  =  4 2]
            1 0]
*/

int main()
{
    int **mat = (int **)malloc(X * sizeof(int *));
    for (int i = 0; i < X; ++i)
    {
        mat[i] = (int *)malloc(Y * sizeof(int));
        for (int j = 0; j < Y; ++j)
            scanf("%d", mat[i] + j);
    }

    int **mat2 = (int **)malloc(Y * sizeof(int *));
    for (int i = 0; i < Y; ++i)
    {
        mat2[i] = (int *)malloc(X * sizeof(int));
        for (int j = 0; j < X; ++j)
            scanf("%d", mat2[i] + j);
    }

    int **mat3 = (int **)calloc(X, sizeof(int *));
    for (int i = 0; i < X; ++i)
    {
        mat3[i] = (int *)calloc(X, sizeof(int));
        for (int j = 0; j < X; ++j)
            for (int p = 0; p < Y; ++p)
                mat3[i][j] += mat[i][p] * mat2[p][j];
    }

    printf("\n");
    for (int i = 0; i < X; ++i)
    {
        for (int j = 0; j < X; ++j)
            printf("%d ", mat3[i][j]);
        printf("\n");
    }

    for (int i = 0; i < X; ++i) free(mat[i]);
    free(mat);

    for (int i = 0; i < Y; ++i) free(mat2[i]);
    free(mat2);

    for (int i = 0; i < X; ++i) free(mat3[i]);
    free(mat3);

    return 0;
}
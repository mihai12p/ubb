#include <stdio.h>

// 2.Write a program that reads a 2D array and prints transpose of the array.

#define X 3
#define Y 2
int array[X][Y];

int main()
{
    for (int i = 0; i < X; ++i)
        for (int j = 0; j < Y; ++j)
            scanf("%d", &array[i][j]);

    for (int i = 0; i < Y; ++i)
    {
        for (int j = 0; j < X; ++j)
            printf("%d ", array[j][i]);
        printf("\n");
    }

    return 0;
}
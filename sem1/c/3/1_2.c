#include <stdio.h>

// 1.Write a program that reads 2 arrays and merges the two arrays into third array.
// Before merging, sort the 2 arrays in ascending order.

#define N 3
int array1[N], array2[N], array3[2 * N];

void sort(int *array)
{
    for (int i = 0; i < N - 1; ++i)
        for (int j = i + 1; j < N; ++j)
            if (*(array + i) > *(array + j))
            {
                int swap = *(array + i);
                *(array + i) = *(array + j);
                *(array + j) = swap;
            }
}

int main()
{
    for (int i = 0; i < N; ++i)
        scanf("%d", array1 + i);

    for (int i = 0; i < N; ++i)
        scanf("%d", array2 + i);

    sort(array1);
    sort(array2);

    int i = 0, j = 0;
    while (i < N && j < N)
    {
        int min;
        if (*(array1 + i) < *(array2 + j))
            min = *(array1 + i), ++i;
        else
            min = *(array2 + j), ++j;
        *(array3 + i + j - 1) = min;
    }

    for (int y = i; y < N; ++y)
        *(array3 + y + N) = *(array1 + y);

    for (int z = j; z < N; ++z)
        *(array3 + z + N) = *(array2 + z);

    for (int i = 0; i < 2 * N; ++i)
        printf("%d ", *(array3 + i));

    return 0;
}
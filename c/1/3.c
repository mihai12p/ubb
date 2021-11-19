#include <stdio.h>

// 3.Write a program that computes out the largest and smallest values of 5 numbers read from the input.

int main()
{
    //                   INT_MAX                                INT_MIN
    //                      =                                      =
    int min = ((1 << ((sizeof(int) * 8) - 1)) + 1) * (-1), max = 1 << ((sizeof(int) * 8) - 1); // INT_MAX = (INT_MIN + 1) * (-1) [no overflow]
    for (int i = 0; i < 5; ++i)
    {
        int x;
        scanf("%d", &x);
        
        min = (x > min) ? min : x;
        max = (x < max) ? max : x;
    }

    printf("(int) Min: %d\n(int) Max: %d", min, max);

    return 0;
}
#include <stdio.h>

//4. Write a program that, given an integer n, computes the first n values from Fibonacci Series.

int main()
{
    int n;
    scanf("%d", &n);
    int f[n];
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i < n; ++i)
        f[i] = f[i-2] + f[i-1];

    for (int i = 0; i < n; ++i)
        printf("%d ", f[i]);
}

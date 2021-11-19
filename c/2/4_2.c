#include <stdio.h>

//4. Write a program that, given an integer n, computes the first n values from Fibonacci Series.

int fibo(int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;

    return fibo(n - 1) + fibo(n - 2);
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        printf("%d ", fibo(i));
}

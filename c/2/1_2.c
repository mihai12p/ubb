#include <stdio.h>
#include <limits.h>

//1. Write a program to read a set of integers and print the maximum and minimun value.

int smaller(int a, int b)
{
    if (a > b)
        return b;

    return a;
}

int greater(int a, int b)
{
    if (a > b)
        return a;
    
    return b;
}

int main()
{
    int n, min = INT_MAX, max = INT_MIN;
    scanf("%d", &n);
    int v[n];
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", v+i);
        min = smaller(min, v[i]);
        max = greater(v[i], max);
    }
    printf("(int) Minimum: %d\n(int) Maximum: %d", min, max);
}
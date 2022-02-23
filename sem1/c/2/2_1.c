#include <stdio.h>
#include <string.h>
#include <math.h>

//2. Use Eratosthenes's sieve to determine all prime numbers less than a given integer.

void markPrimes(int *isPrime, int x, int n, int i)
{
    if (x <= n)
    {
        isPrime[x] = 0;
        markPrimes(isPrime, x + i, n, i);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int isPrime[n + 1];
    memset(isPrime, 1, sizeof(isPrime));
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i * i <= n; ++i)
        if (isPrime[i])
            markPrimes(isPrime, i * i, n, i);

    for (int i = 2; i < n; ++i)
        if (isPrime[i])
            printf("%d ", i);
}
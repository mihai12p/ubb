#include <stdio.h>
#include <string.h>
#include <math.h>

//2. Use Eratosthenes's sieve to determine all prime numbers less than a given integer.

int main()
{
    int n;
    scanf("%d", &n);
    int isPrime[n + 1];
    memset(isPrime, 1, sizeof(isPrime));
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i * i <= n; ++i)
        if (isPrime[i])
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = 0;

    for (int i = 2; i < n; ++i)
        if (isPrime[i])
            printf("%d ", i);
}
#include <stdio.h>

double x_at_n(float x, int n)
{
    if (n == 1)
        return x;
    else if (n % 2)
        return x * x_at_n(x * x, n / 2);
    else
        return x_at_n(x * x, n / 2);
}

int main()
{
    float x;
    printf("x = ");
    scanf_s("%f", &x);

    int n;
    printf("n = ");
    scanf_s("%d", &n);

    printf("x ^ n = %lf", x_at_n(x, n));

    return 0;
}
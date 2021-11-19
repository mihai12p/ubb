#include <stdio.h>

// 2.Read two integers and compute their sum, average and sum of the squares of the numbers.

int main()
{
    int first, second;
    scanf("%d %d", &first, &second);
    printf("(long int) Sum: %ld", first + second);
    printf("\n(float) Average: %.2f", (first + second) / 2.0);

    long long firstSquare = first, secondSquare = second;
    firstSquare *= firstSquare, secondSquare *= secondSquare;

    printf("\n(long long int) Sum of squares: %lld", firstSquare + secondSquare);

    return 0;
}
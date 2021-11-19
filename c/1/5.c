#include <stdio.h>

// 5. Knowing that we have coins of 1, 2 and 5 units, determine the minimum number of coins to pay a given amount.

int main()
{
    int min = 0, amount;
    scanf("%d", &amount);

    min += amount / 5;
    amount %= 5;
    
    min += amount / 2;
    amount %= 2;

    min += amount;

    printf("The minimum number of coins to pay the given amount is %d.", min);

    return 0;
}
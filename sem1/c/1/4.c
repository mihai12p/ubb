#include <stdio.h>

// 4. Given as input a floating number of centimeters, print the corresponding number of feet (integer) and inches (floating, 1 decimal), 
// with the inches given to an accuracy of one decimal place. Assume 2.54 centimeters per inch, and 12 inches per foot.

int main()
{
    float cms;
    scanf("%f", &cms);

    float inches = ((cms / 2.54) * 10 + .5) / 10.0;
    printf("(int) feet: %d\n(float) inches: %.1f", (int)(inches / 12), inches);

    return 0;
}
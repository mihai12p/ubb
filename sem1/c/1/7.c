#include <stdio.h>
#include <math.h>

// 7. Being given the values of the diagonals of a diamond shape (romb), compute the area and perimeter of the diamond shape.

int main()
{
    // A = d1 * d2 / 2
    // P = sqrt(d1^2 + d2^2) * 2

    float d1, d2;
    scanf("%f %f", &d1, &d2);

    printf("(float) Area: %.3f\n(float) Perimeter: %.3f", d1 * d2 / 2.0, sqrtf(d1 * d1 + d2 * d2) * 2.0);
                                                                                                        
    return 0;
}
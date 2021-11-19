#include <stdio.h>

// 1.Write a program to read a number of units of length (a float) and print out the area of a circle with that radius. 
// Assume that the value of pi is 3.14159. After that, change the type to double and compare the results.

#define PI 3.14159

int main()
{
    float fR;
    printf("(float) Radius: ");
    scanf("%f", &fR); // input: 12.1212
    printf("(float) Area: %f", PI*fR*fR); // output: 461.573335

    double dR;
    printf("\n\n(double) Radius: ");
    scanf("%lf", &dR); // input: 12.1212
    printf("(double) Area: %lf", PI*dR*dR); // output: 461.573365

    return 0;
}
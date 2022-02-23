#include <stdio.h>
#include <string.h>

// 3.Write a program that reverses a string (array of char) entered by the user.

#define N 256
char array[N];

int main()
{
    gets(array);
    int arrayLen = strlen(array);
    for (int i = 0; i < arrayLen / 2; ++i)
    {
        char swap = array[i];
        array[i] = array[arrayLen - i - 1];
        array[arrayLen - i - 1] = swap;
    }
    
    printf("%s", array);

    return 0;
}
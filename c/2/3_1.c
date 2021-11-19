#include <stdio.h>
#include <string.h>

//3. Write a program to read an integer with max 3 digits and print the value in words (111 will be printed as one hundred and eleven)

int main()
{
    int n;
    do scanf("%d", &n);
    while (n < -999 || n > 999);

    const char words[21][10] = {"zero ", "one ", "two ", "three ", "four ", "five ", "six ", "seven ", "eight ", "nine ", "ten ", "eleven ", 
                                "twelve ", "thirteen ", "fourteen ", "fifteen ", "sixteen ", "seventeen ", "eighteen ", "nineteen ", "twenty "};
    const char words2[10][8] = {"ten ", "twenty ", "thirty ", "forty ", "fifty ", "sixty ", "seventy ", "eighty ", "ninety ", "hundred "};

    int last_digit = -1000, middle_digit = -1000, first_digit = -1000;
    char print_string[32] = "";

    if (n < 0)
    {
        strcat(print_string, "minus ");
        n = -n;
    }

    while (n)
    {
        if (last_digit == -1000)
            last_digit = n % 10;
        else if (middle_digit == -1000)
            middle_digit = n % 10;
        else if (first_digit == -1000)
            first_digit = n % 10;

        n /= 10;
    }

    if (first_digit != -1000)
    {
        strcat(print_string, words[first_digit]);
        strcat(print_string, "hundred ");
    }
    if (middle_digit != -1000)
    {
        if (middle_digit == 1)
            strcat(print_string, words[middle_digit*10+last_digit]);
        else if (middle_digit > 1)
        {
            strcat(print_string, words2[middle_digit-1]);
            if (last_digit)
                strcat(print_string, words[last_digit]);
        }
        else if (last_digit)
            strcat(print_string, words[last_digit]);
    }
    else if (last_digit != -1000)
        strcat(print_string, words[last_digit]);
    else
        strcat(print_string, words[0]);

    printf("%s", print_string);
}

/*
16. Se da un sir care contine n reprezentari binare pe 8 biti date ca sir de caractere.
Sa se obtina un sir care contine numerele corespunzatoare reprezentarilor binare.
Exemplu:
Se da: '10100111b', '01100011b', '110b', '101011b'
Se stocheaza: 10100111b, 01100011b, 110b, 101011b
*/

#include <stdio.h>
#include <string.h>

int stocheaza(int len, char* sir, int* sirNumere);

int main()
{
                        //    'b''\0'
    char reprezentare[100][8 + 1 + 1] = { 0 };
    int n, sirNumere[100] = { 0 };
    printf("N = ");
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        printf("reprezentare #%d = ", i + 1);
        scanf("%s", reprezentare[i]);
        stocheaza(strlen(reprezentare[i]), reprezentare[i], sirNumere + i); // sirNumere[i] va contine numarul corespunzator reprezentarii binare din reprezentare[i]
    }

    printf("\n");
    for (int i = 0; i < n; ++i)
        printf("#%d %s -> %d\n", i + 1, reprezentare[i], sirNumere[i]);

    return 0;
}
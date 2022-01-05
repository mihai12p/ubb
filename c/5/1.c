#include <stdio.h>
#include <string.h>

// 1.Using file objects and I/O, solve at least one of the following:
// Display odd numbered lines backwards from a given file (liniile impare in ordine inversa).

int main()
{
    FILE* fp = fopen("file.txt", "r");
    if (!fp)
        return -1;

    int odd = 0;
    char line[256] = { 0 };
    while (fgets(line, 256, fp))
        if (++odd % 2)
        {
            line[strlen(line) - 1] = '\0'; // remove '\n' character from each line
            int len = strlen(line);
            for (int i = 0; i < len / 2; ++i)
            {
                char swap = line[i];
                line[i] = line[len - i - 1];
                line[len - i - 1] = swap;
            }
            printf("%s\n", line);
        }

    fclose(fp);

    return 0;
}
#include <stdio.h>
#include <string.h>

// 2.Using file objects and I/O, solve at least one of the following:
// Replace all vowels with # in the text read from a given file.

int main()
{
    FILE* fp = fopen("file.txt", "r+");
    if (!fp)
        return -1;

    char c;
    const char vowels[] = "aeiouAEIOU";
    while ((c = fgetc(fp)) != EOF)
        if (strchr(vowels, c))
        {
            fseek(fp, -1, SEEK_CUR);
            fputs("#", fp);
            fseek(fp, 1, SEEK_CUR);
        }

    fclose(fp);

    return 0;
}
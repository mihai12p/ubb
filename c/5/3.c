#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// 3.Using file objects and I/O, solve at least one of the following:
// Replace even numbers with | in the text read from a given file.

int main()
{
    FILE* fp = fopen("file.txt", "r");
    if (!fp)
        return -1;

    FILE* fTemp = fopen("file.tmp", "w");
    if (!fp)
    {
        fclose(fp);
        return -1;
    }

    char line[256] = { 0 };
    while (fgets(line, 256, fp))
    {
        char* p = line;
        while (*p)
        {
            if (isdigit(*p))
            {
                char* start = p;
                int num_len = 0;
                if (p - 1 && *(p - 1) == '-') ++num_len, start = p - 1;
                int x = strtol(p, &p, 10);
                if (x % 2)
                    continue;

                int copy_x = x;
                while (copy_x)
                {
                    ++num_len;
                    copy_x /= 10;
                }
                *start = '|';
                for (int i = 1; i < strlen(start) - num_len + 1; ++i) start[i] = start[i + num_len - 1];
                start[strlen(start) - num_len + 1] = '\0';
                p = line;
            }
            else ++p;
        }
        fputs(line, fTemp);
    }

    fclose(fTemp);
    fclose(fp);

    remove("file.txt");
    rename("file.tmp", "file.txt");
    remove("file.tmp");

    return 0;
}
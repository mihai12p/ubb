#include <stdio.h>

// 6. Given the natural number h and m, that represent the current time expressed in hours and minutes, compute the time after x hours and y minutes.

int main()
{
    unsigned h, m, x, y;
    scanf("%u %u %u %u", &h, &m, &x, &y);

    x += y / 60;
    y %= 60;

    int trM = (m + y > 59) ? 1 : 0;
    m += y - 60 * trM;

    int trH = (h + x + trM > 23) ? 1 : 0;
    h += x + trM - 24 * trH;

    printf("computed time: %02d:%02d", h, m);

    return 0;
}
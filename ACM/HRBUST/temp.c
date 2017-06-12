#include <stdio.h>
int main(void)
{
    int i, a, b, k, c, re;
    //printf("%d\n\n", 25 % 10 % 8 % 5 % 7); //14 % 10 = 4 < 9; 27 % 10 < 9 BU 27 % 10 > 5
    i = 9 % 5 % 7;
    b = 14;
    a = 10;
    while (b > a)
    {
        for (k = 0, re = 2, c = a; b >= c; c <<= 1)
        {
            if (b - c < a)
            {
                re = b - c;
                k = 1;
                break;
            }
        }
        if (b - c < a && k == 1)
            break;
        b -= c >> 1;
    }
    if (b == a)
        re = 0;
    printf("%d", re);
    return 0;
}
/*
while (b > a[tu])
{
    for (k = 0, c = a[tu]; b >= c; c <<= 1, k++)
    {
        if (b - c < a[tu])
        {
            remainder = b - c;
            break;
        }
    }
    if (b - c < a[tu])
        break;

    b -= c >> 1;
}
b = remainder;

1
4
10 8 5 7
5
14 8 27 11 25

*/
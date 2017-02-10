#include <stdio.h>
long long num[1001000] = {0};
int main(void)
{
    int n, i;
    num[3] = 1;
    num[4] = 3;
    while (~scanf("%d", &n))
    {
        if (n < 4)
        {
            printf("0\n");
            continue;
        }
        if (n == 4)
        {
            printf("1\n");
            continue;
        }
        if (n == 5)
        {
            printf("3\n");
            continue;
        }
        for (i = n; num[i] == 0; i--)
            ;
        //printf("i= %d\n", i);
        for (++i; i < n; i++)
        {
            num[i] = (i - 1) / 2 + (num[i - 1] - num[i - 2]) + num[i - 1];
            //printf("%2d: %4lld\n", i, num[i]);
        }
        printf("%lld\n", num[n - 1]);
    }
    return 0;
}
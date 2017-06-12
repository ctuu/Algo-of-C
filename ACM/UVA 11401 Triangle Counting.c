#include <stdio.h>
int main(void)
{
    int n, i;
    long long num[3] = {1, 3, 0};
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
        num[0] = 1;
        num[1] = 3;
        for (i = 6; i <= n; i++)
        {
            num[2] = i/2  - 1 + (num[1] - num[0]) + num[1] ;
            num[0] = num[1];
            num[1] = num[2];
        }
        printf("%lld\n", num[2]);
    }
    return 0;
}
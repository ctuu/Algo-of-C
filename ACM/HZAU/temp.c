#include <stdio.h>
unsigned int GCD(unsigned int a, unsigned int b);
unsigned int LCM(unsigned int a, unsigned int b);

int main(void)
{
    unsigned int num, ct, sum, su;
    while (~scanf("%d", &num))
    {
        for (su = 1, sum = 0, ct = 2; ct <= num; ct++)
        {
            sum = LCM(su, ct);
            //printf("%d: %d\n", ct, sum);
            su = sum;
        }
        printf("%d\n", sum);
    }
    return 0;
}
unsigned int GCD(unsigned int a, unsigned int b)
{
    if (b)
        while ((a %= b) && (b %= a))
            ;
    return a + b;
}

unsigned int LCM(unsigned int a, unsigned int b)
{
    return a * b / GCD(a, b);
}
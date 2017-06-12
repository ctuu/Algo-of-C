#include <stdio.h>
#include <stdlib.h>
long long GCD(long long a, long long b);
long long LCM(long long a, long long b);

int main(void)
{
    FILE * fp;
    if ((fp = fopen("wordy", "a+")) == NULL)
        {
            fprintf(stdout, "Can't open file.\n");
            exit(EXIT_FAILURE);
       }
    long long num, ct, sum, su;
    num = 100000000;
        for (su = 1, sum = 0, ct = 2; ct <= num; ct++)
        {
            sum = LCM(su, ct);
            fprintf(fp, "%lld,",sum % 4294967296);
            su = sum;
        }
        printf("%lld\n", sum % 4294967296);
    fclose(fp);
    return 0;
}
long long GCD(long long a, long long b)
{
    if (b)
        while ((a %= b) && (b %= a))
            ;
    return a + b;
}

long long LCM(long long a, long long b)
{
    return a * b / GCD(a, b);
}
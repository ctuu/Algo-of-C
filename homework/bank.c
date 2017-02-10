#include <stdio.h>
int main(void)
{
    double sum = 0;
    int count = 5;
    int ct = 12;
    for (;count > 0; count--, ct = 12)
    {
        sum += 1000.0;
        for (;ct > 0;ct--)
            sum /=  1.01875;
        printf("%f\n", sum);
    }
    printf("%f", sum);
    return 0;
}
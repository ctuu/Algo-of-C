#include <stdio.h>
int main(void)
{
    int num,t;
    int k = 2;
    int r = 2;
    scanf("%d",&num);
    while (num-- > 0)
    {
        while (--k > 0)
        {
            printf(" ");
        }
        r = r + 1;
        k = r;
        t = num ;
        num = 2 * num - 1;
        while (num-- > 0)
        {
           printf("#");
        }
        printf("\n");
        num = t; 
        num--;
    }
    return 0;
}

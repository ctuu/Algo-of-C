#include <stdio.h>
char queen[10][10] = {0};
_Bool pin[3][2 * 10] =  {0};
int co = 0;

void find(int x, int y, int NUM);
int main(void)
{
    int NUM;
    while(~scanf("%d", &NUM))
    {
        if (NUM == 0)
            return 0;
        find(0, 0, NUM);
        printf("%d\n", co);
        co = 0;
    }
    return 0;
}

void find(int x, int y, int NUM)
{
    int a, b;
    if (x < NUM)
    {
        for (y = 0; y < NUM; y++, a = 0)
        {
            if (pin[0][y] == 0 && pin[1][x + y] == 0 && pin[2][NUM - 1 + y - x] == 0)
            {
                pin[0][y] = pin[1][x + y] = pin[2][NUM - 1 + y - x] = a = 1;
                find(x + 1, 0, NUM);
                pin[0][y] = pin[1][x + y] = pin[2][NUM - 1 + y - x] = 0;
            }
        }
        if (a == 1)
            find(x + 1, 0, NUM);
    }
    else
        co++;
}
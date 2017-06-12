#include <stdio.h>
#include <string.h>
int main(void)
{
    int a, c;
    char ch[100];
    while (fgets(ch, 100, stdin) != NULL)
    {
        a = strlen(ch) - 1;
        ch[a] = '\0';
        for (a--; a >= 0; a--)
        {
            if (ch[a - 1] == ' ' || a == 0)
            {
                ch[a - 1] = '\0';
                for (c = a; ch[c] != '\0'; c++)
                {
                    printf("%c", ch[c]);
                    ch[c] = '\0';
                }
                printf(" ");
            }
        }
        printf("\b");
    }
    return 0;
}
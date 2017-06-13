#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

void uppercase(char *str)
{
    while (*str)
    {
        *str = toupper(*str);
        str++;
    }
}
void Get_ID(char *stuid)
{
    bool isN = 0;
    do
    {
        isN = 0;
        puts("Please enter Student's ID:");
        s_gets(stuid, 10);
        for (int i = 0; (stuid)[i] != '\0'; ++i)
        {
            if (!isdigit((stuid)[i]))
            {
                isN = 1;
                printf(" is not a number.");
                break;
            }
        }
    } while (isN != 0);
    return;
}

unsigned int Get_Int(void)
{
    unsigned int input;
    char ch;
    while (scanf("%d", &input) != 1)
    {
        while ((ch = getchar()) != '\n')
            putchar(ch);
        printf(" is not an integer.\nPlease enter an integer value: ");
    }
    return input;
}

char *s_gets(char *st, int n)
{
    char *ret_val;
    char *find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');
        if (find)
            *find = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}
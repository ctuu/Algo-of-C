#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"
static bool IsDigit(char *ch);
static bool Get_NULL(char *str);
void uppercase(char *str)
{
    while (*str)
    {
        *str = toupper(*str);
        str++;
    }
}

bool Get_ID(char *stuid)
{
    do
    {
        puts("Please enter Student's ID:");
        s_gets(stuid, LEN_ID);
        if (Get_NULL(stuid))
        {
            puts("Operation canceled.");
            return false;
        }
        if (!IsDigit(stuid))
            printf("ERROR: %s is not a number.\n", stuid);
    } while (!IsDigit(stuid));
    return true;
}

bool Get_Int(int *num)
{
    char ch_num[LEN_NUM];
    do
    {
        s_gets(ch_num, LEN_NUM);
        if (Get_NULL(ch_num))
        {
            puts("Operation canceled.");
            return false;
        }
        if (!IsDigit(ch_num))
            printf("ERROR: %s is not an integer.\nPlease enter an integer value:\n", ch_num);
    } while (!IsDigit(ch_num));
    *num = atoi(ch_num);
    return true;
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

static bool IsDigit(char *ch)
{
    for (int i = 0; (ch)[i] != '\0'; ++i)
        if (!isdigit((ch)[i]))
            return false;
    return true;
}

static bool Get_NULL(char *str)
{
    if (*str == '\0')
        return 1;
    return 0;
}
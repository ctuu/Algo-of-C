#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tel_item.h"
#include "tel_func.h"

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

bool Get_ID(int *id)
{
    char num[11];
    do
    {
        puts("Please enter ID:");
        s_gets(num, 11);
        if (Get_NULL(num))
        {
            puts("Operation canceled.");
            return false;
        }
        if (!IsDigit(num))
            printf("ERROR: %s is not an integer.\nPlease enter an integer value:\n", num);
    } while (!IsDigit(num));
    *id = atoi(num);
    return true;
}

bool Get_Name(char *name)
{
    puts("Please enter Name:");
    s_gets(name, LEN_NAME);
    if (Get_NULL(name))
    {
        puts("Operation canceled.");
        return false;
    }
    return true;
}


bool Get_Phone(char *phone)
{
    do
    {
        puts("Please enter Phone number:");
        s_gets(phone, LEN_PHONE);
        if (Get_NULL(phone))
        {
            puts("Operation canceled.");
            return false;
        }
        if (!IsDigit(phone))
            printf("ERROR: %s is not an integer.\nPlease enter an integer value:\n", phone);
    } while (!IsDigit(phone));
    return true;
}

bool Get_QQ(char *qq)
{
    do
    {
        puts("Please enter QQ:");
        s_gets(qq, LEN_QQ);
        if (Get_NULL(qq))
        {
            puts("Operation canceled.");
            return false;
        }
        if (!IsDigit(qq))
            printf("ERROR: %s is not an integer.\nPlease enter an integer value:\n", qq);
    } while (!IsDigit(qq));
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
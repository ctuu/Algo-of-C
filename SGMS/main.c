#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

char menu(void);
void Stu_Add(List *plist);
void Stu_Drop(List *plist);
void Stu_Modify(List *plist);
void Stu_Count(const List *plist);
void Stu_Display(const List *plist);
void Stu_Search(const List *plist);
void Stu_Sort(List *plist);
char *s_gets(char *st, int n);

int main(void)
{
    List stu;
    char choice;
    InitializeList(&stu);
    while ((choice = menu()) != 0)
    {
        switch (choice)
        case '1':;break;
    }
    EmptyTheList(stu);
    puts("Bye.");
    return 0;
}

char menu(void)
{
    int ch;

    puts("The Students' Grade Management System");
    puts("Enter the letter correspinding to your choice:");
    puts("1) add a record        2) delete a record");
    puts("3) search record   4) Modify record");
    puts("d) delete a pet     q) quit");
    while ((ch = getchar()) != EOF)
    {
        while (getchar() != '\n')
            continue;
        ch = tolower(ch);
        if (strchr("alfndq", ch) == NULL)
            puts("Please enter an a, l, f, n, d, or q:");
        else
            break;
    }
    if (ch == EOF)
        ch = 'q';

    return ch;
}


char * s_gets(char * st, int n)
{
    char * ret_val;
    char * find;

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
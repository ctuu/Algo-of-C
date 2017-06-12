#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

char Menu(void);
void Input_Item(Item *item);

void Stu_Add(List *plist);
void Stu_Delete(List *plist);
void Stu_Search(const List *plist);
void Stu_Modify(List *plist);
void Stu_Sort(List *plist);
void Stu_insert(List *plist);
void Stu_Display(const List *plist);
void Stu_Statistic(const List *plist);

void uppercase(char *str);
char *s_gets(char *st, int n);
void Item_Display(const Item *item);
unsigned int Get_Int(void);
void *Get_ID(char *st);

int main(void)
{
    List stu;
    char choice;
    InitializeList(&stu);
    while ((choice = menu()) != '0')
    {
        switch (choice)
        {
        case '1':
            Stu_Add(&stu);
            break;
        case '2':
            Stu_Delete(&stu);
            break;
        case '3':
            Stu_Search(&stu);
            break;
        case '4':
            Stu_Modify(&stu);
            break;
        case '5':
            Stu_Sort(&stu);
            break;
        case '6':
            Stu_insert(&stu);
            break;
        case '7':
            Stu_Display(&stu);
            break;
        case '8':
            Stu_Statistic(&stu);
            break;
        default:
            puts("Switching error");
        }
    }
    EmptyTheList(stu);
    puts("Bye.");
    return 0;
}

char Menu(void)
{
    char ch;

    puts("The Students' Grade Management System");
    puts("Enter the letter correspinding to your choice:");
    puts("1) add     record        2) delete record");
    puts("3) search  record        4) modify record");
    puts("5) sort    record        6) insert record");
    puts("7) display record        8) statistics");
    puts("0) quit");
    while ((ch = getchar()) != EOF)
    {
        while (getchar() != '\n')
            continue;
        ch = tolower(ch);
        if (strchr("123456780", ch) == NULL)
            puts("Please enter 0 ~ 8:");
        else
            break;
    }
    if (ch == EOF)
        ch = '0';

    return ch;
}

void Stu_Add(List *plist)
{
    Item temp;
    if (ListIsFull(plist)
        puts("No space in the program!");
    else
    {
        input(&temp);
        if (ListAddItem(temp, plist))
            puts("Successful.");
        else
            puts("Fail to add record");
    }
}

void Input_Item(Item *item)
{
    Get_ID(item->StuID);
    puts("Please enter Student's Name:");
    s_gets(item->Name, 15);
    uppercase(item->Name);
    puts("Please enter Student's C language grade:");
    item->grade->C_lang = Get_Int();
    puts("Please enter Student's Math grade:");
    item->grade->Math = Get_Int();
    puts("Please enter Student's English grade:");
    item->grade->Eng = Get_Int();
    puts("Please enter Student's Rating:");
    item->Rating = Get_Int;
    item->grade->Total = item->grade->C_lang + item->grade->Math + item->grade->Eng;
    item->grade->Ave = item->grade->(float)Total / 3;
}

void *Get_ID(char *stuid)
{
    bool isN = 0;
    do
    {
        isN = 0;
        puts("Please enter Student's ID:");
        s_gets(stuid, 10);
        for (int i = 0; (stuid)[i] != '\0'; ++i)
            if (!isdigit((stuid)[i])
            {
                isN = 1;
                printf(" is not a number.");
                break;
            }
    } while (isN != 0);
}

unsigned int Get_Int(void)
{
    unsigned int input;
    char ch while (scanf("%d", &temp) != 1)
    {
        while ((ch = getchar()) != '\n')
            putchar(ch);
        printf(" is not an integer.\nPlease enter an integer value: ");
    }
    return input;
}

void Stu_Delete(List *plist)
{
    Item temp;
    if (ListIsEmpty(plist))
    {
        puts("No entries!");
        return;
    }

    puts("Please enter the ID of Student you wish to delete:");
    Get_ID(temp.StuID);
    printf("ID %s ", temp.StuID);
    if (ListDeleteItem(&temp, plist)
        printf("is dropped from the System.\n");
    else
        printf("is not a member.\n");
}
void Stu_Search(const List *plist)
{
    Item temp;
    if (ListIsEmpty)
    {
        puts("No entries!");
        return;
    }
    puts("Please choice the way of search: ");
    puts("1) ID           2) Name");
    char ch;
    while ((ch = getchar()) != EOF)
    {
        while (getchar() != '\n')
            continue;
        ch = tolower(ch);
        if (strchr("12", ch) == NULL)
            puts("Please enter 1 or 2:");
        else
            break;
    }
    if (ch == '1')
    {
        Node *found = NULL;
        Get_ID(temp.StuID);
        found = ListSeekItem(&temp, plist);
        if (found == NULL)
            printf("ID %s is not a member.\n", temp.StuID);
        else
            Item_Display(found->item);
    }
    else
    {
        s_gets(temp.Name, 15);
        uppercase(temp.Name);
    }
}
void Stu_Modify(List *plist)
{
}
void Stu_Sort(List *plist)
{
}
void Stu_insert(List *plist)
{
}
void Stu_Display(const List *plist)
{
    if (ListIsEmpty(stu))
        puts("No entries!");
    else
        ListTraverse(&stu, Item_Display);
}
void Stu_Statistic(const List *plist)
{
}

void uppercase(char *str)
{
    while (*str)
    {
        *str = toupper(*str);
        str++;
    }
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
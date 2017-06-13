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

void Item_Display(const Item *item);
void Title_Display(void);
bool Item_Name_Search(const Item *pi, const List *plist);
char Modify_Menu(void);

int main(void)
{
    List stu;
    char choice;
    InitializeList(&stu);
    while ((choice = Menu()) != '0')
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
    item->Rating = Get_Int();
    item->grade->Total = item->grade->C_lang + item->grade->Math + item->grade->Eng;
    item->grade->Ave = item->grade->(float)Total / 3;
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
        if (!Item_Name_Search(&temp, plist))
            printf("Name %s is not a member.\n", temp.Name);
    }
}

bool Item_Name_Search(const Item *pi, const List *plist)
{
    Node *look = *plist;
    if (look.next == NULL)
        return 0;
    while (look.next != NULL)
    {
        if (strcmp(pi->Name, look->item.Name) != 0)
        {
            look = look->next;
        }
        else
            Item_Display(look->item);
    }
    return 1;
}

void Stu_Modify(List *plist)
{
    if (ListIsEmpty)
    {
        puts("No entries!");
        return;
    }

    Item temp;
    Item *item;
    Get_ID(&temp);
    item = ListSeekItem(temp, plist);
    char choice;
    while ((choice = Modify_Menu()) != '0')
    {
        switch (choice)
        {
        case '1':
            Get_ID(item->StuID);
            break;
        case '2':
            puts("Please enter Student's Name:");
            s_gets(item->Name, 15);
            uppercase(item->Name);
            break;
        case '3':
            puts("Please enter Student's C language grade:");
            item->grade->C_lang = Get_Int();
            break;
        case '4':
            puts("Please enter Student's Math grade:");
            item->grade->Math = Get_Int();
            break;
        case '5':
            puts("Please enter Student's English grade:");
            item->grade->Eng = Get_Int();
            break;
        case '6':
            puts("Please enter Student's Rating:");
            item->Rating = Get_Int();
            break;
        default:
            puts("Switching error");
        }
        item->grade->Total = item->grade->C_lang + item->grade->Math + item->grade->Eng;
        item->grade->Ave = item->grade->(float)Total / 3;
    }
}

char Modify_Menu(void)
{
    puts("Please choice the data you want to modify: ");
    puts("1) ID                2) Name");
    puts("3) C Language grade  4) Math grade");
    puts("5) English grade     6) Rating");
    puts("0) cancel");
    char ch;
    while ((ch = getchar()) != EOF)
    {
        while (getchar() != '\n')
            continue;
        ch = tolower(ch);
        if (strchr("0123456", ch) == NULL)
            puts("Please enter 0 ~ 6:");
        else
            break;
    }
    if (ch == EOF)
        ch = '0';
    return ch;
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
    {
        Title_Display();
        ListTraverse(&stu, Item_Display, 0);
    }
}

void Item_Display(const Item *item)
{
    printf("%10s %15s %3d %3d %3d %3d %f\n", item->StuID, item->Name, item->grade->C_lang, item->grade->Math, item->grade->Eng, item->grade->Total, item->grade->Ave);
}
void Title_Display(void)
{
    puts("ID    Name    C Language grade    Math grade    English grade    Total grade    Average grade    Rating");
}
void Stu_Statistic(const List *plist)
{
}

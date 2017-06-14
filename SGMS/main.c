#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

bool Stu_Add(List *plist);
void Stu_Delete(List *plist);
void Stu_Search(const List *plist);
void Stu_Modify(List *plist);
void Stu_Sort(List *plist);
void Stu_insert(List *plist);
void Stu_Display(const List *plist);
void Stu_Statistic(const List *plist);

bool Input_Item(Item *item, List *plist);
void Item_Display(const Item item);
void Title_Display(void);

char Menu(void);
char Modify_Menu(void);
char Sort_Menu(void);

int main(void)
{
    List stu;
    InitializeList(&stu);
    char chooce;
    while ((chooce = Menu()) != '0')
    {
        switch (chooce)
        {
        case '1':
            while (Stu_Add(&stu))
            {
                printf("enter 'Y' to add next record(other key to cancel): ");
                char temp[2];
                if (s_gets(temp, 2) == NULL || temp[0] == '\0' || strchr("yY", temp[0]) == NULL)
                    break;
            }
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
            puts("ERROR: Switching error");
        }
        printf("\npress ENTER to continue... ");
        while (getchar() != '\n')
            continue;
    }
    EmptyTheList(&stu);
    puts("Bye.");
    return 0;
}

char Menu(void)
{
    char ch;

    puts("The Students' Grade Management System");
    puts("Enter the letter correspinding to your choice:");
    puts("1) add     record             2) delete record");
    puts("3) search  record             4) modify record");
    puts("5) sort    record             6) insert record");
    puts("7) display record             8) statistics");
    puts("0) quit");
    while ((ch = getchar()) != EOF)
    {
        while (getchar() != '\n')
            continue;
        ch = tolower(ch);
        if (strchr("123456780", ch) == NULL)
            puts("ERROR: Please enter 1 ~ 8 or 0:");
        else
            break;
    }
    if (ch == EOF)
        ch = '0';

    return ch;
}

bool Stu_Add(List *plist)
{
    Item temp;

    if (ListIsFull(plist))
        puts("ERROR: No space in the program!");
    else
    {
        if (!Input_Item(&temp, plist))
            return false;
        if (ListAddItem(&temp, plist))
        {
            puts("Successful.");
            return true;
        }
        else
            puts("ERROR: Fail to add record.");
    }
    return false;
}

bool Input_Item(Item *item, List *plist)
{
    do
    {
        if (!Get_ID(item->StuID))
            return false;
        if (InList(item, plist, seek_bID))
            printf("ERROR: ID %s is exist.\n", item->StuID);
    } while (InList(item, plist, seek_bID));

    puts("Please enter Student's Name:");
    if (s_gets(item->Name, LEN_NAME) == NULL || item->Name[0] == '\0')
    {
        puts("Operation canceled");
        return false;
    }
    uppercase(item->Name);
    puts("Please enter Student's C language grade:");
    if (!Get_Int(&item->grade.C_lang))
        return false;
    puts("Please enter Student's Math grade:");
    if (!Get_Int(&item->grade.Math))
        return false;
    puts("Please enter Student's English grade:");
    if (!Get_Int(&item->grade.Eng))
        return false;
    puts("Please enter Student's Rating:");
    if (!Get_Int(&item->Rating))
        return false;
    item->grade.Total = item->grade.C_lang + item->grade.Math + item->grade.Eng;
    item->grade.Ave = (float)item->grade.Total / 3;
    return true;
}

void Stu_Delete(List *plist)
{
    Item temp;
    if (ListIsEmpty(plist))
    {
        puts("ERROR: No entries!");
        return;
    }
    Stu_Display(plist);
    puts("Please enter the ID of Student you wish to delete:");
    if (!Get_ID(temp.StuID))
        return;
    if (ListDeleteItem(&temp, plist))
        printf("ID %s is dropped from the System.\n", temp.StuID);
    else
        printf("ERROR: Id %s is not a member.\n", temp.StuID);
}

void Stu_Search(const List *plist)
{
    Item temp;
    if (ListIsEmpty(plist))
    {
        puts("ERROR: No entries!");
        return;
    }

    puts("Please chooce the way of search: ");
    puts("1) ID           2) Name");
    char ch;
    while ((ch = getchar()) != EOF)
    {
        while (getchar() != '\n')
            continue;
        ch = tolower(ch);
        if (strchr("12", ch) == NULL)
            puts("ERROR: Please enter 1 or 2:");
        else
            break;
    }
    if (ch == '1')
    {
        Node *found = NULL;
        if (!Get_ID(temp.StuID))
            return;
        found = ListSeekSet(&temp, plist, seek_bID);
        if (found == NULL)
            printf("ERROR: ID %s is not a member.\n", temp.StuID);
        else
        {
            Title_Display();
            Item_Display(found->item);
        }
    }
    else
    {
        puts("Please enter Student's Name:");
        if (s_gets(temp.Name, LEN_NAME) == NULL || temp.Name[0] == '\0')
        {
            puts("Operation canceled");
            return false;
        }
        uppercase(temp.Name);
        if (!InList(&temp, plist, seek_bName))
            printf("ERROR: Name %s is not a member.\n", temp.Name);
        else
        {
            Title_Display();
            ListSeekMultiSet(&temp, plist, seek_bName, Item_Display);
        }
    }
}

void Stu_Modify(List *plist)
{
    if (ListIsEmpty(plist))
    {
        puts("ERROR: No entries!");
        return;
    }
    Stu_Display(plist);

    Item temp;
    Node *fnode;
    Get_ID(temp.StuID);
    fnode = ListSeekSet(&temp, plist, seek_bID);
    if (fnode == NULL)
    {
        printf("ERROR: ID %s is not a member.\n", temp.StuID);
        return;
    }
    Title_Display();
    Item_Display(fnode->item);

    char chooce;
    while ((chooce = Modify_Menu()) != '0')
    {
        switch (chooce)
        {
        case '1':
            if (!Get_ID(temp.StuID))
                break;
            if (!InList(&temp, plist, seek_bID))
                strncpy(fnode->item.StuID, temp.StuID, LEN_ID);
            else
            {
                printf("ERROR: ID %s is exist.\n", temp.StuID);
                continue;
            }
            break;
        case '2':
            puts("Please enter Student's Name:");
            if (s_gets(fnode->item.Name, LEN_NAME) == NULL || fnode->item.Name[0] == '\0')
            {
                puts("Operation canceled");
                break;
            }
            uppercase(fnode->item.Name);
            break;
        case '3':
            puts("Please enter Student's C language grade:");
            if (!Get_Int(&fnode->item.grade.C_lang))
                break;
            break;
        case '4':
            puts("Please enter Student's Math grade:");
            if (!Get_Int(&fnode->item.grade.Math))
                break;
            break;
        case '5':
            puts("Please enter Student's English grade:");
            if (!Get_Int(&fnode->item.grade.Eng))
                break;
            break;
        case '6':
            puts("Please enter Student's Rating:");
            if (!Get_Int(&fnode->item.Rating))
                break;
            break;
        default:
            puts("ERROR: Switching error");
        }
        fnode->item.grade.Total = fnode->item.grade.C_lang + fnode->item.grade.Math + fnode->item.grade.Eng;
        fnode->item.grade.Ave = (float)fnode->item.grade.Total / 3;
        Title_Display();
        Item_Display(fnode->item);
    }
}

char Modify_Menu(void)
{
    puts("Please chooce the data you want to modify: ");
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
            puts("ERROR: Please enter 1 ~ 6 or 0:");
        else
            break;
    }
    if (ch == EOF)
        ch = '0';
    return ch;
}

void Stu_Sort(List *plist)
{
    if (ListIsEmpty(plist))
    {
        puts("ERROR: No entries!");
        return;
    }
    Stu_Display(plist);
    char chooce;
    while ((chooce = Sort_Menu()) != '0')
    {
        switch (chooce)
        {
        case '1':
            ListSort(plist, Cmp_bID);
            break;
        case '2':
            ListSort(plist, Cmp_bName);
            break;
        case '3':
            ListSort(plist, Cmp_bCG);
            break;
        case '4':
            ListSort(plist, Cmp_bMG);
            break;
        case '5':
            ListSort(plist, Cmp_bEG);
            break;
        case '6':
            ListSort(plist, Cmp_bTG);
            break;
        case '7':
            ListSort(plist, Cmp_bRat);
            break;
        }
        Stu_Display(plist);
    }
}

char Sort_Menu(void)
{
    puts("Please chooce the Sorting criteria: ");
    puts("1) ID                2) Name");
    puts("3) C Language grade  4) Math grade");
    puts("5) English grade     6) Average/Total grade");
    puts("7) Rating            0) cancel");
    char ch;
    while ((ch = getchar()) != EOF)
    {
        while (getchar() != '\n')
            continue;
        ch = tolower(ch);
        if (strchr("01234567", ch) == NULL)
            puts("ERROR: Please enter 1 ~ 7 or 0:");
        else
            break;
    }
    if (ch == EOF)
        ch = '0';
    return ch;
}

void Stu_insert(List *plist)
{
    Stu_Display(plist);
    if (ListIsFull(plist))
    {
        puts("ERROR: No space in the program!");
        return;
    }

    Item temp;
    Node *fnode;
    if (!Get_ID(temp.StuID))
        return;
    fnode = ListSeekSet(&temp, plist, seek_bID);
    if (fnode == NULL)
    {
        printf("ERROR: ID %s is not a member.\n", temp.StuID);
        return;
    }

    if(!Input_Item(&temp, plist))
        return;
    if (ListInsertItem(&temp, fnode, plist))
        puts("Insert successful.");
    else
        puts("ERROR: Fail to insert record.");
}

void Stu_Display(const List *plist)
{
    if (ListIsEmpty(plist))
        puts("ERROR: No entries!");
    else
    {
        Title_Display();
        ListTraverse(plist, Item_Display, 0);
    }
}

void Title_Display(void)
{
    puts("|ID         |Name            |C Language Grade  |Math Grade  |English Grade  |Total Grade  |Average Grade  |Rating");
}
void Item_Display(const Item item)
{
    printf(" %-10s  %-15s", item.StuID, item.Name);
    printf("  %-3d                %-3d          %-3d             %-3d           %-5.2f", item.grade.C_lang, item.grade.Math, item.grade.Eng, item.grade.Total, item.grade.Ave);
    printf("           %-4d\n", item.Rating);
}
void Stu_Statistic(const List *plist)
{
    printf("size: %d\n", plist->size);
}

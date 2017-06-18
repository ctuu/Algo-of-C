#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tel_item.h"
#include "tel_func.h"
#include "list.h"

bool Tel_Add(List *plist); 
bool Tel_Delete(List *plist);
void Tel_Search(const List *plist);
bool Tel_Modify(List *plist);
bool Tel_Sort(List *plist);
bool Tel_insert(List *plist);
bool Tel_Display(const List *plist);

void Tel_Open(List *plist);
void Tel_Saved(const List *plist);
void Tel_Exit(List *plist);

bool Input_Item(Item *item, List *plist);
void Title_Display(void);
void Item_Display(const Item item);

char Menu(void);
char Search_Menu(void);
char Modify_Menu(void);
char Sort_Menu(void);

bool unsaved = 0;

int main(void)
{
    List tel;
    InitializeList(&tel);
    Tel_Open(&tel);
    char chooce;
    while ((chooce = Menu()) != '0')
    {
        printf("\n");
        switch (chooce)
        {
        case '1':
            while (Tel_Add(&tel))
            {
                unsaved = 1;
                printf("enter 'Y' to add next record(other key to cancel): ");
                char temp[2];
                if (s_gets(temp, 2) == NULL || temp[0] == '\0' || strchr("yY", temp[0]) == NULL)
                    break;
            }
            break;
        case '2':
            if (Tel_Delete(&tel))
                unsaved = 1;
            break;
        case '3':
            Tel_Search(&tel);
            break;
        case '4':
            if (Tel_Modify(&tel))
                unsaved = 1;
            break;
        case '5':
            if (Tel_Sort(&tel))
                unsaved = 1;
            break;
        case '6':
            if (Tel_insert(&tel))
                unsaved = 1;
            break;
        case '7':
            Tel_Display(&tel);
            break;
        case '8':
             Tel_Saved(&tel);
            break;
        default:
            puts("ERROR: Switching error");
        }
        printf("\npress ENTER to continue... ");
        while (getchar() != '\n')
            continue;
    }
    Tel_Exit(&tel);
    EmptyTheList(&tel);
    puts("Bye.");
    return 0;
}

char Menu(void)
{
    printf("\n----The Tel System----\n");
    puts("1) add     record             2) delete record");
    puts("3) search  record             4) modify record");
    puts("5) sort    record             6) insert record");
    puts("7) display record             8) save record ");
    puts("0) quit");
    puts("Enter the number to your choice(1 ~ 9 or 0):");

    char ch[2];
    while (s_gets(ch, 2) != NULL && ch[0] != '\0')
    {
        ch[0] = tolower(ch[0]);
        if (strchr("123456780", ch[0]) == NULL)
            puts("ERROR: Please enter 1 ~ 8 or 0:");
        else
            break;
    }
    if (ch[0] == '\0')
    {
        ch[0] = '0';
        puts("Operation canceled.");
    }
    return ch[0];
}

bool Tel_Add(List *plist)
{
    Item temp;

    if (ListIsFull(plist))
        return false;

    if (!Input_Item(&temp, plist))
        return false;

    if (ListAddItem(&temp, plist, seek_bID))
    {
        puts("Successful.");
        return true;
    }
    else
        puts("ERROR: Fail to add record.");
    return false;
}

bool Input_Item(Item *item, List *plist)
{
    do
    {
        if (!Get_ID(&item->ID))
            return false;
        if (InList(item, plist, seek_bID))
            printf("ERROR: ID %d is exist.\n", item->ID);
    } while (InList(item, plist, seek_bID));

    if (!Get_Name(item->Name))
        return false;
    if (!Get_Phone(item->Phone))
        return false;
    if (!Get_QQ(item->QQ))
        return false;

    return true;
}

bool Tel_Delete(List *plist)
{
    Item temp;
    if (ListStatus(plist))
        return false;
    Tel_Display(plist);
    puts("Please enter the ID of Person you wish to delete:");
    if (!Get_ID(&temp.ID))
        return false;
    if (ListDeleteItem(&temp, plist, seek_bID))
        printf("ID %d is dropped from the System.\n", temp.ID);
    else
        printf("ERROR: Id %d is not a member.\n", temp.ID);
    return true;
}

void Tel_Search(const List *plist)
{
    Item temp;
    if (ListStatus(plist))
        return false;
    char chooce;
    while ((chooce = Search_Menu()) != '0')
    {
        switch (chooce)
        {
        case '1':
            if (!Get_Name(temp.Name))
                return;

            if (!InList(&temp, plist, seek_bName))
                printf("ERROR: Name %s is not a member.\n", temp.Name);
            else
            {
                Title_Display();
                ListSeekMultiSet(&temp, plist, seek_bName, Item_Display);
            }
            break;
        case '2':
            if (!Get_Phone(temp.Phone))
                return;

            if (!InList(&temp, plist, seek_bPhone))
                printf("ERROR: Phone number %s is not a member.\n", temp.Phone);
            else
            {
                Title_Display();
                ListSeekMultiSet(&temp, plist, seek_bPhone, Item_Display);
            }
            break;
        case '3':
            if (!Get_QQ(temp.QQ))
                return;

            if (!InList(&temp, plist, seek_bQQ))
                printf("ERROR: QQ %s is not a member.\n", temp.QQ);
            else
            {
                Title_Display();
                ListSeekMultiSet(&temp, plist, seek_bQQ, Item_Display);
            }
            break;
        default:
            puts("ERROR: Switching error");
        }
    }
}

char Search_Menu(void)
{
    puts("--------------Search--------------");
    puts("1) Name              2) Phone");
    puts("3) QQ                0) cancel");
    puts("Please chooce the way of search:");
    char ch[2];
    while (s_gets(ch, 2) != NULL && ch[0] != '\0')
    {
        ch[0] = tolower(ch[0]);
        if (strchr("0123", ch[0]) == NULL)
            puts("ERROR: Please enter 1 ~ 3 or 0:");
        else
            break;
    }
    if (ch[0] == '\0')
    {
        ch[0] = '0';
        puts("Operation canceled.");
    }
    return ch[0];
}

bool Tel_Modify(List *plist)
{
    bool isMod = 0;
    if (ListStatus(plist))
        return false;
    Tel_Display(plist);

    Item temp;
    Node *fnode;
    if (!Get_ID(&temp.ID))
        return false;
    fnode = ListSeekSet(&temp, plist, seek_bID);
    if (fnode == NULL)
    {
        printf("ERROR: ID %d is not a member.\n", temp.ID);
        return false;
    }
    Title_Display();
    Item_Display(fnode->item);

    char chooce;
    while ((chooce = Modify_Menu()) != '0')
    {
        switch (chooce)
        {
        case '1':
            if (!Get_ID(&temp.ID))
                break;
            if (!InList(&temp, plist, seek_bID))
                fnode->item.ID = temp.ID;
            else
            {
                printf("ERROR: ID %d is exist.\n", temp.ID);
                continue;
            }
            isMod = 1;
            break;
        case '2':
            if (Get_Name(fnode->item.Name))
                isMod = 1;
            break;
        case '3':
            if (Get_Phone(fnode->item.Phone))
                isMod = 1;
            break;
        case '4':
            if (Get_QQ(fnode->item.QQ))
                isMod = 1;
            break;
        default:
            puts("ERROR: Switching error");
        }
        Title_Display();
        Item_Display(fnode->item);
    }
    if (isMod)
        return true;
    return false;
}

char Modify_Menu(void)
{
    puts("\n--------------Modify--------------");
    puts("1) ID                2) Name");
    puts("3) Phone             4) QQ");
    puts("0) cancel");
    puts("Please chooce the data you want to modify:");
    char ch[2];
    while (s_gets(ch, 2) != NULL && ch[0] != '\0')
    {
        ch[0] = tolower(ch[0]);
        if (strchr("01234", ch[0]) == NULL)
            puts("ERROR: Please enter 1 ~ 4 or 0:");
        else
            break;
    }
    if (ch[0] == '\0')
    {
        ch[0] = '0';
        puts("Operation canceled.");
    }
    return ch[0];
}

bool Tel_Sort(List *plist)
{
    bool isSort = 0;
    if (ListStatus(plist))
        return false;
    Tel_Display(plist);
    char chooce;
    while ((chooce = Sort_Menu()) != '0')
    {
        switch (chooce)
        {
        case '1':
            ListSort(plist, Cmp_bID);
            isSort = 1;
            break;
        case '2':
            ListSort(plist, Cmp_bName);
            isSort = 1;
            break;
        }
        Tel_Display(plist);
    }
    if (isSort)
        return true;
    return false;
}

char Sort_Menu(void)
{
    puts("\n--------------------Sort--------------------");
    puts("1) ID                2) Name");
    puts("0) cancel");
    puts("Please chooce the Sorting criteria(1, 2 or 0):");
    char ch[2];
    while (s_gets(ch, 2) != NULL && ch[0] != '\0')
    {
        ch[0] = tolower(ch[0]);
        if (strchr("012", ch[0]) == NULL)
            puts("ERROR: Please enter 1, 2 or 0: ");
        else
            break;
    }
    if (ch[0] == '\0')
    {
        ch[0] = '0';
        puts("Operation canceled.");
    }
    return ch[0];
}

bool Tel_insert(List *plist)
{
    if (ListStatus(plist))
        return false;

    if (!Tel_Display(plist))
        return false;

    Item temp;
    Node *fnode;
    puts("Select the location to insert:");
    if (!Get_ID(&temp.ID))
        return false;
    fnode = ListSeekSet(&temp, plist, seek_bID);
    if (fnode == NULL)
    {
        printf("ERROR: ID %d is not a member.\n", temp.ID);
        return false;
    }
    printf("Data will be insert before ID %d.\n", temp.ID);
    if (!Input_Item(&temp, plist))
        return false;
    if (ListInsertItem(&temp, fnode, plist, seek_bID))
    {
        puts("Insert successful.");
        return true;
    }
    else
        puts("ERROR: Fail to insert record.");
    return false;
}

bool Tel_Display(const List *plist)
{
    if (ListStatus(plist))
        return false;
    Title_Display();
    ListTraverse(plist, Item_Display, 0);
    return true;
}

void Title_Display(void)
{
    printf("|ID%8s |Name%10s |Phone%8s   |QQ\n", " ", " ", " ");
}
void Item_Display(const Item item)
{
    printf(" %-10d  %-15s %-16s %-15s", item.ID, item.Name, item.Phone, item.QQ);
	putchar('\n');
}

void Tel_Open(List *plist)
{
    FILE *fp;

    if ((fp = fopen("telbook.csv", "r")) == NULL)
    {
        if ((fp = fopen("telbook.csv", "a")) == NULL)
        {
            fprintf(stdout, "Can't open \"telbook\" file.\n");
            exit(EXIT_FAILURE);
        }
        //File_AddTitle(fp);
    }
    else
    {
        if (!feof(fp))
        {
            File_skip(fp);
            ListOpenFile(fp, plist, Item_open, seek_bID);
        }
    }
    if (fclose(fp) != 0)
        fprintf(stderr, "Erroe closing file.\n");
}

void Tel_Saved(const List *plist)
{
    FILE *fp;
    if ((fp = fopen("telbook.csv", "w")) == NULL)
    {
        fprintf(stdout, "Can't open \"telbook\" file.\n");
        exit(EXIT_FAILURE);
    }
    File_AddTitle(fp);
    ListSaveFile(fp, plist, Item_save);
    if (fclose(fp) != 0)
        fprintf(stderr, "Erroe closing file.\n");
    unsaved = 0;
}

void Tel_Exit(List *plist)
{
    if (unsaved == 1)
    {
        puts("File is not save.");
        printf("Do you want to save it?(y/n): ");
        char temp[2];
        if (s_gets(temp, 2) == NULL || temp[0] == '\0' || strchr("yY", temp[0]) == NULL)
            return;
        Tel_Saved(plist);
    }
    return;
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "17.12.8.h"

char menu(void);
void addpet(Tree *pt);
void droppet(Tree *pt);
void showpets(const Tree *pt);
void findpet(const Tree *pt);
void printitem(Item item);
void uppercase(char *str);
char *s_gets(char *st, int n);

int main(void)
{
    Tree pets;
    char choice;

    InitializeTree(&pets);
    while ((choice = menu()) != 'q')
    {
        switch (choice)
        {
        case 'a':
            addpet(&pets);
            break;
        case 'l':
            showpets(&pets);
            break;
        case 'f':
            findpet(&pets);
            break;
        case 'n':
            printf("%d pets in club\n",
                   TreeItemCount(&pets));
            break;
        case 'd':
            droppet(&pets);
            break;
        default:
            puts("Switching error");
        }
    }
    DeleteAll(&pets);
    puts("Bye.");

    return 0;
}

char menu(void)
{
    int ch;

    puts("Nerfville Pet Club Membership Program");
    puts("Enter the letter correspinding to your choice:");
    puts("a) add a pet        l) show list if pets");
    puts("n) number of pets   f) find pets");
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

void addpet(Tree *pt)
{
    Item temp;

    if (TreeIsFull(pt))
        puts("No room in the club!");
    else
    {
        puts("Please enter name of pet:");
        s_gets(temp.petname, SLEN);
        puts("Please enter pet kind:");
        s_gets(temp.petkind, SLEN);
        uppercase(temp.petname);
        uppercase(temp.petkind);
        // puts(temp.petname);
        // puts(temp.petkind);
        TreeAddItem(&temp, pt);
    }
}

void showpets(const Tree *pt)
{
    if (TreeIsEmpty(pt))
        puts("No entries!");
    else
        TreeTraverse(pt, printitem);
}

void printitem(Item item)
{
    printf("Pet: %-19s  Kind: %-19s\n", item.petname, item.petkind);
}

void findpet(const Tree *pt)
{
    Item temp;
    Trnode *exist_node;
    if (TreeIsEmpty(pt))
    {
        puts("No entries!");
        return;
    }
    puts("Please enter name of pet you wish to find:");
    s_gets(temp.petname, SLEN);
    uppercase(temp.petname);
    //printf("%s the %s ", temp.petname, temp.petkind);
    if ((exist_node = TreeSeekItem(&temp, pt).child) != NULL)
    {
        printf("Member List:\n");
        ListTraverse(&exist_node->list, printitem);
    }
    else
        printf("is not a member.\n");
}

void droppet(Tree *pt)
{
    Item temp;

    if (TreeIsEmpty(pt))
    {
        puts("No entries!");
        return;
    }

    puts("Please enter name of pet you wish to delete:");
    s_gets(temp.petname, SLEN);
    puts("Please enter pet kind:");
    s_gets(temp.petkind, SLEN);
    uppercase(temp.petname);
    uppercase(temp.petkind);
    printf("%s the %s ", temp.petname, temp.petkind);
    if (TreeDeleteItem(&temp, pt))
        printf("is dropped from the club.\n");
    else
        printf("is not a member.\n");
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
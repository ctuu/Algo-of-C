#ifndef LIST_H_
#define LISH_H_
#include <stdbool.h>

struct Grade 
{
    unsigned int C_lang;
    unsigned int Math;
    unsigned int Eng;
    unsigned int Total;
    float Ave;
};

typedef struct Student
{
    char StuID[10];
    char Name[15];
    struct Grade grade;
    int Rating;
} Item;

typedef struct node
{
    Item item;
    struct node * pre;
    struct node * next;
} Node;
//typedef Node * List;

typedef struct list
{
    Node * head;
    Node * tail;
    int size;
} List;

//list_api.c
void InitializeList(List *plist);
bool ListIsEmpty(const List *plist);
bool ListIsFull(const List *plist);
unsigned int ListItemCount(const List *plist);
bool ListAddItem(Item *item, List *plist);
void ListTraverse(const List *plist, void (*pfun)(Item item), bool inorder);
void EmptyTheList(List *plist);
bool InList(const Item *pi, const List *plist);
bool ListDeleteItem(const Item *pi, List *plist);
Node *ListSeekID(const Item *pi, const List *plist);
bool ListInsertItem(Item *item, Node *pnode, List *plist);
void ListSort(int i, int j, Node *pn_1, Node *pn_2, List *plist, bool (*cmp)(Item *a, Item *b));


//get_data.c
unsigned int Get_Int(void);
void Get_ID(char *st);
void uppercase(char *str);
char *s_gets(char *st, int n);

//stu_cmp.c
bool Cmp_bID(const Item *pn_a, const Item *pn_b);
bool Cmp_bName(const Item *pn_a, const Item *pn_b);
bool Cmp_bCG(const Item *pn_a, const Item *pn_b);
bool Cmp_bMG(const Item *pn_a, const Item *pn_b);
bool Cmp_bEG(const Item *pn_a, const Item *pn_b);
bool Cmp_bTG(const Item *pn_a, const Item *pn_b);
bool Cmp_bRat(const Item *pn_a, const Item *pn_b);
#endif
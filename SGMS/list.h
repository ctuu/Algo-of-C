//Code by ctuu
#ifndef LIST_H_
#define LISH_H_
#include <stdbool.h>

#define LEN_ID 10
#define LEN_NAME 15
#define LEN_NUM 4
struct Grade 
{
    int C_lang;
    int Math;
    int Eng;
    int Total;
    float Ave;
};

typedef struct Student
{
    char StuID[LEN_ID];
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
bool InList(const Item *pi, const List *plist, bool (*seek)(const Item *pi, const Item *pj));
bool ListDeleteItem(const Item *pi, List *plist);
Node *ListSeekSet(const Item *pi, const List *plist, bool (*seek)(const Item *pi, const Item *pj));
bool ListSeekMultiSet(const Item *pi, const List *plist, bool (*seek)(const Item *pi, const Item *pj), void(*pfun)(Item item));
bool ListInsertItem(Item *item, Node *pnode, List *plist);
void ListSort(List *plist, bool (*cmp)(const Item *a, const Item *b));


//get_data.c
bool Get_Int(int *num);
bool Get_ID(char *st);
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

//stu_seek.c
bool seek_bID(const Item *pi, const Item *pj);
bool seek_bName(const Item *pi, const Item *pj);
#endif
//Code by ctuu
#ifndef LIST_H_
#define LISH_H_
#include <stdbool.h>

#define LEN_ID 10
#define LEN_NAME 15
#define LEN_NUM 4

#define C_PASSED 60
#define MATH_PASSED 60
#define ENG_PASSED 60

typedef struct StuGrade 
{
    int C_lang;
    int Math;
    int Eng;
    int Total;
    float Ave;
} Grade;

typedef struct Student
{
    char StuID[LEN_ID];
    char Name[LEN_NAME];
    Grade grade;
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

void EmptyTheList(List *plist);

bool ListAddItem(Item *item, List *plist, bool (*u_seek)(const Item *pi, const Item *pj));
bool ListDeleteItem(const Item *pi, List *plist, bool (*u_seek)(const Item *pi, const Item *pj));
bool ListInsertItem(Item *item, Node *pnode, List *plist, bool (*u_seek)(const Item *pi, const Item *pj));

void ListTraverse(const List *plist, void (*pfun)(Item item), bool inorder);

Node *ListSeekSet(const Item *pi, const List *plist, bool (*u_seek)(const Item *pi, const Item *pj));
bool ListSeekMultiSet(const Item *pi, const List *plist, bool (*seek)(const Item *pi, const Item *pj), void(*pfun)(Item item));
bool InList(const Item *pi, const List *plist, bool (*u_seek)(const Item *pi, const Item *pj));


void ListSort(List *plist, bool (*cmp)(const Item *a, const Item *b));
Node *GetNextNode(Node *pnode, bool inorder);
Node *GetHead(const List *plist, bool inorder);

bool ListOpenFile(FILE *fp, List *plist, bool (*open)(FILE *fp, Item *pi), bool (*u_seek)(const Item *pi, const Item *pj));
bool ListSaveFile(FILE *fp, const List *plist, bool (*save)(FILE *fp, Item *pi));

#endif
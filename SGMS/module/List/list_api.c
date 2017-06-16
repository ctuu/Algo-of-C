//Code by ctuu
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

static void DeleteAllNodes(Node *head);

static Node *MakeNode(const Item *pi);
static void CopyToNode(Item item, Node *pnode);
static void AddNode(Node *new_node, Node *tail);


static void swapNode(Node *pn_i, Node *pn_j);
static void QuickSort(int i, int j, Node *pn_i, Node *pn_j, List *plist, bool (*cmp)(const Item *a, const Item *b));

void InitializeList(List *plist)
{
    plist->head = NULL;
    plist->tail = NULL;
    plist->size = 0;
}

bool ListIsEmpty(const List *plist)
{
    if (plist->head == NULL)
        return true;
    else
        return false;
}

bool ListIsFull(const List *plist)
{
    Node *pt;
    bool full;

    pt = (Node *)malloc(sizeof(Node));
    if (pt == NULL)
        full = true;
    else
        full = false;
    free(pt);

    return full;
}

unsigned int ListItemCount(const List *plist)
{
    return plist->size;
}
//module


void EmptyTheList(List *plist)
{
    if (plist != NULL)
        DeleteAllNodes(plist->head);
    plist->head = NULL;
    plist->tail = NULL;
    plist->size = 0;
}

static void DeleteAllNodes(Node *head)
{
    Node *psave;
    while (head != NULL)
    {
        psave = head->next;
        free(head);
        head = psave;
    }
}

//module


bool ListAddItem(Item *pi, List *plist, bool (*u_seek)(const Item *pi, const Item *pj))
{
    Node *new_node;
    if (ListIsFull(plist))
    {
        fprintf(stderr, "ERROR: List is full.\n");
        return false;
    }
    if (ListSeekSet(pi, plist, (*u_seek)) != NULL)
    {
        fprintf(stderr, "ERROR: Attempted to add duplicate item.\n");
        return false;
    }
    new_node = MakeNode(pi);
    if (new_node == NULL)
    {
        fprintf(stderr, "ERROR: Couldn't create node.\n");
        return false;
    }
    plist->size++;

    if (plist->head == NULL)
        plist->head = new_node;
    else
        AddNode(new_node, plist->tail);
    plist->tail = new_node;
    return true;
}

static Node *MakeNode(const Item *pi)
{
    Node *new_node;

    new_node = (Node *)malloc(sizeof(Node));
    if (new_node != NULL)
    {
        CopyToNode(*pi, new_node);
        new_node->pre = NULL;
        new_node->next = NULL;
    }
    return new_node;
}

static void CopyToNode(Item item, Node *pnode)
{
    pnode->item = item;
}

static void AddNode(Node *new_node, Node *tail)
{
    tail->next = new_node;
    new_node->pre = tail;
}

//module


bool ListDeleteItem(const Item *pi, List *plist, bool (*u_seek)(const Item *pi, const Item *pj))
{
    Node *look = NULL;
    look = ListSeekSet(pi, plist, (*u_seek));
    if (look == NULL)
        return false;
    plist->size--;
    if (look->pre == NULL)
    {
        if (look->next != NULL)
            plist->head = look->next;
        else
            plist->head = NULL;
    }
    else
        look->pre->next = look->next;

    if (look->next == NULL)
    {
        if (look->pre != NULL)
            plist->tail = look->pre;
        else
            plist->tail = NULL;
    }
    else
        look->next->pre = look->pre;

    free(look);
    return true;
}

//module


bool ListInsertItem(Item *pi, Node *pnode, List *plist, bool (*u_seek)(const Item *pi, const Item *pj))
{
    Node *new_node;
    if (ListIsFull(plist))
    {
        fprintf(stderr, "ERROR: List is full.\n");
        return false;
    }
    if (ListSeekSet(pi, plist, (*u_seek)) != NULL)
    {
        fprintf(stderr, "ERROR: Attempted to add duplicate item.\n");
        return false;
    }
    new_node = MakeNode(pi);
    if (new_node == NULL)
    {
        fprintf(stderr, "ERROR: Couldn't create node.\n");
        return false;
    }
    if (!InList(&pnode->item, plist, (*u_seek)))
    {
        fprintf(stderr, "ERROR: Node is not exist.\n");
        return false;
    }

    plist->size++;
    new_node->pre = pnode->pre;
    new_node->next = pnode;
    if (pnode->pre == NULL)
    {
        plist->head = new_node;
    }
    else
        pnode->pre->next = new_node;
    pnode->pre = new_node;
    return true;
}

//module


void ListTraverse(const List *plist, void (*pfun)(Item item), bool inorder)
{
    Node *pnode;
    if (!inorder)
        pnode = plist->head;
    else
        pnode = plist->tail;
    while (pnode != NULL)
    {
        (*pfun)(pnode->item);
        if (!inorder)
            pnode = pnode->next;
        else
            pnode = pnode->pre;
    }
}

//module


Node *ListSeekSet(const Item *pi, const List *plist, bool (*u_seek)(const Item *pi, const Item *pj))
{
    Node *look = plist->head;
    while (look != NULL)
    {
        if (!(*u_seek)(pi, &look->item))
            look = look->next;
        else
            break;
    }
    return look;
}

bool ListSeekMultiSet(const Item *pi, const List *plist, bool (*seek)(const Item *pi, const Item *pj), void (*pfun)(Item item))
{
    bool isDT = 0;
    Node *look = plist->head;
    while (look != NULL)
    {
        if ((*seek)(pi, &look->item))
        {
            isDT = 1;
            (*pfun)(look->item);
        }
        look = look->next;
    }
    return isDT;
}

bool InList(const Item *pi, const List *plist, bool (*u_seek)(const Item *pi, const Item *pj))
{
    return (ListSeekSet(pi, plist, (*u_seek)) == NULL) ? false : true;
}

//module


void ListSort(List *plist, bool (*cmp)(const Item *a, const Item *b))
{
    QuickSort(0, plist->size - 1, plist->head, plist->tail, plist, (*cmp));
}

Node *GetNextNode(Node *pnode, bool inorder)
{
    if (inorder)
    {
        if (pnode == NULL)
            return pnode;
        else
            return pnode->pre;
    }
    else
    {
        if (pnode == NULL)
            return pnode;
        else
            return pnode->next;
    }
}

Node *GetHead(const List *plist, bool inorder)
{
    if (inorder)
        return plist->tail;
    else
    return plist->head;
}

static void swapNode(Node *pn_i, Node *pn_j)
{
    Item temp;
    temp = pn_i->item;
    pn_i->item = pn_j->item;
    pn_j->item = temp;
}

static void QuickSort(int i, int j, Node *pn_i, Node *pn_j, List *plist, bool (*cmp)(const Item *a, const Item *b))
{
    int a = i;
    int b = j - 1;
    Node *pn_a = pn_i;
    Node *pn_b = GetNextNode(pn_j, 1);
    if (a < b)
    {
        while (a < b)
        {
            while (!(*cmp)(&pn_a->item, &pn_j->item) && a < b)
            {
                a++;
                pn_a = GetNextNode(pn_a, 0);
            }
            while ((*cmp)(&pn_b->item, &pn_j->item) && a < b)
            {
                b--;
                pn_b = GetNextNode(pn_b, 1);
            }
            if (!(*cmp)(&pn_j->item, &pn_a->item) && !(*cmp)(&pn_b->item, &pn_j->item))
            {
                swapNode(pn_a, pn_b);
            }
        }
        if ((*cmp)(&pn_a->item, &pn_j->item))
        {
            swapNode(pn_a, pn_j);
        }
        QuickSort(i, a, pn_i, pn_a, plist, (*cmp));
        QuickSort(b, j, pn_b, pn_j, plist, (*cmp));
    }
    else if (a == b)
    {
        if ((*cmp)(&pn_i->item, &pn_j->item))
        {
            swapNode(pn_i, pn_j);
        }
    }
}

//module


bool ListOpenFile(FILE *fp, List *plist, bool (*open)(FILE *fp, Item *pi), bool (*u_seek)(const Item *pi, const Item *pj))
{
    Item temp;
    while ((*open)(fp, &temp))
        if (!ListAddItem(&temp, plist, (*u_seek)))
            return false;
    puts("File read complete.");
    printf("Read %d records.\n", plist->size);
    return true;
}

bool ListSaveFile(FILE *fp,const List *plist, bool (*save)(FILE *fp, Item *pi))
{
    Node *head = GetHead(plist, 0);
    while (head != NULL)
    {
        (*save)(fp, &head->item);
        head = GetNextNode(head, 0);
    }
    puts("File saved.");
    return true;
}

//module
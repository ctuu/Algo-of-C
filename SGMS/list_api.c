#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
static void CopyToNode(Item item, Node *pnode);
static Node *MakeNode(const Item *pi);
static void swapNode(Node *pn_i, Node *pn_j);
static void AddNode(Node *new_node, Node *head);
static void DeleteAllNodes(Node *head);
static Node *NodeGetPre(Node *pnode);
static Node *NodeGetNext(Node *pnode);
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

bool ListAddItem(Item *pi, List *plist)
{
    Node *new_node;
    if (ListIsFull(plist))
    {
        fprintf(stderr, "List is full\n");
        return false;
    }
    if (ListSeekID(pi, plist) != NULL)
    {
        fprintf(stderr, "Attempted to add duplicate item\n");
        return false;
    }
    new_node = MakeNode(pi);
    if (new_node == NULL)
    {
        fprintf(stderr, "Couldn't create node\n");
        return false;
    }
    plist->size++;

    if (plist->head == NULL)
        plist->head = new_node;
    else
        AddNode(new_node, plist->head);
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

static void AddNode(Node *new_node, Node *head)
{
    while (head->next != NULL)
        head = head->next;

    head->next = new_node;
    new_node->pre = head;
}

bool InList(const Item *pi, const List *plist)
{
    return (ListSeekID(pi, plist) == NULL) ? false : true;
}

bool ListDeleteItem(const Item *pi, List *plist)
{
    Node *look = NULL;
    look = ListSeekID(pi, plist);
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

Node *ListSeekID(const Item *pi, const List *plist)
{
    Node *look = plist->head;
    while (look != NULL)
    {
        if (strcmp(pi->StuID, look->item.StuID) != 0)
        {
            look = look->next;
        }
        else
        {
            break;
        }
    }
    return look;
}

bool ListInsertItem(Item *pi, Node *pnode, List *plist)
{
    Node *new_node;
    if (ListIsFull(plist))
    {
        fprintf(stderr, "List is full\n");
        return false;
    }
    if (ListSeekID(pi, plist) != NULL)
    {
        fprintf(stderr, "Attempted to add duplicate item\n");
        return false;
    }
    new_node = MakeNode(pi);
    if (new_node == NULL)
    {
        fprintf(stderr, "Couldn't create node\n");
        return false;
    }
    if (!InList(&pnode->item, plist))
    {
        fprintf(stderr, "Node is not exist.\n");
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
void ListSort(List *plist, bool (*cmp)(const Item *a,const Item *b))
{
    QuickSort(0, plist->size - 1, plist->head, plist->tail, plist, (*cmp));
}
static void QuickSort(int i, int j, Node *pn_i, Node *pn_j, List *plist, bool (*cmp)(const Item *a, const Item *b))
{
    int a = i;
    int b = j - 1;
    Node *pn_a = pn_i;
    Node *pn_b = NodeGetPre(pn_j);
    if (a < b)
    {
        while (a < b)
        {
            while (!(*cmp)(&pn_a->item, &pn_j->item) && a < b)
            {
                a++;
                pn_a = NodeGetNext(pn_a);
            }
            while ((*cmp)(&pn_b->item, &pn_j->item) && a < b)
            {
                b--;
                pn_b = NodeGetPre(pn_b);
            }
            if ((*cmp)(&pn_a->item, &pn_j->item) && !(*cmp)(&pn_b->item, &pn_j->item))
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

static Node *NodeGetPre(Node *pnode)
{
    if (pnode == NULL)
        return pnode;
    else
        return pnode->pre;
}
static Node *NodeGetNext(Node *pnode)
{
    if (pnode == NULL)
        return pnode;
    else
        return pnode->next;
}

static void swapNode(Node *pn_i, Node *pn_j)
{
    Item temp;
    temp = pn_i->item;
    pn_i->item = pn_j->item;
    pn_j->item = temp;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
static void CopyToNode(Item item, Node *pnode);
static Node *MakeNode(const Item * pi);
static void AddNode(Node * new_node, Node * head);
static void DeleteAllNodes(Node * head);

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

static Node *MakeNode(const Item * pi)
{
    Node * new_node;

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

static void AddNode(Node * new_node, Node * head)
{
    while (head->next != NULL)
        head = head->next;

    head->next = new_node;
    new_node->pre = head;
}

bool InList(const Item *pi, const List *plist)
{
    return (ListSeekID(pi, plist) == NULL) ? false: true;
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
static void DeleteAllNodes(Node * head)
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



bool ListInsertItem(Node *pnode, Item item, List *plist);
bool ListSort(List *plist, bool (*pfun)(Item a, Item b));
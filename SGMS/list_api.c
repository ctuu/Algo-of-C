#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
static void CopyToNode(Item item, Node *pnode);
static Node *MakeNode(const Item * pi);

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
    //Node *scan = *plist;
    if (ListIsFull(*plist))
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
    

    
    pnew->next = NULL;
    pnew->pre = NULL;
    if (scan == NULL)
    {
        *plist = pnew;
    }
    else
    {
        while (scan->next != NULL)
            scan = scan->next;
        scan->next = pnew;
        pnew->pre = scan;
    }

    return true;
}

static Node *MakeNode(const Item * pi)
{
    Node * new_node;

    new_node = (Node *)malloc(sizeof(Node));
    if (new_node != NULL)
    {
        CopyToNode(item, new_node);
        new_node->pre = NULL;
        new_node->next = NULL;
    }
    return new_node;
}

static void CopyToNode(Item item, Node *pnode)
{
    pnode->item = item;
}
void ListTraverse(const List *plist, void (*pfun)(Item item), bool order)
{
    Node *pnode = *plist;
    if (!order)
    {
        while (pnode != NULL)
        {
            (*pfun)(pnode->item);
            pnode = pnode->next;
        }
    }
}

void EmptyTheList(List *plist)
{
    Node *psave;

    while (*plist != NULL)
    {
        psave = (*plist)->next;
        free(*plist);
        *plist = psave;
    }
}

Node *ListSeekID(const Item *pi, const List *plist)
{
    Node *look = *plist;
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

bool ListDeleteItem(const Item *pi, List *plist)
{
    Node *look = NULL;
    look = ListSeekID(pi, plist);
    if (look == NULL)
        return false;
    if (look->next != NULL)
    {
        look->pre->next = look->next;
        look->next->pre = look->pre;
    }
    else if (look->pre != NULL)
        look->pre->next = NULL;
    
    free(look);
    return true;
}

bool ListInsertItem(Node *pnode, Item item, List *plist);
bool ListSort(List *plist, bool (*pfun)(Item a, Item b));
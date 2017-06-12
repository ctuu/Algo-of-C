#include <stdio.h>
#include <stdlib.h>
#include "list.h"
static void CopyToNode(Item item, Node *pnode);

void InitializeList(List *plist)
{
    *plist = NULL;
}
bool ListIsEmpty(const List *plist)
{
    if (*plist == NULL)
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
    unsigned int count = 0;
    Node *pnode = *plist;

    while (pnode != NULL)
    {
        ++count;
        pnode = pnode->next;
    }

    return count;
}

bool ListAddItem(Item item, List *plist)
{
    Node *pnew;
    Node *scan = *plist;

    pnew = (Node *)malloc(sizeof(Node));
    if (pnew == NULL)
        return false;

    CopyToNode(item, pnew);
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

static void CopyToNode(Item item, Node *pnode);
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

*Node ListSeekItem(const Item *pi, const List *plist)
{
    Node *look = *plist;
    if (look.next == NULL)
        return NULL;
    while (look.next != NULL)
    {
        if (strcmp(pi->StuID, look->item.StuID) != 0)
        {
            look = look->next;
        }
        else
            break;
    }
    return look;
}

bool ListDeleteItem(const Item *pi, List *plist)
{
    Node *look;
    look = ListSeekItem(pi, plist);
    if (look == NULL)
        return false;
    look->pre->next = look->next;
    look->next->pre = look->pre;
    free(look);
    return true;
}

bool ListInsertItem(Node *pnode, Item item, List *plist);
bool ListSort(List *plist, bool (*pfun)(Item a, Item b));
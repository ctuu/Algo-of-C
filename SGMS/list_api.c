#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
static void CopyToNode(Item item, Node *pnode);
static Node *MakeNode(const Item *pi);
static void swapNode(Node *pn_i, Node *pn_j, List *plist);
static void AddNode(Node *new_node, Node *head);
static void DeleteAllNodes(Node *head);
static Node *NodeGetPre(const Node *pnode);
static Node *NodeGetNext(const Node *pnode);

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
void ListSort(int i, int j, Node *pn_i, Node *pn_j, List *plist, bool (*cmp)(Item *i_a, Item *i_b))
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
                NodeGetNext(pn_a);
            }
            while ((*cmp)(&pn_b->item, &pn_j->item) && a < b)
            {
                b--;
                NodeGetPre(pn_b);
            }
            if ((*cmp)(&pn_a->item, &pn_j->item) &&(*cmp)(&pn_b->item, &pn_j->item))
            {
                swapNode(pn_a, pn_b, plist);
            }
        }
        if ((*cmp)(&pn_a->item, &pn_j->item))
        {
            swapNode(pn_a, pn_j, plist);
        }
        ListSort(i, a, pn_i, pn_a, plist, (*cmp));
        ListSort(b, j, pn_b, pn_j, plist, (*cmp));
    }
    else if (a == b)
    {
        if ((*cmp)(&pn_i->item, &pn_j->item))
        {
            swapNode(pn_i, pn_j, plist);
        }
    }
}

static Node *NodeGetPre(const Node *pnode)
{
    if (pnode == NULL)
        return NULL;
    else
        return pnode->pre;
}
static Node *NodeGetNext(const Node *pnode)
{
    if (pnode == NULL)
        return NULL;
    else
        return pnode->next;
}

static void swapNode(Node *pn_i, Node *pn_j, List *plist)
{
    Node temp;
    temp.pre = pn_j->pre;
    temp.next = pn_j->next;

    pn_j->pre = pn_i->pre;
    pn_j->next = pn_i->next;
    if (pn_i->pre == NULL)
    {
        plist->head = pn_j;
        pn_j->pre = NULL;
    }
    else
        pn_i->pre->next = pn_j;

    if (pn_i->next == NULL)
    {
        plist->tail = pn_j;
        pn_j->next = NULL;
    }
    else
        pn_i->next->pre = pn_j;

    pn_i->pre = temp.pre;
    pn_i->next = temp.next;
    if (temp.pre == NULL)
    {
        plist->head = pn_i;
        pn_i->pre = NULL;
    }
    else
        temp.pre->next = pn_i;

    if (temp.next == NULL)
    {
        plist->tail = pn_i;
        pn_i->next = NULL;
    }
    else
        temp.next->pre = pn_i;
}
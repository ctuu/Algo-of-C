#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "17.12.8.h"

static void CopyToNode(Item item, Node *pnode);

static Trnode *MakeNode(const Item *pi);
static bool ToLeft(const char i1[], const char i2[]);
static bool ToRight(const char i1[], const char i2[]);
static void AddNode(Trnode *new_node, Trnode *root);
static void InOrder(const Trnode *root, void (*pfun)(Item item));
static void DeleteNode(const Item *pi, Trnode **ptr);
static void DeleteAllNodes(Trnode *ptr);

void InitializeTree(Tree *ptree)
{
    ptree->root = NULL;
    ptree->size = 0;
}

bool TreeIsEmpty(const Tree *ptree)
{
    if (ptree->root == NULL)
        return true;
    else
        return false;
}

bool TreeIsFull(const Tree *ptree)
{
    if (ptree->size == MAXITEMS)
        return true;
    else
        return false;
}

int TreeItemCount(const Tree *ptree)
{
    return ptree->size;
}

bool TreeAddItem(const Item *pi, Tree *ptree)
{
    Trnode *new_node;
    Trnode *exist_node;
    if (TreeIsFull(ptree))
    {
        fprintf(stderr, "Tree is full\n");
        return false;
    }
    if ((exist_node = TreeSeekItem(pi, ptree).child) != NULL)
    {
        //name exist & add node to linklist
        ListAddItem(*pi, &(exist_node->list));
    }
    else
    {
        new_node = MakeNode(pi);
        if (new_node == NULL)
        {
            fprintf(stderr, "Attempted to add duplicate item\n");
            return false;
        }

        if (ptree->root == NULL)
            ptree->root = new_node;
        else
            AddNode(new_node, ptree->root);
    }

    ptree->size++;
    return true;
}

bool InTree(const Item *pi, const Tree *ptree)
{
    return (TreeSeekItem(pi, ptree).child == NULL) ? false : true;
}

bool TreeDeleteItem(const Item *pi, Tree *ptree)
{
    TPair look;

    look = TreeSeekItem(pi, ptree);
    if (look.child == NULL)
        return false;

    if (look.parent == NULL)
        DeleteNode(pi, &ptree->root);
    else if (look.parent->left == look.child)
        DeleteNode(pi, &look.parent->left);
    else
        DeleteNode(pi, &look.parent->right);
    ptree->size--;

    return true;
}

void TreeTraverse(const Tree *ptree, void (*pfun)(Item item))
{
    if (ptree != NULL)
        InOrder(ptree->root, pfun);
}

void DeleteAll(Tree *ptree)
{
    if (ptree != NULL)
        DeleteAllNodes(ptree->root);
    ptree->root = NULL;
    ptree->size = 0;
}

static void InOrder(const Trnode *root, void (*pfun)(Item item))
{
    if (root != NULL)
    {
        InOrder(root->left, pfun);
        ListTraverse(&(root->list), (*pfun));
        //(*pfun)(root->list->node->item);
        InOrder(root->right, pfun);
    }
}

static void DeleteAllNodes(Trnode *root)
{
    Trnode *pright;

    if (root != NULL)
    {
        pright = root->right;
        DeleteAllNodes(root->left);
        free(root->list);
        free(root);
        DeleteAllNodes(pright);
    }
}

static void AddNode(Trnode *new_node, Trnode *root)
{
    if (ToLeft(new_node->petname, root->petname))
    {
        if (root->left == NULL)
            root->left = new_node;
        else
            AddNode(new_node, root->left);
    }
    else if (ToRight(new_node->petname, root->petname))
    {
        if (root->right == NULL)
            root->right = new_node;
        else
            AddNode(new_node, root->right);
    }
    else
    {
        fprintf(stderr, "location error in AddNode()\n");
        exit(1);
    }
}

static bool ToLeft(const char i1[], const char i2[])
{
    if (strcmp(i1, i2) < 0)
        return true;
    else
        return false;
}

static bool ToRight(const char i1[], const char i2[])
{
    if (strcmp(i1, i2) > 0)
        return true;
    else
        return false;
}

static Trnode *MakeNode(const Item *pi)
{
    Trnode *new_node;

    new_node = (Trnode *)malloc(sizeof(Trnode));
    List pet;
    InitializeList(&pet);
    //CREATE A LINKLIST
    if (new_node != NULL)
    {
        sprintf(new_node->petname, "%s", pi->petname);
        new_node->list = pet;
        ListAddItem(*pi, &new_node->list);
        new_node->left = NULL;
        new_node->right = NULL;
    }

    return new_node;
}

TPair TreeSeekItem(const Item *pi, const Tree *ptree)
{
    TPair look;
    look.parent = NULL;
    look.child = ptree->root;

    if (look.child == NULL)
        return look;
    while (look.child != NULL)
    {
        if (ToLeft(pi->petname, look.child->petname))
        {
            look.parent = look.child;
            look.child = look.child->left;
        }
        else if (ToRight(pi->petname, look.child->petname))
        {
            look.parent = look.child;
            look.child = look.child->right;
        }
        else
        {
            break;
        }
    }

    return look;
}

static void DeleteNode(const Item *pi, Trnode **ptr)
{
    Trnode *temp;

    if ((*ptr)->left == NULL)
    {
        ListDeleteItem(pi, &temp->list);
        if (ListIsEmpty(&temp->list))
        {
            temp = *ptr;
            *ptr = (*ptr)->right;
            free(temp);
        }
    }
    else if ((*ptr)->right == NULL)
    {
        ListDeleteItem(pi, &temp->list);
        if (ListIsEmpty(&temp->list))
        {
            temp = *ptr;
            *ptr = (*ptr)->left;
            free(temp);
        }
    }
    else
    {
        ListDeleteItem(pi, &temp->list);
        if (ListIsEmpty(&temp->list))
        {
            for (temp = (*ptr)->left; temp->right != NULL; temp = temp->right)
                continue;
            temp->right = (*ptr)->right;
            temp = *ptr;
            *ptr = (*ptr)->left;

            free(temp);
        }
    }
}

//========================================

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
    if (scan == NULL)
        *plist = pnew;
    else
    {
        while (scan->next != NULL)
            scan = scan->next;
        scan->next = pnew;
    }

    return true;
}

void ListTraverse(const List *plist, void (*pfun)(Item item))
{
    Node *pnode = *plist;

    while (pnode != NULL)
    {
        (*pfun)(pnode->item);
        pnode = pnode->next;
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

static void CopyToNode(Item item, Node *pnode)
{
    pnode->item = item;
}

LPair ListSeekItem(const Item *pi, const List *plist)
{
    LPair look;
    look.parent = NULL;
    look.child = *plist;
    if (look.child == NULL)
        return look;
    while (look.child != NULL)
    {
        if (strcmp(pi->petkind, look.child->item.petkind) != 0)
        {
            look.parent = look.child;
            look.child = look.child->next;
        }
        else
            break;
    }
    return look;
}

bool ListDeleteItem(const Item *pi, List *plist)
{
    LPair look;
    Node *temp;
    look = ListSeekItem(pi, plist);
    if (look.child == NULL)
        return false;

    if (look.parent == NULL)
    {
        temp = look.child;
        *plist = look.child->next;
        free(temp);
    }
    else
    {
        temp = look.child;
        look.parent->next = look.child->next;
        free(temp);
    }
    return true;
}
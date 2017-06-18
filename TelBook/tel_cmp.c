#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tel_item.h"
#include "tel_func.h"

static bool Str_Cmp(const char *a, const char *b);

bool Cmp_bID(const Item *pn_a, const Item *pn_b)
{
    return pn_a->ID > pn_b->ID;
}

bool Cmp_bName(const Item *pn_a, const Item *pn_b)
{
    if (strcmp(pn_a->Name, pn_b->Name) != 0)
        return Str_Cmp(pn_a->Name, pn_b->Name);
    else
        return Cmp_bID(pn_a, pn_b);
}


static bool Str_Cmp(const char *a, const char *b)
{
    if (strcmp(a, b) <= 0)
        return false;
    return true;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stu_item.h"
#include "stu_func.h"

static bool Str_Cmp(const char *a, const char *b);

bool Cmp_bID(const Item *pn_a, const Item *pn_b)
{
    if (strlen(pn_a->StuID) == strlen(pn_b->StuID))
        return Str_Cmp(pn_a->StuID, pn_b->StuID);
    else
        return strlen(pn_a->StuID) > strlen(pn_b->StuID);
}

bool Cmp_bName(const Item *pn_a, const Item *pn_b)
{
    if (strcmp(pn_a->Name, pn_b->Name) != 0)
        return Str_Cmp(pn_a->Name, pn_b->Name);
    else
        return Cmp_bID(pn_a, pn_b);
}
bool Cmp_bCG(const Item *pn_a, const Item *pn_b)
{
    if (pn_a->grade.C_lang != pn_b->grade.C_lang)
        return pn_a->grade.C_lang > pn_b->grade.C_lang;
    else
        return Cmp_bID(pn_a, pn_b);
}
bool Cmp_bMG(const Item *pn_a, const Item *pn_b)
{
    if (pn_a->grade.Math != pn_b->grade.Math)
        return pn_a->grade.Math > pn_b->grade.Math;
    else
        return Cmp_bID(pn_a, pn_b);
}
bool Cmp_bEG(const Item *pn_a, const Item *pn_b)
{
    if (pn_a->grade.Eng != pn_b->grade.Eng)
        return pn_a->grade.Eng > pn_b->grade.Eng;
    else
        return Cmp_bID(pn_a, pn_b);
}

bool Cmp_bTG(const Item *pn_a, const Item *pn_b)
{
    if (pn_a->grade.Total != pn_b->grade.Total)
        return pn_a->grade.Total > pn_b->grade.Total;
    else
        return Cmp_bID(pn_a, pn_b);
}
bool Cmp_bRat(const Item *pn_a, const Item *pn_b)
{
    if (pn_a->Rating != pn_b->Rating)
        return pn_a->Rating > pn_b->Rating;
    else
        return Cmp_bID(pn_a, pn_b);
}

static bool Str_Cmp(const char *a, const char *b)
{
    if (strcmp(a, b) <= 0)
        return false;
    return true;
}
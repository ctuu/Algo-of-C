#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

bool seek_bID(const Item *pi, const Item *pj)
{
    if (strcmp(pi->StuID, pj->StuID) == 0)
        return 1;
    return 0;
}

bool seek_bName(const Item *pi, const Item *pj)
{
    if (strcmp(pi->Name, pj->Name) == 0)
        return 1;
    return 0;
}
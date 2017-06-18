#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tel_item.h"
#include "tel_func.h"

bool seek_bID(const Item *pi, const Item *pj)
{
	return pi->ID == pj->ID;
}

bool seek_bName(const Item *pi, const Item *pj)
{
    if (strcmp(pi->Name, pj->Name) == 0)
        return 1;
    return 0;
}

bool seek_bPhone(const Item *pi, const Item *pj)
{
    if (strcmp(pi->Phone, pj->Phone) == 0)
        return 1;
    return 0;
}

bool seek_bQQ(const Item *pi, const Item *pj)
{
    if (strcmp(pi->QQ, pj->QQ) == 0)
        return 1;
    return 0;
}
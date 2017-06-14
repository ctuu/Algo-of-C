//Code by ctuu
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

bool Item_open(FILE *fp, Item *pi)
{
    if (fscanf(fp, "%s,%s,%d,%d,%d,%d", pi->StuID, pi->Name, &pi->grade.C_lang,&pi->grade.Math, &pi->grade.Eng, pi->Rating) == 6)
    {
        item->grade.Total = item->grade.C_lang + item->grade.Math + item->grade.Eng;
        item->grade.Ave = (float)item->grade.Total / 3;
        return true;
    }
    return false;
}
//Code by ctuu
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tel_item.h"
#include "tel_func.h"

bool File_skip(FILE *fp)
{
    fscanf(fp, "%*[^\n]%*c%*[^\n]%*c");
    return true;
}

bool File_AddTitle(FILE *fp)
{
    fprintf(fp, "The Tel System,,,\n");
    fprintf(fp, "ID,Name,Phone,QQ\n");
    return true;
}

bool Item_open(FILE *fp, Item *pi)
{
    // char ch;
    if (feof(fp))
        return false;
    if (fscanf(fp, "%d,%[^,],%[^,],%[^\n]", &pi->ID, pi->Name, pi->Phone, pi->QQ) == 4)
        return true;
    else
    {
        fprintf(stderr, "ERROR: Data can not be read.\n");
        return false;
    }
}

bool Item_save(FILE *fp, Item *pi)
{
    if (fprintf(fp, "%d,%s,%s,%s\n", pi->ID, pi->Name, pi->Phone, pi->QQ))
        return true;
    else
    {
        fprintf(stderr, "ERROR: Data can not be write.\n");
        return false;
    }
}
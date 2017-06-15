//Code by ctuu
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "stu_func.h"

bool File_skip(FILE *fp)
{
    fscanf(fp, "%*[^\n]%*c%*[^\n]%*c");
    return true;
}

bool File_AddTitle(FILE *fp)
{
    fprintf(fp, "The Students' Grade Management System,,,,,\n");
    fprintf(fp, "ID,Name,C Language Grade,Math Grade,English Grade,Rating\n");
    return true;
}

bool Item_open(FILE *fp, Item *pi)
{
    if (fscanf(fp, "%[^,],%[^,],%d,%d,%d,%d\n", pi->StuID, pi->Name, &pi->grade.C_lang, &pi->grade.Math, &pi->grade.Eng, &pi->Rating) == 6)
    {
        pi->grade.Total = pi->grade.C_lang + pi->grade.Math + pi->grade.Eng;
        pi->grade.Ave = (float)pi->grade.Total / 3;
        return true;
    }
    else
    {
        fprintf(stderr, "ERROR: Data can not be read.\n");
        return false;
    }
}

bool Item_save(FILE *fp, Item *pi)
{
    if (fprintf(fp, "%s,%s,%d,%d,%d,%d\n", pi->StuID, pi->Name, pi->grade.C_lang, pi->grade.Math, pi->grade.Eng, pi->Rating))
        return true;
    else
    {
        fprintf(stderr, "ERROR: Data can not be write.\n");
        return false;
    }
}
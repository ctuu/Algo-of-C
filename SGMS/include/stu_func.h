//Code by ctuu
#ifndef STU_FUNC_H_
#define STU_FUNC_H_
#include <stdbool.h>

//stu_get_data.c
bool Get_Int(int *num);
bool Get_ID(char *st);
void uppercase(char *str);
char *s_gets(char *st, int n);

//stu_cmp.c
bool Cmp_bID(const Item *pn_a, const Item *pn_b);
bool Cmp_bName(const Item *pn_a, const Item *pn_b);
bool Cmp_bCG(const Item *pn_a, const Item *pn_b);
bool Cmp_bMG(const Item *pn_a, const Item *pn_b);
bool Cmp_bEG(const Item *pn_a, const Item *pn_b);
bool Cmp_bTG(const Item *pn_a, const Item *pn_b);
bool Cmp_bRat(const Item *pn_a, const Item *pn_b);

//stu_seek.c
bool seek_bID(const Item *pi, const Item *pj);
bool seek_bName(const Item *pi, const Item *pj);

//stu_file.c
bool File_skip(FILE *fp);
bool File_AddTitle(FILE *fp);
bool Item_open(FILE *fp, Item *pi);
bool Item_save(FILE *fp, Item *pi);

#endif
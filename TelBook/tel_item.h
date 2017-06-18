#ifndef ITEM_H_
#define ITEM_H_

#define LEN_ID 10
#define LEN_NAME 15
#define LEN_PHONE 12
#define LEN_QQ 15

typedef struct tel_item
{
    int ID;
    char Name[LEN_NAME];
    char Phone[LEN_PHONE];
    char QQ[LEN_QQ];
} Item;

#endif
#ifndef ITEM_H_
#define ITEM_H_

#define LEN_ID 10
#define LEN_NAME 15
#define LEN_NUM 5

#define C_PASSED 60
#define MATH_PASSED 60
#define ENG_PASSED 60

typedef struct StuGrade 
{
    int C_lang;
    int Math;
    int Eng;
    int Total;
    float Ave;
} Grade;

typedef struct Student
{
    char StuID[LEN_ID];
    char Name[LEN_NAME];
    Grade grade;
    int Rating;
} Item;

#endif
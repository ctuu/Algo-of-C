#include <stdio.h>

int main(void)
{
   char  *language[]={"FORTRAN","BASIC","PASCAL", "JAVA","C"};
   char lang[5][10]={"FORTRAN","BASIC","PASCAL", "JAVA","C"};
   printf(" : %s\n", *language);
   printf(" : %s\n", lang);
   printf(" : %s\n", *lang);
   printf(" : %p\n", language);
   printf(" : %c\n", *language[2]);
   printf(" : %p\n", language + 2);
   printf(" : %p    %p\n", *language, language[0]);
   printf(" : %p    %p    %p\n", lang, *lang, lang[0]);
    return 0;
}
#include <stdio.h>
int main(void)
{
    char sex, sports, diet;
    float faHeight, moHeight, height;
    printf("Please enter your gender(M or F): ");
    scanf("%c", &sex);
    printf("Enter your father's height(cm): ");
    scanf("%f", &faHeight);
    printf("and your mother's height(cm): ");
    scanf("%f", &moHeight);
    printf("Do you like sport(Y or N): ");
    scanf("%*c%c", &sports);
    printf("Do you have a good eating habit(Y or N): ");
    scanf("%*c%c", &diet);

    if (sex == 'M')
        height = (faHeight + moHeight) * 0.54;
    else
        height = (faHeight * 0.923 + moHeight) / 2;    
    if (sports == 'Y');
        height *= 1.02;
    if (diet == 'Y')
        height *= 1.015;
    printf("Your height will be %f cm", height);
    return 0;
}
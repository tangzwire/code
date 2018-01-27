/********************************************
 * Name: Tanvir Saif Ahmed                  *
 * Date: 6/9-2012                           *
 * Course: Programming C                    *
 * Assignment: Laboration 1 -(Calculator)   *
 ********************************************/

#include<stdio.h>

int main(void)
{
    int ch, fortsatt;
    fortsatt=1;
    while(fortsatt==1)
    {
        float num1,num2,resultat;

        printf("\n          ****** VALKOMMEN TILL MINIRAKNAREN! ******");
        printf("\n\n");
        printf("Skriv in dina tva tal och valj samtidigt om du vill addera, subtrahera,\nmultiplicera eller dividera: ");
        scanf("%f",&num1);
        scanf("%c",&ch);
        scanf("%f",&num2);

        switch(ch)
        {
            case '+' :resultat=num1+num2; break;
            case '-' :resultat=num1-num2; break;
            case '*' :resultat=num1*num2; break;
            case '/' :resultat=num1/num2; break;
        }

        printf("\nResultatet av %.2f %c %.2f blir = %.2f\n",num1,ch,num2,resultat);
        printf("\n________________________________________________________________________________");
        printf("\n                         - MENY -");
        printf("\n");
        printf("\n- Om du vill gora en ny berakning, so anger du siffran 1.");
        printf("\n- Ifall du vill avsluta programmet, so anger du siffran 2.\n");
        printf("\nDitt val: ");
        scanf("%d", &fortsatt);
        printf("\n");
        printf("________________________________________________________________________________");
    }
}

/********************************************************
 * Name: Tanvir Saif Ahmed                              *
 * Date: ?/9-2012                                       *
 * Course: Programming C                                *
 * Assignment: Laboration 2 -(Personnummerkontrollen)   *
 ********************************************************/

#include<stdio.h>

int main(void)
{
    int fortsatt, a[9], i, sista, summa=0, resultat;
    //While loopen för att få möjligheten att köra om programmet igen//
    fortsatt=1;
    while(fortsatt==1)
    {
        printf("\n          ******* VALKOMMEN TILL PERSONNUMMERSKONTROLLEN! *******\n\nBorja med att skriva in ditt 10-siffriga personnummer (YYMMDD-XXXX):\n\n");
        for(i=0;i<9;i++)
        {
            scanf("%1d-", &a[i]);
        }

        scanf("%1d", &sista);
        printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");

        //Här anropar jag alla funktioner som ska genomföras//
        summa = multiplication_addition(a);
        resultat = calc_last(summa);

        printf("\n");
        printf("Din kontrollsiffra (den 10:de siffran i ditt personummer) ska vara: %d", resultat);
        printf("\n");
        printf("\n");

        //Jämför resultatet med den sista siffran, för att tala om ifall man har skrivit ett korrekt eller ett fel personnummer//
        if(resultat == sista)
            printf("DU HAR ANGIVIT ETT KORREKT PERSONNUMMER!\n");
        if(resultat != sista)
            printf("DU HAR ANGIVIT ETT FEL PERSONNUMMER!\n");

        printf("\n");
        printf("________________________________________________________________________________");
        printf("\n                                    -MENY-");
        printf("\n\n");
        printf("- Om du vill gora en till personnummerskontroll, so anger du siffran 1.\n");
        printf("- Ifall du vill avsluta programmet, so anger du siffran 2.\n");
        printf("\n");
        printf("Ditt val: ");
        scanf("%d", &fortsatt);
        printf("\n");
        printf("________________________________________________________________________________");
    }

}
//Här definerar jag alla funktioner som jag ska använda mig av i denna program//
int multiplication_addition(int a[])
{
    int i, summa=0;

    for(i=0;i<9;i+=2)
    {
        a[i]*=2;
    }
    for(i=0;i<9;i++)
    {
        if(a[i] <= 9)
        summa += a[i];
        if(a[i] >= 10)
        summa += a[i]%10 + a[i]/10;
    }
    return summa;
}

int calc_last(summa)
{
    int entalsiffran_minus_tio, resultat;

    entalsiffran_minus_tio = summa % 10;
    resultat =( 10 - entalsiffran_minus_tio)%10;

    return resultat;
}

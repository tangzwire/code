/********************************************
 * Name: Tanvir Saif Ahmed                  *
 * Date: 5/12-2012                          *
 * Course: Programming C                    *
 * Assignment: Laboration 3 -(Bookregister) *
 ********************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 30

    // H�r har jag placerat min struct i b�rjan av programmet. Structen heter bokuppgift.
    // H�r kommer man att vilja lagra f�rfattare, boktiteln och utgivnings�r i en variabel (bokuppgift) i form av str�ngar.
    // Man anv�nder struct, f�r att vi ska kunna samla uppgifter utav olika typer.
    // Denna struct kommer anv�ndas i programmet hela tiden, f�r att man ska kunna lagra bokuppgifter.
    // Med hj�lp av en s�dan struct, s� ska man kunna jobba med inneh�llet som finns i den i olika typer av funktioner.
    struct bokuppgift
    {
        char forfattare[30];
        char boktiteln[40];
        char utgivningsar[30];
    };

    // Detta �r funktionen f�r att man ska kunna �ppna ett existerande fil (en existerande bokregister allts�).
    // [counter]�r den som erh�ller alla b�cker.
    // Anv�nds f�r att denna funktion ska kunna l�sa av inneh�llet som finns i [counter]
    // fseek() anv�nds d� f�r att man ska kunna r�ra sig runt om filen som �r �ppnad.
    void oppna_ett_existerande_fil_bokregister(struct bokuppgift bocker[MAX], char fil_namnet[MAX], int *counter)
    {
        FILE *filen;
        int j;
        printf("_______________________________________________________________________________");
        printf("\n");
        printf("Ange namnet p� filen till din bokregister, som du vill �ppna:\n\n ");
        printf("- ");
        scanf("%s", fil_namnet);
        // H�r �ppnas filen f�r att den ska kunna l�sas av.
        // Med hj�lp av fopen s� �ppnas filen genom att fil_namnet pekar p� filens namn som ska �ppnas i programmet.
        filen = fopen(fil_namnet, "rb");
            // Om det visar sig att filen ej existerar/har fel namn, s� kommer ett meddelande som talar om detta.
            // Detta med hj�lp av en print funktion.
            // Detta sker d� om returv�rdet p� fopen() �r en NULL-pekare. Denna talar om d� att anropet till filen har misslyckats.
            if(filen == NULL)
            {
              printf("\nDet gick inte att �ppna filen. Det kan vara s� att filen har tagits bort, har fel namn eller ej har skapats.\n");
              exit(EXIT_FAILURE);
            }

        // H�r s� placerar man pekaren i slutet av filen.
        // Man ska kunna allts� r�ra sig till slutet av filen i programmet.
        // fseek(SEEK_END) s�ker igenom positionerna i inneh�llet till slutet av filen.
        fseek(filen,0,SEEK_END);
        // ftell(filen)/sizeof(struct bokuppgift) talar om filens position, samt hur m�nga b�cker som det finns i bokregistret.
        // Denna r�knar ut antal b�cker i bokregistret.
        *counter=ftell(filen)/sizeof(struct bokuppgift);
        // H�r s� placerar man pekaren i b�rjan av filen.
        // Man ska kunna allts� r�ra sig till b�rjan av filen i programmet.
        // fseek(SEEK_SET) s�ker igenom positionerna i inneh�llet till b�rjan av filen.
        fseek(filen,0,SEEK_SET);
            // Man har gjort en for-loop f�r att kunna l�sa av filen som man vill �ppna.
            // fread l�ser av b�ckerna, samt antal b�cker som finns i bokregistret (detta med hj�lp av sizeof)
            for (j=0;j<*counter;j++)
            {
              fread(&bocker[j],sizeof(struct bokuppgift),1,filen);
            }
        // F�r att alla �ndringar som vi utf�r i filen ska kunna sparas, s� m�ste fclose() anropas.
        // Str�mmen som tillh�r filen, som vi jobbar med genom att skriva p� den, m�ste st�ngas med fclose().
        fclose(filen);
    }

    // Detta �r en funktion f�r att man ska kunna skapa ett nytt fil f�r sin nya bokregister.
    // D� skriver man in namnet p� filen som ska skapas.
    void skapa_ett_nytt_fil(char fil_namnet[MAX])
    {
        FILE *filen;
        printf("________________________________________________________________________________");
        printf("\n");
        printf("Ange namnet p� den nya filen till ditt bokregister, som du vill skapa:\n\n ");
        printf("- ");
        scanf("%s", fil_namnet);
        // H�r skapas filen till det nya bokregistret.
        filen = fopen(fil_namnet , "wb");
        // F�r att alla �ndringar som vi utf�r i filen ska kunna sparas, s� m�ste fclose() anropas.
        // Str�mmen som tillh�r filen, som vi jobbar med genom att skriva p� den, m�ste st�ngas med fclose().
        // I det h�r fallet s� sparas den nya filen efter att den skapats utan n�gon inneh�ll i filen.
        fclose(filen);
    }

    // Detta �r funktionen f�r att man ska kunna avsluta programmet fr�n allra f�rsta b�rjan (om man inte vill jobba med programmet).
    void avsluta_programmet(void)
    {
        // Exit �r den som avslutar programmet.
        exit(1);
    }

    // Detta �r funktionen f�r att man ska kunna l�gga till b�cker i bokregistret.
    // [raknare] �r sj�lva countern. Det �r den som kommer hj�lpa till att mata in bokuppgifterna som jag l�gger till i registret.
    // [raknare] b�rjar fr�n 0. L�gger man till en bokuppgift, s� �kar [raknare] med 1.
    // Ju mer bokuppgifter som l�ggs, desto mer �kar [raknare].
    // D� tar [bocker] emot uppgifterna som [raknare] l�gger in och sparar de i bokregistret.
    void lagg_till_en_bok(struct bokuppgift *bocker, int *raknare)
    {
        printf("\n");
        printf("********************************************************************************");
        printf("\n");
        printf("Skriv in uppgifterna p� din nya bok som ska l�ggas in i registret:");
        printf("\n");
        printf("\n");
        printf("F�rfattare: ");
        // H�r ropas string-funktionen las_rad, d� denna string ska kunna l�sa av mellanslag.
        // Detta f�r att om man ska skriva in f�rnamnet och efternamnet p� f�rfattaren s� ska mellanslag ocks� s�klart komma emellan d�r.
        las_rad(bocker[*raknare].forfattare, MAX);
        printf("Boktiteln: ");
        // H�r ropas string-funktionen las_rad, d� denna string ska kunna l�sa av mellanslag.
        // Detta f�r att om man ska skriva in namnet p� boktiteln, s� kommer mellanslag dyka upp hela tiden mellan varje ord.
        las_rad(bocker[*raknare].boktiteln, MAX);
        printf("Utgivningsar: ");
        // H�r kr�vs ingen anrop till n�gon string-funktion som las_rad, d� man skriver in utgivnings�ret utan mellanslag.
        // D� r�cker det kort och gott med en scanf-funktion.
        scanf("%s", bocker[*raknare].utgivningsar);
    // Efter att uppgifterna p� den nya boken skrivits och l�sts av, s� l�ggs den in som en bokuppgift i [raknare].
    // Boken som skapas, pekas till [raknare] och l�ggs till d�r. Det �r h�r siffran �kar i [raknare].
    (*raknare)++;
    }

    // Detta �r funktionen f�r att man ska kunna ta bort b�cker fr�n bokregistret.
    // [raknare] �r sj�lva countern. Det �r den som kommer hj�lpa ta bort de bokuppgifter som man v�ljer att ta bort.
    // [raknare] b�rjar fr�n den siffran s� mycket som det finns bokuppgifter.
    // Tar man bort en bokuppgift, s� minskar [raknare] med 1.
    // [raknare] tar d� allts� bort bokuppgiften fr�n [bocker] s� att den inte finns kvar i bokregistret.
    // strcopy anv�nds d� f�r att uppgifterna till boken ska tas bort.
    // Variabeln radera_boken kommer anv�ndas f�r att se till att boken raderas.
    void ta_bort_en_bok(struct bokuppgift *bocker, int *raknare, int list_of_alternatives[MAX])
    {
        // S�kningsfunktionen ropas h�r. Detta f�r att man ska kunna s�ka efter den boken som man vill ta bort fr�n bokregistret.
        sok_efter_en_bok(bocker, raknare, list_of_alternatives);

        int val_av_bok=0, radera_boken;

        printf("\n");
        printf("Vilken bok vill du ta bort fr�n denna register, utifr�n din s�kresultat?\n");
        printf("\n");
        printf("Ditt val: ");

        // H�r s� l�ses sj�lva valet p� boken som ska tas bort av och skickar dig vidare till en for-loop.
        scanf("%d",&val_av_bok);

            // list_of_alternatives[val_av_bok-1] �r den som kommer upp n�r man har s�kt igenom bokregistret.
            // Den f�r fram listan av b�ckerna som man f�r fram utifr�n sin s�kord.
            // Med hj�lp av list_of_alternatives[val_av_bok-1] s� omvandlar det numret som man har matat in till det riktiga array numret.
            // Om vi t.ex har tre b�cker i bokregistret:
            // 0. Tanvir Rozario   -- 0 �r skriven f�r att ett array b�rjar alltid fr�n 0 till MAX.
            // 1. Trey Songz
            // 2. Tata Latina
            // S�ker vi p� "Ta" som s�kord, s� ska bara Tanvir Rozario och Tata Latina dyka upp.
            // D� placeras Tanvir Rozario f�rst i listan i nummer 0 och sedan Tata Latina p� andra platsen (nummer 1).
            // Detta inneb�r att om man vill ta bort Tata Latina fr�n bokregistret s� anger man siffran 2.
            // Siffran 2 f�rvandlas till 1 och tar sedan bort Tata Latina fr�n bokregistret.
            for(radera_boken=list_of_alternatives[val_av_bok-1];radera_boken<*raknare; radera_boken++)
            {
             strcpy(bocker[radera_boken].forfattare, bocker[radera_boken+1].forfattare);
             strcpy(bocker[radera_boken].boktiteln,bocker[radera_boken+1].boktiteln);
             strcpy(bocker[radera_boken].utgivningsar,bocker[radera_boken+1].utgivningsar);
            }
    // Efter att man valt vilken bok som ska raderas, s� tas boken bort fr�n [raknare].
    // Boken som raderas, pekas till [raknare] och tas bort d�rifr�n. Det �r h�r siffran minskar i [raknare].
    // D�refter s� kontrollerar funktionen om det finns n�gon tom plats som �r tom.
    // Om s� �r fallet, s� flyttas en bok som finns i bokregistret till den tomma platsen.
    (*raknare)--;
    }

    // Detta �r funktionen f�r att man ska kunna �ndra en bokuppgift i bokregistret.
    // [raknare] �r sj�lva countern. Det �r den som kommer hj�lpa med att �ndra sj�lva boken som man har valt att �ndra.
    // �ndras en bokuppgift, s� kommer den pekas till [raknare] och skicka iv�g bokuppgiften som �ndrats dit till [bocker].
    // Bokuppgiften sparas d� d�r.
    // Samtidigt som vi �ndrar informationen p� en bokuppgift, tas den gamla informationen av bokuppgiften bort.
    void andra_en_bok(struct bokuppgift *bocker, int *raknare, int list_of_alternatives[MAX])
    {
        int val_av_andrings_metod;
        int val_av_andring_bok;
        printf("\n");
        printf("********************************************************************************");
        printf("\n");
        // I den h�r �ndra en bok-funktionen, s� har man underl�ttat det lite f�r den som vill �ndra en bok.
        // Om det skulle vara som s� att man vill bara �ndra f�rfattaren, boktiteln eller utgivnings�ret p� en bok, s� finns det som ett val.
        // Annars kan man v�lja att �ndra en hel bok (allts� f�rfattaren, boktiteln samt utgivnings�ret).
        printf("Ange om du vill �ndra en hel bokuppgift eller en del utav bokuppgiften.\n\n");
        printf("- En hel bokuppgift (1)\n");
        printf("- En del utav bokuppgiften (2)\n");
        printf("\n");
        printf("Ditt val: ");
        // Valet l�ses av och g�r vidare till en if-sats.
        scanf("%d", &val_av_andrings_metod);
            // Om man har valt 1 som sitt val, s� inneb�r det att man vill �ndra en hel bok (f�rfattaren, boktiteln och utgivnings�ret).
            if (val_av_andrings_metod == 1)
            {
             // S�kningsfunktionen ropas h�r. Detta f�r att man ska kunna s�ka efter den boken som man vill �ndra p� fr�n bokregistret.
             sok_efter_en_bok(bocker, raknare, list_of_alternatives);
             printf("\n");
             printf("Vilken bok vill du �ndra?\n");
             printf("\n");
             printf("Ditt val: ");
             scanf("%d",&val_av_andring_bok);
             // list_of_alternatives[val_av_bok-1] �r den som kommer upp n�r man har s�kt igenom bokregistret.
             // Den f�r fram listan av b�ckerna som man f�r fram utifr�n sin s�kord.
             // Med hj�lp av list_of_alternatives[val_av_bok-1] s� omvandlar det numret som man har matat in till det riktiga array numret.
             // Om vi t.ex har tre b�cker i bokregistret:
             // 0. Tanvir Rozario   -- 0 �r skriven f�r att ett array b�rjar alltid fr�n 0 till MAX.
             // 1. Trey Songz
             // 2. Tata Latina
             // S�ker vi p� "Ta" som s�kord, s� ska bara Tanvir Rozario och Tata Latina dyka upp.
             // D� placeras Tanvir Rozario f�rst i listan i nummer 0 och sedan Tata Latina p� andra platsen (nummer 1).
             // Detta inneb�r att om man vill �ndra p� Tata Latina i bokregistret s� anger man siffran 2.
             // Siffran 2 f�rvandlas till 1 och �ndrar sedan Tata Latina i bokregistret.
             printf("\n");
             //H�r skriver man in de nya uppgifterna p� hela boken som man vill �ndra p� (f�rfattaren, boktiteln och utgivnings�ret).
             printf("F�rfattarens nya namn: ");
             // H�r ropas string-funktionen las_rad, d� denna string ska kunna l�sa av mellanslag.
             // Detta f�r att om man ska skriva in f�rnamnet och efternamnet p� f�rfattaren s� ska mellanslag ocks� s�klart komma emellan d�r.
             las_rad(bocker[list_of_alternatives[val_av_andring_bok-1]].forfattare, MAX);
             printf("Bokens nya titel: ");
             // H�r ropas string-funktionen las_rad, d� denna string ska kunna l�sa av mellanslag.
             // Detta f�r att om man ska skriva in namnet p� boktiteln, s� kommer mellanslag dyka upp hela tiden mellan varje ord.
             las_rad(bocker[list_of_alternatives[val_av_andring_bok-1]].boktiteln, MAX);
             printf("Den nya publicerings�ret: ");
             // H�r kr�vs ingen anrop till n�gon string-funktion som las_rad, d� man skriver in utgivnings�ret utan mellanslag.
             // D� r�cker det kort och gott med en scanf-funktion.
             scanf("%s", bocker[list_of_alternatives[val_av_andring_bok-1]].utgivningsar, MAX);
            }
             // Om man har valt 2 som sitt val, s� inneb�r det att man vill �ndra bara en del av en bok
             // Det kan antingen vara f�rfattaren, boktiteln eller utgivnings�ret som man vill �ndra p�.
             // D� m�ste en variabel skapas. Denna variabel anv�nds f�r att tala om vad du vill �ndra i boken.
             // Variabeln heter val_av_uppgiftsandring.
            if (val_av_andrings_metod == 2)
            {
             int val_av_uppgiftsandring;
             printf("\n\n");
             // S�kningsfunktionen ropas h�r. Detta f�r att man ska kunna s�ka efter den boken som man vill �ndra p� fr�n bokregistret.
             sok_efter_en_bok(bocker, raknare, list_of_alternatives);
             printf("\n");
             printf("Vilken bok vill du �ndra en uppgift p�?\n");
             printf("\n");
             printf("Ditt val: ");
             scanf("%d", &val_av_andring_bok);
             // list_of_alternatives[val_av_bok-1] �r den som kommer upp n�r man har s�kt igenom bokregistret.
             // Den f�r fram listan av b�ckerna som man f�r fram utifr�n sin s�kord.
             // Med hj�lp av list_of_alternatives[val_av_bok-1] s� omvandlar det numret som man har matat in till det riktiga array numret.
             // Om vi t.ex har tre b�cker i bokregistret:
             // 0. Tanvir Rozario  -- 0 �r skriven f�r att ett array b�rjar alltid fr�n 0 till MAX.
             // 1. Trey Songz
             // 2. Tata Latina
             // S�ker vi p� "Ta" som s�kord, s� ska bara Tanvir Rozario och Tata Latina dyka upp.
             // D� placeras Tanvir Rozario f�rst i listan i nummer 0 och sedan Tata Latina p� andra platsen (nummer 1).
             // Detta inneb�r att om man vill �ndra p� Tata Latina i bokregistret s� anger man siffran 2.
             // Siffran 2 f�rvandlas till 1 och �ndrar sedan Tata Latina i bokregistret.
             printf("\n");
             // H�r kommer funktionen fr�ga vad man vill �ndra i boken. �r det f�rfattaren? Boktiteln? Eller kanske utgivnings�ret?
             printf("Vilken uppgift skall �ndras i denna bok? \n\n");
             printf("1. F�rfattaren skall �ndras.\n");
             printf("2. Boktiteln skall �ndras.\n");
             printf("3. Utgivnings�ret skall �ndras.\n");
             printf("\n");
             printf("Ditt val: ");
             // Valet l�ses av och g�r vidare till en annan if-sats.
             scanf("%d", &val_av_uppgiftsandring);

                // Har man valt 1 som sitt val, vill man �ndra p� f�rfattaren.
                // �terigen, s� kommer las_rad funktionen in h�r, som ska kunna l�sa av mellanslag.
                // Detta f�r att man ska kunna skriva mellanslag om man anger f�rnamn och efternamn p� f�rfattaren.
                if (val_av_uppgiftsandring == 1)
                {
                 printf("\n");
                 printf("F�rfattarens nya namn: ");
                 las_rad(bocker[list_of_alternatives[val_av_andring_bok-1]].forfattare, MAX);
                }
                // Har man valt 2 som sitt val, vill man �ndra p� boktiteln.
                // �terigen, s� kommer las_rad funktionen in h�r, som ska kunna l�sa av mellanslag.
                // Detta f�r att man ska kunna skriva mellanslag mellan ord som skrivs in f�r boktiteln.
                if (val_av_uppgiftsandring == 2)
                {
                 printf("\n");
                 printf("Bokens nya titel: ");
                 las_rad(bocker[list_of_alternatives[val_av_andring_bok-1]].boktiteln, MAX);
                }
                // Har man valt 3 som sitt val, vill man �ndra p� utgivnings�ret.
                // H�r kr�vs ingen anrop f�r string-funktion som las_rad.
                // Detta f�r att man anger utgivnings�ret utan mellanslag.
                // D� r�cker det kort och gott med en scanf-funktion.
                if (val_av_uppgiftsandring == 3)
                {
                 printf("\n");
                 printf("Den nya publicerings�ret: ");
                 scanf("%s", bocker[list_of_alternatives[val_av_andring_bok-1]].utgivningsar, MAX);
                }
            }
    }

    // Detta �r funktionen f�r att man ska kunna s�ka igenom bokregistret efter bokuppgifter.
    // [raknare] �r sj�lva countern. Det �r den som kommer hj�lpa med att s�ka igenom bokregistret efter bokuppgifter.
    // En for-loop skapas d�. Denna ska generera bokuppgifterna som finns i bokregistret efter s�kkriterien.
    // Uppgifterna som finns i s�kresultat, lagras d� i en index, som ska sedan anv�ndas f�r att man ska kunna ta bort eller �ndra en bok.
    // Denna index kallas f�r list_of_alternatives[MAX].
    // S�k funktionen defineras som en int, d� denna ska kunna anv�ndas inne i andra funktioner som ta bort-funktionen, �ndra-funktionen.
    int sok_efter_en_bok(struct bokuppgift *bocker, int *raknare, int list_of_alternatives[MAX])
    {
        int val=1;
        int i,j=0;
        // En s�karray som deklareras. Denna ska senare i funktionen j�mf�ras med [raknare].
        char sokord[MAX];
        printf("\n");
        printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
        printf("\n");
        // H�r fr�gar den vad man vill s�ka efter. �r det f�rfattaren? Boktiteln? Eller utgivnings�ret?
        printf("Vad vill du s�ka efter?");
        printf("\n");
        printf("\n");
        printf("- F�rfattare (1)\n");
        printf("- Boktiteln (2)\n");
        printf("- Utgivnings�r (3)\n");
        printf("\n");
        printf("Ditt val: ");
        // Valet l�ses av och g�r senare till en switch-sats.
        scanf("%d",&val);
            // Om man valt 1 som sitt val, s� vill man s�ka efter f�rfattaren.
            switch(val)
            {
                case 1:
                printf("\n");
                printf("S�k efter en bok med hj�lp av f�rfattare: \n\n");
                printf("- ");
                // S�kordet l�ses av och g�r vidare till en for-loop.
                scanf("%s", sokord);
                printf("\n");
                    for(i=0;i<*raknare; i++)
                    {
                        // H�r s� j�mf�rs s�kordet som man angivit med f�rfattaren som finns i bokregistret.
                        // strcasestr j�mf�r bokst�verna som man angivit med f�rfattaren.
                        // strcasestr j�mf�r antalet bokst�ver, bokst�vernas ordning och �r helt oberoende av stora och sm� bokst�ver.
                        // S�kordet ska matcha ihop med f�rfattarna som finns i bokregistret.
                        // Om s� �r fallet, s� skrivs dessa f�rfattarna ut, f�ljd av boktitlarna och utgivnings�ren som f�rfattarna erh�ller.
                        if(strcasestr(bocker[i].forfattare , sokord))
                        {
                         printf("%d. [F�rfattare]: %s   [Boktiteln]: %s  [�r]: %s\n",j+1, bocker[i].forfattare, bocker[i].boktiteln, bocker[i].utgivningsar);
                         // Bokuppgifterna som man f�r fram fr�n s�kresultaten lagras i indexet list_of_alternatives[j].
                         // Denna index beh�vs f�r att man ska kunna ta bort en bok eller �ndra p� en bok.
                         list_of_alternatives[j] = i;
                         j++;
                        }
                    }
                break;
                // Har man valt 2 som sitt val, s� vill man s�ka efter boktiteln.
                case 2:
                printf("\n");
                printf("S�k efter en bok med hjalp av boktiteln: \n\n");
                printf("- ");
                // S�kordet l�ses av och tar dig senare till en for-loop.
                scanf("%s", sokord);
                printf("\n");
                    for(i=0;i<*raknare;i++)
                    {
                        // H�r s� j�mf�rs s�kordet som man angivit med boktitlarna som finns i bokregistret.
                        // strcasestr j�mf�r bokst�verna som man angivit med boktiteln.
                        // strcasestr j�mf�r antalet bokst�ver, bokst�vernas ordning och �r helt oberoende av stora och sm� bokst�ver.
                        // S�kordet ska matcha ihop med boktitlarna som finns i bokregistret.
                        // Om s� �r fallet, s� skrivs dessa boktitlarna ut, f�ljd av f�rfattarna och utgivnings�ren som boktitlarna tillh�r.
                        if(strcasestr(bocker[i].boktiteln, sokord))
                        {
                         printf("%d. [Boktiteln]: %s   [Forfattare]: %s  [�r]: %s\n",j+1, bocker[i].boktiteln, bocker[i].forfattare, bocker[i].utgivningsar);
                         // Bokuppgifterna som man f�r fram fr�n s�kresultaten lagras i indexet list_of_alternatives[j].
                         // Denna index beh�vs f�r att man ska kunna ta bort en bok eller �ndra p� en bok.
                         list_of_alternatives[j] = i;
                         j++;
                        }
                    }

                break;
                // Har man valt 3 som sitt val, s� vill man s�ka efter utgivnings�ret.
                case 3:
                printf("\n");
                printf("S�k efter en bok med hj�lp av utgivnings�ret: \n\n");
                printf("- ");
                // S�kordet l�ses av och tar dig senare till en for-loop.
                scanf("%s", sokord);
                printf("\n");
                    for(i = 0; i < *raknare; i++)
                    {
                        // H�r s� j�mf�rs s�kordet som man angivit med utgivnings�ren som finns i bokregistret.
                        // strcasestr j�mf�r siffrorna som man angivit med utgivnings�ret.
                        // strcasestr j�mf�r antalet siffror, siffrornas ordning, osv.
                        // S�kordet ska matcha ihop med utgivnings�ren som finns i bokregistret.
                        // Om s� �r fallet, s� skrivs dessa utgivnings�r ut, f�ljd av f�rfattarna och boktitlarna som tillh�r utgivnings�ren.
                        if(strcasestr(bocker[i].utgivningsar , sokord))
                        {
                         printf("%d. [�r]: %s   [F�rfattare]: %s  [Boktiteln]: %s\n",j+1, bocker[i].utgivningsar, bocker[i].forfattare, bocker[i].boktiteln);
                         // Bokuppgifterna som man f�r fram fr�n s�kresultaten lagras i indexet list_of_alternatives[j].
                         // Denna index beh�vs f�r att man ska kunna ta bort en bok eller �ndra p� en bok.
                         list_of_alternatives[j] = i;
                         j++;
                        }
                    }
                break;
            }
    }

    // Detta �r funktionen f�r att man ska kunna sortera bokuppgifterna som finns i bokregistret efter en viss ordning.
    // [raknare] �r sj�lva countern. Det �r den som kommer hj�lpa med att sortera b�ckerna som finns i bokregistret.
    // Bubbelsorterings-algoritmen anv�nds i denna funktion, f�r att man ska kunna sortera efter f�rfattare, boktiteln eller utgivnings�ret.
    // Bubbelsorteringsalgoritmen: Om f�rsta bokstaven till v�nster kommer f�rst i alfabetsordningen och detta g�ller genom hela att studera inneh�llet i f�rfattare, boktiteln eller utgivnings�ret.
    // S� kommer b�ckerna att byta plats med varandra.
    // Sker inte detta, s� byter b�ckerna inte plats med varandra.
    void sortera_bocker(struct bokuppgift *bocker, int *raknare)
    {
        int val_av_sortering=0;
        // F�r structen bokuppgift, s� ska en variabel skapas. Denna variabel ska heta temporary.
        // Denna variabel ser till att b�ckerna beh�ller den ordningen som den har/kommer att ha.
        struct bokuppgift temporary;
        int z=0;
        int i;
        printf("\n");
        printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
        printf("\n");
        // H�r fr�gar den vad man vill sortera b�ckerna efter �r det f�rfattare man vill sortera efter? Boktiteln? Eller utgivnings�ret?
        printf("Vad vill du sortera b�ckerna efter?\n");
        printf("\n");
        printf("- F�rfattare (1)\n");
        printf("- Boktiteln (2)\n");
        printf("- Utgivnings�ret (3)\n");
        printf("\n");
        printf("Ditt val: ");
        // Valet l�ses av och g�r vidare till en for-loop, som senare tar dig till en if-sats
        scanf("%d",&val_av_sortering);

            for (i=*raknare-1;i>0;i--)
            {
                for (z=1;z<=i;z++)
                {
                    // Om man har valt 1 som sitt val, vill man sortera efter f�rfattare.
                    // Denna if-sats ska kontrollera om val_av_sortering blir st�rre �n 0.
                    // Om s� �r fallet, s� kommer z-1 och z byta plats med varandra.
                    // Detta f�r att z kommer f�re z-1 i alfabetet.
                    // D� kommer b�ckerna att sorteras efter f�rfattare i bokstavsordning.
                    // Sorteringen �r inte beroende av stora och sm� bokst�verna.
                    // Detta p� grund av att man anv�nder strcasecmp.
                    if (val_av_sortering  == 1 && strcasecmp(bocker[z-1].forfattare,bocker[z].forfattare) > 0)
                    {
                     // temporary-variabeln h�r menas hur b�ckerna ser ut i bokregistret, innan den ska sorteras.
                     temporary = bocker[z-1];
                     bocker[z-1] = bocker[z];
                     // temporary-variabeln �r den som ska se till att b�ckerna sorteras efter f�rfattare.
                     bocker[z] = temporary;
                    }
                    // Har man valt 2 som sitt val, vill man sortera efter boktiteln.
                    // Denna if-sats ska kontrollera om val_av_sortering blir st�rre �n 0.
                    // Om s� �r fallet, s� kommer z-1 och z byta plats med varandra.
                    // Detta f�r att z kommer f�re z-1 i alfabetet.
                    // D� kommer b�ckerna att sorteras efter boktiteln i bokstavsordning.
                    // Sorteringen �r inte beroende av stora och sm� bokst�verna.
                    // Detta p� grund av att man anv�nder strcasecmp.
                    if (val_av_sortering == 2 && strcasecmp(bocker[z-1].boktiteln,bocker[z].boktiteln) > 0)
                    {
                     // temporary-variabeln h�r menas hur b�ckerna ser ut i bokregistret, innan den ska sorteras.
                     temporary = bocker[z-1];
                     bocker[z-1] = bocker[z];
                     // temporary-variabeln �r den som ska se till att b�ckerna sorteras efter boktiteln.
                     bocker[z] = temporary;
                    }
                    // Har man valt 3 som sitt val, vill man sortera efter utgivnings�ret.
                    // Denna if-sats ska kontrollera om val_av_sortering blir st�rre �n 0.
                    // Om s� �r fallet, s� kommer z-1 och z byta plats med varandra.
                    // Detta f�r att z kommer f�re z-1 i alfabetet.
                    // D� kommer b�ckerna att sorteras efter utgivnings�r i sifferordning.
                    // Detta p� grund av att man anv�nder strcasecmp.
                    if (val_av_sortering  == 3 && strcasecmp(bocker[z-1].utgivningsar,bocker[z].utgivningsar) > 0)
                    {
                     // temporary-variabeln h�r menas hur b�ckerna ser ut i bokregistret, innan den ska sorteras.
                     temporary = bocker[z-1];
                     bocker[z-1] = bocker[z];
                     // temporary-variabeln �r den som ska se till att b�ckerna sorteras efter utgivnings�r.
                     bocker[z] = temporary;
                    }
                }
            }
    }

    // Detta �r funktionen f�r att man ska kunna skriva ut alla bokuppgifterna som finns i  bokregistret.
    // Man kan skriva ut b�ckerna efter att man sorterat b�ckerna efter en viss ordning, f�r att se om b�ckerna blev sorterade.
    void skriv_ut_alla_bocker(struct bokuppgift *bocker, int *raknare)
    {
        int i;
        printf("\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n");
        printf("- H�r har alla bokuppgifter fr�n denna register skrivits ut -");
        printf("\n");
        printf("\n");
            // En for-loop startar och kommer skriva ut alla b�cker som finns i bokregistret med hj�lp av [raknare].
            // Funktionen pekar till [raknare] och samlar allt data ifr�n den, f�r att sedan kunna skriva ut det.
            // Bokuppgifterna skrivs ut f�rst med f�rfattaren, d�refter f�ljer boktitlarna och utgivnings�ren med.
            for(i=0;i<*raknare;i++)
            {
             printf("%d. [F�rfattare]: %s   [Boktiteln]: %s  [�r]: %s\n", i+1, bocker[i].forfattare, bocker[i].boktiteln, bocker[i].utgivningsar);
            }
    }

    // Detta �r en funktion f�r att man ska kunna spara filen, allts� bokregistret som man jobbat p�.
    // [counter] �r sj�lva d�r b�ckerna finns. Alla b�cker som man har lagt till, �ndrat, sorterat, kommer att sparas sedan i [counter].
    // [counter] sparar allt data i bokregistret allm�nt, som filen sedan erh�ller.
    void spara_och_avsluta_bokregistret(struct bokuppgift books[MAX], char fil_namnet[MAX], int *counter)
    {
        FILE *filen;
        int i;
        filen = fopen(fil_namnet, "wb");
            // H�r s� sparas sj�lva filen (bokregistret).
            // Med hj�lp av fwrite() s� skriver den in all information som har f�r�ndrats i bokregistret.
            for(i=0;i<*counter;i++)
            {
             fwrite(&books[i],sizeof(struct bokuppgift),1,filen);
            }
    }

    // Detta �r mainfunktionen. Det h�r �r alla menyer, funktionsanrop, if-satser, switch-satserna, de flesta variablerna finns.
    int main(void)
    {
        int valforstamenyn, valandramenyn;
        int list_of_alternatives[MAX];
        int i, counter=0;
        int fortsatt;
        fortsatt=0;
        char fil_namnet[MAX];
        struct bokuppgift books[MAX];

        // H�r b�rjar programmet. F�rsta menyn ska dyka upp och ge dig 3 val som du f�r v�lja mellan.
        printf("\n");
        printf("V�lkommen till bokregistersprogrammet! V�lj nagot utav dessa val nedan:");
        printf("\n");
        printf("\n");
        printf ("- Arbeta med ett redan existerande bokregister. (1)\n");
        printf ("- Skapa ett nytt bokregister. (2)\n");
        printf ("- Avsluta programmet. (3)\n");
        printf ("\n");
        printf ("Ditt val: ");
        // Valet l�ses av och g�r vidare sen till en if-sats.
        scanf("%d", &valforstamenyn);
            // Funktionen till att �ppna en existerande bokregister, anropas h�r.
            if (valforstamenyn == 1)
                oppna_ett_existerande_fil_bokregister(books, fil_namnet, &counter);
            // Funktionen till att skapa ett nytt bokregister, anropas h�r.
            if (valforstamenyn == 2)
                skapa_ett_nytt_fil(fil_namnet);
            // Funktionen till att avsluta programmet, anropas h�r.
            if (valforstamenyn == 3)
                avsluta_programmet();

                    // V�ljs val 1 eller 2 fr�n den f�rsta menyn, s� kommer den att g� vidare till andra menyn.
                    // Detta med hj�lp av en while-loop som man har skapat.
                    // Andra menyn som dyker upp, kommer att ge dig 7 val som du f�r v�lja mellan.
                    while (fortsatt == 0)
                    {
                        printf("\n");
                        printf("-------------------------------------------------------------------------------");
                        printf("\n");
                        printf("I denna meny s� har du olika alternativ f�r ditt bokregister:");
                        printf("\n");
                        printf("\n");
                        printf ("1. L�gg till en bokuppgift till registret. \n");
                        printf ("2. Ta bort en bokuppgift fr�n registret.\n");
                        printf ("3. �ndra en bokuppgift.\n");
                        printf ("4. S�k efter en bokuppgift.\n");
                        printf ("5. Sortera alla bokuppgifter. \n");
                        printf ("6. Skriva ut alla bokuppgifter \n");
                        printf ("7. Avsluta. \n");
                        printf("\n");
                        printf ("Ditt val: ");
                        // Valet l�ses av och g�r vidare senare till en switch-sats.
                        scanf("%d", &valandramenyn);

                            switch(valandramenyn)
                            {
                                // Funktion f�r att l�gga till en bok, anropas h�r.
                                case 1: lagg_till_en_bok(books, &counter); break;
                                // Funktion f�r att ta bort en bok, anropas h�r.
                                case 2: ta_bort_en_bok(books, &counter, list_of_alternatives); break;
                                // Funktion f�r att �ndra en bok, anropas h�r.
                                case 3: andra_en_bok(books, &counter, list_of_alternatives); break;
                                // Funktion f�r att s�ka efter b�cker, anropas h�r.
                                case 4: sok_efter_en_bok(books, &counter, list_of_alternatives); break;
                                // Funktion f�r att sortera b�ckerna, anropas h�r.
                                case 5: sortera_bocker(books, &counter); break;
                                // Funktion f�r att skriva ut alla b�cker, anropas h�r.
                                case 6: skriv_ut_alla_bocker(books, &counter); break;
                                // Funktion f�r att spara och avsluta bokregistret, anropas h�r.
                                // D� sparas bokregistret och d�rmed avslutas sj�lva programmet.
                                case 7: spara_och_avsluta_bokregistret(books, fil_namnet, &counter);
                                fortsatt = 1; break;
                            }
                    }

    }

    // Detta �r funktionen f�r att man ska kunna l�sa av en string som inneh�ller mellanslag.
    // D� scanf inte har st�d f�r att l�sa mellanslag (utan hoppar direkt till n�sta rad), s� �r denna funktion anv�ndbar.
    // Viktigt om man skriver in in f�rnamnet/efternamnet p� en f�rfattare eller ord som ska inneh�lla mellanslag efter varandra f�r boktiteln.
    // las_rad funktionen l�ser av hela stringen d� och forts�tter till n�sta rad, n�r man klickar p� Enter.
    int las_rad(char str[], int n)
    {
        int ch, i=0;

        while (isspace(ch=getchar()));
        while (ch != '\n' && ch != EOF)
        {
            if (i < n)
            str[i++] = ch;
            ch = getchar();
        }
        str[i] = '\0';
        return i;
    }

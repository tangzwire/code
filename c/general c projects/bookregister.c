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

    // Här har jag placerat min struct i början av programmet. Structen heter bokuppgift.
    // Här kommer man att vilja lagra författare, boktiteln och utgivningsår i en variabel (bokuppgift) i form av strängar.
    // Man använder struct, för att vi ska kunna samla uppgifter utav olika typer.
    // Denna struct kommer användas i programmet hela tiden, för att man ska kunna lagra bokuppgifter.
    // Med hjälp av en sådan struct, så ska man kunna jobba med innehållet som finns i den i olika typer av funktioner.
    struct bokuppgift
    {
        char forfattare[30];
        char boktiteln[40];
        char utgivningsar[30];
    };

    // Detta är funktionen för att man ska kunna öppna ett existerande fil (en existerande bokregister alltså).
    // [counter]är den som erhåller alla böcker.
    // Används för att denna funktion ska kunna läsa av innehållet som finns i [counter]
    // fseek() används då för att man ska kunna röra sig runt om filen som är öppnad.
    void oppna_ett_existerande_fil_bokregister(struct bokuppgift bocker[MAX], char fil_namnet[MAX], int *counter)
    {
        FILE *filen;
        int j;
        printf("_______________________________________________________________________________");
        printf("\n");
        printf("Ange namnet på filen till din bokregister, som du vill öppna:\n\n ");
        printf("- ");
        scanf("%s", fil_namnet);
        // Här öppnas filen för att den ska kunna läsas av.
        // Med hjälp av fopen så öppnas filen genom att fil_namnet pekar på filens namn som ska öppnas i programmet.
        filen = fopen(fil_namnet, "rb");
            // Om det visar sig att filen ej existerar/har fel namn, så kommer ett meddelande som talar om detta.
            // Detta med hjälp av en print funktion.
            // Detta sker då om returvärdet på fopen() är en NULL-pekare. Denna talar om då att anropet till filen har misslyckats.
            if(filen == NULL)
            {
              printf("\nDet gick inte att öppna filen. Det kan vara så att filen har tagits bort, har fel namn eller ej har skapats.\n");
              exit(EXIT_FAILURE);
            }

        // Här så placerar man pekaren i slutet av filen.
        // Man ska kunna alltså röra sig till slutet av filen i programmet.
        // fseek(SEEK_END) söker igenom positionerna i innehållet till slutet av filen.
        fseek(filen,0,SEEK_END);
        // ftell(filen)/sizeof(struct bokuppgift) talar om filens position, samt hur många böcker som det finns i bokregistret.
        // Denna räknar ut antal böcker i bokregistret.
        *counter=ftell(filen)/sizeof(struct bokuppgift);
        // Här så placerar man pekaren i början av filen.
        // Man ska kunna alltså röra sig till början av filen i programmet.
        // fseek(SEEK_SET) söker igenom positionerna i innehållet till början av filen.
        fseek(filen,0,SEEK_SET);
            // Man har gjort en for-loop för att kunna läsa av filen som man vill öppna.
            // fread läser av böckerna, samt antal böcker som finns i bokregistret (detta med hjälp av sizeof)
            for (j=0;j<*counter;j++)
            {
              fread(&bocker[j],sizeof(struct bokuppgift),1,filen);
            }
        // För att alla ändringar som vi utför i filen ska kunna sparas, så måste fclose() anropas.
        // Strömmen som tillhör filen, som vi jobbar med genom att skriva på den, måste stängas med fclose().
        fclose(filen);
    }

    // Detta är en funktion för att man ska kunna skapa ett nytt fil för sin nya bokregister.
    // Då skriver man in namnet på filen som ska skapas.
    void skapa_ett_nytt_fil(char fil_namnet[MAX])
    {
        FILE *filen;
        printf("________________________________________________________________________________");
        printf("\n");
        printf("Ange namnet på den nya filen till ditt bokregister, som du vill skapa:\n\n ");
        printf("- ");
        scanf("%s", fil_namnet);
        // Här skapas filen till det nya bokregistret.
        filen = fopen(fil_namnet , "wb");
        // För att alla ändringar som vi utför i filen ska kunna sparas, så måste fclose() anropas.
        // Strömmen som tillhör filen, som vi jobbar med genom att skriva på den, måste stängas med fclose().
        // I det här fallet så sparas den nya filen efter att den skapats utan någon innehåll i filen.
        fclose(filen);
    }

    // Detta är funktionen för att man ska kunna avsluta programmet från allra första början (om man inte vill jobba med programmet).
    void avsluta_programmet(void)
    {
        // Exit är den som avslutar programmet.
        exit(1);
    }

    // Detta är funktionen för att man ska kunna lägga till böcker i bokregistret.
    // [raknare] är själva countern. Det är den som kommer hjälpa till att mata in bokuppgifterna som jag lägger till i registret.
    // [raknare] börjar från 0. Lägger man till en bokuppgift, så ökar [raknare] med 1.
    // Ju mer bokuppgifter som läggs, desto mer ökar [raknare].
    // Då tar [bocker] emot uppgifterna som [raknare] lägger in och sparar de i bokregistret.
    void lagg_till_en_bok(struct bokuppgift *bocker, int *raknare)
    {
        printf("\n");
        printf("********************************************************************************");
        printf("\n");
        printf("Skriv in uppgifterna på din nya bok som ska läggas in i registret:");
        printf("\n");
        printf("\n");
        printf("Författare: ");
        // Här ropas string-funktionen las_rad, då denna string ska kunna läsa av mellanslag.
        // Detta för att om man ska skriva in förnamnet och efternamnet på författaren så ska mellanslag också såklart komma emellan där.
        las_rad(bocker[*raknare].forfattare, MAX);
        printf("Boktiteln: ");
        // Här ropas string-funktionen las_rad, då denna string ska kunna läsa av mellanslag.
        // Detta för att om man ska skriva in namnet på boktiteln, så kommer mellanslag dyka upp hela tiden mellan varje ord.
        las_rad(bocker[*raknare].boktiteln, MAX);
        printf("Utgivningsar: ");
        // Här krävs ingen anrop till någon string-funktion som las_rad, då man skriver in utgivningsåret utan mellanslag.
        // Då räcker det kort och gott med en scanf-funktion.
        scanf("%s", bocker[*raknare].utgivningsar);
    // Efter att uppgifterna på den nya boken skrivits och lästs av, så läggs den in som en bokuppgift i [raknare].
    // Boken som skapas, pekas till [raknare] och läggs till där. Det är här siffran ökar i [raknare].
    (*raknare)++;
    }

    // Detta är funktionen för att man ska kunna ta bort böcker från bokregistret.
    // [raknare] är själva countern. Det är den som kommer hjälpa ta bort de bokuppgifter som man väljer att ta bort.
    // [raknare] börjar från den siffran så mycket som det finns bokuppgifter.
    // Tar man bort en bokuppgift, så minskar [raknare] med 1.
    // [raknare] tar då alltså bort bokuppgiften från [bocker] så att den inte finns kvar i bokregistret.
    // strcopy används då för att uppgifterna till boken ska tas bort.
    // Variabeln radera_boken kommer användas för att se till att boken raderas.
    void ta_bort_en_bok(struct bokuppgift *bocker, int *raknare, int list_of_alternatives[MAX])
    {
        // Sökningsfunktionen ropas här. Detta för att man ska kunna söka efter den boken som man vill ta bort från bokregistret.
        sok_efter_en_bok(bocker, raknare, list_of_alternatives);

        int val_av_bok=0, radera_boken;

        printf("\n");
        printf("Vilken bok vill du ta bort från denna register, utifrån din sökresultat?\n");
        printf("\n");
        printf("Ditt val: ");

        // Här så läses själva valet på boken som ska tas bort av och skickar dig vidare till en for-loop.
        scanf("%d",&val_av_bok);

            // list_of_alternatives[val_av_bok-1] är den som kommer upp när man har sökt igenom bokregistret.
            // Den får fram listan av böckerna som man får fram utifrån sin sökord.
            // Med hjälp av list_of_alternatives[val_av_bok-1] så omvandlar det numret som man har matat in till det riktiga array numret.
            // Om vi t.ex har tre böcker i bokregistret:
            // 0. Tanvir Rozario   -- 0 är skriven för att ett array börjar alltid från 0 till MAX.
            // 1. Trey Songz
            // 2. Tata Latina
            // Söker vi på "Ta" som sökord, så ska bara Tanvir Rozario och Tata Latina dyka upp.
            // Då placeras Tanvir Rozario först i listan i nummer 0 och sedan Tata Latina på andra platsen (nummer 1).
            // Detta innebär att om man vill ta bort Tata Latina från bokregistret så anger man siffran 2.
            // Siffran 2 förvandlas till 1 och tar sedan bort Tata Latina från bokregistret.
            for(radera_boken=list_of_alternatives[val_av_bok-1];radera_boken<*raknare; radera_boken++)
            {
             strcpy(bocker[radera_boken].forfattare, bocker[radera_boken+1].forfattare);
             strcpy(bocker[radera_boken].boktiteln,bocker[radera_boken+1].boktiteln);
             strcpy(bocker[radera_boken].utgivningsar,bocker[radera_boken+1].utgivningsar);
            }
    // Efter att man valt vilken bok som ska raderas, så tas boken bort från [raknare].
    // Boken som raderas, pekas till [raknare] och tas bort därifrån. Det är här siffran minskar i [raknare].
    // Därefter så kontrollerar funktionen om det finns någon tom plats som är tom.
    // Om så är fallet, så flyttas en bok som finns i bokregistret till den tomma platsen.
    (*raknare)--;
    }

    // Detta är funktionen för att man ska kunna ändra en bokuppgift i bokregistret.
    // [raknare] är själva countern. Det är den som kommer hjälpa med att ändra själva boken som man har valt att ändra.
    // Ändras en bokuppgift, så kommer den pekas till [raknare] och skicka iväg bokuppgiften som ändrats dit till [bocker].
    // Bokuppgiften sparas då där.
    // Samtidigt som vi ändrar informationen på en bokuppgift, tas den gamla informationen av bokuppgiften bort.
    void andra_en_bok(struct bokuppgift *bocker, int *raknare, int list_of_alternatives[MAX])
    {
        int val_av_andrings_metod;
        int val_av_andring_bok;
        printf("\n");
        printf("********************************************************************************");
        printf("\n");
        // I den här ändra en bok-funktionen, så har man underlättat det lite för den som vill ändra en bok.
        // Om det skulle vara som så att man vill bara ändra författaren, boktiteln eller utgivningsåret på en bok, så finns det som ett val.
        // Annars kan man välja att ändra en hel bok (alltså författaren, boktiteln samt utgivningsåret).
        printf("Ange om du vill ändra en hel bokuppgift eller en del utav bokuppgiften.\n\n");
        printf("- En hel bokuppgift (1)\n");
        printf("- En del utav bokuppgiften (2)\n");
        printf("\n");
        printf("Ditt val: ");
        // Valet läses av och går vidare till en if-sats.
        scanf("%d", &val_av_andrings_metod);
            // Om man har valt 1 som sitt val, så innebär det att man vill ändra en hel bok (författaren, boktiteln och utgivningsåret).
            if (val_av_andrings_metod == 1)
            {
             // Sökningsfunktionen ropas här. Detta för att man ska kunna söka efter den boken som man vill ändra på från bokregistret.
             sok_efter_en_bok(bocker, raknare, list_of_alternatives);
             printf("\n");
             printf("Vilken bok vill du ändra?\n");
             printf("\n");
             printf("Ditt val: ");
             scanf("%d",&val_av_andring_bok);
             // list_of_alternatives[val_av_bok-1] är den som kommer upp när man har sökt igenom bokregistret.
             // Den får fram listan av böckerna som man får fram utifrån sin sökord.
             // Med hjälp av list_of_alternatives[val_av_bok-1] så omvandlar det numret som man har matat in till det riktiga array numret.
             // Om vi t.ex har tre böcker i bokregistret:
             // 0. Tanvir Rozario   -- 0 är skriven för att ett array börjar alltid från 0 till MAX.
             // 1. Trey Songz
             // 2. Tata Latina
             // Söker vi på "Ta" som sökord, så ska bara Tanvir Rozario och Tata Latina dyka upp.
             // Då placeras Tanvir Rozario först i listan i nummer 0 och sedan Tata Latina på andra platsen (nummer 1).
             // Detta innebär att om man vill ändra på Tata Latina i bokregistret så anger man siffran 2.
             // Siffran 2 förvandlas till 1 och ändrar sedan Tata Latina i bokregistret.
             printf("\n");
             //Här skriver man in de nya uppgifterna på hela boken som man vill ändra på (författaren, boktiteln och utgivningsåret).
             printf("Författarens nya namn: ");
             // Här ropas string-funktionen las_rad, då denna string ska kunna läsa av mellanslag.
             // Detta för att om man ska skriva in förnamnet och efternamnet på författaren så ska mellanslag också såklart komma emellan där.
             las_rad(bocker[list_of_alternatives[val_av_andring_bok-1]].forfattare, MAX);
             printf("Bokens nya titel: ");
             // Här ropas string-funktionen las_rad, då denna string ska kunna läsa av mellanslag.
             // Detta för att om man ska skriva in namnet på boktiteln, så kommer mellanslag dyka upp hela tiden mellan varje ord.
             las_rad(bocker[list_of_alternatives[val_av_andring_bok-1]].boktiteln, MAX);
             printf("Den nya publiceringsåret: ");
             // Här krävs ingen anrop till någon string-funktion som las_rad, då man skriver in utgivningsåret utan mellanslag.
             // Då räcker det kort och gott med en scanf-funktion.
             scanf("%s", bocker[list_of_alternatives[val_av_andring_bok-1]].utgivningsar, MAX);
            }
             // Om man har valt 2 som sitt val, så innebär det att man vill ändra bara en del av en bok
             // Det kan antingen vara författaren, boktiteln eller utgivningsåret som man vill ändra på.
             // Då måste en variabel skapas. Denna variabel används för att tala om vad du vill ändra i boken.
             // Variabeln heter val_av_uppgiftsandring.
            if (val_av_andrings_metod == 2)
            {
             int val_av_uppgiftsandring;
             printf("\n\n");
             // Sökningsfunktionen ropas här. Detta för att man ska kunna söka efter den boken som man vill ändra på från bokregistret.
             sok_efter_en_bok(bocker, raknare, list_of_alternatives);
             printf("\n");
             printf("Vilken bok vill du ändra en uppgift på?\n");
             printf("\n");
             printf("Ditt val: ");
             scanf("%d", &val_av_andring_bok);
             // list_of_alternatives[val_av_bok-1] är den som kommer upp när man har sökt igenom bokregistret.
             // Den får fram listan av böckerna som man får fram utifrån sin sökord.
             // Med hjälp av list_of_alternatives[val_av_bok-1] så omvandlar det numret som man har matat in till det riktiga array numret.
             // Om vi t.ex har tre böcker i bokregistret:
             // 0. Tanvir Rozario  -- 0 är skriven för att ett array börjar alltid från 0 till MAX.
             // 1. Trey Songz
             // 2. Tata Latina
             // Söker vi på "Ta" som sökord, så ska bara Tanvir Rozario och Tata Latina dyka upp.
             // Då placeras Tanvir Rozario först i listan i nummer 0 och sedan Tata Latina på andra platsen (nummer 1).
             // Detta innebär att om man vill ändra på Tata Latina i bokregistret så anger man siffran 2.
             // Siffran 2 förvandlas till 1 och ändrar sedan Tata Latina i bokregistret.
             printf("\n");
             // Här kommer funktionen fråga vad man vill ändra i boken. Är det författaren? Boktiteln? Eller kanske utgivningsåret?
             printf("Vilken uppgift skall ändras i denna bok? \n\n");
             printf("1. Författaren skall ändras.\n");
             printf("2. Boktiteln skall ändras.\n");
             printf("3. Utgivningsåret skall ändras.\n");
             printf("\n");
             printf("Ditt val: ");
             // Valet läses av och går vidare till en annan if-sats.
             scanf("%d", &val_av_uppgiftsandring);

                // Har man valt 1 som sitt val, vill man ändra på författaren.
                // Återigen, så kommer las_rad funktionen in här, som ska kunna läsa av mellanslag.
                // Detta för att man ska kunna skriva mellanslag om man anger förnamn och efternamn på författaren.
                if (val_av_uppgiftsandring == 1)
                {
                 printf("\n");
                 printf("Författarens nya namn: ");
                 las_rad(bocker[list_of_alternatives[val_av_andring_bok-1]].forfattare, MAX);
                }
                // Har man valt 2 som sitt val, vill man ändra på boktiteln.
                // Återigen, så kommer las_rad funktionen in här, som ska kunna läsa av mellanslag.
                // Detta för att man ska kunna skriva mellanslag mellan ord som skrivs in för boktiteln.
                if (val_av_uppgiftsandring == 2)
                {
                 printf("\n");
                 printf("Bokens nya titel: ");
                 las_rad(bocker[list_of_alternatives[val_av_andring_bok-1]].boktiteln, MAX);
                }
                // Har man valt 3 som sitt val, vill man ändra på utgivningsåret.
                // Här krävs ingen anrop för string-funktion som las_rad.
                // Detta för att man anger utgivningsåret utan mellanslag.
                // Då räcker det kort och gott med en scanf-funktion.
                if (val_av_uppgiftsandring == 3)
                {
                 printf("\n");
                 printf("Den nya publiceringsåret: ");
                 scanf("%s", bocker[list_of_alternatives[val_av_andring_bok-1]].utgivningsar, MAX);
                }
            }
    }

    // Detta är funktionen för att man ska kunna söka igenom bokregistret efter bokuppgifter.
    // [raknare] är själva countern. Det är den som kommer hjälpa med att söka igenom bokregistret efter bokuppgifter.
    // En for-loop skapas då. Denna ska generera bokuppgifterna som finns i bokregistret efter sökkriterien.
    // Uppgifterna som finns i sökresultat, lagras då i en index, som ska sedan användas för att man ska kunna ta bort eller ändra en bok.
    // Denna index kallas för list_of_alternatives[MAX].
    // Sök funktionen defineras som en int, då denna ska kunna användas inne i andra funktioner som ta bort-funktionen, ändra-funktionen.
    int sok_efter_en_bok(struct bokuppgift *bocker, int *raknare, int list_of_alternatives[MAX])
    {
        int val=1;
        int i,j=0;
        // En sökarray som deklareras. Denna ska senare i funktionen jämföras med [raknare].
        char sokord[MAX];
        printf("\n");
        printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
        printf("\n");
        // Här frågar den vad man vill söka efter. Är det författaren? Boktiteln? Eller utgivningsåret?
        printf("Vad vill du söka efter?");
        printf("\n");
        printf("\n");
        printf("- Författare (1)\n");
        printf("- Boktiteln (2)\n");
        printf("- Utgivningsår (3)\n");
        printf("\n");
        printf("Ditt val: ");
        // Valet läses av och går senare till en switch-sats.
        scanf("%d",&val);
            // Om man valt 1 som sitt val, så vill man söka efter författaren.
            switch(val)
            {
                case 1:
                printf("\n");
                printf("Sök efter en bok med hjälp av författare: \n\n");
                printf("- ");
                // Sökordet läses av och går vidare till en for-loop.
                scanf("%s", sokord);
                printf("\n");
                    for(i=0;i<*raknare; i++)
                    {
                        // Här så jämförs sökordet som man angivit med författaren som finns i bokregistret.
                        // strcasestr jämför bokstäverna som man angivit med författaren.
                        // strcasestr jämför antalet bokstäver, bokstävernas ordning och är helt oberoende av stora och små bokstäver.
                        // Sökordet ska matcha ihop med författarna som finns i bokregistret.
                        // Om så är fallet, så skrivs dessa författarna ut, följd av boktitlarna och utgivningsåren som författarna erhåller.
                        if(strcasestr(bocker[i].forfattare , sokord))
                        {
                         printf("%d. [Författare]: %s   [Boktiteln]: %s  [År]: %s\n",j+1, bocker[i].forfattare, bocker[i].boktiteln, bocker[i].utgivningsar);
                         // Bokuppgifterna som man får fram från sökresultaten lagras i indexet list_of_alternatives[j].
                         // Denna index behövs för att man ska kunna ta bort en bok eller ändra på en bok.
                         list_of_alternatives[j] = i;
                         j++;
                        }
                    }
                break;
                // Har man valt 2 som sitt val, så vill man söka efter boktiteln.
                case 2:
                printf("\n");
                printf("Sök efter en bok med hjalp av boktiteln: \n\n");
                printf("- ");
                // Sökordet läses av och tar dig senare till en for-loop.
                scanf("%s", sokord);
                printf("\n");
                    for(i=0;i<*raknare;i++)
                    {
                        // Här så jämförs sökordet som man angivit med boktitlarna som finns i bokregistret.
                        // strcasestr jämför bokstäverna som man angivit med boktiteln.
                        // strcasestr jämför antalet bokstäver, bokstävernas ordning och är helt oberoende av stora och små bokstäver.
                        // Sökordet ska matcha ihop med boktitlarna som finns i bokregistret.
                        // Om så är fallet, så skrivs dessa boktitlarna ut, följd av författarna och utgivningsåren som boktitlarna tillhör.
                        if(strcasestr(bocker[i].boktiteln, sokord))
                        {
                         printf("%d. [Boktiteln]: %s   [Forfattare]: %s  [År]: %s\n",j+1, bocker[i].boktiteln, bocker[i].forfattare, bocker[i].utgivningsar);
                         // Bokuppgifterna som man får fram från sökresultaten lagras i indexet list_of_alternatives[j].
                         // Denna index behövs för att man ska kunna ta bort en bok eller ändra på en bok.
                         list_of_alternatives[j] = i;
                         j++;
                        }
                    }

                break;
                // Har man valt 3 som sitt val, så vill man söka efter utgivningsåret.
                case 3:
                printf("\n");
                printf("Sök efter en bok med hjälp av utgivningsåret: \n\n");
                printf("- ");
                // Sökordet läses av och tar dig senare till en for-loop.
                scanf("%s", sokord);
                printf("\n");
                    for(i = 0; i < *raknare; i++)
                    {
                        // Här så jämförs sökordet som man angivit med utgivningsåren som finns i bokregistret.
                        // strcasestr jämför siffrorna som man angivit med utgivningsåret.
                        // strcasestr jämför antalet siffror, siffrornas ordning, osv.
                        // Sökordet ska matcha ihop med utgivningsåren som finns i bokregistret.
                        // Om så är fallet, så skrivs dessa utgivningsår ut, följd av författarna och boktitlarna som tillhör utgivningsåren.
                        if(strcasestr(bocker[i].utgivningsar , sokord))
                        {
                         printf("%d. [År]: %s   [Författare]: %s  [Boktiteln]: %s\n",j+1, bocker[i].utgivningsar, bocker[i].forfattare, bocker[i].boktiteln);
                         // Bokuppgifterna som man får fram från sökresultaten lagras i indexet list_of_alternatives[j].
                         // Denna index behövs för att man ska kunna ta bort en bok eller ändra på en bok.
                         list_of_alternatives[j] = i;
                         j++;
                        }
                    }
                break;
            }
    }

    // Detta är funktionen för att man ska kunna sortera bokuppgifterna som finns i bokregistret efter en viss ordning.
    // [raknare] är själva countern. Det är den som kommer hjälpa med att sortera böckerna som finns i bokregistret.
    // Bubbelsorterings-algoritmen används i denna funktion, för att man ska kunna sortera efter författare, boktiteln eller utgivningsåret.
    // Bubbelsorteringsalgoritmen: Om första bokstaven till vänster kommer först i alfabetsordningen och detta gäller genom hela att studera innehållet i författare, boktiteln eller utgivningsåret.
    // Så kommer böckerna att byta plats med varandra.
    // Sker inte detta, så byter böckerna inte plats med varandra.
    void sortera_bocker(struct bokuppgift *bocker, int *raknare)
    {
        int val_av_sortering=0;
        // För structen bokuppgift, så ska en variabel skapas. Denna variabel ska heta temporary.
        // Denna variabel ser till att böckerna behåller den ordningen som den har/kommer att ha.
        struct bokuppgift temporary;
        int z=0;
        int i;
        printf("\n");
        printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
        printf("\n");
        // Här frågar den vad man vill sortera böckerna efter Är det författare man vill sortera efter? Boktiteln? Eller utgivningsåret?
        printf("Vad vill du sortera böckerna efter?\n");
        printf("\n");
        printf("- Författare (1)\n");
        printf("- Boktiteln (2)\n");
        printf("- Utgivningsåret (3)\n");
        printf("\n");
        printf("Ditt val: ");
        // Valet läses av och går vidare till en for-loop, som senare tar dig till en if-sats
        scanf("%d",&val_av_sortering);

            for (i=*raknare-1;i>0;i--)
            {
                for (z=1;z<=i;z++)
                {
                    // Om man har valt 1 som sitt val, vill man sortera efter författare.
                    // Denna if-sats ska kontrollera om val_av_sortering blir större än 0.
                    // Om så är fallet, så kommer z-1 och z byta plats med varandra.
                    // Detta för att z kommer före z-1 i alfabetet.
                    // Då kommer böckerna att sorteras efter författare i bokstavsordning.
                    // Sorteringen är inte beroende av stora och små bokstäverna.
                    // Detta på grund av att man använder strcasecmp.
                    if (val_av_sortering  == 1 && strcasecmp(bocker[z-1].forfattare,bocker[z].forfattare) > 0)
                    {
                     // temporary-variabeln här menas hur böckerna ser ut i bokregistret, innan den ska sorteras.
                     temporary = bocker[z-1];
                     bocker[z-1] = bocker[z];
                     // temporary-variabeln är den som ska se till att böckerna sorteras efter författare.
                     bocker[z] = temporary;
                    }
                    // Har man valt 2 som sitt val, vill man sortera efter boktiteln.
                    // Denna if-sats ska kontrollera om val_av_sortering blir större än 0.
                    // Om så är fallet, så kommer z-1 och z byta plats med varandra.
                    // Detta för att z kommer före z-1 i alfabetet.
                    // Då kommer böckerna att sorteras efter boktiteln i bokstavsordning.
                    // Sorteringen är inte beroende av stora och små bokstäverna.
                    // Detta på grund av att man använder strcasecmp.
                    if (val_av_sortering == 2 && strcasecmp(bocker[z-1].boktiteln,bocker[z].boktiteln) > 0)
                    {
                     // temporary-variabeln här menas hur böckerna ser ut i bokregistret, innan den ska sorteras.
                     temporary = bocker[z-1];
                     bocker[z-1] = bocker[z];
                     // temporary-variabeln är den som ska se till att böckerna sorteras efter boktiteln.
                     bocker[z] = temporary;
                    }
                    // Har man valt 3 som sitt val, vill man sortera efter utgivningsåret.
                    // Denna if-sats ska kontrollera om val_av_sortering blir större än 0.
                    // Om så är fallet, så kommer z-1 och z byta plats med varandra.
                    // Detta för att z kommer före z-1 i alfabetet.
                    // Då kommer böckerna att sorteras efter utgivningsår i sifferordning.
                    // Detta på grund av att man använder strcasecmp.
                    if (val_av_sortering  == 3 && strcasecmp(bocker[z-1].utgivningsar,bocker[z].utgivningsar) > 0)
                    {
                     // temporary-variabeln här menas hur böckerna ser ut i bokregistret, innan den ska sorteras.
                     temporary = bocker[z-1];
                     bocker[z-1] = bocker[z];
                     // temporary-variabeln är den som ska se till att böckerna sorteras efter utgivningsår.
                     bocker[z] = temporary;
                    }
                }
            }
    }

    // Detta är funktionen för att man ska kunna skriva ut alla bokuppgifterna som finns i  bokregistret.
    // Man kan skriva ut böckerna efter att man sorterat böckerna efter en viss ordning, för att se om böckerna blev sorterade.
    void skriv_ut_alla_bocker(struct bokuppgift *bocker, int *raknare)
    {
        int i;
        printf("\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n");
        printf("- Här har alla bokuppgifter från denna register skrivits ut -");
        printf("\n");
        printf("\n");
            // En for-loop startar och kommer skriva ut alla böcker som finns i bokregistret med hjälp av [raknare].
            // Funktionen pekar till [raknare] och samlar allt data ifrån den, för att sedan kunna skriva ut det.
            // Bokuppgifterna skrivs ut först med författaren, därefter följer boktitlarna och utgivningsåren med.
            for(i=0;i<*raknare;i++)
            {
             printf("%d. [Författare]: %s   [Boktiteln]: %s  [År]: %s\n", i+1, bocker[i].forfattare, bocker[i].boktiteln, bocker[i].utgivningsar);
            }
    }

    // Detta är en funktion för att man ska kunna spara filen, alltså bokregistret som man jobbat på.
    // [counter] är själva där böckerna finns. Alla böcker som man har lagt till, ändrat, sorterat, kommer att sparas sedan i [counter].
    // [counter] sparar allt data i bokregistret allmänt, som filen sedan erhåller.
    void spara_och_avsluta_bokregistret(struct bokuppgift books[MAX], char fil_namnet[MAX], int *counter)
    {
        FILE *filen;
        int i;
        filen = fopen(fil_namnet, "wb");
            // Här så sparas själva filen (bokregistret).
            // Med hjälp av fwrite() så skriver den in all information som har förändrats i bokregistret.
            for(i=0;i<*counter;i++)
            {
             fwrite(&books[i],sizeof(struct bokuppgift),1,filen);
            }
    }

    // Detta är mainfunktionen. Det här är alla menyer, funktionsanrop, if-satser, switch-satserna, de flesta variablerna finns.
    int main(void)
    {
        int valforstamenyn, valandramenyn;
        int list_of_alternatives[MAX];
        int i, counter=0;
        int fortsatt;
        fortsatt=0;
        char fil_namnet[MAX];
        struct bokuppgift books[MAX];

        // Här börjar programmet. Första menyn ska dyka upp och ge dig 3 val som du får välja mellan.
        printf("\n");
        printf("Välkommen till bokregistersprogrammet! Välj nagot utav dessa val nedan:");
        printf("\n");
        printf("\n");
        printf ("- Arbeta med ett redan existerande bokregister. (1)\n");
        printf ("- Skapa ett nytt bokregister. (2)\n");
        printf ("- Avsluta programmet. (3)\n");
        printf ("\n");
        printf ("Ditt val: ");
        // Valet läses av och går vidare sen till en if-sats.
        scanf("%d", &valforstamenyn);
            // Funktionen till att öppna en existerande bokregister, anropas här.
            if (valforstamenyn == 1)
                oppna_ett_existerande_fil_bokregister(books, fil_namnet, &counter);
            // Funktionen till att skapa ett nytt bokregister, anropas här.
            if (valforstamenyn == 2)
                skapa_ett_nytt_fil(fil_namnet);
            // Funktionen till att avsluta programmet, anropas här.
            if (valforstamenyn == 3)
                avsluta_programmet();

                    // Väljs val 1 eller 2 från den första menyn, så kommer den att gå vidare till andra menyn.
                    // Detta med hjälp av en while-loop som man har skapat.
                    // Andra menyn som dyker upp, kommer att ge dig 7 val som du får välja mellan.
                    while (fortsatt == 0)
                    {
                        printf("\n");
                        printf("-------------------------------------------------------------------------------");
                        printf("\n");
                        printf("I denna meny så har du olika alternativ för ditt bokregister:");
                        printf("\n");
                        printf("\n");
                        printf ("1. Lägg till en bokuppgift till registret. \n");
                        printf ("2. Ta bort en bokuppgift från registret.\n");
                        printf ("3. Ändra en bokuppgift.\n");
                        printf ("4. Sök efter en bokuppgift.\n");
                        printf ("5. Sortera alla bokuppgifter. \n");
                        printf ("6. Skriva ut alla bokuppgifter \n");
                        printf ("7. Avsluta. \n");
                        printf("\n");
                        printf ("Ditt val: ");
                        // Valet läses av och går vidare senare till en switch-sats.
                        scanf("%d", &valandramenyn);

                            switch(valandramenyn)
                            {
                                // Funktion för att lägga till en bok, anropas här.
                                case 1: lagg_till_en_bok(books, &counter); break;
                                // Funktion för att ta bort en bok, anropas här.
                                case 2: ta_bort_en_bok(books, &counter, list_of_alternatives); break;
                                // Funktion för att ändra en bok, anropas här.
                                case 3: andra_en_bok(books, &counter, list_of_alternatives); break;
                                // Funktion för att söka efter böcker, anropas här.
                                case 4: sok_efter_en_bok(books, &counter, list_of_alternatives); break;
                                // Funktion för att sortera böckerna, anropas här.
                                case 5: sortera_bocker(books, &counter); break;
                                // Funktion för att skriva ut alla böcker, anropas här.
                                case 6: skriv_ut_alla_bocker(books, &counter); break;
                                // Funktion för att spara och avsluta bokregistret, anropas här.
                                // Då sparas bokregistret och därmed avslutas själva programmet.
                                case 7: spara_och_avsluta_bokregistret(books, fil_namnet, &counter);
                                fortsatt = 1; break;
                            }
                    }

    }

    // Detta är funktionen för att man ska kunna läsa av en string som innehåller mellanslag.
    // Då scanf inte har stöd för att läsa mellanslag (utan hoppar direkt till nästa rad), så är denna funktion användbar.
    // Viktigt om man skriver in in förnamnet/efternamnet på en författare eller ord som ska innehålla mellanslag efter varandra för boktiteln.
    // las_rad funktionen läser av hela stringen då och fortsätter till nästa rad, när man klickar på Enter.
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

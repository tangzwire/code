/**
******************************************************************************
* defined_task.c
* Skriven av: Tanvir Ahmed
* Version: 4.0
* Datum: 3 mars, 2016
* Beskrivning: Programmodul för Turtle, skapar ett eget kommando för sköldpaddan.
******************************************************************************
*/

#include "defined_task.h"
#include "string.h"
#include "radio_com.h"
#include "ctype.h"


//Variabler för att skapa en array av structar, samt datamedlemmarna för structen.
definedTask taskDatabase[DATABASE];

char taskName[TASKNAME] = "";
char taskRepetitions[REPETITIONS] = "";
char taskDefinition[DEFINITIONOFTASK] = "";

//Funktion för att skapa namnet på det ordet som användaren vill lära sköldpaddan.
void createTaskName(void)
{
  int i = 0;
  int positionConfig = 0;
  
  //Läser av ordet som användaren vill skapa.
  for(i=3;i<COLLECTSIZE;i++)
  {
    collectCommando[positionConfig] = collectCommando[i];
    positionConfig++;  
  }
  
  i = 0;
  
  //Tar bort tecken (som t.ex. '\r') och sparar namnet på kommandot.
  for(i=0;i<COLLECTSIZE;i++)
  {
    if(collectCommando[i] != '\r')
    {
      taskName[i] = collectCommando[i];
    }
  }
  
  return;
}

//Funktion för att skapa definitionen samt antalet repetitioner för det nya kommandot.
void createRepetitionsDefinition(void)
{
  int i = 0;
  int positionConfig = 0;
  int positionDefConfig = 0;
  
  //Rensar bort 'repeat ' från inmatningen.
  for(i=0;i<7;i++)
  {
    collectCommando[i] = '\0';
  }
  
  i = 0;
  
  //Läser av antalet repetitioner (användaren kan max mata in 999, d.v.s tre siffror).
  for(i=7;i<11;i++)
  {
    //Sparar siffran som den läser av, genom att kontrollera ifall texten innehåller siffror.
    if(isdigit(collectCommando[i]))
    {
    taskRepetitions[positionConfig] = collectCommando[i];
    collectCommando[i] = '\0';
    positionConfig++;  
    }
  }
  
  i = 0;
  
  //Tar bort mellanslag och andra tecken som ej ska vara med efter att siffrorna lästs in.
  for(i=7;i<11;i++)
  {
    if(collectCommando[i] == ' ')
    {
      collectCommando[i] = '\0';
    }
  }
  
  i = 0;
  
  //Läser av definitionen av kommandot som skall skapas.
  for(i=0; i<COLLECTSIZE; i++)
  {
    //Kommandot får bara innehålla mellanslag, siffror samt bokstäver för att detta skall läsas in.
    if(collectCommando[i] == ' ' || isdigit(collectCommando[i]) || isalpha(collectCommando[i]))
    {
      taskDefinition[positionDefConfig] = collectCommando[i];
      positionDefConfig++;
    }  
  }

  
  return;
}

//Skapar det nya kommandot som en struct och lägger det på en ledig plats i arrayet.
void addTask(int place, char taskName[], char taskRepetitions[], char taskDefinition[])
{
  strcpy(taskDatabase[place].nameOfTask, taskName);
  strcpy(taskDatabase[place].repeatOfMovements, taskRepetitions);
  strcpy(taskDatabase[place].definitionOfTask, taskDefinition);
  
  return;
} 

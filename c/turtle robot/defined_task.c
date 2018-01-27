/**
******************************************************************************
* defined_task.c
* Skriven av: Tanvir Ahmed
* Version: 4.0
* Datum: 3 mars, 2016
* Beskrivning: Programmodul f�r Turtle, skapar ett eget kommando f�r sk�ldpaddan.
******************************************************************************
*/

#include "defined_task.h"
#include "string.h"
#include "radio_com.h"
#include "ctype.h"


//Variabler f�r att skapa en array av structar, samt datamedlemmarna f�r structen.
definedTask taskDatabase[DATABASE];

char taskName[TASKNAME] = "";
char taskRepetitions[REPETITIONS] = "";
char taskDefinition[DEFINITIONOFTASK] = "";

//Funktion f�r att skapa namnet p� det ordet som anv�ndaren vill l�ra sk�ldpaddan.
void createTaskName(void)
{
  int i = 0;
  int positionConfig = 0;
  
  //L�ser av ordet som anv�ndaren vill skapa.
  for(i=3;i<COLLECTSIZE;i++)
  {
    collectCommando[positionConfig] = collectCommando[i];
    positionConfig++;  
  }
  
  i = 0;
  
  //Tar bort tecken (som t.ex. '\r') och sparar namnet p� kommandot.
  for(i=0;i<COLLECTSIZE;i++)
  {
    if(collectCommando[i] != '\r')
    {
      taskName[i] = collectCommando[i];
    }
  }
  
  return;
}

//Funktion f�r att skapa definitionen samt antalet repetitioner f�r det nya kommandot.
void createRepetitionsDefinition(void)
{
  int i = 0;
  int positionConfig = 0;
  int positionDefConfig = 0;
  
  //Rensar bort 'repeat ' fr�n inmatningen.
  for(i=0;i<7;i++)
  {
    collectCommando[i] = '\0';
  }
  
  i = 0;
  
  //L�ser av antalet repetitioner (anv�ndaren kan max mata in 999, d.v.s tre siffror).
  for(i=7;i<11;i++)
  {
    //Sparar siffran som den l�ser av, genom att kontrollera ifall texten inneh�ller siffror.
    if(isdigit(collectCommando[i]))
    {
    taskRepetitions[positionConfig] = collectCommando[i];
    collectCommando[i] = '\0';
    positionConfig++;  
    }
  }
  
  i = 0;
  
  //Tar bort mellanslag och andra tecken som ej ska vara med efter att siffrorna l�sts in.
  for(i=7;i<11;i++)
  {
    if(collectCommando[i] == ' ')
    {
      collectCommando[i] = '\0';
    }
  }
  
  i = 0;
  
  //L�ser av definitionen av kommandot som skall skapas.
  for(i=0; i<COLLECTSIZE; i++)
  {
    //Kommandot f�r bara inneh�lla mellanslag, siffror samt bokst�ver f�r att detta skall l�sas in.
    if(collectCommando[i] == ' ' || isdigit(collectCommando[i]) || isalpha(collectCommando[i]))
    {
      taskDefinition[positionDefConfig] = collectCommando[i];
      positionDefConfig++;
    }  
  }

  
  return;
}

//Skapar det nya kommandot som en struct och l�gger det p� en ledig plats i arrayet.
void addTask(int place, char taskName[], char taskRepetitions[], char taskDefinition[])
{
  strcpy(taskDatabase[place].nameOfTask, taskName);
  strcpy(taskDatabase[place].repeatOfMovements, taskRepetitions);
  strcpy(taskDatabase[place].definitionOfTask, taskDefinition);
  
  return;
} 

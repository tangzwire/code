/**
************************************************************************************************************************
* interpreter.c
* Skriven av: Tanvir Ahmed
* Version: 4.0
* Datum: 3 mars, 2016
* Beskrivning: Programmodul för Turtle, kontroll av kommando, stränghantering av kommando, avläsning av parametrar, etc.
************************************************************************************************************************
*/

#include "interpreter.h"
#include "stdbool.h"
#include "string.h"
#include "ctype.h"
#include "defined_task.h"
#include "turtle_functions.h"


//Variabler för kontroll av felinmatning, sparning av kommando, avläsning av fördefinierad/egendefinierad kommando, etc.
bool wrongCommand = false;

char savedCommando[COLLECTSIZE];
char savedValue[3];
int numberValue = 0;

int repetitionOfDef = 0;
char savedDefinition[DEFINITIONOFTASK];
char processDefinition[DEFINITIONOFTASK];

char forwardCommand[COLLECTSIZE] = "forward";
char rightCommand[COLLECTSIZE] = "right";
char leftCommand[COLLECTSIZE] = "left";
char penupCommand[COLLECTSIZE] = "penup";
char pendownCommand[COLLECTSIZE] = "pendown";

//Funktion för att dela upp en sträng i två delar (normalt ett kommando och ett värde).
void save_split_commando()
{
  int i = 0;
  int j = 0;
  int numberPosition = 0;
 
  //Läser av kommandot och sparar det i en strängvariabel (läser ej av siffror, mellanslag, eller andra tecken).
  for(i=0;i<COLLECTSIZE;i++)
  {
    
    if(collectCommando[i] != ' ' && collectCommando[i] != '\r' && !(isdigit(collectCommando[i])) )
    {
      savedCommando[i] = collectCommando[i];
    }
  }
 
  //Läser av värdet och spara det i en strängvariabel (läser ej av bokstäver, mellanslag, eller andra tecken).
  for(j=0;j<COLLECTSIZE;j++)
  {
    if(isdigit(collectCommando[j]))
    {
      savedValue[numberPosition] = collectCommando[j];
      numberPosition++;
    }
  }
  
  //Gör om det sparade värdet till ett int-typ.
  numberValue = atoi(savedValue);

  return;
}

//Funktion för att behandla definitionen av kommandot som skapats av användaren.
void processDefinedTask(char definitionProcessing[])
{
  //Räknare för att kontrollera om kommandot har ett värde att skickas med som parameter.
  int counter = 0;
  
  //Variabler för att dela upp strängen i små delar.
  char delimiter[] = " ";
  char *splittedCommand = NULL;
  char checkingCommand[COMMAND];
  
  //Delar upp definitionen av kommandot genom att läsa korta kommandon, en i taget.
  splittedCommand = strtok(definitionProcessing, delimiter);
  while(splittedCommand != NULL )
  {
      strcpy(checkingCommand, splittedCommand);
      
      //Kollar om den korta kommandot innehåller bokstäver.
      if(isalpha(checkingCommand[0]))
      {
        strcpy(savedCommando, checkingCommand);
      }
      //Kollar om den korta kommandot innehåller siffror.
      if(isdigit(checkingCommand[0]))
      {
        numberValue = atoi(checkingCommand);
      }
      
      //Om kommandot är 'penup' eller 'pendown', skall inget värde skickas som en parameter.
      if((strncmp(savedCommando, "penup", 5) == 0) || (strncmp(savedCommando, "pendown", 7) == 0))
      {
        check_commando();
      }
      //Annars ökas räknaren till ett.
      else
      {  
        counter++;
      }
                 
      //Om räknaren är lika med 2, skall två paramterar skickas med (t.ex. 'forward' och '90').
      if(counter==2)
      {
        check_commando();
        counter = 0;
      }
      splittedCommand = strtok(NULL, delimiter);
  }       
  return;
  
}

//Funktion för att kontrollera kommando som är egendefinerad av användaren.
void specializedTasks(void)
{
  int j=0;
  int i=0;
  
  //Kontrollerar i databasen om den egendefinierad orden finns, samt samt behandlar kommandot.
  for(j=0;j<DATABASE;j++)
  {
   if((strcmp(savedCommando, taskDatabase[j].nameOfTask)) == 0)
    {
      repetitionOfDef = atoi(taskDatabase[j].repeatOfMovements);  
      strcpy(savedDefinition, taskDatabase[j].definitionOfTask);
      
      for(i=0;i<repetitionOfDef;i++)
      { 
        strcpy(processDefinition, savedDefinition);
        processDefinedTask(processDefinition);
      }
       memset(savedCommando, '\0', sizeof(savedCommando));
       memset(savedDefinition, '\0', sizeof(savedDefinition));
       memset(processDefinition, '\0', sizeof(processDefinition));
       repetitionOfDef = 0;
  
       UartReady = RESET;
      
       return;
    }
  }
  
  //Om kommandot ej existerar, kommer användaren att få ett felmeddelande skickat till terminalen.
  wrongCommand = true;
  
  if(wrongCommand == true)
  {
    
      strcpy(sendingCommand, "404 ERROR: Wrong command!\n\r");
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
      HAL_Delay(500);
      
      wrongCommand = false;
   }  
  
  //Rensar strängvariablerna för att återgå till nytt.
  memset(savedCommando, '\0', sizeof(savedCommando));
  memset(savedDefinition, '\0', sizeof(savedDefinition));
  memset(processDefinition, '\0', sizeof(processDefinition));
  repetitionOfDef = 0;
  
  UartReady = RESET;
  
  return;
}

//Funktion för att kontrollera först om kommandot är fördefinierad.
void check_commando()
{
   //Om kommandot är forward, kommer sköldpaddan att åka framåt ett viss avstånd (mätt i mm).
  if((strcmp(savedCommando, forwardCommand)) == 0)
  {
    //Meddelande som talar om att kommandokörningen gick bra.
    strcpy(sendingCommand, "forward command = OK!\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    //Anrop till funktionen för att få sköldpaddan att åka framåt.
    forwardTheTurtle(numberValue);
    
    //Meddelande som talar om att kommandokörningen är klar.
    strcpy(sendingCommand, "forward operation DONE\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    wrongCommand = false;
    
    memset(savedCommando, '\0', sizeof(savedCommando));
    memset(savedValue, '\0', sizeof(savedValue));
    
    return;
 
  }
  //Om kommandot är right, kommer sköldpaddan att rotera höger en viss grad (mätt i grader).
  if((strcmp(savedCommando, rightCommand)) == 0)
  {
    //Meddelande som talar om att kommandokörningen gick bra.
    strcpy(sendingCommand, "right command = OK!\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    //Anrop till funktionen för att få sköldpaddan att rotera höger.
    rightTheTurtle(numberValue);
    
    //Meddelande som talar om att kommandokörningen är klar.
    strcpy(sendingCommand, "right command DONE\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    wrongCommand = false;
    
    memset(savedCommando, '\0', sizeof(savedCommando));
    memset(savedValue, '\0', sizeof(savedValue));
    
    return;
    
  }
  //Om kommandot är left, kommer sköldpaddan att rotera vänster en viss grad (mätt i grader).
  if((strcmp(savedCommando, leftCommand)) == 0)
  {
    //Meddelande som talar om att kommandokörningen gick bra.
    strcpy(sendingCommand, "left command = OK!\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    //Anrop till funktionen för att få sköldpaddan att rotera vänster.
    leftTheTurtle(numberValue);
    
    //Meddelande som talar om att kommandokörningen är klar.
    strcpy(sendingCommand, "left command DONE\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    wrongCommand = false;
    
    memset(savedCommando, '\0', sizeof(savedCommando));
    memset(savedValue, '\0', sizeof(savedValue));
    
    return;
    
  }
  //Om kommandot är penup, kommer sköldpaddan att lyfta upp pennan.
  if((strcmp(savedCommando, penupCommand)) == 0)
  {
    //Meddelande som talar om att kommandokörningen gick bra.
    strcpy(sendingCommand, "penup command = OK!\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
   
    //Anrop till funktionen för att få sköldpaddan att lyfta upp pennan.
    penupTheTurtle();
    
    //Meddelande som talar om att kommandokörningen är klar.
    strcpy(sendingCommand, "penup command DONE\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    wrongCommand = false;
    
    memset(savedCommando, '\0', sizeof(savedCommando));
    memset(savedValue, '\0', sizeof(savedValue));
    
    return;

  } 
  //Om kommandot är pendown, kommer sköldpaddan att lyfta ned pennan.  
  if((strcmp(savedCommando, pendownCommand)) == 0)
  {
    //Meddelande som talar om att kommandokörningen gick bra.
    strcpy(sendingCommand, "pendown command = OK!\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    //Anrop till funktionen för att få sköldpaddan att lyfta ned pennan.
    pendownTheTurtle();
    
    //Meddelande som talar om att kommandokörningen är klar.
    strcpy(sendingCommand, "pendown command DONE\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    wrongCommand = false;
    
    memset(savedCommando, '\0', sizeof(savedCommando));
    memset(savedValue, '\0', sizeof(savedValue));
    
    return;
    
  }
  //Annars så kommer en anrop till en funktion göras, för att kolla ifall kommandot är egendefinierad.
  else
  {
    specializedTasks();
  } 

  return;
}

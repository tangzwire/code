/**
************************************************************************************************************************
* interpreter.c
* Skriven av: Tanvir Ahmed
* Version: 4.0
* Datum: 3 mars, 2016
* Beskrivning: Programmodul f�r Turtle, kontroll av kommando, str�nghantering av kommando, avl�sning av parametrar, etc.
************************************************************************************************************************
*/

#include "interpreter.h"
#include "stdbool.h"
#include "string.h"
#include "ctype.h"
#include "defined_task.h"
#include "turtle_functions.h"


//Variabler f�r kontroll av felinmatning, sparning av kommando, avl�sning av f�rdefinierad/egendefinierad kommando, etc.
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

//Funktion f�r att dela upp en str�ng i tv� delar (normalt ett kommando och ett v�rde).
void save_split_commando()
{
  int i = 0;
  int j = 0;
  int numberPosition = 0;
 
  //L�ser av kommandot och sparar det i en str�ngvariabel (l�ser ej av siffror, mellanslag, eller andra tecken).
  for(i=0;i<COLLECTSIZE;i++)
  {
    
    if(collectCommando[i] != ' ' && collectCommando[i] != '\r' && !(isdigit(collectCommando[i])) )
    {
      savedCommando[i] = collectCommando[i];
    }
  }
 
  //L�ser av v�rdet och spara det i en str�ngvariabel (l�ser ej av bokst�ver, mellanslag, eller andra tecken).
  for(j=0;j<COLLECTSIZE;j++)
  {
    if(isdigit(collectCommando[j]))
    {
      savedValue[numberPosition] = collectCommando[j];
      numberPosition++;
    }
  }
  
  //G�r om det sparade v�rdet till ett int-typ.
  numberValue = atoi(savedValue);

  return;
}

//Funktion f�r att behandla definitionen av kommandot som skapats av anv�ndaren.
void processDefinedTask(char definitionProcessing[])
{
  //R�knare f�r att kontrollera om kommandot har ett v�rde att skickas med som parameter.
  int counter = 0;
  
  //Variabler f�r att dela upp str�ngen i sm� delar.
  char delimiter[] = " ";
  char *splittedCommand = NULL;
  char checkingCommand[COMMAND];
  
  //Delar upp definitionen av kommandot genom att l�sa korta kommandon, en i taget.
  splittedCommand = strtok(definitionProcessing, delimiter);
  while(splittedCommand != NULL )
  {
      strcpy(checkingCommand, splittedCommand);
      
      //Kollar om den korta kommandot inneh�ller bokst�ver.
      if(isalpha(checkingCommand[0]))
      {
        strcpy(savedCommando, checkingCommand);
      }
      //Kollar om den korta kommandot inneh�ller siffror.
      if(isdigit(checkingCommand[0]))
      {
        numberValue = atoi(checkingCommand);
      }
      
      //Om kommandot �r 'penup' eller 'pendown', skall inget v�rde skickas som en parameter.
      if((strncmp(savedCommando, "penup", 5) == 0) || (strncmp(savedCommando, "pendown", 7) == 0))
      {
        check_commando();
      }
      //Annars �kas r�knaren till ett.
      else
      {  
        counter++;
      }
                 
      //Om r�knaren �r lika med 2, skall tv� paramterar skickas med (t.ex. 'forward' och '90').
      if(counter==2)
      {
        check_commando();
        counter = 0;
      }
      splittedCommand = strtok(NULL, delimiter);
  }       
  return;
  
}

//Funktion f�r att kontrollera kommando som �r egendefinerad av anv�ndaren.
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
  
  //Om kommandot ej existerar, kommer anv�ndaren att f� ett felmeddelande skickat till terminalen.
  wrongCommand = true;
  
  if(wrongCommand == true)
  {
    
      strcpy(sendingCommand, "404 ERROR: Wrong command!\n\r");
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
      HAL_Delay(500);
      
      wrongCommand = false;
   }  
  
  //Rensar str�ngvariablerna f�r att �terg� till nytt.
  memset(savedCommando, '\0', sizeof(savedCommando));
  memset(savedDefinition, '\0', sizeof(savedDefinition));
  memset(processDefinition, '\0', sizeof(processDefinition));
  repetitionOfDef = 0;
  
  UartReady = RESET;
  
  return;
}

//Funktion f�r att kontrollera f�rst om kommandot �r f�rdefinierad.
void check_commando()
{
   //Om kommandot �r forward, kommer sk�ldpaddan att �ka fram�t ett viss avst�nd (m�tt i mm).
  if((strcmp(savedCommando, forwardCommand)) == 0)
  {
    //Meddelande som talar om att kommandok�rningen gick bra.
    strcpy(sendingCommand, "forward command = OK!\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    //Anrop till funktionen f�r att f� sk�ldpaddan att �ka fram�t.
    forwardTheTurtle(numberValue);
    
    //Meddelande som talar om att kommandok�rningen �r klar.
    strcpy(sendingCommand, "forward operation DONE\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    wrongCommand = false;
    
    memset(savedCommando, '\0', sizeof(savedCommando));
    memset(savedValue, '\0', sizeof(savedValue));
    
    return;
 
  }
  //Om kommandot �r right, kommer sk�ldpaddan att rotera h�ger en viss grad (m�tt i grader).
  if((strcmp(savedCommando, rightCommand)) == 0)
  {
    //Meddelande som talar om att kommandok�rningen gick bra.
    strcpy(sendingCommand, "right command = OK!\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    //Anrop till funktionen f�r att f� sk�ldpaddan att rotera h�ger.
    rightTheTurtle(numberValue);
    
    //Meddelande som talar om att kommandok�rningen �r klar.
    strcpy(sendingCommand, "right command DONE\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    wrongCommand = false;
    
    memset(savedCommando, '\0', sizeof(savedCommando));
    memset(savedValue, '\0', sizeof(savedValue));
    
    return;
    
  }
  //Om kommandot �r left, kommer sk�ldpaddan att rotera v�nster en viss grad (m�tt i grader).
  if((strcmp(savedCommando, leftCommand)) == 0)
  {
    //Meddelande som talar om att kommandok�rningen gick bra.
    strcpy(sendingCommand, "left command = OK!\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    //Anrop till funktionen f�r att f� sk�ldpaddan att rotera v�nster.
    leftTheTurtle(numberValue);
    
    //Meddelande som talar om att kommandok�rningen �r klar.
    strcpy(sendingCommand, "left command DONE\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    wrongCommand = false;
    
    memset(savedCommando, '\0', sizeof(savedCommando));
    memset(savedValue, '\0', sizeof(savedValue));
    
    return;
    
  }
  //Om kommandot �r penup, kommer sk�ldpaddan att lyfta upp pennan.
  if((strcmp(savedCommando, penupCommand)) == 0)
  {
    //Meddelande som talar om att kommandok�rningen gick bra.
    strcpy(sendingCommand, "penup command = OK!\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
   
    //Anrop till funktionen f�r att f� sk�ldpaddan att lyfta upp pennan.
    penupTheTurtle();
    
    //Meddelande som talar om att kommandok�rningen �r klar.
    strcpy(sendingCommand, "penup command DONE\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    wrongCommand = false;
    
    memset(savedCommando, '\0', sizeof(savedCommando));
    memset(savedValue, '\0', sizeof(savedValue));
    
    return;

  } 
  //Om kommandot �r pendown, kommer sk�ldpaddan att lyfta ned pennan.  
  if((strcmp(savedCommando, pendownCommand)) == 0)
  {
    //Meddelande som talar om att kommandok�rningen gick bra.
    strcpy(sendingCommand, "pendown command = OK!\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    //Anrop till funktionen f�r att f� sk�ldpaddan att lyfta ned pennan.
    pendownTheTurtle();
    
    //Meddelande som talar om att kommandok�rningen �r klar.
    strcpy(sendingCommand, "pendown command DONE\n\r");
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
    HAL_Delay(500);
    
    wrongCommand = false;
    
    memset(savedCommando, '\0', sizeof(savedCommando));
    memset(savedValue, '\0', sizeof(savedValue));
    
    return;
    
  }
  //Annars s� kommer en anrop till en funktion g�ras, f�r att kolla ifall kommandot �r egendefinierad.
  else
  {
    specializedTasks();
  } 

  return;
}

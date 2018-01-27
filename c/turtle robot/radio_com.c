/**
************************************************************************************
* radio_com.c
* Skriven av: Tanvir Ahmed
* Version: 4.0
* Datum: 3 mars, 2016
* Beskrivning: Programmodul f�r Turtle, s�ndning/mottagning av text via Radio (UART)
************************************************************************************
*/

#include "stm32f3xx_hal.h"
#include "usart.h"
#include "string.h"
#include "radio_com.h"


//Variabler f�r att tala om statusen f�r UART, l�sa av tecken som buffer, skicka/ta emot text, osv.
ITStatus UartReady = RESET;

uint8_t Buffer[BUFFERSIZE]; 

char sendingCommand[SENDING_COMMAND];
char nextlineCommand[NEXTLINE]; 
char collectCommando[COLLECTSIZE];

int positionIncrement = 0;

//Funktion som anropas n�r en text har skickats till terminalen.
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  UartReady = SET;

  memset(sendingCommand, '\0', sizeof(sendingCommand));
}

//Funktion som anropas n�r en text har mottagits fr�n terminalen
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    UartReady = SET;
    
    //L�ser en tecken i taget och sparar det i en tempor�r str�ngvariabel.
    HAL_UART_Receive_IT(&huart3, (uint8_t *)Buffer, BUFFERSIZE);
    collectCommando[positionIncrement] = Buffer[0]; 
    positionIncrement++;
    
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)Buffer, BUFFERSIZE);
    
    //Ser till att texten hamnar p� n�sta rad i terminalen.
    strcpy(nextlineCommand, "\r\n");
}
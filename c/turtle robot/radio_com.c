/**
************************************************************************************
* radio_com.c
* Skriven av: Tanvir Ahmed
* Version: 4.0
* Datum: 3 mars, 2016
* Beskrivning: Programmodul för Turtle, sändning/mottagning av text via Radio (UART)
************************************************************************************
*/

#include "stm32f3xx_hal.h"
#include "usart.h"
#include "string.h"
#include "radio_com.h"


//Variabler för att tala om statusen för UART, läsa av tecken som buffer, skicka/ta emot text, osv.
ITStatus UartReady = RESET;

uint8_t Buffer[BUFFERSIZE]; 

char sendingCommand[SENDING_COMMAND];
char nextlineCommand[NEXTLINE]; 
char collectCommando[COLLECTSIZE];

int positionIncrement = 0;

//Funktion som anropas när en text har skickats till terminalen.
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  UartReady = SET;

  memset(sendingCommand, '\0', sizeof(sendingCommand));
}

//Funktion som anropas när en text har mottagits från terminalen
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    UartReady = SET;
    
    //Läser en tecken i taget och sparar det i en temporär strängvariabel.
    HAL_UART_Receive_IT(&huart3, (uint8_t *)Buffer, BUFFERSIZE);
    collectCommando[positionIncrement] = Buffer[0]; 
    positionIncrement++;
    
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)Buffer, BUFFERSIZE);
    
    //Ser till att texten hamnar på nästa rad i terminalen.
    strcpy(nextlineCommand, "\r\n");
}
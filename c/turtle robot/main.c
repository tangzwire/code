/**
******************************************************************************
* TURTLE main.c
* Skriven av: Tanvir Ahmed
* Version: 4.0
* Datum: 3 mars, 2016
* Beskrivning: Mainprogrammet för turtle, där hela programmet startas.
******************************************************************************
*/

#include "stm32f3xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include "tim.h"

#include "string.h"
#include "ctype.h"
#include "stdbool.h"

#include "radio_com.h"
#include "turtle_functions.h"
#include "interpreter.h"
#include "defined_task.h"


//Variabel för att placera egenskapade kommandot på rätt plats.
int taskPlacement = 1;

void SystemClock_Config(void);

int main(void)
{
  //Initieringar av HAL, GPIO, USART, TIM, osv.
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_TIM4_Init();
  
  //Start av programmet, ett meddelande skickas till terminalen.
  HAL_Delay(1000);
  strcpy(sendingCommand, "Turtle ready \r\n");
  HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
  HAL_Delay(400);
  
  //Väntar på att användaren skall mata in ett kommando eller skapa ett nytt kommando.
  HAL_Delay(1000);
  HAL_UART_Receive_IT(&huart3, (uint8_t *)Buffer, BUFFERSIZE);
  HAL_Delay(500);
 
  taskPlacement = taskPlacement - 1;
  while (1)
  {
    //När användaren matar in ENTER-knappen, kommer programmet gå vidare hit.
    if(Buffer[0] == '\r')
    {
      //Om användaren har matat in "to ", så vill den skapa ett nytt kommando.
      if(strncmp(collectCommando, "to ", 3) == 0) 
      {
      HAL_Delay(1000);  
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)collectCommando, strlen(collectCommando));
      HAL_Delay(500);
      HAL_Delay(1000);
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)nextlineCommand, strlen(nextlineCommand));
      HAL_Delay(500);   
      
      
      //Skapar ordet.
      createTaskName();
      
      //Rensar det som användaren har matat in.
      memset(nextlineCommand, '\0', sizeof(nextlineCommand));
      memset(collectCommando, '\0', sizeof(collectCommando));
      
      //Återställer platsen där nästa tecken skall hamna (se filen radio_com.c)
      positionIncrement = 0;
      
      UartReady = RESET;
      }
      //Om användaren har matat in 'repeat ', så vill den definiera den nya kommandot.
      else if(strncmp(collectCommando, "repeat ", 7) == 0) 
      {
      HAL_Delay(1000);  
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)collectCommando, strlen(collectCommando));
      HAL_Delay(500);
      HAL_Delay(1000);
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)nextlineCommand, strlen(nextlineCommand));
      HAL_Delay(500);   
      
      //Skapar en definition samt antalet gånger definitionen skall göras.
      createRepetitionsDefinition();
        
      memset(nextlineCommand, '\0', sizeof(nextlineCommand));
      memset(collectCommando, '\0', sizeof(collectCommando));
        
      positionIncrement = 0;
      
      UartReady = RESET;
      }
      //Om användaren har matat in 'end", så vill den spara den nya kommandot.
      else if(strncmp(collectCommando, "end", 3) == 0) 
      {
      HAL_Delay(1000);  
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)collectCommando, strlen(collectCommando));
      HAL_Delay(500);
      HAL_Delay(1000);
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)nextlineCommand, strlen(nextlineCommand));
      HAL_Delay(500);   
     
      //Sparar kommandot i en array som en struct.
      addTask(taskPlacement, taskName, taskRepetitions, taskDefinition);
      
      //Ökar på positionen av arrayen, så att nästa ord som skapas, kan lagras.
      taskPlacement++;
      
      memset(taskName, '\0', sizeof(taskName));
      memset(taskRepetitions, '\0', sizeof(taskRepetitions));
      memset(taskDefinition, '\0', sizeof(taskDefinition));    
      
      
      memset(nextlineCommand, '\0', sizeof(nextlineCommand));
      memset(collectCommando, '\0', sizeof(collectCommando));
        
      positionIncrement = 0;
      
      UartReady = RESET;
      }
      
      else
      { 
      //Om användaren har matat in ett fördefinierad kommando/egen kommando, kommer kommandot att kontrolleras. 
      HAL_Delay(1000);
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)collectCommando, strlen(collectCommando));
      HAL_Delay(500);
      HAL_Delay(1000);
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)nextlineCommand, strlen(nextlineCommand));
      HAL_Delay(500);  
      
      //Delar upp kommandot i två delar (normalt till en sträng och en siffra).
      save_split_commando();

      //Kontrollerar vilken kommando som matats in.
      check_commando();
     
      memset(nextlineCommand, '\0', sizeof(nextlineCommand));
      memset(collectCommando, '\0', sizeof(collectCommando));
      
      positionIncrement = 0;
      
      UartReady = RESET;
      }
    }
    
   while (UartReady != SET)
    {
    }
    UartReady = RESET;
  
  }

}



void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART3;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);


  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}



#ifdef USE_FULL_ASSERT


void assert_failed(uint8_t* file, uint32_t line)
{
  
}

#endif

/**
***************************************************************************************************************
* TURTLE main (TEST).c
* Skriven av: Tanvir Ahmed
* Version: 4.0
* Datum: 3 mars, 2016
* Beskrivning: Testprogram för Turtle, kontrollerar ifall programmodulerna fungerar efter de kraven som ställts.
***************************************************************************************************************
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

//Variabler för att testa funktionerna i programmodulerna som har skapats.
int taskPlacement = 1;
int testloop = 0;

int wrongCommandTest = 1;

void SystemClock_Config(void);


int main(void)
{
  //Initieringar av HAL, GPIO, USART, TIM, osv.
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_TIM4_Init();
  
  
  //Testar om det går att sända en text till terminalen.
  printf("Test 1: Skickar en text till terminalen (sändning) \n\r");
  
  HAL_Delay(1000);
  strcpy(sendingCommand, "Send \r\n");
  printf("Skickade texten: %s \n\r", sendingCommand);
  HAL_UART_Transmit_IT(&huart3, (uint8_t *)sendingCommand, SENDING_COMMAND);
  HAL_Delay(400);

  //Testar om det går att motta en text från terminalen.
  printf("Test 2: Ta emot en text från terminalen (mottagning) \r\n");
  HAL_Delay(1000);
  HAL_UART_Receive_IT(&huart3, (uint8_t *)Buffer, BUFFERSIZE);
  HAL_Delay(500);
 
  
  
  taskPlacement = taskPlacement - 1;
  
  while (1)
  {
    
    
    if(Buffer[0] == '\r')
    {
      printf("Tog emot texten: '%s'\n\r", collectCommando);
      printf("\n\r");
      
      //Testar om ett nytt kan skapas.
      if(strncmp(collectCommando, "to ", 3) == 0) 
      {
      printf("Test 4: Kollar om ett nytt ord skall skapas\r\n"); 
      HAL_Delay(1000);  
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)collectCommando, strlen(collectCommando));
      HAL_Delay(500);
      HAL_Delay(1000);
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)nextlineCommand, strlen(nextlineCommand));
      HAL_Delay(500);   
      
      createTaskName();
       
      printf("Nytt ord ska skapas!\r\n");
      printf("Orden som sköldpaddan ska lära sig: %s \r\n", taskName);
      
      memset(nextlineCommand, '\0', sizeof(nextlineCommand));
      memset(collectCommando, '\0', sizeof(collectCommando));
        
      positionIncrement = 0;
      
      UartReady = RESET;
      }      
      
      //Testar om definitionen samt repetitioner för det nya kommandot kan skapas.
      else if(strncmp(collectCommando, "repeat ", 7) == 0) 
      {
      printf("Test 5: Kollar om ett repetition och en definition ska skapas\r\n");  
      HAL_Delay(1000);  
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)collectCommando, strlen(collectCommando));
      HAL_Delay(500);
      HAL_Delay(1000);
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)nextlineCommand, strlen(nextlineCommand));
      HAL_Delay(500);   
        
      createRepetitionsDefinition();
      
      printf("Ny repetition samt definition ska skapas! \r\n");  
      printf("Repetitionssiffran: %s \r\n", taskRepetitions);
      printf("Definitionen: %s \r\n", taskDefinition);
      
      
      memset(nextlineCommand, '\0', sizeof(nextlineCommand));
      memset(collectCommando, '\0', sizeof(collectCommando));
        
      positionIncrement = 0;
      
      UartReady = RESET;
      }
      
      //Testar om det nya kommandot kan sparas som en struct i en array.
      //Skriver ut arrayen som en lista för kontroll.
      else if(strncmp(collectCommando, "end", 3) == 0) 
      {
      printf("Test 6: Kollar om ett nytt kommando ska sparas!\r\n");
      HAL_Delay(1000);  
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)collectCommando, strlen(collectCommando));
      HAL_Delay(500);
      HAL_Delay(1000);
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)nextlineCommand, strlen(nextlineCommand));
      HAL_Delay(500);   
     
      
      addTask(taskPlacement, taskName, taskRepetitions, taskDefinition);
      
      taskPlacement++;
      
      printf("Nytt kommando har skapats!\r\n");
      printf("Skriver ut en lista på alla egna kommandon som skapats.\r\n");
     
      for(testloop=0;testloop<DATABASE;testloop++)
      {  
        printf("Task name: %s, Repeat: %s, Definition: %s \n", taskDatabase[testloop].nameOfTask, taskDatabase[testloop].repeatOfMovements, taskDatabase[testloop].definitionOfTask);
      }
      
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
      //Testar om vanliga kommandon har tagits emot av användaren.  
      printf("Test 3: Kollar om vanliga kommandon har tagits emot\r\n");
      HAL_Delay(1000);
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)collectCommando, strlen(collectCommando));
      HAL_Delay(500);
      HAL_Delay(1000);
      HAL_UART_Transmit_IT(&huart3, (uint8_t *)nextlineCommand, strlen(nextlineCommand));
      HAL_Delay(500);  
      
      save_split_commando();
      
      //Testar uppdelningen av strängen i två delar (kommando samt värde).
      printf("Kommando: %s \r\n", savedCommando);
      printf("Värde: %s \r\n", savedValue);
      
      printf("\r\n");
      
      //Testar om kommandot existerar bland de fördefinierade kommandona.
      printf("Test 7: Kollar om fel kommando har tagits emot\r\n");
      
      if((strcmp(savedCommando, forwardCommand)) == 0)
      {
        printf("En existerande kommando har tagits emot: %s \r\n", savedCommando);
        
      }
      
      else if((strcmp(savedCommando, leftCommand)) == 0)
      {
         printf("En existerande kommando har tagits emot: %s \r\n", savedCommando);
      }
      
      else if((strcmp(savedCommando, rightCommand)) == 0)
      {
         printf("En existerande kommando har tagits emot: %s \r\n", savedCommando);
      }
      
      else if((strcmp(savedCommando, penupCommand)) == 0)
      {
        printf("En existerande kommando har tagits emot: %s \r\n", savedCommando);
      }
      
      else if((strcmp(savedCommando, pendownCommand)) == 0)
      {
         printf("En existerande kommando har tagits emot: %s \r\n", savedCommando);
      }
      else
      { 
         int i = 0;
         for(i=0;i<DATABASE;i++)
         {
           //Testar om kommandot är egendefinierad, samt skriver ut dess definition och repetition.
           if((strcmp(savedCommando, taskDatabase[i].nameOfTask)) == 0)
           {
             printf("En existerande kommando finns, som du själv skapat: %s \r\n", savedCommando);
             printf("Denna har följande parametrar: \r\n");
             
             printf("Repetitions: %s \n\r", taskDatabase[i].repeatOfMovements);
             printf("Definitions: %s \n\r", taskDatabase[i].definitionOfTask);
            
             wrongCommandTest = 0;
           }
         }
      
        //Testar om ett fel kommando har tagits emot av användaren. 
        if(wrongCommandTest == 0)
        {
         wrongCommand = false; 
        }
        else
        {
         wrongCommand = true; 
        }  
               
        if(wrongCommand == true)
        {
          printf("Fel kommando har matats in! Du får en error. \r\n");
      
          wrongCommand = false;
        }   
         
      }
              

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

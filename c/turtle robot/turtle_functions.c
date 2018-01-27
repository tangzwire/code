/**
*******************************************************************************************************
* turtle_functions.c
* Skriven av: Tanvir Ahmed
* Version: 4.0
* Datum: 3 mars, 2016
* Beskrivning: Programmodul f�r Turtle, utf�ra olika saker (k�ra fram�t, rotera, lyfta upp pennan, osv)
********************************************************************************************************
*/

#include "turtle_functions.h"
#include "gpio.h"
#include "tim.h"
#include "stm32f3xx_hal.h"


//Funktion f�r att initiera motorerna till Quarterstep.
void initialize_MotorEngine(void)
{
  HAL_GPIO_WritePin(_ENABLE_GPIO_Port,_ENABLE_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(MS1_GPIO_Port,MS1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(MS2_GPIO_Port,MS2_Pin, GPIO_PIN_SET);
}

//Funktion f�r att k�ra fram sk�ldpaddan.
void forwardTheTurtle(int unitValue)
{ 
    initialize_MotorEngine();  

    int pulses = 0;
    int j;
    
    //Ber�kningar f�r att ta reda p� antalet pulser som kr�vs f�r en viss l�ngd i mm.
    unitValue = unitValue * 4;
    pulses = (int) unitValue / 1.47;
    pulses = pulses - 1;
    
    //Skickar pulserna.
   for(j=0; j<pulses; j++)
  {
    HAL_GPIO_WritePin(DIR2_GPIO_Port, DIR2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(STEP1_GPIO_Port, STEP1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(STEP2_GPIO_Port, STEP2_Pin, GPIO_PIN_SET);

    HAL_Delay(10);

    HAL_GPIO_WritePin(STEP1_GPIO_Port, STEP1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(STEP2_GPIO_Port, STEP2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DIR2_GPIO_Port, DIR2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, GPIO_PIN_RESET);
    
  }
  
  
  return;
  
}




//Funktion f�r att rotera roboten �t h�ger.
void rightTheTurtle(int unitValue)
{
  initialize_MotorEngine(); 
  
  int pulses = 0;
  int calculation = 0;
  int k;
  
  //Ber�kningar f�r att ta reda p� antalet pulser som kr�vs f�r en viss rotation i grader.
  unitValue = unitValue * 4;
  calculation = (int) unitValue * 1.05;
  
  pulses = (int) calculation / 1.47;
  pulses = pulses - 1;
  
  //Skickar pulserna.
  for(k=0; k<pulses; k++)
  {
    HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(STEP1_GPIO_Port, STEP1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(STEP2_GPIO_Port, STEP2_Pin, GPIO_PIN_SET);
    
    HAL_Delay(10);

    HAL_GPIO_WritePin(STEP1_GPIO_Port, STEP1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(STEP2_GPIO_Port, STEP2_Pin, GPIO_PIN_RESET);
    
  }
  HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, GPIO_PIN_RESET);
  
    
  return;
  
}

//Funktion f�r att rotera roboten �t v�nster.
void leftTheTurtle(int unitValue)
{
  initialize_MotorEngine(); 
 
  int pulses = 0;
  int calculation = 0;
  int k;
 
   //Ber�kningar f�r att ta reda p� antalet pulser som kr�vs f�r en viss rotation i grader.
  unitValue = unitValue * 4;
  calculation = (int) unitValue * 1.05;
  
  pulses = (int) calculation / 1.47;
  pulses = pulses - 1;
  
  //Skickar pulserna.
  for(k=0; k<pulses; k++)
  {
    HAL_GPIO_WritePin(DIR2_GPIO_Port, DIR2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(STEP1_GPIO_Port, STEP1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(STEP2_GPIO_Port, STEP2_Pin, GPIO_PIN_SET);
    
    HAL_Delay(10);

    HAL_GPIO_WritePin(STEP1_GPIO_Port, STEP1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(STEP2_GPIO_Port, STEP2_Pin, GPIO_PIN_RESET);
    
  }
  HAL_GPIO_WritePin(DIR2_GPIO_Port, DIR2_Pin, GPIO_PIN_RESET);
  
  
  return;
}

//Funktion f�r att lyfta upp pennan.
void penupTheTurtle(void)
{
  //Pulsbreddsmodulering som ser till att pennan lyfts upp (pulsl�ngd 1 ms).
  sConfigOC.Pulse = (40000 * 5) / 100;
  HAL_TIM_PWM_ConfigChannel(&htim4,&sConfigOC, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
  
  return;
  
}
//Funktion f�r att lyfta ner pennan.
void pendownTheTurtle(void)
{
  //Pulsbreddsmodulering som ser till att pennan lyfts ned (pulsl�ngd 0,6 ms).
  sConfigOC.Pulse = (40000 * 3) / 100;
  HAL_TIM_PWM_ConfigChannel(&htim4,&sConfigOC, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
  
  return;
}
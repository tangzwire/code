/**********************************************************************************
 * Name: Tanvir Saif Ahmed                                                        *
 * Date: 16/1-2016                                                                *
 * Course: Sensor Based System              	         			  *
 * Assignment: Project (Gesture based user interface) 				  *			
 * Description: For digital signal processing of the ultrasonic receiver signals. *
 **********************************************************************************/


int digitalPin = 3;
int digitalOutput = 4;

int val = 0;


void setup() 
{
  pinMode(digitalOutput, OUTPUT);
}

void loop() 
{
  val = digitalRead(digitalPin);

  if(val == 1)
  {
    digitalWrite(digitalOutput, LOW);
  }
  if(val == 0)
  {
    digitalWrite(digitalOutput, HIGH);
    delay(50);
  }

}

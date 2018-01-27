/**********************************************************************************
 * Name: Tanvir Saif Ahmed                                                        *
 * Date: 16/1-2016                                                                *
 * Course: Sensor Based System              	         			  *
 * Assignment: Project (Gesture based user interface) 				  *			
 * Description: For time measurements of the three ultrasonic receivers.          *
 **********************************************************************************/


void setup () 
{
  Serial.begin (9600);
  pinMode (2, INPUT);  
  pinMode (3, INPUT);     
  pinMode (4, INPUT);
  pinMode (5, INPUT);
}

short sigs = 0; // bit0-bit10: r_in, r_old, 1_in, 1_old, 2_in, 2_old, 3_in, 3_old, trig1, trig2, trig3

unsigned long start, stop0, stop1, stop2, stop3 = 0; // timing variables

long int period = 100000; // period of radio wave in us, 1/f (set somewhat lower, e.g. if period is 250000, set it to 200000)

void loop() 
{
  if ( (sigs & 1792)==0 )                                 // if all triggers == 0
  {
    sigs = (sigs & ~1) | digitalRead(2);                // reset r_in and read in new val
    
    /* check if radioOld==0 and radioIn==1 (rising edge) AND 200ms have passed */
    if ( (sigs & 3)==1 && (micros()-start)>period )
    {
      start = micros();                                 // start timer
      sigs = sigs | 1792;                               // set trigger bits
    }
    
    sigs = (sigs & ~2) | ( (sigs & 1) << 1 );           // set radioOld to radioIn value
  }
  
  else
  {
    sigs = (sigs & ~84) | digitalRead(5)<<6 | digitalRead(4)<<4 | digitalRead(3)<<2; // reset in-signals and throw in new vals    
    stop0 = micros();
    if ( (sigs & 256) && (sigs & 12)==4         // trigger1 & rising edge on sig1
    {
      stop1 = stop0;                            // stop timer1
      sigs = sigs & ~256;                       // reset trig1
    }
      
    if ( (sigs & 512) && (sigs & 48)==16 )      // trigger2 & rising edge on sig2
    {
      stop2 = stop0;                            // stop timer2
      sigs = sigs & ~512;                       // reset trig2
    }
    
    if ( (sigs & 1024) && (sigs & 192)==64 )    // trigger3 & rising edge on sig3
    {
      stop3 = stop0;                            // stop timer3
      sigs = sigs & ~1024;                      // reset trig3
    }

    if ( !(sigs & 1792) )
    {
      String pr = "";
      pr += stop1-start;
      pr += ", ";
      pr += stop2-start;
      pr += ", ";
      pr += stop3-start;
      pr += ";";
      Serial.println(pr);

    }

    sigs = (sigs & ~168) | ( (sigs & 84) << 1 );          // reset old values and set them to what was read in before
  }
}


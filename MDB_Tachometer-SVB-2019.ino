// source of code: http://www.pyroelectro.com/tutorials/tachometer_rpm_arduino/software.html
// trigger idea: https://forum.arduino.cc/index.php?topic=155270.0 

volatile unsigned long time;
volatile int trigger = 0;
volatile unsigned long int t = 0;
volatile unsigned long int time_last = 0;
volatile float rpm_array[5] = {0,0,0,0,0};
unsigned long int rpm = 0;
volatile int adjust = 6;

void setup()
{
  Serial.begin(9600);
  //Digital Pin 2 Set As An Interrupt
 attachInterrupt(0, my_interrupt, FALLING);

}

//Main Loop To Calculate RPM
void loop()
{
  ////lcd.setCursor(4, 1);
  ////lcd.print(time);   

  {    
    //Last 5 Average RPM Counts Eqauls....
      if (trigger >= 5) 
          {rpm = (rpm_array[0] + rpm_array[1] + rpm_array[2] + rpm_array[3] + rpm_array[4]) / 5;
          
          Serial.print(rpm);
          Serial.print("  ");
          trigger = 0;
          }
      }   
}
 

//Capture Interrupt
void my_interrupt()
{
   time = millis();
   t = ((millis() - time_last)); // Stores time in ms between two interrupts 
   time_last = millis(); // Time in ms from program start
   //Serial.print(t);
   //Serial.print("  ");
   


   // Queue array
      //if (t > 0) {
      rpm_array[0] = rpm_array[1];
      rpm_array[1] = rpm_array[2];
      rpm_array[2] = rpm_array[3];
      rpm_array[3] = rpm_array[4];
      rpm_array[4] = 100000/t;  //converting to 100 Hz  
      //Serial.print (rpm_array[1,2,3,4,5] \r);
      //Serial.print("  ");
      //}

     
 trigger++;
}

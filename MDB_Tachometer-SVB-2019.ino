// source of code: http://www.pyroelectro.com/tutorials/tachometer_rpm_arduino/software.html
// trigger idea: https://forum.arduino.cc/index.php?topic=155270.0 

volatile int trigger = 0;
volatile float time = 0;
volatile float time_last = 0;
volatile int rpm_array[5] = {0,0,0,0,0};
int rpm = 0;

void setup()
{
  //Digital Pin 2 Set As An Interrupt
 attachInterrupt(0, my_interrupt, FALLING);

}

//Main Loop To Calculate RPM
void loop()
{
  ////lcd.setCursor(4, 1);
  ////lcd.print(time);   

  
  {    
    //Last 3 Average RPM Counts Eqauls....
      if (trigger < 5) 
          {rpm = (rpm_array[0] + rpm_array[1] + rpm_array[2] + rpm_array[3] + rpm_array[4]) / 5;
          trigger = 0;
          }
      }
      
      // print(rpm);   
      
}
 

//Capture Interrupt
void my_interrupt()
{
   time = (micros() - time_last); 
   time_last = micros();

      rpm_array[0] = rpm_array[1];
      rpm_array[1] = rpm_array[2];
      rpm_array[2] = rpm_array[3];
      rpm_array[3] = rpm_array[4];
      rpm_array[4] = 60*(1000000/(time));    
     
 trigger++;
}

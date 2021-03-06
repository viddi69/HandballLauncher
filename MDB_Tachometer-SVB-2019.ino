// source of code: http://www.pyroelectro.com/tutorials/tachometer_rpm_arduino/software.html
// trigger idea: https://forum.arduino.cc/index.php?topic=155270.0 

volatile unsigned long int t = 0;
volatile unsigned long int time_last = 0;
volatile float rpm_array[5] = {0,0,0,0,0};
volatile unsigned long int rpm = 0;

void setup()
{
  Serial.begin(9600);
  //Digital Pin 2 Set As An Interrupt
 attachInterrupt(0, my_interrupt, FALLING);

}

//Main Loop
void loop()
{
}
 

//Capture Interrupt
void my_interrupt()
{
   t = ((millis() - time_last)); // Stores to t, ms between two interrupts 
   time_last = millis(); // Time in ms from program start
   //Serial.print(t);
   //Serial.print("  ");

   // Queue array
      //if (t > 0) { // originally, we had a trigger "t"
      rpm_array[0] = rpm_array[1];
      rpm_array[1] = rpm_array[2];
      rpm_array[2] = rpm_array[3];
      rpm_array[3] = rpm_array[4];
      rpm_array[4] = 100000/t;  //converting to 100 Hz  
      //Serial.print (rpm_array[1,2,3,4,5] \r); // For testing in beginning
      //Serial.print("  ");
      //}
  
      //Last 5 Average RPM Counts Eqauls.... (first 5 results are weird/wrong - but this way makes it easier to process)
          rpm = (rpm_array[0] + rpm_array[1] + rpm_array[2] + rpm_array[3] + rpm_array[4]) / 5;
}

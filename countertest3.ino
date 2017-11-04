/* Arduino program to be used in counting objects passing on a conveyor
       Written by Shawn
*/
const int irPin = 22; //Infrared sensor's signal pin connected to pin 22 on the Arduino
int count = 0; //flag
int detect; // initializes the variable 'detect'. This variable is either a 1 or 0

void setup(){
  pinMode(irPin,INPUT); //declares the Infrared sensor to be an input
  Serial.begin(9600); // initializes the Serial monitor
  Serial.println("CLEARSHEET"); //clears the excel sheet
  Serial.println("LABEL,Date,Time,Timer,Counter,millis"); /* Defines the 5 columns on the excel sheet;
                                                          Date, Time, Timer, Counter and Millis.*/
  //the following snippet sets the names for the 3 checkboxes for PLX-DAQ
   Serial.println("CUSTOMBOX1,LABEL,Stop logging at 250?");
   Serial.println("CUSTOMBOX2,LABEL,Resume log at 350?");
   Serial.println("CUSTOMBOX3,LABEL,Quit at 450?");
  // the following snippet checks the the first two checkboxes
   Serial.println("CUSTOMBOX1,SET,1");
   Serial.println("CUSTOMBOX2,SET,1");
   Serial.println("CUSTOMBOX3,SET,0");
}

void loop(){
  int dummy=0;
  dummy = scontrol();// main function to be used with the infrared sensor
  excel(); // function that prints the data in realtime to the Excel worksheet
}
int scontrol(){
  detect = digitalRead(irPin); // reads thee value of the infrared sensor, either high or low
  if (detect == 0){
    //if the sensor has sensed a box the flag is set
    if (count == 0){
       count = 1;
        delay(1000);
    }
    //the box is still being sensed
    else{
      return 0;
    }
  }
  // when no object is being detected, the flag is reset
  else{
    count = 0;
  }  
 }
  void excel(){
    if (detect == 0){
    Serial.print("DATA,DATE,TIME,TIMER,"); // prints out on the excel worksheet the date, time and whether an object has been detected.
    Serial.print("detect");
    Serial.print(",");
    delay(10);
    Serial.println(millis());
    }
  }

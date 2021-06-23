#include <Servo.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int output1Value = 0;
int sen1Value = 0;
int sen2Value = 0;
int const gas_sensor = A1;
int const LDR = A0;
int limit = 400;
float x,z,temp;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
// Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

Servo servo_7;

void setup(){
  
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  
  Serial.begin(9600);		//initialize serial communication
  pinMode(A0, INPUT);		//LDR
  pinMode(A1,INPUT);      	//gas sensor
  pinMode(A4, INPUT);       //temperature sensor
  pinMode(13, OUTPUT);		//connected to relay
  servo_7.attach(7, 500, 2500); //servo motor

  pinMode(8,OUTPUT);     	//signal to piezo buzzer
  pinMode(9, INPUT);		//signal to PIR	
  pinMode(10, OUTPUT);		//signal to npn as switch
 
}

void loop()
{
  lcd.clear();
  
     //------light intensity control------//
//-------------------------------------------------------------- 
    int val1 = analogRead(LDR);
    sen2Value = digitalRead(9);
  if ((val1 > 500)||(sen2Value == 1)) 
  	{
    digitalWrite(13, LOW);
    Serial.print("Bulb ON = ");
    Serial.print(val1);
    //lcd.clear();
    //lcd.setCursor(0,1);
    lcd.print("L: ON ");
    //delay(1500);
  	} 
  else 
  	{
     digitalWrite(13, HIGH);
     Serial.print("Bulb OFF = ");
     Serial.print(val1);
    // lcd.clear();
    // lcd.setCursor(0,1);
     lcd.print("L: OFF");
    // delay(300);
  	}

//--------------------------------------------------------------  
        //------ light & fan control --------// 
//--------------------------------------------------------------
  sen2Value = digitalRead(9);
  z= analogRead(A4);  //Fan on with high temperature
  temp = (double)z / 1024;       
  temp = temp * 5;                 
  temp = temp - 0.5;               
  temp = temp * 100;
  if ((sen2Value == 1) || (temp>30)) 
  {
     digitalWrite(10, HIGH);//npn as switch ON
     delay(500);
     lcd.setCursor(0,1);
     lcd.print("F: ON");
   }
  
  else if ((sen2Value == 0) || (temp<30)) 
  	{
    	
    digitalWrite(10, LOW); //npn as switch OFF
    lcd.setCursor(0,1);
    lcd.print("F: OFF");
  	}
  
   delay(1000);
//---------------------------------------------------------------
       // ------- Gas Sensor --------//
//---------------------------------------------------------------
int val = analogRead(gas_sensor);      //read sensor value
  //Serial.print("|| Gas Sensor Value = ");
  Serial.print(val);				   //Printing in serial monitor
//val = map(val, 300, 750, 0, 100); 
  //if (val > limit)
  	//{
    //	tone(8, 650);
lcd.clear();  	//}
if(val>600){
tone(8,650);  
//digitalWrite(9,HIGH);
lcd.setCursor(0,0);
lcd.print("Gas level = ");
lcd.print(val);
lcd.setCursor(0,1);
lcd.print("Gas leak");
delay(3000);
}
  else {
//tone(8,450);    
//digitalWrite(9,LOW);
lcd.setCursor(0,0);
lcd.print("Gas level = ");
lcd.print(val);
//lcd.setCursor(0,1);
//lcd.print("Yay no gas leak ");
noTone(8);    
delay(500);
}
     
delay(300);
noTone(8);

 //-------------------------------------------------------------- 
      //-------  servo motor  ---------//
 //------------------------------------------------------------- 
  sen1Value = 0.01723 * readUltrasonicDistance(6, 6);
  lcd.clear();
  lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("D:"); // Prints string "Distance" on the LCD
  lcd.print(sen1Value); // Prints the distance value from the sensor
  lcd.print("cm");
  delay(10);
  
  if (sen1Value < 100) 
  	{
    lcd.setCursor(0,1);
    lcd.print("Door Open");
    delay(1000);
    servo_7.write(90);
    Serial.print(" 	  || Door Open!  ; Distance = ");
    Serial.print(sen1Value);
    Serial.print("\n");
  	} 
  
  else 
  	{
    lcd.setCursor(0,1);
    lcd.print("Door Close");
    delay(1000);
    servo_7.write(0);
    Serial.print(" 	  || Door Closed! ; Distance =  ");
    Serial.print(sen1Value);
    Serial.print("\n");
  }
  delay(1000); // Delay a little bit to improve simulation performance
}
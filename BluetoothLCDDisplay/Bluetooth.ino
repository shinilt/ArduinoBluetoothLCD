/*
Program to activate an LCD display where there is a motion detected.
Digitial pin D7 is the input for pir sensor, bluetooth uses tx rx serial pins, and lcd uses a4 and a5 as the contorl pins for serial comm.
*/

#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
const byte pirSensorPin = 7;
int pir_sensor_value;
String message;
String message_1;
String message_2;
String message_3;
String message_4;
String message_5;

void setup() 
{
  pinMode(pirSensorPin,INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.begin(20,4);
  lcd.backlight();
  writeLCD204("Initiated. No new messages!");
  delay(2000);
  message="";
  message_1="No more messages";
  message_2="";
  message_3="";
  message_4="";
  message_5="";
  
}
void loop() 
{
 
  pir_sensor_value=digitalRead(pirSensorPin);
  if(Serial.available()>0) //if the bluetooth module is sending something...
  {
    message = Serial.readString();
    message.trim();
    HandleIncomingString(message);
    
  }
DisplayMsgs();    
}

void writeLCD204(String inputStr){
 lcd.clear();
 int maxRow=findLines(inputStr); 
 int totalLength=inputStr.length();
 for(int row=0; row<maxRow;row++){
  for (int thisColumn = 0; thisColumn < 20; thisColumn++) {
  lcd.setCursor(thisColumn,row); 
  int currentPosition=20*row + thisColumn;
  if(currentPosition<totalLength){
    lcd.print(inputStr[20*row + thisColumn]);}
  }
 }  
}

int findLines(String inputStr){
  float lines = inputStr.length()/20.0;
  if (lines<=1.0){
    return 1;}
    else if(lines<=2.0){
      return 2;}
      else if(lines<=3.0){
      return 3;}
      else{return 4;}
}

void ManageMsgQ(String newMsg){
  message_5 = message_4;
  message_4 = message_3;
  message_3 = message_2;
  message_2 = message_1;
  message_1 = newMsg;
}
void DisplayMsgs(){
 if (pir_sensor_value==1){
    lcd.backlight();
    
  if(message_1.length()>0){  
  writeLCD204(message_1);
  delay(4000);}
  if(message_2.length()>0){
  writeLCD204(message_2);
  delay(4000);}
  if(message_3.length()>0){
  writeLCD204(message_3);
  delay(4000);}
  if(message_4.length()>0){
  writeLCD204(message_4);
  delay(4000);}
  if(message_5.length()>0){
  writeLCD204(message_5);
  delay(4000);}
    }
 else{
      lcd.noBacklight();
    delay(2000);}
  }


  
void HandleIncomingString(String newMsg){
  if(newMsg.startsWith("cmd-"))
  {
    String command= newMsg.substring(4);
    int commandIndicator;
    if (command== "clear"){commandIndicator=1;}
    if (command== "backlightoff"){commandIndicator=2;}
    if (command== "backlighton"){commandIndicator=3;}
switch (commandIndicator) {
  case 1:
    //do something when var equals 1
    command_clear();
    break;
  case 2:
    //do something when var equals 1
    command_backlightOff();
    break;
  case 3:
    //do something when var equals 1
    command_backlightOn();
    break;
  default:
    // if nothing else matches, do the default
    // default is optional
    break;
}
    }
  else{
    ManageMsgQ(message);
    }
}

void command_clear()
{
  message_5 = "";
  message_4 = "";
  message_3 = "";
  message_2 = "";
  message_1 = "No more messages";
  }

  void command_backlightOff(){
     lcd.noBacklight();
    }
  void command_backlightOn(){
     lcd.backlight();
     delay(3000);
    }

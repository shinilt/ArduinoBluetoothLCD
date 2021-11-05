#include "DHT.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht;
String message;
String message2;
byte buzzer;
void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");
  dht.setup(2);   /* set pin for data communication */
  lcd.init();
  lcd.begin(20,4);
  lcd.backlight();
  writeLCD204("Initiated.Waiting..");
  delay(2000);
  buzzer=5;
  pinMode(buzzer,OUTPUT);
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());  /* Delay of amount equal to sampling period */  

  float humidity = dht.getHumidity();     /* Get humidity value */
  float temperature = dht.getTemperature(); /* Get temperature value */
  
  message ="Temp- "+ String(temperature) + "*C   Humidity-" + String(humidity) + "%";
  message2="Humidity-" + String(humidity) + "%";
  writeLCD204(message);
 // writeLCD204Line(message2,2);

  
  if (humidity > 60.00){
    Serial.println("humidity is more");
    callBuzzer();
    }
  
  delay(5000);
}

void writeLCD204(String inputStr){
 int maxRow=findLines(inputStr); 
 int totalLength=inputStr.length();
 for(int row=0; row<maxRow;row++){
  for (int thisColumn = 0; thisColumn < 16; thisColumn++) {
  lcd.setCursor(thisColumn,row); 
  int currentPosition=16*row + thisColumn;
  if(currentPosition<totalLength){
    lcd.print(inputStr[16*row + thisColumn]);}
  }
 }  
}

int findLines(String inputStr){
  float lines = inputStr.length()/16.0;//this is specific to 16*2 LCD display. That is were 16 is coming from.
  if (lines<=1.0){
    return 1;}
    else{return 2;}
}
void callBuzzer()
{tone(buzzer,200);
delay(500);
noTone(buzzer);
delay(500);}

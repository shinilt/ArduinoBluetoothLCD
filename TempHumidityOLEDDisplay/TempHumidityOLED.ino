//https://randomnerdtutorials.com/guide-for-oled-display-with-arduino/ Read this tutorial for more info on working with oled.
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
DHT dht;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
String message;
String message2;
byte buzzer=5;//set buzzer control pin to Digital pin 5
void setup()
{
  Serial.begin(9600);
  //Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");
  dht.setup(2);   /* set pin for data communication */
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Initiated. Waiting..");
  display.display(); 
  pinMode(buzzer,OUTPUT);
  callBuzzer();//buzzer test
  display.clearDisplay();
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());  /* Delay of amount equal to sampling period */  

  float humidity = dht.getHumidity();     /* Get humidity value */
  float temperature = dht.getTemperature(); /* Get temperature value */
  writeOLED(temperature,humidity);
  if (humidity > 60.00){
    Serial.println("humidity is more");
    callBuzzer();
    }
  
  delay(5000);
  display.clearDisplay();
}




void callBuzzer()
{tone(buzzer,200);
delay(500);
noTone(buzzer);
delay(500);}
void writeOLED(float temperature, float humidity){
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(temperature);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(humidity);
  display.print(" %"); 
  display.display();
  }

//Created by Aref Nik 


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SparkFunHTU21D.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

//Create an instance of the object
HTU21D myHumidity;


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

//===============================================================================
//  Initialization
//===============================================================================
void setup() {
  Serial.begin(115200);
  myHumidity.begin();
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // I2C Address 0x3C for 128x32
    Serial.println(F("failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer, set small font size and print 4 lines of text to display
  display.clearDisplay(); 
  display.setTextSize(1);                    // Set for small font
  display.setTextColor(WHITE);
  

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
}
//===============================================================================
//  Main
//===============================================================================
void loop() {
  float humd = myHumidity.readHumidity();
  float temp = myHumidity.readTemperature();
  display.clearDisplay(); 
  display.setCursor(0,0); 
  display.setTextSize(1); // Set cursor to upper left
  display.print("Temp:  ");  // Println moves the cursor down
  display.setTextSize(2); 
  display.print(temp, 1);
  display.setCursor(0,16);
  display.setTextSize(1);
  display.print("Humid: ");
  display.setTextSize(2); 
  display.print(humd, 1);
  display.display();
  delay(200);
}

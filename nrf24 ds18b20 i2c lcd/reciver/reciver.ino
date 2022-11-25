//Created by Aref Nik 


#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 
#include <Wire.h> 
#include <printf.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);
RF24 radio(9, 8);  // CE, CSN

const byte address[6] = "GLB01";

float temp = 0.0;
unsigned long count = 0;
void setup() {
  printf_begin();
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.begin(16, 2);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
  radio.setChannel(120);
  radio.setDataRate(RF24_250KBPS);
  radio.enableDynamicPayloads();
  radio.setPALevel(RF24_PA_MAX);
}

void loop() {
 if (radio.available())
  {
    lcd.clear();
    radio.read(&temp, sizeof(temp)); 
    Serial.println(temp);
    lcd.print("Temp:  ");
    lcd.print(temp);
    lcd.setCursor(0,1);
    lcd.print("Count: ");
    count++;
    lcd.print(count);
    //radio.testRPD();
    
  }
}

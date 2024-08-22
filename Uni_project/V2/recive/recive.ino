#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16x2 LCD
LiquidCrystal_I2C lcd(0x3F, 16, 2);

const uint64_t pipeIn = 0xE8E8F0F0E1LL; 
RF24 radio(9, 10);

struct MyData {
  byte mq2; 
  float temp;
};

MyData data;

byte zero[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte one[] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
};
byte two[] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000
};
byte three[] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100
};
byte four[] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110
};
byte five[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
bool toggle = false;

void setup()
{
  Serial.begin(9600); 
  radio.begin();
  //radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, pipeIn);
  radio.startListening();

  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
  lcd.clear();                     // Clear the LCD
   
  lcd.createChar(0, zero);
  lcd.createChar(1, one);
  lcd.createChar(2, two);
  lcd.createChar(3, three);
  lcd.createChar(4, four);
  lcd.createChar(5, five);
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print(" golabi master");
  delay(500);
}


void loop()
{
  int percent = 0;
  lcd.setCursor(0,0);
  
  if ( radio.available() ) {
    radio.read(&data, sizeof(data));
    Serial.print("Gas Value recived: ");
    Serial.println(data.mq2);
    Serial.print("temp: ");
    Serial.println(data.temp);
    
    percent = map(data.mq2 , 0 , 256, 0, 100);
    lcd.clear();
    lcd.print(data.temp);
    updateProgressBar(percent, 100, 1);
    
    }
    if(percent > 50 && toggle == true){
      lcd.noBacklight();
      delay(200);
      toggle = !(toggle);
    }
    if(percent > 50 && toggle == false){
      lcd.backlight();
      delay(200);
      toggle = !(toggle);
    }
  
}

void updateProgressBar(unsigned long count, unsigned long totalCount, int lineToPrintOn) {
    double factor = totalCount/80.0;          
    int percent = (count+1)/factor;
    int number = percent/5;
    int remainder = percent%5;
    int i = number;
    if(number > 0)
    {
      for(i ; i > -1 ; i--){
       lcd.setCursor(i-1,lineToPrintOn);
       lcd.write(5);
      }
    }
   
       lcd.setCursor(number,lineToPrintOn);
       lcd.write(remainder);   
 }

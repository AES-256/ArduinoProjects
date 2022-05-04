#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2); 

String output;
int numberofphrases = 17;
String phrases[] ={"Ask again later", "It is certain", "Without a doubt", "Yes - definitely", "As I see it, yes", "Most likely", "Outlook good", "Yes", "My reply is no", "Very doubtful", "No", "Not a chance", "No way", "Absolutely not", "I doubt it", "Ask again", "I'm uncertain"};


void setup() {
  pinMode(9,INPUT_PULLUP);
  lcd.init();                      
  lcd.backlight();
  lcd.home();
  lcd.begin(16, 2);
  randomSeed(analogRead(A3));
}

void loop() {
  if(digitalRead(9)==0){
    lcd.clear();
    output = phrases[random(numberofphrases)];
    lcd.print(output);
  }

}

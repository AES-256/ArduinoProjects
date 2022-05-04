#include <EEPROM.h>

void setup() {
  String readBack;
  Serial.begin(9600);
  Serial.println("Read String from EEPROM: ");
  readBack = EEPROM.get(0 , readBack);
  Serial.println(readBack);  

}
 
void loop() {
  
}

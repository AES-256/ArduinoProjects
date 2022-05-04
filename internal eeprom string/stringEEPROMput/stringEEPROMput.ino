#include <EEPROM.h>

String sample = "this is a sample text i dont know what to put here";

void setup() {
  Serial.begin(9600);
  int eeAddress = 0;   //Location we want the data to be put.
  EEPROM.put(0, sample);
  delay(5);
  Serial.println("Written String data type!");
}

void loop() {
}

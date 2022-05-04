//change setting before you run it

#include <Wire.h>

#include "SparkFun_External_EEPROM.h" 
ExternalEEPROM myMem;

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("I2C EEPROM Cleaner");

  Wire.begin();
  Wire.setClock(400000);

  if (myMem.begin() == false)
  {
    Serial.println("No memory detected. Freezing.");
    while (1);
  }
  Serial.println("Memory detected!");

  //Set settings for this EEPROM
  myMem.setMemorySize(1024/8); //In bytes. 512kbit = 64kbyte
  myMem.setPageSize(8); //In bytes. Has 128 byte page size.
  myMem.enablePollForWriteComplete(); //Supports I2C polling of write completion
  myMem.setPageWriteTime(5); //3 ms max write time

  Serial.print("Mem size in bytes: ");
  Serial.println(myMem.length());

  for(int i = 0 ; i<=myMem.length() ; i++){
    myMem.put(i, 0); //(location, data)
  }
  int temp=0;
  for(int j = 0 ; j<=myMem.length();j++){
    myMem.get(j, temp); //location to read, thing to put data into
    Serial.print("I read: ");
    Serial.print(temp);
    Serial.print("   ");
    Serial.println(j);
  }
  
  
}

void loop()
{

}

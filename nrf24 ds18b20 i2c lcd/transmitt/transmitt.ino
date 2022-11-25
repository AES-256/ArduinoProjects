//Created by Aref Nik 


#include <DS18B20.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>


DS18B20 ds(2);
RF24 radio(9, 8);
const byte address[6] = "GLB01";

float temp=0.0;


  void setup() {
  Serial.begin(9600);
  ds.setResolution(12);
  printf_begin();
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();
  radio.setChannel(120);
  radio.setDataRate(RF24_250KBPS);
  radio.enableDynamicPayloads();
  radio.setPALevel(RF24_PA_MAX);
  radio.setCRCLength(RF24_CRC_16);
  
}

void loop() {
   while (ds.selectNext()) {
       temp = ds.getTempC();
       radio.powerUp();
       radio.printDetails();
       radio.write(&temp, sizeof(temp));
       radio.powerDown();
   }
    
}

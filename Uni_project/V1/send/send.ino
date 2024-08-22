#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeOut = 0xE8E8F0F0E1LL; 

RF24 radio(9, 10); //  CN and CSN  pins of nrf
const int mq2Pin = A0; // Analog pin connected to MQ-2 sensor

struct MyData {
  byte mq2;
};
MyData data;

void setup()
{
  Serial.begin(9600); 
  radio.begin();
  //radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
}
void loop()
{
  data.mq2 = analogRead(mq2Pin); // Read the analog value from MQ-2 sensor 
  
  if (isnan(data.mq2)){
    Serial.println(F("Failed to read from MQ-2 sensor!"));
    return;
  }
  Serial.print("Gas Level: ");
  Serial.println(data.mq2);
  
  radio.write(&data, sizeof(data));

  delay(500);
  }

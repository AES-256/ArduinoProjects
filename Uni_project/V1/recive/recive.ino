#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeIn = 0xE8E8F0F0E1LL; 
RF24 radio(9, 10);

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
  radio.openReadingPipe(1, pipeIn);
  radio.startListening();

}


void loop()
{
  if ( radio.available() ) {
    radio.read(&data, sizeof(data));
    Serial.print("Gas Value recived: ");
    Serial.println(data.mq2);
    }
  
  delay(500);
  
}

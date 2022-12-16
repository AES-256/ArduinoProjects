#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 9
#define RST_PIN 10
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "C1 39 52 D3") //to find card uid go to the serial moniter, scan your card and copy uid into the section

  {
    digitalWrite(4,HIGH);
    digitalWrite(3,LOW);
    Serial.println("Authorized access");
    Serial.println();
    delay(1000);
  }
 
 else   {
    digitalWrite(4,LOW);
    digitalWrite(3,HIGH);
    Serial.println(" Access denied");
    Serial.println();
    delay(1000);
  }
} 

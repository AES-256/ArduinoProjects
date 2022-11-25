//Created by Aref Nik 
 
// Define Connections to 74HC595
 
// ST_CP pin 12
const int latchPin = 10;
// SH_CP pin 11
const int clockPin = 11;
// DS pin 14
const int dataPin = 12;

int cycle[10] = {B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B10000000};
int runner[12] = {B0000001,B00000011,B00000111,B00001110,B00011100,B00111000,B01110000,B11100000,B11000000,B10000000};
int flashy[4] = {B10101010,B01010101};
int police[14] = {B11110000,B00000000,B11110000,B00000000,B11110000,B00000000,B00001111,B00000000,B00001111,B00000000,B00001111,B00000000};
void setup ()
{
  // Setup pins as Outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
 
void loop() {
  // Count from 0 to 255 and display in binary
 
 // Count from 0 to 15
  for (int num = 0; num < 10; num++)
  {
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latchPin, LOW);
 
    // Shift out the bits
    shiftOut(dataPin, clockPin, MSBFIRST, cycle[num]);
 
    // ST_CP HIGH change LEDs
    digitalWrite(latchPin, HIGH);
 
    delay(1000);
  }
   // Count from 0 to 15
  for (int num = 0; num < 12; num++)
  {
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latchPin, LOW);
 
    // Shift out the bits
    shiftOut(dataPin, clockPin, MSBFIRST, runner[num]);
 
    // ST_CP HIGH change LEDs
    digitalWrite(latchPin, HIGH);
 
    delay(333);
  }
  for(int temp=0;temp<10;temp++){
    for (int num = 0; num < 2; num++)
  {
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latchPin, LOW);
 
    // Shift out the bits
    shiftOut(dataPin, clockPin, MSBFIRST, flashy[num]);
 
    // ST_CP HIGH change LEDs
    digitalWrite(latchPin, HIGH);
 
    delay(333);
    }
  }
    for (int num = 0; num < 12; num++)
  {
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latchPin, LOW);
 
    // Shift out the bits
    shiftOut(dataPin, clockPin, MSBFIRST, police[num]);
 
    // ST_CP HIGH change LEDs
    digitalWrite(latchPin, HIGH);
 
    delay(100);
    }
}

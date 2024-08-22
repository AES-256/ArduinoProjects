/** This example works just like normal Blink except that it goes to sleep instead of just `delay()`.
 *
 */
 
#include <SimpleSleep.h>

SimpleSleep Sleep;

const uint8_t ledPin1 = 4;
const uint8_t ledPin2 = 1;


void setup()
{
  pinMode(4, OUTPUT);
  pinMode(1, OUTPUT);
}

void loop()
{
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  Sleep.deeplyFor(100);
  
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  Sleep.deeplyFor(1900);
}

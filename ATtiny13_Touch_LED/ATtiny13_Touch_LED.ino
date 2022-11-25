/***********************************************************************|
| Capacitive touch library for ATtiny13                                 |
| //Created by Aref Nik                                                                       |
| Touch_LED.ino                                                         |
|                                                                       |
| A light-weight library for using the ADC inputs on the ATtiny13 as    |
| capacitive touch sensors.                                             |
| Developed by MCUdude, based on nerdralph's adctouch implementation.   |
| https://github.com/MCUdude/MicroCore                                  |
|                                                                       |
| In this example we use A2 and A3 as touch sensor pins, and two LEDs   |
| will light up if the touch pins are being touched and the value is    |
| greater than the threshold.                                           |
|***********************************************************************/

#include <ADCTouch.h>

// Sample each touch pin 32 times
const uint16_t ADCTouch::samples = 32;

// LED pins
const uint8_t LED1 = 4;


// Touch reference values to zero out the offset
int16_t ref_A3;


// Touch threshold for turning on or off the LEDs
// Lower is more sensitive
const uint8_t threshold = 10;


void setup()
{
  // Set LED pins as output
  pinMode(LED1, OUTPUT);


  // Reference values to account for the capacitance of the touch pad
  ref_A3 = Touch.read(A3);

}

void loop()
{
  // Read touch
  int16_t touch_A3 = Touch.read(A3) - ref_A3;


  // Turn on or off LED based on threshold
  digitalWrite(LED1, touch_A3 > threshold);

}

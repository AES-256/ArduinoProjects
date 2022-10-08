# High Voltage Seiral Programmer for AVR

if you accidently bricked your AVR microcontroller or set the fuse-bits wrong you know that now your microcontroller cant take new code 

luckly, AVR micros has a backup way to reset you microcontroller 

the reset pin in you controller has a maximum of 13V tolerance and if we connect 12V signal to it at the right moment we can make micro to take our code

in this procces clock is provided by host (witch in this case is arduino UNO) so that even when clock is not avalable on micro we can reset it back to normal.

## resetting ATTINY

1. Uploading code to arduino UNO
2. get the hardware ready
3. connecting 12V supply 
4. opening Serial monitor at 19200 BuadRate

## code

upload code provided in repository to your arduino UNO

## hardware

for hardware we need:

* Generic NPN transistor (2N2222 , 2N3904 , BC547)
* 1KOhm Resistor

thats all.


so start connect them as shown in this below diagram

![Diagram](https://github.com/AES-256/ArduinoProjects/raw/main/attiny13aHVSP/diagram.png)

---
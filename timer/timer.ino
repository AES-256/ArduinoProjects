void setup() {
  DDRB = 0;
  PORTB = 0;
  DDRB |= (1 << DDB0); //setting attiny13 pin0 (PB0) to OUTPUT

  
  TCCR0A |= (1 << WGM01);   //CTC mode
  TCCR0A |= (1 << COM0A0);  //toggle OC0A on compare match

  TCCR0B |= (1 << CS02) | (1 << CS00); //1024 prescalar
  OCR0A = 52;              //1Hz @ 128KHz internal clock
  
  
 
  
}

void loop() {
  

}

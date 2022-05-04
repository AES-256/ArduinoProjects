void setup(){ 
  TCCR1A = 0; //clear control register part A
  TCCR1B = 0; //clear control register part B 
  // Wave Form Generator: PWM, phase and frequency correct 8, Top = ICR1
  TCCR1A = (1<<COM1A1) + (0<<COM1A0) + (1<<COM1B1) + (0<<COM1B0) + (0<<WGM11)+ (0<<WGM10); 
  TCCR1B = (0<<ICNC1) + (0<<ICES1) + (1<<WGM13) + (0<<WGM12) + (0<<CS12) + (0<<CS11) + (1<<CS10); // prescaler = 1 (none) 
  ICR1 = 63999;
  DDRB |= (1<<PB1)|(1<<PB2);
  OCR1A = 31999;
  OCR1B = 15999;

} 
void loop() { 
 // do something else
} 

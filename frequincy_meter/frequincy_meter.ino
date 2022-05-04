bool flag=false;
volatile long time1;
volatile long time2;
void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), golabi, FALLING); 
}

void loop() {
  ///*
  Serial.println("------------------");
  Serial.print("time1: ");
  Serial.println(time1);
  Serial.print("time2: ");
  Serial.println(time2);
  Serial.print("period: ");
  Serial.println(time2-time1);
  Serial.print("frequincy: ");
  Serial.println(1/time2-time1);
  delay(500);

}

void golabi(){
  if(flag==false){
    time1 = 0;
    flag=true;
    time1 = micros();
  }
  else{
    time2 = 0;
    flag=false;
    time2 = micros();
  }
  
}

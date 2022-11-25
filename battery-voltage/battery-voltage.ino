//Created by Aref Nik 


void setup() {
  pinMode(A0,INPUT); //set pin A0 as input form voltage divider
  //voltage divider Vcc--100K-A0-22K--GND
  analogReference(INTERNAL);//set ADC to use 
  // 1V1 internal voltage refrence
  Serial.begin(115200); // begining Serial 
  
}

void loop() {
  float sensorValue = analogRead(A0); //read raw ADC value
  float voltage = sensorValue * (1.1 / 1023.0); // this is voltage at A0 pin
  Serial.print("----------------");
  Serial.println();
  Serial.print("Vcc voltage is: ");//some dignity
  Serial.println(voltage*5.77777777); //divide actual Vcc
  //voltage and voltage reading at A0 pin
  //for Example Vcc = 4.17 voltage is = 0.72
  //4.17/0.72 = 5.77777777
  Serial.print("ADC voltage is: ");
  Serial.println(voltage);
  Serial.print("ADC value is: ");
  Serial.println(sensorValue);
  delay(250);
}

#include <DS18B20.h>

DS18B20 ds(2);

void setup() {
  Serial.begin(9600);
  ds.setResolution(12);
  //setting resolution, can be between 9-bit to 12-bit 
  ds.setAlarms(24,26);
  //low alarm , high alarm. if alarm is set you can check ds.hasAlarm();
}

void loop() {
  while (ds.selectNext()) {
    Serial.println("------------------------");
    
    Serial.print("Temp : ");
    Serial.println(ds.getTempC());
    //tempture in celciuse
    
    Serial.print("Resolution : ");
    Serial.println(ds.getResolution());
    //return resolution in bit
    
    Serial.print("Power Mode : ");
    Serial.println(ds.getPowerMode());
    //if 1 means powered from external power supply
    //if 0 means powered from parasite power on dataline
    
    Serial.print("Family code : ");
    Serial.println(ds.getFamilyCode());
    
    
    Serial.print("Number Of Devices : ");
    Serial.println(ds.getNumberOfDevices());
    //return number of device on bus
    
    Serial.print("Alarm : ");
    Serial.println(ds.hasAlarm());
    //return HIGH if high or low bound passes
    
    Serial.print("Alarm Low: ");
    Serial.println(ds.getAlarmLow());
    //return low alarm value
    
    Serial.print("Alarm High: ");
    Serial.println(ds.getAlarmHigh());
    ////return high alarm value

  }
}

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeOut = 0xE8E8F0F0E1LL; 

RF24 radio(9, 10); //  CN and CSN  pins of nrf
const int mq2Pin = A0; // Analog pin connected to MQ-2 sensor

struct MyData {
  byte mq2;
  float temp;
};
MyData data;

// Define the analog input pin
const int THERMISTOR_PIN = A1;

// Constants for the 10k NTC thermistor
const float THERMISTOR_NOMINAL = 10000;  // 10k Ohms at 25°C
const float TEMPERATURE_NOMINAL = 25;    // 25°C
const float B_COEFFICIENT = 3950;        // Beta coefficient (usually between 3000-4000)
const float SERIES_RESISTOR = 10000;     // 10k Ohm fixed resistor

void setup()
{
  Serial.begin(9600); 
  radio.begin();
  //radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
}
void loop()
{
  data.mq2 = analogRead(mq2Pin); // Read the analog value from MQ-2 sensor 
  
  if (isnan(data.mq2)){
    Serial.println(F("Failed to read from MQ-2 sensor!"));
    return;
  }
  Serial.print("Gas Level: ");
  Serial.println(data.mq2);
  

  // Read the analog value from the thermistor
  int analogValue = analogRead(THERMISTOR_PIN);

  // Convert the analog value to resistance
  float resistance = SERIES_RESISTOR / ((1023.0 / analogValue) - 1);

  // Convert the resistance to temperature using the Steinhart-Hart equation
  float temperature;
  temperature = resistance / THERMISTOR_NOMINAL;          // (R/Ro)
  temperature = log(temperature);                         // ln(R/Ro)
  temperature /= B_COEFFICIENT;                           // 1/B * ln(R/Ro)
  temperature += 1.0 / (TEMPERATURE_NOMINAL + 273.15);    // + (1/To)
  temperature = 1.0 / temperature;                        // Invert
  temperature -= 273.15;                                  // Convert to Celsius

  data.temp = temperature;
  Serial.println(data.temp);
  
  radio.write(&data, sizeof(data));

  delay(500);
  }

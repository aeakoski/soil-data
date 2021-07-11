#include <dht.h>
#include <OneWire.h>
#include <DallasTemperature.h>

dht DHT;
#define DHT11_PIN A1

int RYE_SOIL_MOISTURE_PIN = 0; // Soil Sensor input at Analog PIN A0
int RYE_SOIL_TEMPERATURE_PIN = A2; // Soil Temperature input at Analog PIN A2
int AIR_TEMPERATURE_PIN = A3; // Soil Temperature input at Analog PIN A3

OneWire ryeSoilWire(RYE_SOIL_TEMPERATURE_PIN);
OneWire airWire(AIR_TEMPERATURE_PIN);
DallasTemperature ryeSoilSensor(&ryeSoilWire);
DallasTemperature airTemperatureSensor(&airWire);

void setup() {
  Serial.begin(9600);
  Serial.println("");
  ryeSoilSensor.begin();
  airTemperatureSensor.begin();
  delay(2000);
}

void metricToSerial(String location, String type, String unit, float measurement){
  Serial.println(location + ":" + type + ":" + unit + ":" + String(measurement));
}

void meassureSoilMoisture(){
  float value = 0.0;
  for(int i = 0; i<=100; i++){
    value = value + (analogRead(RYE_SOIL_MOISTURE_PIN)/10.0);
  }
  value = value/100.0;
  metricToSerial("RYE","SOIL-MOISTURE","PERCENT", value);
}

void meassureSoilTemperature(){
  ryeSoilSensor.requestTemperatures(); // Send the command to get temperatures
  if(ryeSoilSensor.getTempCByIndex(0) < -50){ return; }
  metricToSerial("RYE","SOIL-TEMPERATURE","CELSIUS", ryeSoilSensor.getTempCByIndex(0));
}

void meassureAirTemperature(){
  airTemperatureSensor.requestTemperatures(); // Send the command to get temperatures
  if(airTemperatureSensor.getTempCByIndex(0) < -50){ return; }
  metricToSerial("FIELD","AIR-TEMPERATURE","CELSIUS", airTemperatureSensor.getTempCByIndex(0));
}
void meassureAirMoisture(){
  if(DHT.humidity < 0){ return; }
  metricToSerial("FIELD","AIR-MOISTURE","PERCENT", DHT.humidity);
}
void meassureSunlight(){}

void loop() {
 int chk = DHT.read11(DHT11_PIN);
 meassureSoilMoisture();
 meassureAirTemperature();
 meassureAirMoisture();
 meassureSoilTemperature();
 delay(5000);

}

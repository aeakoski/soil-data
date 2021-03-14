#include <dht.h>

dht DHT;
#define DHT11_PIN 6

int WHEAT_SOIL_MOISTURE_PIN = 0; // Soil Sensor input at Analog PIN A0

void setup() {
  Serial.begin(9600);
  Serial.println("");
}

void metricToSerial(String location, String type, String unit, float measurement){
  Serial.println(location + ":" + type + ":" + unit + ":" + String(measurement));
}

void meassureSoilMoisture(){
  float value;
  value = analogRead(WHEAT_SOIL_MOISTURE_PIN)/10.0;
  metricToSerial("WHEAT","SOIL-MOISTURE","PERCENT", value);
}

void meassureSoilTemperature(){}
void meassureAirTemperature(){
  metricToSerial("FIELD","AIR-TEMPERATURE","CELSIUS", DHT.temperature);
}
void meassureAirMoisture(){
  metricToSerial("FIELD","AIR-MOISTURE","PERCENT", DHT.humidity);  
}
void meassureSunlight(){}

void loop() {
 int chk = DHT.read11(DHT11_PIN);
 meassureSoilMoisture();
 meassureAirTemperature();
 meassureAirMoisture();
 delay(5000);

}


int WHEAT_SOIL_MOISTURE_PIN = 0; // Soil Sensor input at Analog PIN A0

void setup() {
  Serial.begin(9600);
}

void metricToSerial(String location, String type, String unit, int measurement){
  Serial.println(location + ":" + type + ":" + unit + ":" + String(measurement));
}

void meassureSoilMoisture(){
  int value;
  value = analogRead(WHEAT_SOIL_MOISTURE_PIN)/10;
  metricToSerial("WHEAT","SOIL-MOISTURE","PERCENT", value);
}

void meassureSoilTemperature(){}
void meassureAirTemperature(){}
void meassureAirMoisture(){}
void meassureSunlight(){}

void loop() {
 meassureSoilMoisture();
 delay(5000);

}

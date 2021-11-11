//In this algorithm we read the humidity and the temperature values in the environment 
//using the (DHT11) Temperature_Humidity_Sensor and tern the Fan on when 
//the temperature reach 30°C or the humidity reach 40% and tern it off otherwise

#include "DHT.h"
#define DHTPIN 13
#define DHTTYPE DHT11
DHT Temp_Humidity_Sensor(DHTPIN, DHTTYPE);
int Fan = 10 ;
float Temp_Value ;
float Humidity_Value ;

void setup() {
  Serial.begin(9600);
  pinMode(Fan, OUTPUT);
  Temp_Humidity_Sensor.begin();
  Serial.println("Reading From the Sensors ...");
  delay(2000);
}
void loop() {
  Temp_Value = Temp_Humidity_Sensor.readTemperature();
  Humidity_Value = Temp_Humidity_Sensor.readHumidity();

  if (Temp_Value > 30 || Humidity_Value > 40) {
    digitalWrite(Fan, HIGH);
  } else {
    digitalWrite(Fan, LOW);
  }

  Serial.print("Temp_Value_Mositured : ");
  Serial.print(Temp_Value);
  Serial.print("°C   ||     Humidity_Value_Mositured : ");
  Serial.print(Humidity_Value);
  Serial.println("%");
  delay(5000);
}

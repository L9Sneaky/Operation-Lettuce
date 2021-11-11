#include "DHT.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void FPump(int Sol_Senser_pin, int WaterLevel_Senser_pin, int Pump_pin){
  int Sol_Senser_Value ;
  int WaterLevel_Senser_Value ;
  pinMode(Pump_pin, OUTPUT);
  Sol_Senser_Value = analogRead(Sol_Senser_pin);
    Sol_Senser_Value = map(Sol_Senser_Value, 550, 0, 0, 100);
    WaterLevel_Senser_Value = analogRead(WaterLevel_Senser_pin);
  
  if (Sol_Senser_Value < 10 && WaterLevel_Senser_Value < 450) {
    digitalWrite(Pump_pin, HIGH);
    while (WaterLevel_Senser_Value < 700) {
      Sol_Senser_Value = analogRead(Sol_Senser_pin);
      Sol_Senser_Value = map(Sol_Senser_Value, 550, 0, 0, 100);
      WaterLevel_Senser_Value = analogRead(WaterLevel_Senser_pin);
      Serial.print("Sol_Senser_Mositure : ");
      Serial.print(Sol_Senser_Value);
      Serial.print("   ||     WaterLevel_Senser_Mositure : ");
      Serial.print(WaterLevel_Senser_Value);
      Serial.println("%");
      delay(1000);
      }
    } else {
      digitalWrite(Pump_pin, LOW);
    }
    Serial.print("Pump #");
    Serial.print(Pump_pin);
    Serial.print("   ||     Sol_Senser_Mositure : ");
    Serial.print(Sol_Senser_Value);
    Serial.print("   ||     WaterLevel_Senser_Mositure : ");
    Serial.print(WaterLevel_Senser_Value);
    Serial.println("%");
    delay(1000);
}

void FLight(int Photoresistor_Sensor_pin , int LED_pin) {
  pinMode(LED_pin, OUTPUT);
  int MaxRead = 100 ;
  int MinRead = 0 ;
  int Photoresistor_Sensor_Value;
  Photoresistor_Sensor_pin = analogRead(Photoresistor_Sensor_pin);
  Photoresistor_Sensor_Value = map(Photoresistor_Sensor_Value, 0, 75, 0, 100);
  if (Photoresistor_Sensor_Value < 10) {
    digitalWrite(LED_pin, HIGH);
  } else {
    digitalWrite(LED_pin, LOW);
  }
  Serial.print("LED #");
  Serial.print(LED_pin);
  Serial.print("Photoresistor_Sensor_Mositure : ");
  Serial.print(Photoresistor_Sensor_Value);
  Serial.println(" % ");
  delay(1000);
}

void FFan(int Fan_pin) {
  #define DHTPIN Fan_pin
  #define DHTTYPE DHT11
  float Temp_Value ;
  float Humidity_Value ;
  DHT Temp_Humidity_Sensor(DHTPIN, DHTTYPE);
  Temp_Value = Temp_Humidity_Sensor.readTemperature();
  Humidity_Value = Temp_Humidity_Sensor.readHumidity();

  if (Temp_Value > 30 || Humidity_Value > 40) {
    digitalWrite(Fan_pin, HIGH);
  } else {
    digitalWrite(Fan_pin, LOW);
  }
  Serial.print("Fan #");
  Serial.print(Fan_pin);
  Serial.print("Temp_Value_Mositured : ");
  Serial.print(Temp_Value);
  Serial.print("°C   ||     Humidity_Value_Mositured : ");
  Serial.print(Humidity_Value);
  Serial.println("%");
  delay(5000);
}

int Sol_Senser_pin = A0;
int WaterLevel_Senser_pin = A1;
int Pump = 8;


void setup() {
  Serial.begin(9600);
  pinMode(Pump, OUTPUT);
  Serial.println("Reading From the Sensors ...");
  delay(2000);
}

void loop() {
  Sol_Senser_Value = analogRead(Sol_Senser_pin);
  Sol_Senser_Value = map(Sol_Senser_Value, 550, 0, 0, 100);
  WaterLevel_Senser_Value = analogRead(WaterLevel_Senser_pin);

  if (Sol_Senser_Value < 10 && WaterLevel_Senser_Value < 450) {
    digitalWrite(Pump, HIGH);
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
    digitalWrite(Pump, LOW);
  }
  Serial.print("Sol_Senser_Mositure : ");
  Serial.print(Sol_Senser_Value);
  Serial.print("   ||     WaterLevel_Senser_Mositure : ");
  Serial.print(WaterLevel_Senser_Value);
  Serial.println("%");
  delay(1000);
}

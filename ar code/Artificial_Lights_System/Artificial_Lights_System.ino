//In this algorithm we read light values in the environment 
//using the Photoresistor_Senser and tern the LED on when 
//the the light value is less than 30% of what the plant needs and tern it off otherwise

int Photoresistor_Senser_pin = A2;
int LED = 9;
int Photoresistor_Senser_Value ;
int MaxRead = 100 ;
int MinRead = 0 ; 

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  Serial.println("Reading From the Sensor ...");
  delay(2000);
}

void loop() {
  Photoresistor_Senser_Value = analogRead(Photoresistor_Senser_pin);
  Photoresistor_Senser_Value = map(Photoresistor_Senser_Value, 0, 75, 0, 100);

  if (Photoresistor_Senser_Value < 10) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
  Serial.print("Photoresistor_Senser_Mositure : ");
  Serial.print(Photoresistor_Senser_Value);
  Serial.println(" % ");
  delay(1000);
}

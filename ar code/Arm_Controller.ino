//Servo Definitions
#include <Servo.h>
Servo servo01;
Servo servo02;
Servo servo03;
Servo servo04;
Servo servo05;
Servo servo06;

//Constant Declerations
const byte delaySpeed=50;
const byte numChars = 32;

//Variable Declerations
byte servo1CurrPos, servo2CurrPos, servo3CurrPos, servo4CurrPos, servo5CurrPos, servo6CurrPos; //Servo Current Position
char receivedChars[numChars];
boolean newData = false;
String angle;


void setup() 
{
  // Pin attachment to Servo
  servo01.attach(5);
  servo02.attach(6);
  servo03.attach(7);
  servo04.attach(8);
  servo05.attach(9);
  servo06.attach(10);
  
  // Servo initial positions
  servo1CurrPos=180;
  servo01.write(servo1CurrPos);
  servo2CurrPos=120;
  servo02.write(servo2CurrPos);
  servo3CurrPos=100;
  servo03.write(servo3CurrPos);
  servo4CurrPos=45;
  servo04.write(servo4CurrPos);
  servo5CurrPos=0;
  servo05.write(servo5CurrPos);
  servo6CurrPos=90;
  servo06.write(servo6CurrPos);

  //Bluetooth initiation
  Serial.begin(9600); //Serial communication port 1, with 9600 baud rate
  
}

void loop() 
{
  // put your main code here, to run repeatedly
  if (Serial.available()>0)
  {
    ReadCurrentBuff();
    if (newData == true) {
        Serial.print("This just in ... ");
        for (int i = 1; i<4; i++)
          angle += receivedChars[i];
        servoSelector(receivedChars[0],angle.toInt());
        newData = false;
        angle="";
    }
   
  }

}

//This method activates the chosen servo
void servoSelector(char servoNum,int servoPos)
{
  switch(servoNum)
  {
   case '1':
        moveServoSlow(servo01,servoPos);
        servo1CurrPos=servoPos;  
        break;
   case '2':
        moveServoSlow(servo02,servoPos);
        servo2CurrPos=servoPos;
        break;
   case '3':
        moveServoSlow(servo03,servoPos);
        servo3CurrPos=servoPos;
        break;
   case '4':
        moveServoSlow(servo04,servoPos);
        servo4CurrPos=servoPos;
        break;
   case '5':
        moveServoSlow(servo05,servoPos);
        servo5CurrPos=servoPos;
        break;
   case '6':
        moveServoSlow(servo06,servoPos);
        servo6CurrPos=servoPos;
        break;
  }
}
void moveServoFast(Servo servo,byte newPos)
{
  
}
//This method moves the chosen servo to the new position
void moveServoSlow(Servo servo,byte newPos)
{
  int currentPos = servo.read();
  // If new position is smaller than current position
  if (currentPos > newPos) 
      {
        for ( int j = currentPos; j >= newPos; j--)   // Run servo down to new position
        { 
          servo.write(j);
          delay(delaySpeed);    // defines the speed at which the servo rotates
        }
      }
      // If current position is smaller than new position
   if (currentPos < newPos) 
      {
        for ( int j = currentPos; j <= newPos; j++) // Run servo up to new position
        {   
          servo.write(j);
          delay(delaySpeed);
        }
      }
}

void ReadCurrentBuff() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
 // if (Serial.available() > 0) {
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}
void showNewData() {
    if (newData == true) {
        Serial.print("This just in ... ");
        String angle;
        for (int i = 1; i<4; i++)
          angle += receivedChars[i];
        Serial.println(angle.toInt()+50);
        newData = false;
    }
}

//Servo Definitions
#include <Servo.h>
Servo servo01;
Servo servo02;
Servo servo03;
Servo servo04;
Servo servo05;
Servo servo06;

//Constant Declerations
const byte delaySpeed=200;
const byte numChars = 32;

//Variable Declerations
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
  //       Straight arm status  ==>  <1090><2080><3090><4090><5070><6070>  
  servo01.write(180);
  servo02.write(100);
  servo03.write(70);
  servo04.write(180);
  servo05.write(90);
  servo06.write(100);

  delay(500);
  servo01.detach();
  servo02.detach();
  servo03.detach();
  servo04.detach();
  servo05.detach();
  servo06.detach();

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
        Serial.print("I'm working ere \n");
        for (int i = 1; i<4; i++)
          angle += receivedChars[i];
        servoSelector(receivedChars[0],angle.toInt());
        newData = false;
        angle="";
        Serial.print("I'm Done \n");
    }
   
  }

}

//This method activates the chosen servo
void servoSelector(char servoNum,int servoPos)
{
  switch(servoNum)
  {
   case '1':
        moveServoFast(servo01,servoPos,5);
        break;
   case '2':
        moveServoFast(servo02,servoPos,6);
        break;
   case '3':
        moveServoFast(servo03,servoPos,7);
        break;
   case '4':
        moveServoFast(servo04,servoPos,8);
        break;
   case '5':
        moveServoFast(servo05,servoPos,9);
        break;
   case '6':
        moveServoFast(servo06,servoPos,10);
        break;
  }
}
void moveServoFast(Servo servo,byte newPos, byte pin)
{
  delay(500);
  servo.attach(pin);
  servo.write(newPos);
  delay(1000);
  servo.detach();
  delay(1000);
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
//void showNewData() {
//    if (newData == true) {
//        Serial.print("This just in ... ");
//        String angle;
//        for (int i = 1; i<4; i++)
//          angle += receivedChars[i];
//        Serial.println(angle.toInt()+50);
//        newData = false;
//    }
//}

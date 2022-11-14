/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 28 May 2015
  by Michael C. Miller
  modified 8 Nov 2013
  by Scott Fitzgerald

  http://arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards


void setup() {
  // initialize serial:
  Serial.begin(115200);
  Serial.println("hello world");


  myservo.attach(15, 500, 2500);  // attaches the servo on GIO2 to the servo object
  myservo.attach(14, 500, 2500);  // attaches the servo on GIO2 to the servo object


  Serial.println("PLease input two angles, seperatred with ','.");
}


int incomingByte = 0;
char serialBuffer[64];
int bufferIndex = 0;
int strLength = 0;
int seperatorIndex = 0;

int servoAngle[] = {0,0};
int servoIndex = 0;

void loop() {
  int pos;
  
  
  
  
  while (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.print(char(incomingByte));
    serialBuffer[bufferIndex++] = incomingByte;

    if (incomingByte == '\r')
    {
      Serial.println();
      serialBuffer[bufferIndex] = 0;
      strLength = bufferIndex;
      //Serial.println("got \\r");
      bufferIndex = 0;

      // Find seperarting charecter
      for (int i = 0; i <= strLength; i++)
      {
        seperatorIndex = i;
        if (serialBuffer[i] == ',')
        {
          break;
        }
        
      }
      // abort if no seperator is found.
      if (seperatorIndex >= strLength )
      {
        Serial.println("No ',' found, please input 2 angles.");
        break;
      }
      


      servoAngle[servoIndex] = atoi(serialBuffer);
      Serial.print("Read angle: ");
      Serial.println(servoAngle[servoIndex]);

      if (servoAngle[servoIndex] < 0)
      {
        servoAngle[servoIndex] = servoAngle[servoIndex] * -1;
      }
      if (servoAngle[servoIndex] > 180)
      {
        servoAngle[servoIndex] = servoAngle[servoIndex]%180;
      }
      

      Serial.print("Moving to angle: ");
      Serial.println(servoAngle[servoIndex]);
      myservo.write(servoAngle[servoIndex]);              // tell servo to go to position in variable 'pos'
    }
    


    // look for the next valid integer in the incoming serial stream:
    //int firstAngle = Serial.parseInt();
    

    // look for the newline. That's the end of your sentence:
    if (Serial.read() == '\r') {
      // if (firstAngle < 0)
      // {
      //   firstAngle = firstAngle * -1;
      // }
      // if (firstAngle > 180)
      // {
      //   firstAngle = firstAngle%180;
      // }
      
      // Serial.print("Moving to angle: ");
      // Serial.println(pos);
      // myservo.write(pos);              // tell servo to go to position in variable 'pos'
      
    }
  }

  // Make a sweep with the servo.
  // for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  //   // in steps of 1 degree
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   Serial.print("current angle: ");
  //   Serial.println(pos);
  //   delay(15);                       // waits 15ms for the servo to reach the position
  // }
  // for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   Serial.print("current angle: ");
  //   Serial.println(pos);
  //   delay(15);                       // waits 15ms for the servo to reach the position
  // }
}

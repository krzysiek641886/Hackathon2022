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
Servo myservo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards


void setup() {
  // initialize serial:
  Serial.begin(115200);
  Serial.println("hello world");


  myservo.attach(15, 500, 2500);  // attaches the servo on GIO2 to the servo object
  myservo2.attach(14, 500, 2500);  // attaches the servo on GIO2 to the servo object


  Serial.println("PLease input two angles, seperatred with ','.");
}


int incomingByte = 0;
char serialBuffer[64];
int bufferIndex = 0;
int strLength = 0;
int seperatorIndex[] = {0,0};

int servoAngle[] = {0,0};
int servoIndex = 0;

//Flags
bool recievedString = false;
bool updateServos = false;

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
        seperatorIndex[1] = i+1;
        if (serialBuffer[i] == ',')
        {
          break;
        }
        
      }
      // abort if no seperator is found.
      if (seperatorIndex[1] >= strLength )
      {
        Serial.println("No ',' found, please input 2 angles.");
        break;
      }
      // Serial.print("Seperator index: ");
      // Serial.println(seperatorIndex[1] );
      // Serial.println(serialBuffer+seperatorIndex[1] );


      // DO math to make input into an angle
      
      for (int i = 0; i < 2; i++)
      {
        servoAngle[i] = atoi(serialBuffer+seperatorIndex[i]);
        Serial.print("Read angle "); Serial.print(i); Serial.print(": ");
        Serial.println(servoAngle[i]);

        if (servoAngle[i] > 90)
        {
          servoAngle[i] = 90;
        }
        if (servoAngle[i] < -90)
        {
          servoAngle[i] = -90;
        }
      }
      
      updateServos = true;
    }
    
  }

  if (updateServos)
  {
    updateServos = false;
    Serial.print("Moving to angle: ");
    Serial.println(servoAngle[0]+90);
    myservo.write(servoAngle[0]+90);              // tell servo to go to position in variable 'pos'
    
    Serial.print("Moving to angle: ");
    Serial.println(90-servoAngle[0]);
    myservo2.write(90-servoAngle[0]);              // tell servo to go to position in variable 'pos'

    Serial.println();
  }
  

  
}

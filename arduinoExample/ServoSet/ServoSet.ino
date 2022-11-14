/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 28 May 2015
  by Michael C. Miller
  modified 8 Nov 2013
  by Scott Fitzgerald

  http://arduino.cc/en/Tutorial/Sweep
*/

#include <math.h>
#include <Servo.h>

Servo servo0;  // create servo object to control a servo
Servo servo1;  // create servo object to control a servo
Servo servo2;
Servo servo3;
// twelve servo objects can be created on most boards


void setup() {
  // initialize serial:
  Serial.begin(115200);
  Serial.println("hello world");


  servo0.attach(15, 500, 2500);  // attaches the servo on GIO15 to the servo object
  servo1.attach(14, 500, 2500);  // attaches the servo on GIO14 to the servo object
  servo2.attach(13, 500, 2500);  // attaches the servo on GIO13 to the servo object
  servo3.attach(12, 500, 2500);  // attaches the servo on GIO12 to the servo object


  Serial.println("PLease input two angles, seperatred with ','.");
}


int incomingByte = 0;
char serialBuffer[64];
int bufferIndex = 0;
int strLength = 0;
int seperatorIndex[] = {0,0};

int pitch = 0;
int roll = 0;

int servoAngle[] = {0,0};
int servoIndex = 0;

float temp = 0;

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


    
      
      // get pitch and roll from input.
      pitch = atoi(serialBuffer+seperatorIndex[0]);
      roll = atoi(serialBuffer+seperatorIndex[1]);
      Serial.print("pitch angle: "); Serial.print(pitch); Serial.print("  ");
      Serial.print("roll angle: "); Serial.print(roll);
      Serial.println("");


      // Serial.print("tangent of pitch using (double) rad : ");
      // Serial.println ( tan (double(pitch)/(180.0/3.1415)) ); // returns tangent of x
      // Serial.print("tangent of pitch using deg : ");
      // Serial.println ( tan (pitch) ); // returns tangent of x
      // Serial.print("tangent of pitch using (double) deg : ");
      // Serial.println ( tan (double(pitch)) ); // returns tangent of x
      // Serial.print("130.0/(40.0/180.0) =  ");
      // temp = 130.0/(40.0/180.0);
      // Serial.println ( temp );



      // tan(pitch)*130mm  /  ( 40mm/180deg ) = degServo
      // servoAngle[0] = (tan(pitch)*130.0)/(40.0/180.0);
      // servoAngle[1] = (tan(roll)*130.0)/(40.0/180.0);
      servoAngle[0] = int(  tan(double(pitch)/(180.0/3.1415)) * ((585/2)*1.15) );
      servoAngle[1] = int(  tan(double(roll)/(180.0/3.1415)) * ((585/2)*1.15) );
      
      Serial.print("pitchServo: "); Serial.print(servoAngle[0]); Serial.print("  ");
      Serial.print("rollServo: "); Serial.print(servoAngle[1]);
      Serial.println("");
      
      updateServos = true;
      // servoAngle[0] = 0;
      // servoAngle[1] = 0;
    }
    
  }

  if (updateServos)
  {
    updateServos = false;

    for (int i = 0; i < 2; i++)
    {
      if (servoAngle[i] > 90)
      {
        servoAngle[i] = 90;
      }
      if (servoAngle[i] < -90)
      {
        servoAngle[i] = -90;
      }
    }
    

    Serial.print("Moving to angle: ");
    Serial.println(servoAngle[0]+90);
    servo0.write(servoAngle[0]+90);              // tell servo to go to position in variable 'pos'
    
    Serial.print("Moving to angle: ");
    Serial.println(90-servoAngle[0]);
    servo1.write(90-servoAngle[0]);              // tell servo to go to position in variable 'pos'


    updateServos = false;
    Serial.print("Moving to angle: ");
    Serial.println(servoAngle[1]+90);
    servo2.write(servoAngle[1]+90);              // tell servo to go to position in variable 'pos'
    
    Serial.print("Moving to angle: ");
    Serial.println(90-servoAngle[1]);
    servo3.write(90-servoAngle[1]);              // tell servo to go to position in variable 'pos'

    Serial.println();
  }
  

  
}

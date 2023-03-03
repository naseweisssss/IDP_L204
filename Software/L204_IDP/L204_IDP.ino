#include <Servo.h>
#include "robotDefines.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


String command;   // Not sure what these 2 lines are doing
String device;


Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor_1 = AFMS.getMotor(4);
Adafruit_DCMotor *myMotor_2 = AFMS.getMotor(3);

void setup()
{
  AFMS.begin();
  myMotor_1->setSpeed(iniMotorPower);
  myMotor_2->setSpeed(iniMotorPower);
  Serial.begin(9600);

  

  
  pinMode(OrangeLED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // line follow sensors
  pinMode(lineFollowSensor0, INPUT);
  pinMode(lineFollowSensor1, INPUT);
  pinMode(lineFollowSensor2, INPUT);
  pinMode(lineFollowSensor3, INPUT);


  //startswitch
  pinMode(buttonPin, INPUT);



  //-----------------------------------------
  //May need to remove the button requirement while there is no button during testing
  Serial.println("Line Follower is alive ==> Presss the button to start");


  // Theoretical code for starting loop when everything is started
;
/*buttonPressed = 0;
while (buttonPressed!= 1){
    readSwitch();
    if (Buttonsensor == 1){
      buttonPressed = 1;
      starting_square();
    
    }
    delay(20);
}*/

starting_square();
}

void loop() {
  // Should follow the line exactly as it did previously
  followLine();
  


  // IN CASE THIS STOPS THINGS WORKING I HAVE CHANGED:
    // - MOVED MODE DECISIONS OUT OF ONE SENSOR FUNCTION
    // - MOVED THE FOLLOWLINE CODE TO ANOTHER FUNCTION
    // NOTHING ELSE RELATING TO LINE SENSING SHOULD HAVE BEEN CHANGED


 

   
  
  
}

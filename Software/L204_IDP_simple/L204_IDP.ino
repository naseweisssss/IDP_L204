#include <Servo.h>
#include "robotDefines.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

String command;
String device;

// BT Module
#include <SoftwareSerial.h>
//TODO: Enter the value of the port for serial communication
//---------------------------------------------\\


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
  
  

  

  Serial.println("Line Follower is alive ==> Presss the button to start");

  while (digitalRead(buttonPin))
  {  
  }
  
}

void loop() 
{
  
readLFSsensors();    
switch (mode)
 {
   case STOPPED: 
     motorStop();
     break;

   case NO_LINE:  
     motorStop();
     motorTurn(LEFT, 180);
     previousError = 0;
     break;

   case FOLLOWING_LINE:     
     calculatePID();
     motorPIDcontrol();    
     break;     
 }
}

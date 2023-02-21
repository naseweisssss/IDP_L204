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
  //myMotor_1->setSpeed(iniMotorPower);
  //myMotor_2->setSpeed(iniMotorPower);
  Serial.begin(9600);
  
  
  pinMode(OrangeLED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  // line follow sensors
  pinMode(lineFollowSensor0, INPUT);
  pinMode(lineFollowSensor1, INPUT);
  pinMode(lineFollowSensor2, INPUT);
  pinMode(lineFollowSensor3, INPUT);
  
  

  
  //-----------------------------------------
  //May need to remove the button requirement while there is no button during testing
  Serial.println("Line Follower is alive ==> Presss the button to start");

  while (digitalRead(buttonPin))
  {  
  }
  
}

void loop() 
{
int delay_time = 50; // Delay between each sensor reading 
readLFSsensors();    
switch (mode)
 {
   case STOPPED: 
     motorStop();
     delay(delay_time);
     break;

   case ON_LINE:  
     motorForward();
     delay(delay_time);
     break;

   case LEFT_LINE:     
     motorTurn(RIGHT);
     delay(delay_time);
     break;     
  
   case RIGHT_LINE:     
     motorTurn(LEFT);
     delay(delay_time);
     break;    
    
   case NO_LINE:     
     motorForward();
     delay(delay_time);
     break;    
 }
}

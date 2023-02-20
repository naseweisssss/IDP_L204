#include <Servo.h>
#include "robotDefines.h"

String command;
String device;

// BT Module
#include <SoftwareSerial.h>
//TODO: Enter the value of the port for serial communication
SoftwareSerial BT1(10, 11); // El pin 10 es Rx y el pin 11 es Tx
//10 is rxPin which is used to receive serial data
//---------------------------------------------
void setup() 
{
  
  Serial.begin(9600);
  
  
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  // line follow sensors
  pinMode(lineFollowSensor0, INPUT);
  pinMode(lineFollowSensor1, INPUT);
  pinMode(lineFollowSensor2, INPUT);
  pinMode(lineFollowSensor3, INPUT);
  
  
  // servos
  //TODO: Choose the port for motors (right and left)
  //TODO: Change to motors code
  leftServo.attach(5);
  rightServo.attach(3);
  

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
      ledBlink();
      previousError = error;
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

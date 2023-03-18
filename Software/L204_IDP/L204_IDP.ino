//import the neccessary library

#include <Servo.h>
#include "robotDefines.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"



//iniitalise motor on port 4 and port 3 respectively
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor_1 = AFMS.getMotor(4);
Adafruit_DCMotor *myMotor_2 = AFMS.getMotor(3);
Servo myservo;

void setup()
{
  //set an initial speed to the motor
  AFMS.begin();
  myMotor_1->setSpeed(iniMotorPower);
  myMotor_2->setSpeed(iniMotorPower);
  Serial.begin(9600);
  //attach servo to port 10 
  myservo.attach(10);
 

 //initialise servo ar position 0
  myservo.write(0);


  
  pinMode(OrangeLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(coloursensorpin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // line follow sensors
  pinMode(lineFollowSensor0, INPUT);
  pinMode(lineFollowSensor1, INPUT);
  pinMode(lineFollowSensor2, INPUT);
  pinMode(lineFollowSensor3, INPUT);

 
  Serial.println("Line Follower is alive ==> Presss the button to start");

//robot will wait for button press
//when the button is pressed, starting_square() will be run 
int buttonPressed = 0;
while (buttonPressed!= 1){
    readSwitch();
    if (Buttonsensor == 0){
      buttonPressed = 1;
      delay(1500);
      ledBlink();
      starting_square();
    
    }
    delay(20);
}



}

void loop() {
  
  // Should follow the line exactly as it did previously
  followLine();
  



 

   
  
  
}

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor_1 = AFMS.getMotor(4);
Adafruit_DCMotor *myMotor_2 = AFMS.getMotor(3);

void setup() {
  // put your setup code here, to run once:
  AFMS.begin();
  myMotor_1->setSpeed(150);
  myMotor_2->setSpeed(150);

}

void loop() {
  // put your main code here, to run repeatedly:
myMotor_1->run(FORWARD);
myMotor_2 -> run(BACKWARD);
}

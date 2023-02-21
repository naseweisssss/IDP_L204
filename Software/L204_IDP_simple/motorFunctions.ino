
void motorRun(int spd1, int spd2){
  if (spd1 < 0 ){
     myMotor_1->setSpeed(- spd1);
     myMotor_1-> run(BACKWARD);
  }
    elif (spd1 >= 0 ){
     myMotor_1->setSpeed(spd1);
     myMotor_1-> run(FORWARD);
  }

    if (spd2 < 0 ){
     myMotor_2->setSpeed(- spd2);
     myMotor_2-> run(FORWARD);
  }
    elif (spd2 >= 0 ){
     myMotor_2->setSpeed(spd2);
     myMotor_2-> run(BACKWARD);
  }
  
}

void motorStop()
{
  motorRun(0, 0);
  delay(200);
}

//--------------------------------------------- 
void motorForward()
{
//  leftServo.writeMicroseconds(1500 - power);
//  rightServo.writeMicroseconds(1500 + power*adj);
motorRun(power, power*adj);
}

//---------------------------------------------
void motorBackward()
{
//  leftServo.writeMicroseconds(1500 + power);
//  rightServo.writeMicroseconds(1500 - power);
motorRun(power/2, power/2);
}

//---------------------------------------------
void motorFwTime (unsigned int time)
{
  motorForward();
  delay (time);
  motorStop();
}

//---------------------------------------------
void motorBwTime (unsigned int time)
{
  motorBackward();
  delay (time);
  motorStop();
}

//------------------------------------------------
void motorTurn(int direction, int degrees)
{ if (direction == LEFT){

  motorRun(power - iniMotorPower, power);
}

if (direction == RIGHT){

  motorRun(power, power - iniMotorPower);
}
//  leftServo.writeMicroseconds(1500 - iniMotorPower*direction);
//  rightServo.writeMicroseconds(1500 - iniMotorPower*direction);

//  delay (round(adjTurn*degrees+1));

  delay(20);
  motorStop();
}

//---------------------------------------------------
void motorPIDcontrol()
{
  
  int leftMotorSpeed = power - iniMotorPower - PIDvalue;
  int rightMotorSpeed = power + iniMotorPower*adj - PIDvalue;
  
  // The motor speed should not exceed the max PWM value
   constrain(leftMotorSpeed, -255, 255);
   constrain(rightMotorSpeed, -255, 255);
  
  motorRun(leftMotorSpeed, rightMotorSpeed);
  
//  Serial.print (PIDvalue);
//  Serial.print (" ==> Left, Right:  ");
//  Serial.print (leftMotorSpeed);
//  Serial.print ("   ");
}

//-----------------------------
void drivePolygon(unsigned int time, int sides) // for motor test only
{
    for (int i = 0; i<sides; i++)
    {
        motorFwTime (time);
        motorTurn(RIGHT, 360/sides);
    }

}

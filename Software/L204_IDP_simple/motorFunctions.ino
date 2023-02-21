
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
delay(20);
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
void motorTurn(int direction)
{ if (direction == LEFT){

  motorRun(power - iniMotorPower, power);
}

if (direction == RIGHT){

  motorRun(power, power - iniMotorPower);
}

  delay(20);
}
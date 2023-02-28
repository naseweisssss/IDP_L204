

//-------------------------------------------------------------
/* read line sensors values 

Sensor Array 	Error Value
0 0 0 1 error = 3
0 0 1 1 error = 2
0 0 1 0 error = 1
0 1 1 0 error = 0
0 1 0 0 error = 1
1 1 0 0 error = 2
1 0 0 0 error = 3

New line sensor options:
1 1 0 0 Junction
1 1 1 0 Junction 
0 1 0 0 Pointing right
0 0 0 0 On Line
0 0 1 0 Pointing left
0 1 1 1 Junction
0 0 1 1 Junction
1 1 1 1 Leaving box meeting junction

1 1 1 1        0 Robot found continuous line : STOPPED
0 0 0 0        0 Robot found no line: turn 180o //TODO: Determine something to do

*/



void readLFSsensors() {

// Function for reading the line sensors and storing them in an array
  LFSensor[0] = digitalRead(lineFollowSensor0);
  LFSensor[1] = digitalRead(lineFollowSensor1);
  LFSensor[2] = digitalRead(lineFollowSensor2);
  LFSensor[3] = digitalRead(lineFollowSensor3);


// Where the function below used to be ************************************


// Code for printing out the line sensor readings and the current mode
  for (int i=0; i<4; i++){
    Serial.print(LFSensor[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
//3 of them at junction TODO: Code the 3 1110
// change to junction mode:; which junction at


}


void lineFollowingMode(){
  // Contains the logic for normal line following


    // Old code in case I stop something from working :)
  // if((     LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 ))  {mode = RIGHT_LINE;} // Junction
  // else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 ))  {mode = ON_LINE;} // Junction
  // else if((LFSensor[0]== 0 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 ))  {mode = RIGHT_LINE;}
  // else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 ))  {mode = ON_LINE;}
  //  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 ))  {mode = ON_LINE;}
  // else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 ))  {mode = LEFT_LINE;}
  // else if((LFSensor[0]== 0 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 ))  {mode = ON_LINE;} // Junction
  // else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 ))  {mode = LEFT_LINE;} // Junction
  // else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 ))  {mode = STOPPED;} // Leaving box


// Code for normal line following (not the corners or the junctions)
  if(     (LFSensor[0]== 0 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 ))  {mode = RIGHT_LINE; tight = 0; iniMotorPower = power * steeringSmoothness;}  // Allows for smoother steering as there is less slowing down from the inside wheel
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 ))  {mode = ON_LINE; tight = 0; iniMotorPower = power * steeringSmoothness;}
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 ))  {mode = LEFT_LINE; tight = 0; iniMotorPower = power * steeringSmoothness;}

// Code allowing for tighter turning at the corners --> the only time just a single outside sensor should be on is when the robot doesn't turn enough for a corner
//  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 ))  {mode = RIGHT_LINE; tight = 1; iniMotorPower = power; Serial.println("Tight LEFT turn");}
//  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 1 ))  {mode = LEFT_LINE; tight = 1; iniMotorPower = power; Serial.println("Tight RIGHT turn");}

// Code which detects the presence of a junction  
  //else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 ))  {mode = JUNCTION;}   // Don't think this state is possible
  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 ))  {mode = JUNCTION;} // Junction
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 ))  {mode = JUNCTION;} // Junction
  //else if((LFSensor[0]== 0 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 ))  {mode = JUNCTION;} // Leaving box

// Code for error states --> not currently using as for leaving the squares
//  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 ))  {mode = ERROR;}



  //else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 ))  {mode = STOPPED; error = 0;}
  //else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 ))  {mode = NO_LINE; error = 0;}

}


int colourDetection(){
  // Function that detects the colour of the block depending on the sensors from the Arduino reading
  int colour = 1;

  return colour;
}

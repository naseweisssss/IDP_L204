

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
void readLFSsensors()
{
  LFSensor[0] = digitalRead(lineFollowSensor0); LFSensor[0] = 0;
  LFSensor[1] = digitalRead(lineFollowSensor1);
  LFSensor[2] = digitalRead(lineFollowSensor2);
  LFSensor[3] = digitalRead(lineFollowSensor3); LFSensor[3] = 0;
 
  
  if((     LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 ))  {mode = RIGHT_LINE;} // Junction 1100
  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 ))  {mode = ON_LINE;} // Junction 1110
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 ))  {mode = RIGHT_LINE;} //0100
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 ))  {mode = ON_LINE;} //0000
   else if((LFSensor[0]== 0 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 ))  {mode = ON_LINE;} //0110
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 ))  {mode = LEFT_LINE;} //0010
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 ))  {mode = ON_LINE;} // Junction //0111
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 ))  {mode = LEFT_LINE;} // Junction 0011
  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 ))  {mode = ON_LINE;} // Leaving box 1111

  for (int i=0; i<4; i++){
    Serial.print(LFSensor[i]);
    Serial.print(" ");
  }
  Serial.println(mode);
//3 of them at junction TODO: Code the 3 1110
// change to junction mode:; which junction at

  //else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 ))  {mode = STOPPED; error = 0;}
  //else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 ))  {mode = NO_LINE; error = 0;}
}

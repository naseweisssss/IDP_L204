

//-------------------------------------------------------------
/* read line sensors values 


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
void readSwitch(){
  Buttonsensor = digitalRead(buttonPin);
}


void readLFSsensors() {

// Function for reading the line sensors and storing them in an array
  LFSensor[0] = digitalRead(lineFollowSensor0);
  LFSensor[1] = digitalRead(lineFollowSensor1);
  LFSensor[2] = digitalRead(lineFollowSensor2);
  LFSensor[3] = digitalRead(lineFollowSensor3);




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
// Code for normal line following (not the corners or the junctions)
  if(    (LFSensor[1]== 1 )&&(LFSensor[2]== 0 ))  {mode = RIGHT_LINE; tight = 0; iniMotorPower = power * steeringSmoothness;}  // Allows for smoother steering as there is less slowing down from the inside wheel
  else if((LFSensor[1]== 0 )&&(LFSensor[2]== 0 ))  {mode = ON_LINE; tight = 0; iniMotorPower = power * steeringSmoothness;}
  else if((LFSensor[1]== 0 )&&(LFSensor[2]== 1 ))  {mode = LEFT_LINE; tight = 0; iniMotorPower = power * steeringSmoothness;}


 
  if (outside_junction == 0){
  if((     LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 ))  {mode = JUNCTION;}
  else if((     LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 ))  {mode = JUNCTION;}// Junction
  else if((LFSensor[0]== 1 )&&(LFSensor[3]== 1 ))  {mode = ON_LINE;}
  }
  else if (outside_junction == 1){
    if((     LFSensor[0]== 1 )&&(LFSensor[3]== 0 ))  {mode = JUNCTION;}
    else if((     LFSensor[0]== 0 )&&(LFSensor[3]== 1 ))  {mode = JUNCTION;}// Junction
    
  }
  
}


int colourDetection(){
  // Function that detects the colour of the block depending on the sensors from the Arduino reading
  delay(2000);
int colour1 = digitalRead(coloursensorpin);
  Serial.println(colour1);

  if (colour1 == 0){
    digitalWrite(GreenLED, HIGH);
    motorStop();
    delay(5000);
    digitalWrite(GreenLED, LOW);
    ledBlink();
    return BLUE;
    }

   else if(colour1 == 1){

  digitalWrite(RedLED, HIGH);
  motorStop();
  delay(5000);
  digitalWrite(RedLED, LOW);
  ledBlink();
  return BROWN;


   } 
  
  }

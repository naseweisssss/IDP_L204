void ledBlink(void)
{
   for (int i = 0; i<4; i++)
   { 
      digitalWrite (OrangeLED, HIGH);
      delay (1000);
      digitalWrite (OrangeLED, LOW);
      delay (1000);
   } 
}

void followLine(void){
   // Function to make the robot follow the line (what used to be in the loop function)

  readLFSsensors(); // Reads the sensor
  lineFollowingMode();  // Gets the correct mode depending on the output of the line sensors
  
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

    case JUNCTION:
      motorForward();           // Needs to be changed when we want to actually stop at a junction
      delay(delay_time);
      break;
}


// TODO - make all the LED commands work
void mark(void){
  // Keeps track of the current position of the robot

}

void setDestination(void){
   // Function for setting the nect destination for the robot to head to depending on the current aim of the robot
   // Responsible for turning out of junctions?

   switch(pos){
      case BLOCK1: case BLOCK2:
         colour = colourDetection();
         if (colour == 1){
            target = 5;
         }
         else if (colour == 2){
            target = 2;
         }
         break;
      
      case RED_BOX:
         target = 3;    // Should turn right and go over the ramp to the closet location
         dir = RIGHT;
         // Or if at time limit go back to END
         break;

      case GREEN_BOX:
         target = 4;    // Should turn left and go out of the tunnel
         dir = LEFT;
         // Or if at time limit go back to END
         break;
   }
}

void turn90degrees(int direction){
   // Function for turning in a specific direction until the robot senses it is back on the line
   int onLine = 0;   // For keeping track of when the turn is completed

   while (!onLine){
      readLFSensors();
      if (direction == RIGHT){
         if (LFSensor[1] == 1){
            onLine = 1;
         }
         motorTurn(RIGHT);       // Need to test that this function is the right way around MIGHT NEED TO CHANGE
      }
      else if (direction == LEFT){
         if (LFSensor[2] == 1){
            onLine = 1;
         }
         motorTurn(LEFT);
      }
      delay(50);     // Might need to adjust so doesn't miss the line
   }
}


void starting_square(void){
   // function to hardcode leaving the starting square
   int first_line = 0;  // Tracks when robot finds the edge of the square
   int main_line = 0;   // Tracks when robot finds the main line

   while (!first_line){
      readLFSsensors();
      if ((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 )){
         first_line = 1;   // Robot has reached the first line at the edge of the square
         motorForward();   // Drive over the line
         delay(500);
      }
      motorForward();
      delay(100);          //Delay in looking for the line
   }

   while (!main_line){
      readLFSsensors();
      if ((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 )){
         main_line = 1;   // Robot has reached the main line at the junction
         pos = START_END_BOX;          // Set the current position of the robot to position 1

         motorStop();
         delay(1000):

         turn90degrees(RIGHT);    // Turn right towards the ramp to go and fetch a block --> this needs to be tested because not currently working
      }
      followLine();  // Just run the same line following program
   }

}

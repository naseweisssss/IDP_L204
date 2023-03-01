void ledBlink(void)
{
     if (millis() - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = millis();   

    // if the LED is off turn it on and vice-versa:
    if (OrangeLEDState == LOW)
      OrangeLEDState = HIGH;
    else
      OrangeLEDState = LOW;
      
    // set the LED with the ledState of the variable:
    //digitalWrite(OrangeLED, ledState);
  }
}

void followLine(void){
   // Function to make the robot follow the line (what used to be in the loop function)
  
  readLFSsensors(); // Reads the sensor
  lineFollowingMode();  // Gets the correct mode depending on the output of the line sensors
  //ledBlink();
   power = 235;

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
       if (!tight){
         motorTurn(RIGHT);
         delay(delay_time);
      }
      else if (tight){
        Serial.println("Started tight RIGHT turn");
        int  onLine = 0;
        while (!onLine){
          readLFSsensors();
          if (LFSensor[2] == 1){
            onLine = 1;
            tight = 0;
          }
          else if (LFSensor[2] == 0){
            motorTurn(RIGHT);
          }
          delay(100);
        }
      }
       break;

     case RIGHT_LINE:
      if (!tight){
         motorTurn(LEFT);
         delay(delay_time);
      }
      else if (tight){
        Serial.println("Started tight LEFT turn");
        int  onLine = 0;
        while (!onLine){
          readLFSsensors();
          if (LFSensor[1] == 1){
            onLine = 1;
            tight = 0;
          }
          else if (LFSensor[1] == 0){
            motorTurn(LEFT);
          }
          delay(100);
        }
      }
       break;

     case JUNCTION:
       mark();
       break;

     // case ERROR:
     //   motorForward();
     //   delay(delay_time);
    //   break;
   
}
}

void block_junction_case(void){
   if (pos == target){
   // Robot is at the desired location so do something

   motorStop();
   delay(500);
   motorForward();
   delay(1200);
   int new_turn = -1 * dir;   // Always need to turn opposite way into junction as out of last junction
   dir = new_turn;
   int onLine = 0;
   backMotorTurn(new_turn); // robot turning into the junction
   delay(500);
   while(!onLine){
    readLFSsensors();
    if ((dir == LEFT) && (LFSensor[2] == 1)){
      onLine = 1;
      motorStop();
      delay(1000);
    }
    else if ((new_turn == RIGHT) && (LFSensor[1] == 1))
    {
      onLine = 1;
      motorStop();
      delay(1000);
    }
    backMotorTurn(new_turn);  // not sure what is this for
    delay(50);

   //  assuming it has aligned with the straight line in the junction
   // picking_up_block();
   // setDestination();
   turn180degrees();
   motorTightTurn(dir);
   delay(1200); 

   }   

  }
 else if (pos != target){
   // Not sure if this is the best way of avoid a junction being registered twice as hardcoding
   motorForward();
   delay(1000);
  }
}

void color_junction_case(void){
   if (pos == target){
   // Robot is at the desired location so do something

   motorStop();
   delay(500);
   motorForward();
   delay(1200);
   int new_turn = -1 * dir;   // Always need to turn opposite way into junction as out of last junction
   dir = new_turn;
   int onLine = 0;
   backMotorTurn(new_turn); // robot turning into the junction
   delay(500);
   while(!onLine){
    readLFSsensors();
    if ((dir == LEFT) && (LFSensor[2] == 1)){
      onLine = 1;
      motorStop();
      delay(1000);
    }
    else if ((new_turn == RIGHT) && (LFSensor[1] == 1))
    {
      onLine = 1;
      motorStop();
      delay(1000);
    }
    backMotorTurn(new_turn);  // not sure what is this for
    delay(50);

   //  assuming it has aligned with the straight line in the junction
   // drop_off_block();
   // setDestination();
   turn180degrees();   //assume this works
   starting_square();

   }   

  }
 else if (pos != target){
   // Not sure if this is the best way of avoid a junction being registered twice as hardcoding
   motorForward();
   delay(1000);
  }
}

// TODO - make all the LED commands work
void mark(void){
  // Keeps track of the current position of the robot
  int temp = pos;
  if (dir == RIGHT){
   // Last turned right at a junction so is moving anti-clockwise
   
   // Slightly janky code to make sure no errors
   
   temp++;
  }

  else if (dir == LEFT){
   // Last turned left at a junction so is moving clockwise
   
   // Slightly janky code to make sure no errors
   temp--;
  }

  temp = temp % 4;

  if (temp == 0){pos = 0;}
  else {pos = temp;}

// switch case for positions

      switch (pos)
      {
      case 0:
      Serial.println("Running case Position 0");
      /*Action: Finishing Algo, not sure what would need to go into starting box during the process*/
         if (target == 0){
               finishing_square();
         }

         else if (target != 0){
         motorForward();
         delay(1000);
         }
         break;

      case 1:
         Serial.println("Running case Position 1");
         /* code */
         /*Action: Turn into green box if target is 1 (i.e. only happens when holding a block) -> turn 180 degrees -> starting_square()*/
         color_junction_case();
         
         break;
         
      case 2:
      // case 2 and case 3 same since set destination will set a target 
         Serial.println("Running case Position 2");
         block_junction_case();

         break;

      case 3:
         Serial.println("Running case Position 3");
         block_junction_case();
         break;

      case 4:
         /* code */
         /*Action: Turn into red box if target is 4 (i.e. only happens when holding a block) -> turn 180 degrees -> starting_square()*/
         color_junction_case();
         break;


      default:
         Serial.println("No position case registered"); 
         break;
      }

  
}

void setDestination(void){
   // Function for setting the nect destination for the robot to head to depending on the current aim of the robot
   // Responsible for turning out of junctions?

   switch(pos){
    
      case BLOCK1: case BLOCK2:
      
         colour = colourDetection();
         if (colour == 1){
            target = 4;
         }
         else if (colour == 2){
            target = 1;
         }
         break;
      
      case RED_BOX:
         target = 2;    // Should turn right and go over the ramp to the closest location
         dir = RIGHT;
         // Or if at time limit go back to END
         break;

      case GREEN_BOX:
         target = 3;    // Should turn left and go out of the tunnel
         dir = LEFT;
         // Or if at time limit go back to END
         break;
   }
}

void turn90degrees(int direction){
  Serial.println("running turn90degrees");
   // Function for turning in a specific direction until the robot senses it is back on the line
   int onLine = 0;   // For keeping track of when the turn is completed

   while (!onLine){
      readLFSsensors();
      if (direction == RIGHT){
         if (LFSensor[0] == 1){
            onLine = 1;
 
         }
//         iniMotorPower = power;
         motorTightTurn(RIGHT);       // Need to test that this function is the right way around MIGHT NEED TO CHANGE
      }
      else if (direction == LEFT){
         if (LFSensor[3] == 1){
            onLine = 1;
          
         }
//         iniMotorPower = power;
         motorTightTurn(LEFT);
      }
      delay(50);     // Might need to adjust so doesn't miss the line
   }
}

void turn180degrees(){
   // Hardcoded function for turning around when in the squares
   motorTightTurn(LEFT);
   delay(2000);       // Needs to be tuned to get accurate turning around
   motorStop();
}

void starting_square(void){
  Serial.println ("running starting_square");
   // function to hardcode leaving the starting square
   int first_line = 0;  // Tracks when robot finds the edge of the square
   int main_line = 0;   // Tracks when robot finds the main line
   power = 160;

   while (!first_line){
      readLFSsensors();
      if ((LFSensor[1]== 1 )||(LFSensor[2]== 1 )||(LFSensor[0]== 1 )||(LFSensor[3]== 1 )){
        Serial.println("in line 1");
         first_line = 1;   // Robot has reached the first line at the edge of the square
         motorForward();   // Drive over the line
         delay(500);
      }
      motorForward();
      delay(50);          //Delay in looking for the line
   }

   while (!main_line){
      readLFSsensors();
      if ((LFSensor[0]== 1 )||(LFSensor[3]== 1 )){
                Serial.println("in main line");
         main_line = 1;   // Robot has reached the main line at the junction
         pos = START_END_BOX;          // Set the current position of the robot to position 0

         motorStop();
         delay(500);
         dir = RIGHT;
//         turn90degrees(RIGHT);    // Turn right towards the ramp to go and fetch a block 
         motorTightTurn(dir);
         delay(1200);      
      }
      
      followLine();  // Just run the same line following program
      delay (50);
   }

}

void finishing_square(void){
   // Code for getting back into the END square from the junction
         int  new_turn = -1 * dir;  //i.e. come from left, turn right etc
         dir = new_turn;
         motorTightTurn(new_turn);
         motorForward();
         delay(500);
         motorStop(); //motor stop at finishing square
}

void picking_up_block(void){
   // Code for picking up the block
}

void drop_off_block(void){
   // Code for dropping off the block
}

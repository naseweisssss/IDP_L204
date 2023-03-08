void ledBlink(void)
{
   

    // if the LED is off turn it on and vice-versa:
    if (OrangeLEDState == LOW)
      OrangeLEDState = HIGH;
    else if (OrangeLEDState == HIGH){
      OrangeLEDState = LOW;}
      
    // set the LED with the ledState of the variable:
    digitalWrite(OrangeLED, OrangeLEDState);
  
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
     //motorStop();
     
     //delay(1000);
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
   delay(10);
   motorForward();
   delay(1250);
      myservo.write(140);
   
   int new_turn = -1 * dir;   // Always need to turn opposite way into junction as out of last junction
   //dir = new_turn;
   int onLine = 0;
   backMotorTurn(new_turn); // robot turning into the junction
   delay(1000);
   while(!onLine){
    readLFSsensors();
    if ((new_turn == LEFT) && (LFSensor[1] == 1)){
      onLine = 1;
      motorStop();
      delay(10);
    }
    else if ((new_turn == RIGHT) && (LFSensor[2] == 1))
    {
      onLine = 1;
      motorStop();
      delay(10);
    }
    else{
      Serial.println("finding junction  lines");    
      backMotorTurn(new_turn);  
    delay(50);
    }

   
    

   }  
   //  assuming it has aligned with the straight line in the junction
    
   
   
   Serial.println("line found");

   previousMillis = millis();
   while ((millis() - previousMillis) < 850){
    followLine();
    delay(50);
   }
   motorStop();
   delay(100);

   picking_up_block();
   // Something is happening to pick up the block and sense the colour
   setDestination();
   
   
   turn180degrees(RIGHT);
   //delay(1000);
   dir = RIGHT;
   

  

  }
 else if (pos != target){
    Serial.println("position not in target");
   // Not sure if this is the best way of avoid a junction being registered twice as hardcoding
   motorForward();
   delay(800);
  }
}

void color_junction_case(void){
if (pos == target){
   // Robot is at the desired location so do something

   motorStop();
   delay(500);
   motorForward();
   if (pos == 4){
    delay(800);
   }
   else if (pos == 1){
    delay(1300);
   }
   
   // Don't need to change the direction of turning as still set to right
   //int new_turn = -1 * dir;   // Always need to turn opposite way into junction as out of last junction
   //dir = new_turn;
   int onLine = 0;
   backMotorTurn(dir); // robot turning into the junction
   delay(1000);
   while(!onLine){
    readLFSsensors();
    if ((dir == LEFT) && (LFSensor[1] == 1)){
      onLine = 1;
      motorStop();
      delay(1000);
    }
    else if ((dir == RIGHT) && (LFSensor[2] == 1))
    {
      onLine = 1;
      motorStop();
      delay(1000);
    }
    else{
      Serial.println("finding junction  lines");    
      backMotorTurn(dir);  
    delay(20);
    }

   
    

   }  
   //  assuming it has aligned with the straight line in the junction
   drop_off_block();
   iteration ++;
   Serial.print("The iteration number is ");
   Serial.println(iteration);
   
   
   Serial.println("line found");

   previousMillis = millis();
   while ((millis() - previousMillis) < 700){
    followLine();
    delay(50);
   }
   motorStop();
   delay(50);
   motorForward();
   delay(500);
   motorStop();
   delay(1000);   // Dropping off the block
   motorBackward();
   delay(800);
   


  // Could potentially change this to a straight delay function and make it shorter than the previous part before turning and cutting the corner

   motorStop();
   setDestination();
   
   if (pos == GREEN_BOX){
    if (iteration == TOTAL_ITER){
      dir = RIGHT;
      target = 0;
      Serial.println("At iteration number");
    } else {
    dir = LEFT;
    Serial.println("Not at iteration number");
    }
   }
   else if (pos == RED_BOX){
    if (iteration == TOTAL_ITER){
      dir = LEFT;
      target = 0;
      Serial.println("At iteration number");
    } else {
    dir = RIGHT;
    Serial.println("Not at iteration number");
    }
   }
   motorTightTurn(-dir);
   delay(800);
   turn180degrees(-dir);
   //delay(500);
   
   if (pos == RED_BOX){
     
    
       previousMillis = millis();
       int ramp = 0;
   while (!ramp){
    if ((millis() - previousMillis) < 5800){
      Serial.println("Still following line");
      followLine();
    }
    else{
      Serial.println("reached 5.5s");
      ramp = 1;
    }
    }
    Serial.println("motor on ramp");
    motorTightTurn(RIGHT);
    delay(200);
    motorForward();
    delay(200);
    int onLine = 0;
     while(!onLine){
      readLFSsensors();


      if ((LFSensor[2] == 1)){
        onLine = 1;
        motorTightTurn(LEFT); 
        delay(20);
        motorStop();
        delay(20);
      }
          else{
    motorTightTurn(LEFT);  
    delay(20);
    }
    
   }
   }

  

  }
 else if (pos != target){
    Serial.println("position not in target");
   // Not sure if this is the best way of avoid a junction being registered twice as hardcoding
   motorForward();
   delay(800);
  }
}

// TODO - make all the LED commands work
void mark(void){
  // Keeps track of the current position of the robot
  //int temp = pos;
  if (dir == RIGHT){
   // Last turned right at a junction so is moving anti-clockwise
   
   // Slightly janky code to make sure no errors
   
   //temp++;
   pos++;
  }

  else if (dir == LEFT){
   // Last turned left at a junction so is moving clockwise
   
   // Slightly janky code to make sure no errors
   //temp--;
   pos--;
  }

  //temp = temp % 5;
  //pos = temp;
  pos = pos % 5;

  if (pos == 1 && dir == RIGHT && target != 1){
    delay(800);
   
    
       previousMillis = millis();
       int ramp = 0;
   while (!ramp){
    if ((millis() - previousMillis) < 5800){
      Serial.println("Still following line");
      followLine();
    }
    else{
      Serial.println("reached 5.5s");
      ramp = 1;
    }
    }
    Serial.println("motor on ramp");
    motorTightTurn(RIGHT);
    delay(400);
    motorForward();
    delay(50);
    int onLine = 0;
     while(!onLine){
      readLFSsensors();


      if ((LFSensor[2] == 1)){
        onLine = 1;
        motorTightTurn(LEFT); 
        delay(20);
        motorStop();
        delay(200);
      }
          else{
    motorTightTurn(LEFT);  
    delay(20);
    }
    
   }
    
  }
  

  if (pos == 4 ){
    motorTightTurn(RIGHT);
    delay(200);
    motorForward();
    delay(200);
    turn180degrees(LEFT);
    motorTightTurn(LEFT);
    delay(100);
    
  }
   if ((pos == 3) && (dir == RIGHT)){
    motorTightTurn(LEFT);
    delay(300);
    motorForward();
    delay(200);
    int onLine = 0;
     while(!onLine){
      readLFSsensors();


      if ((LFSensor[1] == 1)){
        onLine = 1;
        motorTightTurn(dir); 
        delay(20);
        motorStop();
        delay(20);
      }
          else{
    motorTightTurn(dir);  
    delay(20);
    } 
}
   
   }
   if ((pos == 0) && (dir == RIGHT)){
    motorTightTurn(RIGHT);
    delay(300);
    motorForward();
    delay(400);
    int onLine = 0;
     while(!onLine){
      readLFSsensors();


      if ((LFSensor[2] == 1)){
        onLine = 1;
        motorTightTurn(LEFT); 
        delay(20);
        motorStop();
        delay(20);
      }
          else{
    motorTightTurn(LEFT);  
    delay(20);
    } 
}
   
   }

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
         delay(800);
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
    
      case BLOCK1: 
      //case BLOCK2:
      
         colour = colourDetection();
         if (colour == 1){
          Serial.println("Target set to 4");
            target = 4;
         }
         else if (colour == 2){
          Serial.println("Target set to 1");
            target = 1;
         }
         dir = LEFT;
         break;

      case BLOCK2:
         colour = colourDetection();
         if (colour == 1){
          Serial.println("Target set to 4");
            target = 4;
         }
         else if (colour == 2){
          Serial.println("Target set to 1");
            target = 1;
         }
         dir = LEFT;
         break;

      case RED_BOX:
        if (iteration == TOTAL_ITER){
          target = 0;}
        target = 2;    // Should turn right and go over the ramp to the closest location
        dir = RIGHT;
        // Or if at time limit go back to END
        break;

      case GREEN_BOX:
         if (iteration == TOTAL_ITER){
             target = 0;}
         
         
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

void turn180degrees(int direction){
   // Hardcoded function for turning around when in the squares
   
   motorTightTurn(direction);
   delay(300);
   
   int onLine = 0;
   while(!onLine){
    readLFSsensors();
    if ((LFSensor[2] == 1)|| (LFSensor[1]==1))
    {
      onLine = 1;
      motorTightTurn(direction);  
      delay(60);
      motorStop();
      delay(10);
    }
    else{
    motorTightTurn(direction);  
    delay(20);
    }} 


/*    while(!onLine){
      readLFSsensors();
      if ((LFSensor[2] == 1) && (direction == LEFT)){
        onLine = 1;
            motorTightTurn(direction);  
    delay(20);
        motorStop();
        delay(20);
      }

      else if ((LFSensor[1] == 1) && (direction == RIGHT)){
        onLine = 1;
            motorTightTurn(direction);  
    delay(20);
        motorStop();
        delay(20);
      }
          else{
    motorTightTurn(direction);  
    delay(20);
    }
}*/}

void starting_square(void){
  Serial.println ("running starting_square");
   // function to hardcode leaving the starting square
   int first_line = 0;  // Tracks when robot finds the edge of the square
   int main_line = 0;   // Tracks when robot finds the main line
   //power = 160;
   int line_following = 0;
   while (!first_line){
      readLFSsensors();
      if ((LFSensor[1]== 1 )||(LFSensor[2]== 1 )){
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
         delay(50);
         dir = RIGHT;
//         turn90degrees(RIGHT);    // Turn right towards the ramp to go and fetch a block 
         motorTightTurn(dir);
         delay(1400);      // used to be 1600 when the power was 100
      }
      
      followLine();  // Just run the same line following program
      delay (50);
   }



}

void finishing_square(void){
   // Code for getting back into the END square from the junction
   motorStop();
   delay(1000);
    motorForward();
    delay(1250);
    //int new_turn = -1 * dir;   // Always need to turn opposite way into junction as out of last junction
    //dir = new_turn;
    int onLine = 0;
    backMotorTurn(dir); // robot turning into the junction
    delay(1000);
    while(!onLine){
      readLFSsensors();
      if ((dir == LEFT) && (LFSensor[1] == 1)){
        onLine = 1;
        motorStop();
        delay(1000);
      }
      else if ((dir == RIGHT) && (LFSensor[2] == 1))
      {
        onLine = 1;
        motorStop();
        delay(1000);
      }
      else{
        Serial.println("finding junction  lines");    
        backMotorTurn(dir);  
      delay(50);
      }
   }  

   int front_line = 0;
   while (!front_line){
    readLFSsensors();
    if ((LFSensor[0] == 1) || (LFSensor[3] == 1)){
      front_line = 1;
      delay(100);
    }
    followLine();
   }

   motorForward();
   delay(910);
   motorStop();
   Serial.println("The robot should have returned to the starting square");
   ledBlink();
   while (1){
    // Create an infinite loop to stop the robot moving
    delay(5000);
    Serial.println("In an infinite loop");
   }

}

void picking_up_block(void){
ledBlink();
myservo.write(0);

ledBlink();
}

void drop_off_block(void){
   // Code for dropping off the block
   ledBlink();
myservo.write(140);

   ledBlink();
}

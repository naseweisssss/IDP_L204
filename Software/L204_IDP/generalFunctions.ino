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
//modes are switched according to different line sensor reading (as shown in sensorFunctions.ino)
//tight variable is used when an extreme cases is encountered (when the robot has steered away too much from the line), it will trigger the robot to stop one wheel and turn the other one until it finds a line
   
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
//if a junction is encountered, mark() function will be called
     case JUNCTION:
       mark();
       break;

   
}
}
// this function will be called when the robot is at the block-collecting junction
void block_junction_case(void){
   if (pos == target){
   // Robot is at the desired location so do something

   motorStop();
   delay(10);
   motorForward();
   delay(1250);
      myservo.write(140);
   
   int new_turn = -1 * dir;   // Always need to turn opposite way into junction as out of last junction
   int onLine = 0;
   backMotorTurn(new_turn); // robot turning into the junction
   delay(1000);
   //robot will stop turning once it find a line
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
   // after the line is found, robot will follow the line for 850 ms to make sure it aligns with the straight line
    Serial.println("line found");
    
   previousMillis = millis();
   while ((millis() - previousMillis) < 850){
    followLine();
    delay(50);
   }
   motorStop();
   delay(100);
      
   picking_up_block();
   //desitionation is set according to the colour of the block
   setDestination();

  

  }
 else if (pos != target){
    Serial.println("position not in target");
   // if the current position is not the target destination, ignore the junction and go forward
   motorForward();
   delay(800);
  }
}
// this function is called when it is at the block-dropping junction
void color_junction_case(void){
if (pos == target){
   //code for robot to turn into the junction
   motorStop();
   delay(500);
   motorForward();
   int onLine = 0;
   backMotorTurn(dir); // robot turning into the junction
   delay(1000);
   //same logic for robot to continue turning until it finds a line
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
   
   drop_off_block();
   //iteration number increased
   iteration ++;
   Serial.print("The iteration number is ");
   Serial.println(iteration);

   motorStop();
   //destination will be set to the nearest block-picking junction
   setDestination();
   
   if (pos == GREEN_BOX){
     //check for the robot if it has reached the iteration limit (the "time" limit that we have set in to go back to the orignal square)
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
  

  }
 else if (pos != target){
    Serial.println("position not in target");
   //ignore the junction
   motorForward();
   delay(800);
  }
}

void mark(void){
  // Keeps track of the current position of the robot
  if (dir == RIGHT){
   // Last turned right at a junction so is moving anti-clockwise
   pos++;
  }

  else if (dir == LEFT){
   // Last turned left at a junction so is moving clockwise
   pos--;
  }
  pos = pos % 5;

// switch case for positions

      switch (pos)
      {
      case 0:
      Serial.println("Running case Position 0");
         if (target == 0){
            //run finishing_square() when the robot re-arrive at original square
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

   switch(pos){
    
      case BLOCK1: 
      
         colour = colourDetection();
         if (colour == 1){
          Serial.println("Target set to 4");
            target = 4;
         }
         else if (colour == 2){
          Serial.println("Target set to 1");
            target = 1;
         }
         dir = RIGHT;
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
         dir = RIGHT;
         break;

      case RED_BOX:
        if (iteration == TOTAL_ITER){
          target = 0;}
        target = 2;    // Should turn right and go over the ramp to the closest location
        dir = RIGHT;

        break;

      case GREEN_BOX:
         if (iteration == TOTAL_ITER){
             target = 0;}
         
         
         target = 3;    // Should turn left and go out of the tunnel
         dir = LEFT;

         break;
   }
}


void turn180degrees(int direction){
   // Hardcoded function for turning around when in the squares
   
   motorTightTurn(direction);
   delay(300);
   
   int onLine = 0;
   while(!onLine){
    readLFSsensors();
    if ((LFSensor[2] == 1) || (LFSensor[1]==1))
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
}

void starting_square(void){
  Serial.println ("running starting_square");
   // function to  leaving the starting square
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
    delay(900);
    if (dir == LEFT){
      delay(400);
    }
    int onLine = 0;
    backMotorTurn(dir); // robot turning into the junction
    delay(1000);
   //continue turning until found a line
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
   delay(950);
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
//code for picking up the block
 ledBlink();
myservo.write(0);


}

void drop_off_block(void){
   // Code for dropping off the block
   ledBlink();
myservo.write(140);

   ledBlink();
}

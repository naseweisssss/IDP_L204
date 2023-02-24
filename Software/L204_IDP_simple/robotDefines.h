int mode = 0;
int pos = 0;// 1 - 5 depending on location
int prev_pos = 0;
int target = 3; // Where the robot is trying to go

# define STOPPED 0
# define ON_LINE 1
# define LEFT_LINE 2        // Include if the outside sensors measure a junction
# define RIGHT_LINE 3
# define JUNCTION 4
# define ERROR 5


const int power = 100;     
const float steeringSmoothness = 0.5;
int iniMotorPower = power * steeringSmoothness; // This function is later overwritten relative to iniMotorPower
const float adj = 1;          // In case one motor drives at different speed to the other so the robot will drive in a straight line
// float adjTurn = 8;

const int OrangeLED = 13;
const int RedLED = 12;              // May need to change the pins
const int GreenLED = 11;
const int buttonPin = 9;

// LFSensor more to the Left is "0"
const int lineFollowSensor0 = 5; 
const int lineFollowSensor1 = 6; 
const int lineFollowSensor2 = 7; 
const int lineFollowSensor3 = 8;


int LFSensor[4]={0, 0, 0, 0};

#define RIGHT 1
#define LEFT -1

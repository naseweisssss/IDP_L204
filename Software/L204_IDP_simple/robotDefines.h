int mode = 0;

// Stores the navigation constants
int pos = 0;// 1 - 5 depending on location
int target = 0; // Where the robot is trying to go
int dir = 0;    // For storing direction turns when get to junctions
# define START_END_BOX 1
# define RED_BOX 2
# define BLOCK1 3
# define BLOCK2 4
# define GREEN_BOX 5
int tight = 0;

// Defines the update frequency of the robot
int delay_time = 50; // Delay between each sensor reading


// Defining the constants for the colour sensing#
int colour; 
# define BLUE 1
# define BROWN 2


// Defining the line sensing modes
# define STOPPED 0
# define ON_LINE 1
# define LEFT_LINE 2        // Include if the outside sensors measure a junction
# define RIGHT_LINE 3
# define JUNCTION 4
//# define ERROR 5


// Defining constants for robot speed and steering smoothness/reactivity
const int power = 160;     
const float steeringSmoothness = 0.7;
int iniMotorPower = power * steeringSmoothness; // This function is later overwritten relative to power
const float adj = 1;          // In case one motor drives at different speed to the other so the robot will drive in a straight line
const int spinSpeed = 100;          // Controls how case spins 180 in boxes

// Defining the pins for LED output
const int OrangeLED = 13;
const int RedLED = 12;              // May need to change the pins
const int GreenLED = 11;
const int buttonPin = 9;

// Defining the pins for the line sensors
// LFSensor more to the Left is "0"
const int lineFollowSensor0 = 7; 
const int lineFollowSensor1 = 6; 
const int lineFollowSensor2 = 5; 
const int lineFollowSensor3 = 4;
int LFSensor[4]={0, 0, 0, 0};       // Array for storing the line sensor readings in

// Defining directions
#define RIGHT 1
#define LEFT -1

void readLFSsensors();
void lineFollowingMode();
void motorStop();
void motorForward();
void motorTurn(int direction);
void motorTightTurn(int direction);
void motorBackward();
void motorRun(int spd1, int spd2);
void mark();
void setDestination();
void turn90degrees(int direction);
void turn180degrees();
void starting_square();
void finishing_square();
void picking_up_block();
void drop_off_block();

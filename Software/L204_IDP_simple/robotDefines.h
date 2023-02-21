int mode = 0;

# define STOPPED 0
# define ON_LINE 1
# define LEFT_LINE 2        // Include if the outside sensors measure a junction
# define RIGHT_LINE 3
# define NO_LINE 4

const int power = 255;
const int iniMotorPower = 100;
const int adj = 1;
float adjTurn = 8;

const int OrangeLED = 13;
const int RedLED = 12;              // May need to change the pins
const int GreenLED = 11;
const int buttonPin = 9;

// LFSensor more to the Left is "0"
const int lineFollowSensor0 = 12; 
const int lineFollowSensor1 = 18; 
const int lineFollowSensor2 = 17; 
const int lineFollowSensor3 = 16;


int LFSensor[4]={0, 0, 0, 0};

#define RIGHT 1
#define LEFT -1
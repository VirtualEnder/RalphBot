int bjtPin =  2;    // Headlights
int ledPin =  3;    // LED Status Light

// Motors
int motor_left[] = {5, 4};
int motor_right[] = {7, 6};

// WiFly
#define WIFLYTX 8
#define WIFLYRX 9

#define panPin 11            // Camera Pan servo pin

#define armPin 12            // Arm Tilt servo pin
#define clawPin 13           // Claw servo pin

#define rangeActivePin A1    // Range finder active pin
#define rangePin 0           // Range finder analog pin

int analogPin = 3;           // switch circuit input connected to analog pin 3
long buttonLastChecked = 0;  // variable to limit the button getting checked every cycle


/*#################################################   
#              Camera Pan/Tilt                    #
#################################################*/

int camYPosition = tiltCenter;
int camXPosition = panCenter;
int clawPosition = clawCenter;
String camMode = "relative";

bool panTiltSet = true; 
bool runSet = true; 
bool pressed = false;
String runDir = "";

Servo panServo;
Servo tiltServo;
Servo clawServo;

/*#################################################   
#                Motor Functions                  #
#################################################*/

void motor_stop(){
digitalWrite(motor_left[0], LOW);
digitalWrite(motor_left[1], LOW);

digitalWrite(motor_right[0], LOW);
digitalWrite(motor_right[1], LOW);
delay(25);
}

void drive_forward(){
digitalWrite(motor_left[0], HIGH);
digitalWrite(motor_left[1], LOW);

digitalWrite(motor_right[0], HIGH);
digitalWrite(motor_right[1], LOW);
}

void drive_backward(){
digitalWrite(motor_left[0], LOW);
digitalWrite(motor_left[1], HIGH);

digitalWrite(motor_right[0], LOW);
digitalWrite(motor_right[1], HIGH);
}

void turn_left(){
digitalWrite(motor_left[0], LOW);
digitalWrite(motor_left[1], HIGH);

digitalWrite(motor_right[0], HIGH);
digitalWrite(motor_right[1], LOW);
}

void turn_right(){
digitalWrite(motor_left[0], HIGH);
digitalWrite(motor_left[1], LOW);

digitalWrite(motor_right[0], LOW);
digitalWrite(motor_right[1], HIGH);
}

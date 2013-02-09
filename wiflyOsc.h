/*#################################################   
#                 WiFly Setup                     #
#################################################*/

//            Arduino  WiFly
//  WIFLYTX - receive  TX   (Send from Wifly, Receive to Arduino)
//  WIFLYRX - send     RX   (Send from Arduino, Receive to WiFly) 
SoftwareSerial wiflyOSC(WIFLYTX,WIFLYRX); 

int oscMsg[12];    // buffer for incoming OSc packet  
int inByte = 0;    // incomming serial byte  
int inbyteIndex=0;   // incomming bytes counter   
float msgVal=0;    // resulting message value  


// function to process simple OSC message sent by TouchOSC for iPad  
float getOscMsg(){  
  inByte=wiflyOSC.read();      // read next serial byte  
  if (inByte == 47){                 // if byte = slash it's message start  
    inbyteIndex=0;                   // and we set array pointer to 0  
  }  
  if ((inbyteIndex <= 11) && (inbyteIndex >= 0)){   // is it time to finish or can we start?  
     oscMsg[inbyteIndex]=inByte;            // we add the byte to the array   
     inbyteIndex++;                  // increase array counter  
  }   
  if (inbyteIndex == 11){            // end of the message  
    inbyteIndex=-1;                  // set the pointer to -1 so we stop processing   
    union u_tag {                    // this is array to float conversation routine  
      byte bytes[4];                 // I copied from Arduino.cc forum  
      float buffer;  
    } u;  
    u.bytes[0]=oscMsg[11];           // to decode we have to supply bytes in reverse order  
    u.bytes[1]=oscMsg[10];  
    u.bytes[2]=oscMsg[9];  
    u.bytes[3]=oscMsg[8];  
    msgVal = u.buffer;               // byte array to float  
    return 1;                        // signal we are ready to display value   
  }   
 return 0;                           // in this case the message is not ready yet   
}  

void oscMessageEvent(char address, float value) {
    
    float tmp = value;
    
    if (address == 'f') {
      
      if(tmp > 0) {
        //Drive forward
        drive_forward();
      } else {
        motor_stop();
      }
    } else if (address == 'b') {
          
      if(tmp > 0) {
        //Drive backward
        drive_backward();
      } else {
        motor_stop();
      }
    } else if (address == 'r') {
          
      if(tmp > 0) {
        //Turn right
        turn_right();
      } else {
        motor_stop();
      }
    } else if (address == 'l') {
          
      if(tmp > 0) {
        //Turn Left
        turn_left();
      } else {
        motor_stop();
      }
    } else if (address == 's') {
          
      if(tmp > 0) {
        //Turn Left
        motor_stop();
      }
    } else if (address == 'a') {
      
      camYPosition = map(tmp, 0, 255, 2400, 550); 
      tiltServo.writeMicroseconds(camYPosition);
      
    } else if (address == 'c') {
      
      //Set claw position
      clawPosition = map(tmp, 0, 255,clawCenter,2400);
      clawServo.writeMicroseconds(clawPosition);
        
    } else if (address == 'h') {
          
      if(tmp > 0) {
          //Lights on
          digitalWrite(bjtPin, HIGH);
      } else {
          //Lights off
          digitalWrite(bjtPin, LOW);
      }
    }
}

void wiflyCommand(char wiflyCmd) {
  wiflyOSC.print("$$$");
  delay(150);
  wiflyOSC.println(wiflyCmd);// when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      lcd.write(Serial.read());
    }
  }
  delay(150);
  wiflyOSC.println("exit");
}

#include <Servo.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <wiflyOSC.h>
#include <Wire.h> 
//#include <LiquidTWI2.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


#include "Constants.h"
#include "IOpins.h"
#include "motor_control.h"
#include "wiflyOsc.h"
#include "rangeFinder.h"
#include "buttonRead.h"


void setup()
{
  
 // Set up LCD
 lcd.init();
 
 // Print a message to the LCD.
 lcd.backlight();
  
 Serial.begin(9600);
 Serial.println("Setup Started...");
 lcd.print("Setup Started...");
   
 /*#################################################   
 #                   General Setup                 #
 #################################################*/
   
  // Setup pan-tilt
  panServo.attach(panPin);                                    // attach servos
  tiltServo.attach(armPin); 
  clawServo.attach(clawPin);
  
  panServo.writeMicroseconds(panCenter);                     // center servos
  tiltServo.writeMicroseconds(tiltCenter); 
  
  // Setup motors
  int i;
  for(i = 0; i < 2; i++){
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
  pinMode(rangeActivePin,OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(bjtPin, OUTPUT);
  digitalWrite(bjtPin, LOW);
  digitalWrite(rangeActivePin, LOW);
  
  lcd.clear();
  lcd.print("Hello, my name");
  lcd.setCursor(0, 1);
  lcd.print("is RALPH!");
  
  //Let wifly recieve UDP data
  wiflyOSC.begin(38400);
  delay(2000);
  lcd.clear();
  lcd.print("Waiting for");
  lcd.setCursor(0, 1);
  lcd.print("range finder!");
  digitalWrite(rangeActivePin, HIGH);
  delay(500);
  
  lcd.clear();
  lcd.print("Setup Finished!"); 
  lcd.setCursor(0, 1);
  lcd.print("Code started!");
  delay(500);
}
int counter = 0;
void loop()
{ 
    
    
    //Listen for OSC message over WiFly
    if (wiflyOSC.available()) {         // if we have new byte from WiFly  
       if (getOscMsg()==1){                   // add it to message while is is not ready    
          oscMessageEvent(oscMsg[1],msgVal);
       }  
    } 
    
    if (counter == 15000) {
      getInches();
      counter = 0;
    }
    /*
    if( buttonLastChecked == 0 )                              // see if this is the first time checking the buttons
      buttonLastChecked = millis()+BUTTONDELAY;               // force a check this cycle
      if( millis() - buttonLastChecked > BUTTONDELAY ) {      // make sure a reasonable delay passed
      if( int buttNum = buttonPushed(analogPin) ) {
        Serial.print("Button "); Serial.print(buttNum); Serial.println(" was pushed.");  
      }
      buttonLastChecked = millis(); // reset the lastChecked value
    }
    */
    counter++;
}

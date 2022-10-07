/*                          
                             
                   nRF Tranciver 
                   1 = GRN  Black   
                   2 = 3.3v Red
                   3 = CE   Pin 7  Blue
                   4 = CSN  Pin 8  Breen
                   5 = SCK  Pin 13 Yellow
                   6 = MOSI Pin 11 White
                   7 = MISO Pin 12 Orange
                   _______________________
                  | 1 | 2 |              |
                  | 3 | 4 |              | 
                  | 5 | 6 |              |
                  |_7_|___|______________|
*/                                 

#include <Wire.h>
#include  <SPI.h>
#include "RF24.h"
const byte address[6] = "00092";
float data[4] = {0, 0, 0, 0}; //Data Array:
RF24 radio(7,8);
int SWL = 4; //Joystick Switch:


void setup() {
 Serial.begin(9600);
  Wire.begin();
   radio.begin();
  radio.openWritingPipe(address);
 pinMode(SWL, INPUT_PULLUP); //Pull-Up for Joystick Switch:
}

void loop() {
delay(50);
 
if (analogRead(A0) <450) //Joystick forward:
 {
  int forward = (analogRead(A0));
   data[0] = 15; //Code to Identify Foward: 
  data[1] = map(analogRead(A0), 450, 0, 0, 255); //Send PWM to reciver Motor Controler:
 radio.write( data, sizeof(data) );
}

if (analogRead(A0) > 585) //Joystick Reverse: 
 {
  int reverse = (analogRead(A0));
   data[0] = 20; //Code to Identify Reverse: 
  data[1] = map(analogRead(A0), 585, 1024, 0, 255); //Send PWM to reciver Motor Controler:
 radio.write( data, sizeof(data) );
}

if (digitalRead(SWL) == LOW) //Code to Identify STOP:
 {
  data[0] = 7; //Code to Identify STOP:
   data[1] = 7; 
   data[2] = 7;
  radio.write( data, sizeof(data) );
 }
}

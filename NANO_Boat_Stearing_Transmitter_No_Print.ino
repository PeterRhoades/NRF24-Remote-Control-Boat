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
int SWR = 4; //Joystick Switch:

void setup() {
 Serial.begin(9600);
  Wire.begin();
   radio.begin();
  radio.openWritingPipe(address);
 pinMode(SWR, INPUT_PULLUP); //Pull-Up for Joystick Switch:
}

void loop() {
delay(50);
 
if (analogRead(A0) > 550) //Joystick Left: 
 {
  int left = (analogRead(A0));
  data[2] = 25; //Code to Identify Rudder Left:  
 radio.write( data, sizeof(data) );
}
 
if (analogRead(A0) < 400) //Joystick Right: 
 {
  int right = (analogRead(A0));
  data[2] = 30; //Code to Identify Rudder Right: 
 radio.write( data, sizeof(data) );
}
   
if (digitalRead(SWR) == LOW) //Code to Identify Rudder 90°:
 {
  data[2] = 3; //Code to Identify Rudder 90°:
  radio.write( data, sizeof(data) );
 } 
}

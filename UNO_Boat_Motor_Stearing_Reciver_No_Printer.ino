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


#include <Servo.h> //Servo library: 
#include  <SPI.h>
#include "RF24.h"
#include <Wire.h>
Servo myservo;
float data[4] = {0, 0, 0, 0}; //[0]=Foward, Reverse, Stop [1]=PWM Foward & Reverse [2]=Rudder Left-Right-90°:
RF24 radio(7,8);               
const byte address[6] = "00092"; //Pipe Number same as nRF Sender:
int i = 90; //Servos Variable Center Position -> 90°:
int servoPin = 9; //Servo Pin:
// Motor Control Pins:
int enA = 3;
int in1 = 5;
int in2 = 6;

void setup(){
Serial.begin(9600);
 radio.begin();
  radio.openReadingPipe(1,address);
   radio.startListening();
    Wire.begin();
pinMode(enA, OUTPUT); //Set All Motor Control Pins OUTPUT:
 pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
   digitalWrite(in1, LOW); //Turn Off Motors (Initial State):
    digitalWrite(in2, LOW);
myservo.attach(servoPin);
 myservo.write(i); //Move Servos to Center Position -> 90°  
}
 
void loop()
{
 if ( radio.available()) //Wait For Radio
 {
 radio.read(data, sizeof(data));
 
if (data[0] == 15) //Data Header Forward:
{
analogWrite(enA, data[1]); //data[1] = PWM to Motor:
 digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

if (data[0] == 20) //Data Header Reverse:
{
 analogWrite(enA, data[1]); //data[2] = PWM to Motor:
  digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
}

if (data[0] == 7 && data[1] == 7 && data[2] == 7) //Safety STOP!!!!!
{
 digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

if (data[2] == 25) //Data Header Left:
 {
  i = i - 5; //Subtract 5° from Servo:
if (i < 20) //Servo Rudder Maximum Deg Left Rudder:
 {
  i = 20;
 }
 myservo.write(i); //Move Servo Rudder 5° Left:
}

if (data[2] == 30) //Data Header Right:
 {
  i = i + 5; //Add 5° to Servo:
if (i > 160) //Servo Rudder Maximum Deg Right Rudder:
 {
  i = 160;
  }
 myservo.write(i); //Move Servo Rudder 5° Right:
}

if (data[2] == 3) //Data Header 90°:
 {  
  i = 90;
  myservo.write(i); //Move Servo Rudder 90°:
  }
 }
}

 

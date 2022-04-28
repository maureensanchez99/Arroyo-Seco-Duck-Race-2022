/*
Authors: Maureen Sanchez, Alondra Rodriguez, Elmer Ramirez
Purpose: Create an Arduino RC Duck to compete in Arroyo Seco Duck Race 2022
Objective: Acts as the controller and sends to the reciever arduino the actions it needs to perform 
*/

#include <SPI.h>
#include "RF24.h"
RF24 radio(9,10);

//constants 
const uint64_t address = 0xF0F0F0F000LL; //address 
int msg[1]; //message that is being sent to the Aruino receiver 
int joystick = A1; //where the joystick is connected

int motor1pin1 = 2; //pin connection for motor 1 to go in certain direction
int motor1pin2 = 3; //pin connection for motor 1 to go in other direction

int motor2pin1 = 4; //pin connection for motor 2 to go in certain direction
int motor2pin2 = 5; //pin connection for motor 2 to go in other direction

int motor3pin1 = 2; //pin connection for motor 3 to go in certain direction
int motor3pin2 = 3; //pin connection for motor 3 to go in other direction

int motor4pin1 = 4; //pin connection for motor 4 to go in certain direction
int motor4pin2 = 5; //pin connection for motor 4 to go in other direction

//changing variables
int direction; //determines the direction/angle of the rudder 

void setup() {
  radio.begin(); //starts the radio module 
  radio.openWritingPipe(address); //looks for reviever module at certain address
}

void loop() {
  direction = analogRead(joystick); //reads what direction the joystick is telling the rudder to go
  direction = map(direction, 0, 1023, 0, 127); //converts the values from joystick range to Servo range
  msg[0] = direction; //writes the message to send out to reciever module
  radio.write(msg, 1); //sends out message to reciever module 
}

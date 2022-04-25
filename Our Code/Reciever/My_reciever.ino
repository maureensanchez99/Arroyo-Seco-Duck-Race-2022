/*
Authors: Maureen Sanchez, Alondra Rodriguez, Elmer Ramirez
Purpose: Create an Arduino RC Duck to compete in Arroyo Seco Duck Race 2022
Objective: Recieve the signals from transmitter arduino so it can carry out the commands given. 
*/

#include <Servo.h>
#include <SPI.h>
#include "RF24.h"

Servo servo;
RF24 radio(9,10);
const uint64_t address = 0xF0F0F0F000LL; 
int msg[1]; 
int data; 
int pos;

void setup() {
  servo.attach(3); //attachs the pin the servo is connected to
  servo.write(90); //sets servo to midpoint
  delay(50); //delays the start of the radio module so the servo has time to be connected to module 
  radio.begin(); //starts the radio module
  radio.openReadingPipe(1, address); //opens connections between the radio modules
  radio.startListening(); //reciever begins waiting for commands from transmitter Arduino
}

void loop() {
  if (radio.available()){ //checks to see if radio is able to connect
    radio.read(msg,1); //if so start recieving messages to perform
  }
  data = msg[0]; 
  pos = map(data, 0, 126, 7, 67);
  servo.write(pos);
}

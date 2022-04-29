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
const int speed = 190;

// L1 is motor driver for motors 1 & 2
const int L1in1 = 2; // direction motor 1 pin 1
const int L1in2 = 4; // direction motor 1 pin 2
const int L1ena = 5; // PWM pin to change speed of motor 1

const int L1in3 = 7; // direction motor 2 & 3 pin 1
const int L1in4 = 8; // direction motor 2 & 3 pin 2
const int L1enb = 6; // PWM pin to change speed of motor 2

const int L1in5 = 7; // direction motor 3 pin 1
const int L1in6 = 8; // direction motor 3 pin 2
//const int L1ena = 6; // PWM pin to change speed of motor 3
/*
const int L2in7 = 2; // direction motor 4 pin 1
const int L2in8 = 4; // direction motor 4 pin 2
const int L2enb = 6; // PWM pin to change speed for motor 4
*/

void setup() {
  pinMode(L1in1, OUTPUT); //motor 1
  pinMode(L1in2, OUTPUT); //motor 1
  pinMode(L1ena, OUTPUT); //motor 1
  
  pinMode(L1in3, OUTPUT); //motor 2
  pinMode(L1in4, OUTPUT); //motor 2
  pinMode(L1enb, OUTPUT); //motor 2
  
  servo.attach(9); //attachs the pin the servo is connected to
  servo.write(0); //sets servo to midpoint
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
  pos = map(data, 0, 126, 0, 180); //changes values from joystick into values that fit the servo range 
  servo.write(pos);
  
  //controlling speed of motors
  analogWrite(5, speed); //sets motor speed to 75% potential
  analogWrite(6, speed); //sets motor speed to 75% potential
  
  //setting direction of motors
  digitalWrite(L1in1, HIGH);
  digitalWrite(L1in2, LOW);
  digitalWrite(L1in3, HIGH);
  digitalWrite(L1in4, LOW); 
}

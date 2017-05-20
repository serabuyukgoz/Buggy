#ifndef init_h
#define init_h

#include "Arduino.h" 

//defining pin for ultrasonic sensor
const int trigPin = 6;
const int echoPin = 5;

//defining pin for motors
const int dirA = 12;
const int dirB = 13;
const int pwmA = 3;
const int pwmB = 11;
const int brkA = 9;
const int brkB = 8;

//defining pin for buzzer
const int buzzer = 2;

void init_setup();
int distance_detect();
void stop_motor();
void move_front();
void move_back();
void move_right();
void move_left();

void buzzer();


void control_obstacle();
void decide_direction(int);

void messagePublish();

#endif

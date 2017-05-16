#ifndef init_h
#define init_h

#include "Arduino.h" 

//defining pin for ultrasonic sensor
#define trigPin 6
#define echoPin 5

//defining pin for motors
#define dirA 12
#define dirB 13
#define pwmA 3
#define pwmB 11
#define brkA 9
#define brkB 8

//defining pin for led
#define led 2

void init_setup();
int distance_detect();
void stop_motor();
void move_front();
void move_back();
void move_right();
void move_left();

void control_obstacle();
void decide_direction(int);



#endif

#include "init.h"

//make it global to reach from other functions
int distance;
// 255 high speed of motor
int speeds = 255;

void init_setup()
{
  //defining led
  pinMode(led, OUTPUT);
  
  //defining ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //defining motors
  pinMode(dirA, OUTPUT);//Channel A
  pinMode(dirB, OUTPUT);//Channel B
  pinMode(brkA, OUTPUT);//break for channel A
  pinMode(brkB, OUTPUT);//break for channel B
}

//function for distance detection 
//by using ultra sonic sensor
int distance_detect()
{ 
  long duration;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); 
  distance = (duration/2) / 29.1; //turn into cm
  
  return distance;
}

//******************************
//Definitions motors for different movements

void stop_motor()
{
  //stop both of them
  digitalWrite(brkA, HIGH);
  digitalWrite(brkB, HIGH);
  analogWrite(pwmA, 0);
  analogWrite(pwmB, 0);
}

void move_front()
{
  digitalWrite(dirA, HIGH);
  digitalWrite(brkA, LOW);
  analogWrite(pwmA, speeds);
    
  digitalWrite(dirB, LOW);
  digitalWrite(brkB, LOW);
  analogWrite(pwmB, speeds);
}

void move_back()
{
  digitalWrite(dirA, LOW);
  digitalWrite(brkA, LOW);
  analogWrite(pwmA, speeds);
  
  digitalWrite(dirB, HIGH);
  digitalWrite(brkB, LOW);
  analogWrite(pwmB, speeds);
}

//to be able to turn 
//motors must be use full speed  
void move_right()
{
  digitalWrite(dirA, HIGH);
  digitalWrite(brkA, LOW);
  analogWrite(pwmA, 255); 
   
  analogWrite(pwmB, 0);
}

void move_left()
{
  digitalWrite(dirB, LOW);
  digitalWrite(brkB, LOW);
  analogWrite(pwmB, 255); 
   
  analogWrite(pwmA, 0);
}

//**************************************

void decide_direction(int given)
{   
  switch(given)
  {
    case 1:
    {
      //turn left
      move_left();
      break;
    }
    case 2:
    {
      //turn right
      move_right();
      break; 
    }
    case 3:
    {
      //go to check
      control_obstacle();
      break;   
    }
    case 4:    
    {
      //towards move
      move_front();
      break;      
    }
    default:
    {
      debug2.data = sera;
      debug.publish( &debug2 );
      //other cases do not move
      stop_motor();
      break;
    }
  }
}

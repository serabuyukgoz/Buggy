#include "init.h"

//make it global to reach from other functions
int distance;
// 255 high speed of motor
int speeds = 180;

int count;
boolean checkFlag = true;

void init_setup()
{
  //defininf led
  pinMode(ledPin, OUTPUT);
  
  //defining buzzer
  pinMode(buzPin, OUTPUT);
  
  //defining ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //defining motors
  pinMode(dirA, OUTPUT);//Channel A
  pinMode(dirB, OUTPUT);//Channel B
  pinMode(brkA, OUTPUT);//break for channel A
  pinMode(brkB, OUTPUT);//break for channel B
}

void led()
{
  digitalWrite(ledPin, HIGH);
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
void move_right_front()
{
  digitalWrite(dirA, HIGH);
  digitalWrite(brkA, LOW);
  analogWrite(pwmA, 255); 
   
  analogWrite(pwmB, 0);
}

void move_left_front()
{
  digitalWrite(dirB, LOW);
  digitalWrite(brkB, LOW);
  analogWrite(pwmB, 255); 
   
  analogWrite(pwmA, 0);
}

void move_right_back()
{
  digitalWrite(dirA, LOW);
  digitalWrite(brkA, LOW);
  analogWrite(pwmA, 255); 
   
  analogWrite(pwmB, 0);
}

void move_left_back()
{
  digitalWrite(dirB, HIGH);
  digitalWrite(brkB, LOW);
  analogWrite(pwmB, 255); 
   
  analogWrite(pwmA, 0);
}

//**************************************
void control_obstacle()
{
  if (distance < 8)
  {
    count = 2;
    messagePublish(distance);
    stop_motor();
	buzzer();
    checkFlag = false;
  }else
  {
    checkFlag = true;
  }
}

void buzzer()
{
	tone(buzPin, 1000);
	delay(500);
	noTone(buzPin);
}
void decide_direction(int given)
{   
  switch(given)
  {
    case 1:
    {
      //front
	  move_front();
      break;
    }
    case 2:
    {
	//back 
      control_obstacle();
      if(checkFlag == true)
      {
        move_back();
      }
      break; 
    }
    case 11:
    {
      //front left
	  move_left_front();
      break;   
    }
    case 12:    
    {
      //towards move
	 move_right_front();
      break;      
    }
    case 21:
    {
      //Back left
      control_obstacle();
      if(checkFlag == true)
      {
        move_left_back();
      }
      
        break;
    }
    case 22:
    {
      //Back Right
      control_obstacle();
      if(checkFlag == true)
      {
        move_right_back();
      }
      
      break;
    }
    default:
    {
      debug2.data = given;
      debug.publish( &debug2 );
      //other cases do not move
      stop_motor();
      break;
    }
  }
}

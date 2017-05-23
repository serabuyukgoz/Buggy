#include "init.h"

//make it global to reach from other functions
//distance of ultrasonic sensor
int distance;

// 255 high speed of motor
int speeds = 180;

int count;
boolean checkFlag = true;
boolean backFlag = false;

//Initilasing every sensor 
void init_setup()
{
  //defininf led
  pinMode(ledPin, OUTPUT);
  
  //defining buzzer
  pinMode(buzPin, OUTPUT);
  
  //defining motors
  pinMode(dirA, OUTPUT);//Channel A
  pinMode(dirB, OUTPUT);//Channel B
  pinMode(brkA, OUTPUT);//break for channel A
  pinMode(brkB, OUTPUT);//break for channel B
}

//This function illuminates led 
//for understading of buggy works
void led()
{
  digitalWrite(ledPin, HIGH);
}

//Using ultrasoic library
//for getting ditance in cm
int distance_detect()
{ 
  //define ultasonic sensors
  Ultrasonic ultrasonic1(trigPin, echoPin);
  distance = ultrasonic1.Ranging(CM);
  
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

//This function check obstacles
//and return a flag
void control_obstacle()
{
  if (distance < 8)
  {
    //enter if close buggy close to an obstacle
    //Publishing warning message
    //invoke buzzer
    if (backFlag == true) {
      //only run if robot move backward
    messagePublish();
    stop_motor();
    buzzer();
    }
    checkFlag = false;
  }else
  {
    checkFlag = true;
  }
}

//this function for physical
//create noise for a short time
void buzzer()
{
   tone(buzPin, 1000);
   delay(500);
   noTone(buzPin);
}

//function deside motors movement
//according to data come from subscriber
void decide_direction(int given)
{   

  //Cases motor needed to move backward
  //first check is there any obstacle and
  //move according to result
  switch(given)
  {
    case 1:
    {
      //front
       move_front();
       backFlag = false;
      break;
    }
    case 2:
    {
	//back 
      backFlag = true;
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
      backFlag = false;
      break;   
    }
    case 12:    
    {
      //towards move
      move_right_front();
      backFlag = false;
      break;      
    }
    case 21:
    {
      //Back left
       backFlag = true;
      if(checkFlag == true)
      {
        move_left_back();
      }
      break;
    }
    case 22:
    {
      //Back Right
       backFlag = true;
      if(checkFlag == true)
      {
        move_right_back();
      }      
      break;
    }
    case 100:
    { 
      //turned on to led
      //for check connetion of communication	
      led();
    }  
    default:
    {
      //other cases do not move
      backFlag = false;
      stop_motor();
      break;
    }
  }
}

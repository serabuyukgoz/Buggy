#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int8.h>

String x;
int data;
//defining publisher alert
long duration;
long dist;

//defining pin
#define trigPin 6
#define echoPin 5
#define dirA 12
#define dirB 13
#define pwmA 3
#define pwmB 11
#define brkA 9
#define brkB 8

//ros definitions for publisher and subscriber
ros::NodeHandle nh;
std_msgs::String str_msg;

ros::Publisher sensor ("sensor", &str_msg);

std_msgs::Int8 debug2;
ros::Publisher debug ("debug", &debug2);

void messageCb( const std_msgs::Int8& msg)
{
  data = msg.data;

  message(data);
  

}

void message(int sera)
{ 
  switch(sera)
  {
    case 1:
    {
      //left
      //stop_motor();
      digitalWrite(dirB, LOW);
      digitalWrite(brkB, LOW);
      analogWrite(pwmB, 255); 
    
      analogWrite(pwmA, 0); 
      break;
    }
    case 2:
    {
      //right
      //stop_motor();
      digitalWrite(dirA, HIGH);
      digitalWrite(brkA, LOW);
      analogWrite(pwmA, 255); 
     
      analogWrite(pwmB, 0);
      break; 
    }
    case 3:
    {
      //back
      control();
       break;   
    }
    case 4:
    
    {
      //front
      digitalWrite(dirA, HIGH);
      digitalWrite(brkA, LOW);
      analogWrite(pwmA, 255);
    
      digitalWrite(dirB, LOW);
      digitalWrite(brkB, LOW);
      analogWrite(pwmB, 255);
      // move_motor(front);
      break;      
    }
    default:
    {
      debug2.data = sera;
      debug.publish( &debug2 );
      //breake
      stop_motor();
      break;
    }
  }
}

ros::Subscriber<std_msgs::Int8>path("chatter", &messageCb);

void distance_detect()
{
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); 
  dist = (duration/2) / 29.1; //turn into cm

}

void stop_motor()
{
  //stop both of them
  digitalWrite(brkA, HIGH);
  digitalWrite(brkB, HIGH);
  analogWrite(pwmA, 0);
  analogWrite(pwmB, 0);
}

void control()
{
  if (dist < 6)
  {
    str_msg.data = "Hit";
    sensor.publish( &str_msg );
    stop_motor();
  }
  else
  {
    digitalWrite(dirA, LOW);
    digitalWrite(brkA, LOW);
    analogWrite(pwmA, 255);
  
    digitalWrite(dirB, HIGH);
    digitalWrite(brkB, LOW);
    analogWrite(pwmB, 255);
  }
}

void setup()
{
 // Serial.begin (9600);
  
  //defining ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //defining motors
  pinMode(dirA, OUTPUT);//Channel A
  pinMode(dirB, OUTPUT);//Channel B
  pinMode(brkA, OUTPUT);//break for channel A
  pinMode(brkB, OUTPUT);//break for channel B
  
  //initials for mesage
  nh.initNode();
  nh.advertise(sensor);
    nh.advertise(debug); 
  nh.subscribe(path); 
}

void loop()
{
  distance_detect();
  
  nh.spinOnce();
  delay(1);
}

#include <ros.h>
#include <std_msgs/String.h>

//ros definitions for publisher and subscriber
ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

//defining publisher alert
//str_msg.data = Hit Alert!;
long duration;
long dist;

//defining pin
#define trigPin 6
#define echoPin 5

void distance_detect()
{
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  //delay(1000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  //delay(1000);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); 
  dist = (duration/2) / 29.1; //turn into cm
  
  //visualise
 // Serial.print(dist);
 // Serial.println(" cm");
}

void setup()
{
  Serial.begin (9600);
  
  //defining ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //initials for mesage
  nh.initNode();
  nh.advertise(chatter);  
}

void loop()
{
  distance_detect();
  Serial.println(" test");
 
  nh.spinOnce();
  delay(1000);
}

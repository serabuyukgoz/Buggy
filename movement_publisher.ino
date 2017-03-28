//	
// 	Test rosserial on sonar sensor and send warning message 
//

#include <ros.h>
#include <std_msgs/String.h>

//defining message 
ros::NodeHandle nh;
 
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

//defining pin 
#define trigPin 6
#define echoPin 5
#define breakA 9
#define breakB 8

void setup()
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel B pin
  pinMode(breakB, OUTPUT);  //Initiates Brake Channel B pin
  
  //initial for message
  nh.initNode();
  nh.advertise(chatter);
}

void loop() 
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  //delay(1000);
  digitalWrite(trigPin, HIGH);
  //delay(1000);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); 
  distance = (duration/2) / 29.1; //turn into cm
  Serial.print(distance);
  Serial.println(" cm");

  if(distance < 6)
  {
     Serial.println("stop");
//     digitalWrite(breakA, HIGH);  //Engage the Brake for Channel A
//     analogWrite(3, 0);
//     digitalWrite(breakB, HIGH);  //Engage the Brake for Channel B
//     analogWrite(11, 0);

     //message initials 
     str_msg.data = Warning: Buggy Stopped because of an obstacle;
     chatter.publish( &str_msg );
     nh.spinOnce();
     delay(1000);
  }
//  else if(distance < 10 && distance > 1)
//  {
//    //going 
//    //Motor A 
//    digitalWrite(12, HIGH);  //Establishes backward direction of Channel A
//    digitalWrite(breakA, LOW);   //Disengage the Brake for Channel A
//    analogWrite(3, 123);    //Spins the motor on Channel A at half speed
//
//    //Motor B 
//    digitalWrite(13, LOW); //Establishes forward direction of Channel B
//    digitalWrite(breakB, LOW);   //Disengage the Brake for Channel B
//    analogWrite(11, 123);   //Spins the motor on Channel B at half speed
//    
//  }
  else
  {
    Serial.println("cont");
//    //going 
//    //Motor A 
//    digitalWrite(12, LOW);  //Establishes backward direction of Channel A
//    digitalWrite(breakA, LOW);   //Disengage the Brake for Channel A
//    analogWrite(3, 123);    //Spins the motor on Channel A at half speed
//
//    //Motor B 
//    digitalWrite(13, HIGH); //Establishes forward direction of Channel B
//    digitalWrite(breakB, LOW);   //Disengage the Brake for Channel B
//    analogWrite(11, 123);   //Spins the motor on Channel B at half speed
  }

}

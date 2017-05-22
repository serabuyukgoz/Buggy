#include <Ultrasonic.h>

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int8.h>

#include "init.h"

String x;
int data;
int dist;

//ros definitions for publisher and subscriber
ros::NodeHandle nh;
std_msgs::String str_msg;

//callback function for subscriber always listen
void messageCb( const std_msgs::Int8& msg)
{
  data = msg.data;

  //after get data send to decision function
  decide_direction(data); 
}

ros::Publisher sensor ("sensor", &str_msg);
ros::Subscriber<std_msgs::Int8>path("chatter", &messageCb);

//function for publishing warning message
void messagePublish()
{
  str_msg.data = "Hit";
  sensor.publish( &str_msg );
}

//main setup function for arduino
void setup()
{
  //setup function for initializing every sensors
  init_setup();
  
  //ros initializing 
  nh.initNode();
  nh.advertise(sensor);
  nh.advertise(debug); 
  nh.subscribe(path); 

}

//main loop function
void loop()
{
//turned on to led	
  led(); 
 //checking distance regularly
  dist = distance_detect();

  //for rosserial connection stay open
  nh.spinOnce();
  delay(1);
}

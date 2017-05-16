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

//callback function
void messageCb( const std_msgs::Int8& msg)
{
  data = msg.data;
  decide_direction(data); 
}

ros::Publisher sensor ("sensor", &str_msg);
ros::Subscriber<std_msgs::Int8>path("chatter", &messageCb);

std_msgs::Int8 debug2;
ros::Publisher debug ("debug", &debug2);

void control_obstacle()
{
  if (dist < 6)
  {
    str_msg.data = "Hit";
    sensor.publish( &str_msg );
    stop_motor();
  }
  else
  {
    //move back
    move_back();
  }
}

void setup()
{
  init_setup();
  
  //ros initializing 
  nh.initNode();
  nh.advertise(sensor);
  nh.advertise(debug); 
  nh.subscribe(path); 
}

void loop()
{
  dist = distance_detect();
  
  nh.spinOnce();
  delay(1);
}

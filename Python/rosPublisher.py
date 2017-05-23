import sys
import rospy
from std_msgs.msg import Int8

#Function for changing TCP server string data to subcribing interger data
def decideValue(msg):
    if  msg == "no":
        return 0
    elif msg == "front":
	return 1
    elif msg == "back":
	return 2
    elif msg == "frontleft":
	return 11
    elif msg == "frontright":
	return 12
    elif msg == "backleft":
	return 21
    elif msg == "backright":
	return 22
    elif msg == 'led':    
        return 100    
    else:
	return 0
		
#that funtion is main ros publisher		
def rosPub(msg):
    value = decideValue(msg);
    pub = rospy.Publisher('chatter', Int8, queue_size=10) #defining ros publisher in integer
    rospy.init_node('talker', anonymous=True) #defining nodes of ros
	
    pub.publish(value) #publishing value




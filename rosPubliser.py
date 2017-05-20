import sys
import rospy
from std_msgs.msg import Int8

def decideValue(msg):
	if 	msg == "no":
		return 0
	elif msg == "front":
		return 1
	elif msg == "back":
		return 2
	elif value == "frontleft":
		return 11
	elif value == "frontright":
		return 12
	elif value == "backleft":
		return 21
	elif value == "backright":
		return 22
	else:
		return 0
		
		
def rosPublisher(msg):
	value = decideValue(msg);
	pub = rospy.Publisher('chatter', Int8, queue_size=10)
	rospy.init_node('talker', anonymous=True)
	
	pub.publish(value)
	

import sys
import rospy
from std_msgs.msg import Int8


print("start")
pub = rospy.Publisher('chatter', Int8, queue_size=10)
rospy.init_node('talker', anonymous=True)
while True:
    char = sys.stdin.read(1)
    if char == 'a':
        value = 1
    elif char == 's':
        value = 3
    elif char == 'd':
        value = 2
    elif char == 'w':
        value = 4
    else:
        value = 8

    pub.publish(value)
    print("You pressed " + char)
    char = sys.stdin.read(1)
    

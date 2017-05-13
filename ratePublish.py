import sys
import rospy
from std_msgs.msg import String

print("start")
pub = rospy.Publisher('chatter', String, queue_size=10)
rospy.init_node('talker', anonymous=True)
while True:
    char = sys.stdin.read(1)
    pub.publish(char)
    print("You pressed " + char)
    char = sys.stdin.read(1)
    

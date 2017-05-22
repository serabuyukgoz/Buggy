import rospy
from std_msgs.msg import String

def callback(msg):
    taken = data.msg
    rospy.loginfo("I heard %s", taken)

def listener():
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber('chatter', String, callback)
    rospy.spin()

if __name__ == '__main__'
    listener()

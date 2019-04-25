#!/usr/bin/env python

from __future__ import print_function
from __future__ import division

import roslib
roslib.load_manifest('turtlebot3_rosserial')

import sys
import rospy

from std_msgs.msg import Int32
from std_msgs.msg import String


class display_cal_node:
    def __init__(self):
        self.var = None

        """  Initializing your ROS Node """
        rospy.init_node('display_cal_node', anonymous=True)

        rospy.on_shutdown(self.shutdown)

        self.rate=rospy.Rate(10)

        """ Subscribe to the camera info topic """
        self.randNo_sub = rospy.Subscriber("/random_number", Int32, self.callback)

        """ Publish as the opencv image topic """
        # self.LED_pub = rospy.Publisher("/LED", String, queue_size=10)
        self.LED_pub = rospy.Publisher("/LED", Int32, queue_size=10)

        while not rospy.is_shutdown():
            if self.var <= 2500:
                """ send message to turn OFF the LED """
                self.varP = str("OFF")
                rospy.logwarn("The output is OFF and the var is: %s", self.var)
            else:
                """ send message to turn ON the LED """
                self.varP = str("ON")
                rospy.loginfo("The output is ON and the var is: %s", self.var)

            self.varPVal = self.var
            self.LED_pub.publish(self.varPVal)
            self.rate.sleep()

    """ define the display text """
    def callback(self, msg):
        self.var=msg.data

    def shutdown(self):
        try:
            rospy.loginfo("Display cal node [OFFLINE]...")

        finally:
            self.varPVal = 0
            self.LED_pub.publish(self.varPVal)


def usage():
    print("%s" % sys.argv[0])

def main(args):
    vn = display_cal_node()

    try:
        rospy.spin()
    except KeyboardInterrupt:
        print("Display cal node [OFFLINE]...")

if __name__ == '__main__':
    if len(sys.argv) < 1:
        print(usage())
        sys.exit(1)
    else:
        print("Display cal node [ONLINE]...")
        main(sys.argv)

#!/usr/bin/env python3

import rospy
from sobit_edu_module import SobitEduJointController
from sobit_edu_module import Joint
import sys
import math

def main():
    rospy.init_node('sobit_edu_initial_pose')
    args = sys.argv
    edu_ctr = SobitEduJointController(args[0]) # args[0] : Arguments for ros::init() on C++

    # Set initial pose
    edu_ctr.moveToPose( "initial_pose" )

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass
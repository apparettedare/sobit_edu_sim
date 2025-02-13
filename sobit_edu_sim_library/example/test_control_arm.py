#!/usr/bin/env python3
#coding: utf-8

import sys
import rospy
from sobit_edu_module import SobitEduJointController
from sobit_edu_module import Joint

def test_control_arm():
    rospy.init_node('sobit_edu_test_control_arm')

    args = sys.argv
    edu_joint_ctrl = SobitEduJointController(args[0]) # args[0] : C++上でros::init()を行うための引数

    # Move all the arm joints
    edu_joint_ctrl.moveArm( 0.0, -1.5708, 1.5708, 0.0, 1.0 )

    # Close the gripper
    edu_joint_ctrl.moveJoint( Joint.HAND_JOINT, 0, 2.0, True )

    # Set the initial pose
    edu_joint_ctrl.moveToPose( "initial_pose", 5.0)

    del edu_joint_ctrl
    del args

if __name__ == '__main__':
    try:
        test_control_arm()
    except rospy.ROSInterruptException:
        pass
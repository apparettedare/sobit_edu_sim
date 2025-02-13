#include <ros/ros.h>
#include "sobit_edu_sim_library/sobit_edu_joint_controller.hpp"


int main( int argc, char *argv[] ){
    ros::init(argc, argv, "sobit_edu_test_control_head");
    
    sobit_edu::SobitEduJointController edu_joint_ctrl;

    const double MAX_ANGLE =  1.57;
    const double MIN_ANGLE = -1.57;
    double target_angle    =  0.0;
    double increment       =  0.05;

    while( ros::ok() ){
        target_angle += increment;
        if (target_angle > MAX_ANGLE || target_angle < MIN_ANGLE) increment *= -1.0;

        // Option 1: Move the head joints simultaneously
        edu_joint_ctrl.moveHeadPanTilt( target_angle, target_angle, 0.5, false );
        ros::Duration(0.5).sleep();

        /***
        // Option 2: Move the head joints individually
        edu_joint_ctrl.moveJoint( sobit_edu::Joint::HEAD_PAN_JOINT , target_angle, 0.5, false );
        edu_joint_ctrl.moveJoint( sobit_edu::Joint::HEAD_TILT_JOINT, target_angle, 0.5, false );
        ***/
    }


    return 0;
}
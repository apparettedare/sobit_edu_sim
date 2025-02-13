#include <cstdlib>

#include <ros/ros.h>
#include "sobit_edu_sim_library/sobit_edu_joint_controller.hpp"


int main( int argc, char *argv[] ){
    ros::init(argc, argv, "sobit_edu_test_put_on_table");

    sobit_edu::SobitEduJointController edu_joint_ctrl;

    std::string target_name = "placeable_point";
    bool is_done = false;

    // Set the detecting_pose
    edu_joint_ctrl.moveToPose( "detecting_pose", 5.0);

    // Lauch the placeable_position_estimator node
    std::string package_name = "placeable_position_estimator";
    std::string node_name    = "placeable_position_estimator";
    std::string launch_name  = node_name+".launch";
    std::string command      = "roslaunch " + package_name + " " + launch_name;
    int is_launch = system(command.c_str());

    if( is_launch == -1 ){
        ROS_ERROR("Failed to execute roslaunch command");
        return 1;
    }

    ros::Duration(10.0).sleep();

    // Option 1: Place object on the given TF position
    // Arm will move down until it touches the placeable_point
    is_done = edu_joint_ctrl.moveHandToPlaceTF( target_name, -0.15, 0.0, 0.2 );

    // Option 2: Place object on the given coordinates (x,y,z) position
    // Arm will move down until it touches the placeable_point
    // bool res = edu_joint_ctrl.moveHandToPlaceCoord( 0.0, 0.0, 0.0, -0.15, 0.0, 0.2 );

    if( is_done ){
        // Open the hand
        edu_joint_ctrl.moveJoint( sobit_edu::Joint::HAND_JOINT, -1.57, 2.0, true );

        // Set the put_high_pose pose to avoid collision
        edu_joint_ctrl.moveToPose( "detecting_pose", 5.0);
    } else{
        ROS_ERROR("Failed to place the object");
    }

    // Set the initial pose
    edu_joint_ctrl.moveToPose( "initial_pose", 5.0);

    // Kill the placeable_position_estimator node
    command   = "rosnode kill /" + node_name + "/" + node_name + "_node";
    is_launch = system(command.c_str());
    ros::Duration(5.0).sleep();

    if( is_launch == -1 ){
        ROS_ERROR("Failed to kill the placeable_position_estimator node");
        return 1;
    }

    return 0;
}
#!/bin/bash
echo "Starting ROS node for Dynamixel Servos (5-axis and gripper)"
source /opt/ros/noetic/setup.bash 
source /usr/src/dynamixel/catkin_ws/devel/setup.bash 
roslaunch sieglinde_gripper_control controller.launch
sleep 1


#Dockerfile for Taurob Gripper 
FROM ros:noetic
LABEL maintainer="michael.schebek@technikum-wien.at"
LABEL version="0.1"
LABEL description="ROS Container connected to Taurob Gripper via ArduinoMega"

#Update and upgrade, install ROS Serial for communication with Arduino
RUN apt update -y
RUN apt upgrade -y 
RUN apt install ros-noetic-rosserial* ros-noetic-catkin* python3 -y


RUN mkdir -p ~/catkin_ws/src 
RUN /bin/bash -c '. /opt/ros/noetic/setup.bash; cd  ~/catkin_ws; catkin_make'
#RUN /bin/bash -c '. /opt/ros/noetic/setup.bash; export ROS_MASTER_URI=http://rosmaster:11311/'
RUN /bin/bash -c '. /opt/ros/noetic/setup.bash; rosrun rosserial_arduino make_libraries.py .'
#RUN /bin/bash -c '. /opt/ros/noetic/setup.bash; rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0'

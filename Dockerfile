FROM ros:noetic

# LABEL about the custom image
LABEL maintainer="ma0180@technikum-wien.at"
LABEL version="1.0"
LABEL description="Dynamixel ROS_Control"


#Updating and Installing stuff
RUN apt update -y
RUN apt upgrade -y
RUN apt install -y git ros-noetic-dynamixel-sdk ros-noetic-dynamixel-workbench* ros-noetic-ros-controllers ros-noetic-ros-control* ros-noetic-dynamixel*

#Creating Workspace
RUN mkdir -p /usr/src/dynamixel/catkin_ws/src
#Building ROS Workspace
RUN /bin/bash -c '. /opt/ros/noetic/setup.bash; cd  /usr/src/dynamixel/catkin_ws; catkin_make'

WORKDIR /usr/src/dynamixel/catkin_ws/src
COPY . ./
RUN chmod +x start.sh
RUN git clone https://github.com/ROBOTIS-GIT/DynamixelSDK.git
RUN /bin/bash -c '. /opt/ros/noetic/setup.bash; cd  /usr/src/dynamixel/catkin_ws; catkin_make'

#include <ros/ros.h>
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"
#include "sensor_msgs/JointState.h"
#include "dynamixel_sdk_examples/GetPosition.h"
#include "dynamixel_sdk_examples/SetPosition.h"
#include "dynamixel_sdk/dynamixel_sdk.h"


using namespace dynamixel;

// Control table address
#define ADDR_TORQUE_ENABLE    64
#define ADDR_GOAL_POSITION    116
#define ADDR_PRESENT_POSITION 132
#define Operation_Mode        11
#define ADDR_current_limit    38            // mit write2byte 2 Byte
#define ADDR_goal_current     102           // mit 2 Byte
#define ADDR_goal_position    116           // mit 4 Byte
// Protocol version
#define PROTOCOL_VERSION      2.0             // Default Protocol version of DYNAMIXEL X series.

// Default setting
#define DXL1_ID               1               // DXL1 ID
#define DXL2_ID               2               // DXL2 ID
#define BAUDRATE              1000000           // Default Baudrate of DYNAMIXEL X series
#define DEVICE_NAME           "/dev/ttyUSB0"  // [Linux] To find assigned port, use "$ ls /dev/ttyUSB*" command
#define current_mode                   0
#define position_current_mode          5                //Current Mode = 0; Position_current_mode = 5
#define M_PI           3.14159265358979323846  /* pi */
PortHandler * portHandler;
PacketHandler * packetHandler;


uint8_t dxl_error = 0;
int dxl_comm_result = COMM_TX_FAIL;

//Torque is enabled for both servos
void enable()
{
  //Servo1      
  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL1_ID, ADDR_TORQUE_ENABLE, 1, &dxl_error);
  if (dxl_comm_result != COMM_SUCCESS) 
  {
    ROS_ERROR("Failed to enable torque for Dynamixel ID %d", DXL1_ID);
  }
  //Servo2
  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL2_ID, ADDR_TORQUE_ENABLE, 1, &dxl_error);
  if (dxl_comm_result != COMM_SUCCESS) 
  {
    ROS_ERROR("Failed to enable torque for Dynamixel ID %d", DXL2_ID);

  }

}

bool getPresentPositionCallback(dynamixel_sdk_examples::GetPosition::Request & req,dynamixel_sdk_examples::GetPosition::Response & res)
{
  uint8_t dxl_error = 0;
  int dxl_comm_result = COMM_TX_FAIL;

  int32_t position = 0;

  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, (uint8_t)req.id, ADDR_PRESENT_POSITION, (uint32_t *)&position, &dxl_error);
  if (dxl_comm_result == COMM_SUCCESS) 
  {
    ROS_INFO("getPosition : [ID:%d] -> [POSITION:%d]", req.id, position);
    res.position = position;
    return true;
  } 
  else 
  {
    ROS_INFO("Failed to get position! Result: %d", dxl_comm_result);
    return false;
  }
}


void setCurrent1(const std_msgs::Int32::ConstPtr& msg)
{
  uint8_t dxl_error = 0;
  int dxl_comm_result = COMM_TX_FAIL;

  int current = msg->data;

  dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, DXL1_ID, ADDR_goal_current, current, &dxl_error);
  if (dxl_comm_result == COMM_SUCCESS) 
  {
     ROS_INFO("setCurrent : [ID:1] [Current:%d]", current);
  } 
  else 
  {
    ROS_ERROR("Failed to set position! Result: %d", dxl_comm_result);
  }
}

void setposition2(const std_msgs::Int32::ConstPtr& msg)
{
  uint8_t dxl_error = 0;
  int dxl_comm_result = COMM_TX_FAIL;

  int position = msg->data;

  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL2_ID, ADDR_goal_position, position, &dxl_error);
  if (dxl_comm_result == COMM_SUCCESS) 
  {
    ROS_INFO("setPosition : [ID:2] [Position:%d]", position);
  } 
  else 
  {
    ROS_ERROR("Failed to set Position! Result: %d", dxl_comm_result);
  }
}

//Set Operation Mode for both servos 0 = Current Mode, 5 = Position_Current Mode
void setOperationMode()
{   //Servo 1 (Axis 5)

    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL1_ID, Operation_Mode, current_mode, &dxl_error);
    
    if (dxl_comm_result != COMM_SUCCESS)
        {
          printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
        }
    else if (dxl_error != 0)
        {
          printf("%s\n", packetHandler->getRxPacketError(dxl_error));
        }
    else
        {
          printf("Operating mode changed to current mode. \n");
        }
    //Servo 2 (Gripper)    
    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL2_ID, Operation_Mode, position_current_mode, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
        {
          printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
        }
    else if (dxl_error != 0)
        {
          printf("%s\n", packetHandler->getRxPacketError(dxl_error));
        }
    else
        {
          printf("Operating mode changed to current mode. \n");
        }
}

void init()
{

  
  if (!portHandler->openPort()) 
  {
    ROS_ERROR("Failed to open the port!");

  }

  if (!portHandler->setBaudRate(BAUDRATE)) 
  {
    ROS_ERROR("Failed to set the baudrate!");

  }

}

void setCurrentLimit()
{
    int low = 70; // = ungefähr 200mA
    
    dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, DXL1_ID, ADDR_current_limit, 100, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS) 
    {
      ROS_ERROR("Failed to enable torque for Dynamixel ID %d", DXL1_ID);

    }
    
    dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, DXL2_ID, ADDR_current_limit, 100, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS) 
    {
      ROS_ERROR("Failed to enable torque for Dynamixel ID %d", DXL2_ID);
 
    }

}

void publish_position(ros::Publisher* pub)
{
  uint8_t dxl_error = 0;
  int dxl_comm_result = COMM_TX_FAIL;
  int32_t position1 = 0;
  int32_t position2 = 0;

  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL1_ID , ADDR_PRESENT_POSITION, (uint32_t *)&position1, &dxl_error);
  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL2_ID , ADDR_PRESENT_POSITION, (uint32_t *)&position2, &dxl_error);
  
  
  float pos1 = ((position1 * 0.088)* M_PI)/180 ;
  float pos2 = ((position2 * 0.088)* M_PI)/180 ;
  
  sensor_msgs::JointState msg;
  msg.name.resize(2);
  msg.position.resize(2);
  msg.velocity.resize(2);
  msg.effort.resize(2);
  
  msg.header.stamp = ros::Time::now();
  msg.name[0] = "arm_joint_5";
  msg.name[1] = "Grip";
  msg.position[0] = (pos1 + 2*M_PI)/3;
  msg.position[1] = pos2;
  
  pub->publish(msg);
  
}



int main(int argc, char ** argv)
{


  portHandler = PortHandler::getPortHandler(DEVICE_NAME); // /dev/ttyUSB0 
  packetHandler = PacketHandler::getPacketHandler(PROTOCOL_VERSION); // 2.0
  
  
  init();
  setOperationMode();
  setCurrentLimit();
  enable();

  //ROS INIT
  ros::init(argc, argv, "Sieglinde_Gripper_Control");
  ros::NodeHandle nh;
  ros::ServiceServer get_position_srv = nh.advertiseService("/get_position", getPresentPositionCallback);
  ros::Subscriber set_current_sub1 = nh.subscribe("/set_current1", 10, setCurrent1);
  ros::Subscriber set_position_sub2 = nh.subscribe("/set_position2", 10, setposition2);
  ros::Publisher pub = nh.advertise<sensor_msgs::JointState>("joint_states", 1);
  
  
  ros::Rate loop_rate(5);
  while (ros::ok())
  {
    publish_position(&pub);
    ros::spinOnce();
    loop_rate.sleep();
  }
  
 

  portHandler->closePort();
  return 0;
}

import time
import rospy
from std_msgs.msg import Int32
import sys
import copy


gripper_1 = 0   #Rotation Axis 5
gripper_2 = 0   #Gripper Grip

rospy.init_node('sieglinde_gripper_control', anonymous=False)
pub_grip = rospy.Publisher('set_position2', Int32, queue_size=1)
pub_rot = rospy.Publisher('set_current1', Int32, queue_size=1)

        
def move_gripper_1(current): #Move Axis 5 with speed/current (min = -100; max = current maximum = 100)
    for i in range(50):
        pub_rot.publish(current)
        time.sleep(0.1)
  
def move_gripper_2(angle): #Move Gripper Grip with position (min = -4095; max = 4095)
    for i in range(50):
        pub_grip.publish(angle)
        time.sleep(0.1)
    

def test_program():

    #Stop all Gripper movement
    move_gripper_1(0)
    move_gripper_2(0)
    time.sleep(1)
    
    #Move Axis 5 slow/with low torque
    move_gripper_1(20)
    time.sleep(1)
    
    #Move Axis 5 fast/with high torque
    move_gripper_1(100)
    time.sleep(1)
    
    #Stop Axis 5
    move_gripper_1(0)
    time.sleep(1)
    
    #Fully close Gripper
    move_gripper_2(4095)
    time.sleep(1)
    
    #Fully open Gripper
    move_gripper_2(0)
    time.sleep(1)
    
    #Fully close Gripper (other side)
    move_gripper_2(-4095)
    time.sleep(1)
    
    #Fully open Gripper
    move_gripper_2(0)
    time.sleep(1)
    
if __name__ == "__main__":
    test_program()

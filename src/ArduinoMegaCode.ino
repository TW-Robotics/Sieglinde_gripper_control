#include <MeSmartServo.h>
#include <SoftwareSerial.h>
#include "MeOrion.h"
#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int8.h>
#include <std_msgs/UInt8.h>

ros::NodeHandle nh;
MeSmartServo servo(PORT5);  //Arduino Mega UART2 = RX2,TX2 = 17,16
int speed1 = 25;            //Geschwindigkeit Motor 1 (zwischen 0 und 50)
int speed2 = 25;            //Geschwindigkeit Motor 2 (zwischen 0 und 50)



void init_cb(const std_msgs::UInt8& msg)
{
    //Setzen der Nullstellung für den Motor mit der ID (ID 1 = Drehachse; ID 2 = Greifer)
    servo.setBreak(msg.data, 1);
    servo.setZero(msg.data);
}

void speed1_cb(const std_msgs::UInt8& msg)
{
    //Geschwindigkeit für Motor 1 (Drehachse)
    speed1 = msg.data;  
}

void speed2_cb(const std_msgs::UInt8& msg)
{
    //Geschwindigkeit für Motor 2 (3-Finger-Greifer)
    speed2 = msg.data;  
}



void greifen_cb(const std_msgs::Int16& msg) 
{
  //Greifer Servo
  servo.moveTo(2, msg.data, speed2);
  delay(5);
}

void drehen_cb(const std_msgs::Int8& msg) 
{
  //Roationsservo
  // -1 = nach links drehen; 0 = stoppen und halten; 1 = nach rechts drehen

  if (msg.data == -1) 
  {
    //servo.setPwmMove(1, -50);
    servo.move(1,-10,speed1);
  } 
  else if (msg.data == 0) 
  {
    servo.setBreak(1, 1);
  } 
  else if (msg.data == 1) 
  {
    //servo.setPwmMove(1, 50);
    servo.move(1,10,speed1);
  }
}


ros::Subscriber<std_msgs::Int16> sub("greifen", greifen_cb);
ros::Subscriber<std_msgs::Int8> sub1("drehen", drehen_cb);
ros::Subscriber<std_msgs::UInt8> sub2("setspeed1", speed1_cb);
ros::Subscriber<std_msgs::UInt8> sub3("setspeed2", speed2_cb);
ros::Subscriber<std_msgs::UInt8> sub4("init", init_cb);

void setup() 
{

  //Ros Nodehandle
  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
  delay(250);

  servo.begin(115200);
  delay(250);
  servo.assignDevIdRequest();
  delay(250);  //must delay over 50ms

  servo.setZero(1);
  delay(250);

}

void loop() {
  nh.spinOnce();
  delay(1);
}

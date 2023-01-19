#include <MeSmartServo.h>
#include <SoftwareSerial.h>
#include "MeOrion.h"
#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int8.h>





ros::NodeHandle nh;
MeSmartServo servo(PORT5);  //Arduino Mega UART2 = RX2,TX2 = 17,16


void greifen_cb(const std_msgs::Int16& msg) {
  //Greifer Servo
  servo.moveTo(2, msg.data, 20);
  delay(5);
}

void drehen_cb(const std_msgs::Int8& msg) {
  //Roationsservo
  // -1 = nach links drehen; 0 = stoppen und halten; 1 = nach rechts drehen

  if (msg.data == -1) {
    servo.setPwmMove(1, -50);
  } else if (msg.data == 0) {
    servo.setBreak(1, 1);
  } else if (msg.data == 1) {
    servo.setPwmMove(1, 50);
  }
}


ros::Subscriber<std_msgs::Int16> sub("greifen", greifen_cb);
ros::Subscriber<std_msgs::Int8> sub1("drehen", drehen_cb);

void setup() {

  //Ros Nodehandle
  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(sub1);
  delay(100);

  servo.begin(115200);
  delay(100);
  servo.assignDevIdRequest();
  delay(100);  //must delay over 50ms

  servo.setInitAngle(1);
  delay(100);

}

void loop() {
  nh.spinOnce();
  delay(1);
}

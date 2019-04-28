
#include <ros.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>
#include "Arduino.h"
#include "AX12A.h"

#define DirectionPin 	(10u)
#define BaudRate  		(1000000ul)
#define ID1				(15u)
#define ID2				(6u)

ros::NodeHandle nh;

float transVelocity;
float rotVelocity;

float transVelocity;
float rotVelocity;
float wheelSep = 0.165; //  16.5cm
float wheelRadius = 0.07; //  70mm


void messageCb(const geometry_msgs::Twist &msg)
{
  transVelocity = msg.linear.x;
  rotVelocity = msg.angular.z;
  double velDiff = (wheelSep * rotVelocity) / 2.0;
  double leftPower = (transVelocity + velDiff) / wheelRadius;
  double rightPower = (transVelocity - velDiff) / wheelRadius;

  // ax12a.turn(ID1, RIGHT, speed);
  // ax12a.turn(ID2, LEFT, speed);
  nh.loginfo([leftPower, rightPower])
}

// ros::Subscriber<std_msgs::Int32> sub("/random_number", &messageCb);
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &messageCb);

void setup()
{
  ax12a.begin(BaudRate, DirectionPin, &Serial1);  // Using HardwareSerial (Serial1 or Serial2 or Serial3) of ARDUINO MEGA 2560
  ax12a.setEndless(ID1, ON);
  ax12a.setEndless(ID2, ON);

  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(200);
}

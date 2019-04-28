
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

float wheelSep = 0.165; //  16.5cm
float wheelRadius = 0.07; //  70mm

double velDiff;
double leftPower;
double rightPower;

double motorPower;
double motorSpeed;

void messageCb(const geometry_msgs::Twist &msg)
{
  transVelocity = msg.linear.x;
  rotVelocity = msg.angular.z;
  velDiff = (wheelSep * rotVelocity) / 2.0;
  leftPower = (transVelocity + velDiff) / wheelRadius;
  rightPower = (transVelocity - velDiff) / wheelRadius;

  // leftPowerSPD = (leftPower - 0.01) * (1000 - 100) / (0.22 - 0.01) + 100;
  //
  // if (leftPower > 0)
  // {
  //   leftPowerSPD = (leftPower - 0.01) * (1000 - 100) / (0.22 - 0.01) + 100;
  // }

  double leftSpeed = motorSPD(leftPower);
  double rightSpeed = motorSPD(rightPower);

  // ax12a.turn(ID1, RIGHT, speed);
  // ax12a.turn(ID2, LEFT, speed);
  char result[8];
  char result1[8];
  // dtostrf(abs(leftPower), 4, 4, result);
  // dtostrf(abs(rightPower), 4, 4, result1);
  dtostrf(abs(leftSpeed), 4, 4, result);
  dtostrf(abs(rightSpeed), 4, 4, result1);
//  sprintf(log_msg,"leftPower =%s", result);
  nh.loginfo(result);
  nh.loginfo(result1);
}

double motorSPD(double motorPower)
{
  if (abs(motorPower) > 0)
  {
    // Determine the motor speed
    motorSpeed = (motorPower - 0.01) * (1000 - 100) / (0.22 - 0.01) + 100;

    // Determine the direction
    if (motorPower > 0)
    {
      motorSpeed = motorSpeed;
    }
    else
    {
      motorSpeed = -motorSpeed;
    }
    return motorSpeed;
  }
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

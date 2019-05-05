
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

float varLinearX;
float varLinearY;
float varLinearZ;

float varAngularX;
float varAngularY;
float varAngularZ;

int speed;

float transVelocity;
float rotVelocity;

float wheelSep = 0.165; //  16.5cm
float wheelRadius = 0.07; //  70mm

double velDiff;
double leftPower;
double rightPower;

void messageCb(const geometry_msgs::Twist &msg)
{
  varLinearX = msg.linear.x;
  varLinearY = msg.linear.y;
  varLinearZ = msg.linear.z;
  varAngularX = msg.angular.x;
  varAngularY = msg.angular.y;
  varAngularZ = msg.angular.z;

  motorDirection();
}

void motorDirection()
{
  if(abs(varLinearX) > 0)
  {
    // set the speed
    speed = (abs(varLinearX) - 0.01) * (1000 - 100) / (0.22 - 0.01) + 100;

    if(varLinearX > 0)
    {
      moveForward(speed, speed);
    }
    else
    {
      moveBackward(speed, speed);
    }
  }
  else
  {
    moveStop();
  }
}

void moveForward(int speed1, int speed2)
{
  ax12a.turn(ID1, RIGHT, speed1);  // MAX SPEED: TRY and ERROR ~ 1000
  ax12a.turn(ID2, LEFT, speed2);
}

void moveBackward(int speed1, int speed2)
{
  ax12a.turn(ID1, LEFT, speed1);
  ax12a.turn(ID2, RIGHT, speed2);
}

void moveStop()
{
  ax12a.turn(ID1, LEFT, 0);
  ax12a.turn(ID2, LEFT, 0);

  //  or
  // ax12a.turn(ID1, RIGHT, 0);
  // ax12a.turn(ID2, RIGHT, 0);
}

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
  // comment to eliminate slow communication between node
  //  its good for publishing topic use delay -- perhaps :)
  // delay(200);

}

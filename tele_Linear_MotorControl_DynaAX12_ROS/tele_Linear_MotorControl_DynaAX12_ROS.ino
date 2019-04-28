
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

void messageCb(const geometry_msgs::Twist &msg)
{
  varLinearX = msg.linear.x;
  varLinearY = msg.linear.y;
  varLinearZ = msg.linear.z;
  varAngularX = msg.angular.x;
  varAngularY = msg.angular.y;
  varAngularZ = msg.angular.z;


  if(varLinearX > 0)  //  FORWARD
  {
    // int speed = map(varLinearX, 0.01, 0.22, 100, 1000);
    speed = (varLinearX - 0.01) * (1000 - 100) / (0.22 - 0.01) + 100;
    ax12a.turn(ID1, LEFT, speed);  // MAX SPEED: TRY and ERROR ~ 1000
    ax12a.turn(ID2, RIGHT, speed);
  }
  else if(varLinearX < 0) //  BACKWARD
  {
    // int speed = map(varLinearX, -0.01, -0.22, 100, 1000);
    speed = (varLinearX - (-0.01)) * (1000 - 100) / ((-0.22) - (-0.01)) + 100;
    ax12a.turn(ID1, RIGHT, speed);
    ax12a.turn(ID2, LEFT, speed);
  }
  else
  {
    ax12a.turn(ID1, LEFT, 0);  //  or ax12a.turn(ID, RIGHT, 0);
    ax12a.turn(ID2, LEFT, 0);
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

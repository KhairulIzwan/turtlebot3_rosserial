//different specific libraries
#include <ros.h>
// #include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include "Arduino.h"
#include "AX12A.h"

#define DirectionPin 	(10u)
#define BaudRate  		(1000000ul)
#define ID1				(15u)
#define ID2				(6u)

// create the ros node nh. The node will be used to publish to Arduino
ros::NodeHandle nh;

float transVelocity;
float rotVelocity;

float wheelSep = 0.165; //  16.5cm
float wheelRadius = 0.07; //  70mm

double velDiff;
double leftPower;
double rightPower;

double speed;

double speed1;
double speed2;

// double motorPower;
// double motorSpeed;

char latt[9];
char lon[9];

void messageCb(const geometry_msgs::Twist &msg)
{
  // varLinearX = msg.linear.x;
  // varLinearY = msg.linear.y;
  // varLinearZ = msg.linear.z;
  // varAngularX = msg.angular.x;
  // varAngularY = msg.angular.y;
  // varAngularZ = msg.angular.z;

  transVelocity = msg.linear.x;
  rotVelocity = msg.angular.z;

  velDiff = (wheelSep * rotVelocity) / 2.0;
  leftPower = (transVelocity + velDiff) / wheelRadius;
  rightPower = (transVelocity - velDiff) / wheelRadius;

  motorDirection();
}

void motorDirection()
{
  if((abs(leftPower) > 0) && (abs(rightPower) > 0))
  {
    // set the speed
    // speed = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    speed = (abs(leftPower) - 0.00) * (1000 - 0) / (6.49 - 0.00) + 0;
  }
  else
  {
    speed = 0;
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


// ros::Subscriber<std_msgs::Int32> sub("/random_number", &messageCb);
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &messageCb);

// std_msgs::String str_msg;
// ros::Publisher pub("chatter", &str_msg);

void setup()
{
  ax12a.begin(BaudRate, DirectionPin, &Serial1);  // Using HardwareSerial (Serial1 or Serial2 or Serial3) of ARDUINO MEGA 2560
  ax12a.setEndless(ID1, ON);
  ax12a.setEndless(ID2, ON);

  nh.initNode();
  nh.subscribe(sub);
  // nh.advertise(pub);
}

void loop()
{
  dtostrf(speed, 8, 4, lon);
  // dtostrf(leftPower, 8, 4, lon);
  // dtostrf(rightPower, 8, 4, latt);
  nh.loginfo(lon);
  // nh.loginfo(latt);
  // str_msg.data = [leftPower, rightPower]
  // pub.publish(&str_msg);
  nh.spinOnce();
  // delay(200);
}

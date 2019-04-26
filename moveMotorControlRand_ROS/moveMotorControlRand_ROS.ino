
#include <ros.h>
#include <std_msgs/Int32.h>
#include "Arduino.h"
#include "AX12A.h"

#define DirectionPin 	(10u)
#define BaudRate  		(1000000ul)
#define ID				(13u)

ros::NodeHandle nh;

float var;

void messageCb(const std_msgs::Int32 &msg)
{
  var=msg.data;

  if(var > 2000)
  {
    ax12a.turn(ID, LEFT, 500);
  }
  else
  {
    ax12a.turn(ID, RIGHT, 500);
  }
}

// ros::Subscriber<std_msgs::Int32> sub("/random_number", &messageCb);
ros::Subscriber<std_msgs::Int32> sub("/LED", &messageCb);

void setup()
{
  ax12a.begin(BaudRate, DirectionPin, &Serial1);  // Using HardwareSerial (Serial1 or Serial2 or Serial3) of ARDUINO MEGA 2560
  ax12a.setEndless(ID, ON);

  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(200);
}

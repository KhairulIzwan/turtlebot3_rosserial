#include "Arduino.h"
#include <ros.h>
#include <std_msgs/Int32.h>
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
    digitalWrite(13, HIGH);   // blink the led
    ax12a.ledStatus(ID, ON);
  }
  else
  {
    digitalWrite(13, LOW);   // turn off the led
    ax12a.ledStatus(ID, OFF);
  }
}

// ros::Subscriber<std_msgs::Int32> sub("/random_number", &messageCb);
ros::Subscriber<std_msgs::Int32> sub("/LED", &messageCb);

void setup()
{
  pinMode(13, OUTPUT);
  ax12a.begin(BaudRate, DirectionPin, &Serial);

  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  // delay(200);
}

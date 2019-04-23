/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>

ros::NodeHandle  nh;

std_msgs::String str_msg;
std_msgs::Int32 int_msg;
ros::Publisher chatter("chatter", &str_msg);
ros::Publisher chatter("chatterNo", &int_msg);

char hello[13] = "hello world!";
int count = 0;

void setup()
{
  nh.initNode();
  nh.advertise(chatter);
}

void loop()
{
  str_msg.data = hello;
  int_msg.data = count;
  chatter.publish( &str_msg );
  chatter.publish( &int_msg );
  nh.spinOnce();
  delay(1000);

  ++count;
}

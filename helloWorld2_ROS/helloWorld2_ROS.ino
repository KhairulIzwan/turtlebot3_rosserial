/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */

#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle  nh;

std_msgs::Int32 int_msg;
ros::Publisher chatter("chatterNo", &int_msg);

int count = 0;

void setup()
{
  nh.initNode();
  nh.advertise(chatter);
}

void loop()
{
  int_msg.data = count;
  chatter.publish( &int_msg );
  nh.spinOnce();
  delay(1000);

  ++count;
}

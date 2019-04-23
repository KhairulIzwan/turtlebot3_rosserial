/*
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

void messageCb(const std_msgs::String& msg)
{
  if(msg.data == 1)
    digitalWrite(13, HIGH-digitalRead(13));   //blink the led
else
   digitalWrite(13, LOW-digitalRead(13));   //turn off the led
}

ros::Subscriber<std_msgs::String> sub("LED", &messageCb);

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(1);
}

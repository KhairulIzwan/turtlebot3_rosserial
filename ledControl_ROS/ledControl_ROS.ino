#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;

char var;

void messageCb(const std_msgs::String &msg)
{
  var=msg.data;

  if(msg.data == "ON")
  {
    digitalWrite(13, HIGH);   // blink the led
  }
  else
  {
    digitalWrite(13, LOW);   // turn off the led
  }
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

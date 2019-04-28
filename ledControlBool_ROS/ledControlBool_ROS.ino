#include <ros.h>
#include <std_msgs/Bool.h>

ros::NodeHandle nh;

void messageCb(const std_msgs::Bool &msg)
{
  if(msg.data == true)
  {
    digitalWrite(13, HIGH);   // blink the led
  }
  else
  {
    digitalWrite(13, LOW);   // turn off the led
  }
}

ros::Subscriber<std_msgs::Bool> sub("LED", &messageCb);

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(200);
}

#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

float var;

void messageCb(const std_msgs::Int32 &msg)
{
  var=msg.data;

  if(var > 2000)
  {
    digitalWrite(2, HIGH);   // blink the led
    digitalWrite(7, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(8, LOW);
    digitalWrite(13, LOW);
  }
  else
  {
    digitalWrite(2, LOW);   // turn off the led
    digitalWrite(7, LOW);
    digitalWrite(12, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(13, HIGH);
  }
}

// ros::Subscriber<std_msgs::Int32> sub("/random_number", &messageCb);
ros::Subscriber<std_msgs::Int32> sub("/LED", &messageCb);

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(1);
}

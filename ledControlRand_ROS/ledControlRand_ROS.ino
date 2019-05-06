#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

float var;

void messageCb(const std_msgs::Int32 &msg)
{
  var=msg.data;

  if(var > 2000)
  {
    digitalWrite(22, HIGH);   // blink the led
    digitalWrite(26, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(40, HIGH);
    digitalWrite(39, HIGH);
    digitalWrite(43, HIGH);
    digitalWrite(24, LOW);
    digitalWrite(30, LOW);
    digitalWrite(34, LOW);
    digitalWrite(38, LOW);
    digitalWrite(42, LOW);
    digitalWrite(41, LOW);

  }
  else
  {
    digitalWrite(22, LOW);   // turn off the led
    digitalWrite(26, LOW);
    digitalWrite(32, LOW);
    digitalWrite(40, LOW);
    digitalWrite(39, LOW);
    digitalWrite(43, LOW);
    digitalWrite(24, HIGH);
    digitalWrite(30, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(38, HIGH);
    digitalWrite(42, HIGH);
    digitalWrite(41, HIGH);
  }
}

// ros::Subscriber<std_msgs::Int32> sub("/random_number", &messageCb);
ros::Subscriber<std_msgs::Int32> sub("/number", &messageCb);

void setup()
{
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(43, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(1);
}

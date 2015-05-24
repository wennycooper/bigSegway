#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>

#define RANGE	100
#define INITIAL_VALUE 0

void init_motors()
{
  wiringPiSetup();

  // initialize left motor (0:pwm, 2:in1 & 3:in2)
  softPwmCreate(0, INITIAL_VALUE, RANGE);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  softPwmWrite(0, 0);

  // initialize right motor (4:pwm, 5:in3 & 6:in4)
  softPwmCreate(4, INITIAL_VALUE, RANGE);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  softPwmWrite(4, 0);
}

void stop_motors()
{
  softPwmWrite(0, 0);
  softPwmWrite(4, 0);
}

double left_speed;
double right_speed;

void motors(double speed, double left_offset, double right_offset)
{
// pin 0:pwm, 2:in1, 3:in2
// pin 4:pwm, 5:in3, 6:in4
// to forward, 2:HIGH & 3:LOW   5:HIGH & 6:LOW
// to backward, 2:LOW & 3:HIGH  5:LOW  & 6:HIGH

  left_speed = speed + left_offset;
  right_speed = speed + right_offset;

  // left motor
  if (left_speed < 0)  {
    softPwmWrite(0, (int) -left_speed);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
  }
  else
  if (left_speed > 0)  {
    softPwmWrite(0, (int) left_speed);
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
  }

  // right motor
  if (right_speed < 0)  {
    softPwmWrite(4, (int) -right_speed);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
  }
  else
  if (right_speed > 0)  {
    softPwmWrite(4, (int) right_speed);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
  }
}




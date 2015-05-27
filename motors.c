#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>

#define RANGE	100
#define INITIAL_VALUE 0

void init_motors()
{
  wiringPiSetup();

  // initialize left motor (0:pwm, 2:pwm & 3:ce)
  softPwmCreate(0, INITIAL_VALUE, RANGE);
  softPwmCreate(2, INITIAL_VALUE, RANGE);
  pinMode(3, OUTPUT);
  softPwmWrite(0, 0);
  softPwmWrite(2, 0);

  // initialize right motor (4:pwm, 5:pwm & 6:ce)
  softPwmCreate(4, INITIAL_VALUE, RANGE);
  softPwmCreate(5, INITIAL_VALUE, RANGE); 
  pinMode(6, OUTPUT);

  softPwmWrite(4, 0);
  softPwmWrite(5, 0);
}

void stop_motors()
{
  softPwmWrite(0, 0);
  softPwmWrite(2, 0);

  softPwmWrite(4, 0);
  softPwmWrite(5, 0);
}

double left_speed;
double right_speed;

void motors(double speed, double left_offset, double right_offset)
{
// pin 0:pwm, 2:pwm, 3:ce
// pin 4:pwm, 5:pwm, 6:ce
// to forward,  0:pwm, 2:low  && 4:pwm, 5:low
// to backward, 0:low, 2:pwm  && 4:low, 5:pwm

  left_speed = speed + left_offset;
  right_speed = speed + right_offset;

  // left motor
  if (left_speed < 0)  {
    softPwmWrite(0, (int) -left_speed);
    softPwmWrite(2, 0);
    digitalWrite(3, HIGH);
  }
  else
  if (left_speed > 0)  {
    softPwmWrite(0, 0);
    softPwmWrite(2, (int) left_speed);
    digitalWrite(3, HIGH);
  }

  // right motor
  if (right_speed < 0)  {
    softPwmWrite(4, (int) -right_speed);
    softPwmWrite(5, 0);
    digitalWrite(6, HIGH);
  }
  else
  if (right_speed > 0)  {
    softPwmWrite(4, 0);
    softPwmWrite(5, (int) right_speed);
    digitalWrite(6, HIGH);
  }
}




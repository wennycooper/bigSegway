#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>

#define RANGE	100
#define INITIAL_VALUE 0

void init_motors()
{
  wiringPiSetup();

  // initialize left motor (0:pwm, 2:dir & 3:F)
  softPwmCreate(0, INITIAL_VALUE, RANGE);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  softPwmWrite(0, 0);
  digitalWrite(3, HIGH);

  // initialize right motor (4:pwm, 5:dir & 6:F)
  softPwmCreate(4, INITIAL_VALUE, RANGE);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  softPwmWrite(4, 0);
  digitalWrite(6, HIGH);
}

void stop_motors()
{
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(0, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);

  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(6, HIGH);

//  printf("motor stopped!!\n");

  // exit(1);

}

double left_speed;
double right_speed;

void motors(double speed, double left_offset, double right_offset)
{

// to come to me, drive pin 0&5 to some power
// to away from me, drive pin 2&4 to some power

// pin 0:pwm, 2:dir, 3:F
// pin 4:pwm, 5:dir, 6:F
// to forward, 2:HIGH & 5:LOW 
// to backward, 2:LOW & 5:HIGH

  left_speed = speed + left_offset;
  right_speed = speed + right_offset;

  // left motor
  if (left_speed < 0)  {
    softPwmWrite(0, (int) -left_speed);
    digitalWrite(2, LOW);
  }
  else
  if (left_speed > 0)  {
    softPwmWrite(0, (int) left_speed);
    digitalWrite(2, HIGH);
  }

  // right motor
  if (right_speed < 0)  {
    softPwmWrite(4, (int) -right_speed);
    digitalWrite(5, HIGH);
  }
  else
  if (right_speed > 0)  {
    softPwmWrite(4, (int) right_speed);
    digitalWrite(5, LOW);
  }
}




#include "Robot.h"

#include <stack.h>

#include <iostream>

double _lasttime = 0;
double _lasterror = 0;
double _sum = 0;

void Robot::RobotInit() {
  usage::xbox(0);
  usage::pendulum(0, 1, -30);

  _lasttime = get_time();
}

void Robot::RobotPeriodic() {
  double goal = 0;
  double actual = degrees_bound(get_encoder_value(encoder) / 512 * 180);

  double time = get_time();
  double dt = time - _lasttime;

  double kP = -0.2;
  double kI = 0.001;
  double kD = -0.005;

  double error = goal - actual;
  double derror = dt > 0.01 ? (error - _lasterror) / dt : 0;
  _sum += error * dt;

  double output = kP * error;
  output += kI * _sum;
  output += kD * derror;

  motor.Set(output);

  _lasterror = error;
  _lasttime = time;
}
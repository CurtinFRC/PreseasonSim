#include "Robot.h"

#include <stack.h>

#include <iostream>

void Robot::RobotInit() {
  // Motor #0, 1m long, starts at -30 degrees
  usage::pendulum(0, 1, -30);
}

void Robot::RobotPeriodic() {
  int encoder_value = encoder.Get();
  // Our encoders have 1024 ticks per revolution, so this
  // converts it to degrees. degrees_bound converts 0-360
  // to -180 - 180
  double input = degrees_bound(encoder_value / 512.0 * 180.0);
  // Call the Lua script to calculate the output
  double output = script.calculate(input);

  // Send the output to the motor
  motor.Set(output);
}
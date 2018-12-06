#include "Robot.h"

#include <stack.h>

#include <iostream>

void Robot::RobotInit() {
  // Group 1: 
  //  Setup The xbox controller (usage::xbox) and the drivetrain (usage::drivetrain)
  //    Try not to hard code the values (try using GetChannel on the motors and GetPort on the
  //    xbox controller)
}

void Robot::RobotPeriodic() {
  // Group 1: 
  //  Use get_control_signal on the '_control' variable and pass it to the Drive() method.
}

void Robot::Drive(double left, double right) {
  // Group 2:
  //  Control the _left and _right motors with the given values.
}
#include "Robot.h"

#include <stack.h>

#include <iostream>

void Robot::RobotInit() {
  usage::xbox(0);
}

void Robot::RobotPeriodic() {
  double yspeed = -xbox.GetY(frc::XboxController::JoystickHand::kLeftHand);
  motor.Set(yspeed);
}
#include "Robot.h"

#include <stack.h>

#include <iostream>

void Robot::RobotInit() {
  usage::drivetrain(0, 1);
  left.SetInverted(true);
}

void Robot::RobotPeriodic() {
  auto hand = frc::XboxController::JoystickHand::kRightHand;
  double xspeed = xbox.GetX(hand);
  double yspeed = -xbox.GetY(hand);

  left.Set(yspeed + xspeed);
  right.Set(yspeed - xspeed);
}
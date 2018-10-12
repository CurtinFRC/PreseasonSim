#include "Robot.h"

#include <iostream>

void Robot::RobotInit() {
  usage::drivetrain(0, 1);
  left.SetInverted(true);
}

void Robot::RobotPeriodic() {
  frc::XboxController::JoystickHand hand = frc::XboxController::JoystickHand::kRightHand;
  diff.ArcadeDrive(xbox.GetX(hand), -xbox.GetY(hand));
  
  // double xspeed = xbox.GetX(hand);
  // double yspeed = -xbox.GetY(hand);

  // left.Set(yspeed + xspeed);
  // right.Set(yspeed - xspeed);
}
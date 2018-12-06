#include "robot_control.h"

// Group 2: 
//  Do the logic for creating the control signal based on a previous class.
std::pair<double, double> robot_control::get_control_signal(frc::XboxController &xbox) {
  double xspeed = xbox.GetX(frc::XboxController::JoystickHand::kLeftHand);
  double yspeed = -xbox.GetY(frc::XboxController::JoystickHand::kRightHand);

  std::pair<double, double> signal;
  // Do your logic here!
  return signal;
}
#include "Robot.h"

#include <iostream>

void Robot::RobotInit() {
  motor = std::make_shared<frc::Spark>(0);
  xbox = std::make_shared<frc::XboxController>(0);
}

void Robot::RobotPeriodic() {
  motor->Set(xbox->GetX(frc::XboxController::JoystickHand::kLeftHand));
}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {}

void Robot::TestPeriodic() {}
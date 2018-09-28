#include "Robot.h"

#include <iostream>

void Robot::RobotInit() {
  motor_0 = std::make_shared<frc::Spark>(0);
  motor_1 = std::make_shared<frc::Spark>(1);
  xbox = std::make_shared<frc::XboxController>(0);
}

void Robot::RobotPeriodic() {
  motor_0->Set(xbox->GetX(frc::XboxController::JoystickHand::kLeftHand));
  motor_1->Set(xbox->GetY(frc::XboxController::JoystickHand::kLeftHand));
}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {}

void Robot::TestPeriodic() {}
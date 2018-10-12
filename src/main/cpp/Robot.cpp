#include "Robot.h"

#include <iostream>

void Robot::RobotInit() {
    usage::drivetrain(0, 1);
    frc::Spark *spark = new frc::Spark(0);
    spark->Set(1.0);
}

void Robot::RobotPeriodic() {
}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {}

void Robot::TestPeriodic() {}
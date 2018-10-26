/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/Spark.h>
#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/Encoder.h>
#include <frc/Timer.h>
#include <frc/drive/DifferentialDrive.h>

#include <usage.h>

#include <memory>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;

  double get_encoder_value(frc::Encoder &enc) {
    return static_cast<double>(enc.Get());
  }

  double degrees_bound(double deg) {
    return std::fmod(deg + 180, 360) - 180;
  }

  double get_time() {
    return frc::Timer::GetFPGATimestamp();
  }

 private:
  frc::Spark motor{0};
  frc::Encoder encoder{0, 1};
};

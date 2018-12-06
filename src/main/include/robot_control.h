#pragma once

#include <utility>
#include <frc/XboxController.h>

class robot_control {
 public:
  /**
   * Calculate the left and right control signals for the motors on a standard
   * differential (tank) drive from an Xbox Controller.
   * 
   * @param xbox The xbox controller
   * @return  A pair of control signals, where the first is the left signal, and the
   *          second is the right signal.
   */
  std::pair<double, double> get_control_signal(frc::XboxController &xbox);
};
#include <frc/RobotBase.h>
#include "Robot.h"

#ifdef SIMULATION
#include "sim_main.h"
#endif

#include <iostream>

#ifndef RUNNING_FRC_TESTS
int main() {
  #ifdef SIMULATION
  sim_main sim;
  sim.run();
  #endif
  std::cout << "Starting Robot..." << std::endl;
  return frc::StartRobot<Robot>();
}
#endif
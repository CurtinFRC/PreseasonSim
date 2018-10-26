#include "sim_main.h"
#include "motor_window.h"
#include "tank_window.h"
#include "xbox_window.h"
#include "pendulum_window.h"

#include "usage.h"

#include "hal/HAL.h"
#include "mockdata/PWMData.h"
#include "opencv2/highgui/highgui.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <thread>

static std::vector<sim_motor_window> _motors;
static std::vector<tank_window>      _tanks;
static std::vector<sim_xbox_window>  _xboxes;
static std::vector<pendulum_window>  _pendulums;

#define ALL_UPD8(list) for (auto it = list.begin(); it != list.end(); ++it) cb(*it);

void all_windows(std::function<void(window &)> cb) {
  ALL_UPD8(_xboxes);
  ALL_UPD8(_motors);
  ALL_UPD8(_tanks);
  ALL_UPD8(_pendulums);
}

void sim_main::run() {
  std::cout << "[SIM] Simulation Starting..." << std::endl;
  HAL_Initialize(500, 0);

  _motors.reserve(10);
  _xboxes.reserve(6);
  for (int i = 0; i < 10; i++) _motors.emplace_back(i);
  for (int i = 0; i < 6; i++)  _xboxes.emplace_back(i);

  usage::on_drivetrain([](int id) {
    std::pair<int, int> motors = usage::get_drivetrain(id);
    std::cout << "[SIM] Found Drivetrain: " << id << " Left: " << motors.first << " Right: " << motors.second
              << std::endl;
    _tanks.emplace_back(motors.first, motors.second);
    _tanks.back().start();
  });

  usage::on_xbox([](int id, bool enable) {
    std::cout << "[SIM] Xbox " << id << " {" << enable << "}" << std::endl;
    if (enable) {
      _xboxes[id].start();
    } else {
      _xboxes[id].stop();
    }
  });

  usage::on_pendulum([](int id, double len, double angle) {
    std::cout << "[SIM] Pendulum " << id << std::endl;
    _pendulums.emplace_back(id, len, angle * 3.141593 / 180.0);
    _pendulums.back().start();
  });

  std::cout << "[SIM] Starting UI Thread..." << std::endl;
  std::thread thread([]() {
    while (true) {
      all_windows([](window &win) { win.update(); });

      cv::waitKey(static_cast<int>(1000.0 / 45.0));
    }
  });
  thread.detach();
  std::cout << "[SIM] Simulation Initialized!" << std::endl;
}
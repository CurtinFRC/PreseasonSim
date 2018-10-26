#pragma once

#include "MiniLua.hpp"
#include <frc/Timer.h>
#include <usage.h>
#include <iostream>
#include <vector>

class PendulumControlScript {
public:
  PendulumControlScript() {
    reload();
    usage::on_pendulum_reset([&]() {
      this->reload();
    });
  }

  void reload() {
    _lua.Close();
    _lua.Load("../../../../../../src/main/lua/control.lua");
    setup();
  }

  void setup() {
    _lua.Call("setup", 0, std::vector<double>{ });
    _lasttime = frc::Timer::GetFPGATimestamp();
  }

  double calculate(double input) {
    double time = frc::Timer::GetFPGATimestamp();
    double dt = time - _lasttime;
    
    _lua.Call("calculate", 1, std::vector<double>{dt, input});

    _lasttime = time;
    return _lua.PopNumber();
  }

private:
  MiniLua _lua;
  double _lasttime = 0;
};
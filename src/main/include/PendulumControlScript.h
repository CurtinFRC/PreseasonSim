#pragma once

#include "MiniLua.hpp"
#include <frc/Timer.h>
#include <usage.h>
#include <iostream>
#include <vector>
#include <mutex>

class PendulumControlScript {
public:
  PendulumControlScript() {
    reload();
    usage::on_pendulum_reset([&]() {
      this->reload();
    });
  }

  void reload() {
    mtx.lock();
    _lua.Close();
    _lua.Load("../../../../../../src/main/lua/pendulum.lua");
    setup();
    mtx.unlock();
  }

  void setup() {
    _lua.Call("setup", 0, std::vector<double>{ });
    _lasttime = frc::Timer::GetFPGATimestamp();
  }

  double calculate(double input) {
    double time = frc::Timer::GetFPGATimestamp();
    double dt = time - _lasttime;
    
    mtx.lock();
    _lua.Call("calculate", 1, std::vector<double>{dt > 0.01 ? dt : 0.01, input});
    double output = _lua.PopNumber();
    mtx.unlock();

    _lasttime = time;
    return output;
  }

private:
  MiniLua _lua;
  double _lasttime = 0;
  std::mutex mtx;
};
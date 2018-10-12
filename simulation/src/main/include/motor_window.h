#pragma once

#include "window.h"

class sim_motor_window : public window {
public:
  sim_motor_window(int motor) : window("Motor #" + std::to_string(motor), 250, 250), pwm(motor) {
    on_ready();
  }

  sim_motor_window(const sim_motor_window &other) : sim_motor_window(other.pwm) {}

  void on_ready();
  virtual void render(cv::Mat &img) override;

private:
  int pwm;
  double rots;
  int32_t _cbid;
};
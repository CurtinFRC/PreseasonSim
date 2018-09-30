#pragma once

#include "threaded_window.h"

class sim_motor_window : public threaded_window {
public:
  sim_motor_window(int motor) : threaded_window("Motor #" + std::to_string(motor), 250, 250), pwm(motor) {}

  sim_motor_window(const sim_motor_window &other) : sim_motor_window(other.pwm) {}

  virtual void on_open() override;
  virtual void render(cv::Mat &img) override;
  virtual void on_close() override;

private:
  int pwm;
  double rots;
  int32_t _cbid;
};
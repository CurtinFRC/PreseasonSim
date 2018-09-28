#pragma once

#include "threaded_window.h"

class sim_motor_window : public threaded_window {
public:
  sim_motor_window(int motor) : threaded_window("Motor #" + std::to_string(motor), 250, 250), pwm(motor) {} 

  virtual void render(cv::Mat &img) override;

private:
  int pwm;
  double rots;
};
#pragma once

#include "window.h"

class tank_window : public window {
public:
  tank_window(int left, int right) : window("Tank Drive", 600, 600) {}

  tank_window(const tank_window &other) : tank_window(other.leftPWM, other.rightPWM) {}

  // virtual void on_open() override;
  // virtual void render(cv::Mat &img) override;

private:
  int leftPWM, rightPWM;
};
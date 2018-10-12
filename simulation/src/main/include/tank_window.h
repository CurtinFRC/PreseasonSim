#pragma once

#include "window.h"

class tank_window : public window {
 public:
  tank_window(int left, int right) : _leftPWM(left), _rightPWM(right), window("Tank Drive", 600, 600) {}

  tank_window(const tank_window &other) : tank_window(other._leftPWM, other._rightPWM) {}

  // virtual void on_open() override;
  virtual void render(cv::Mat &img) override;

  void drawRobot(cv::Mat &img, double lspeed, double rspeed);
  void drawBox(cv::Mat &img, cv::Scalar col, int thick, double x1, double y1, double w, double h);

  double linear(double left, double right);
  double angular(double left, double right);

  cv::Point toWorld(double x, double y);

 private:
  int    _leftPWM, _rightPWM;
  double _x = 0, _y = 0;
  double _heading = -3.14 / 2;
};
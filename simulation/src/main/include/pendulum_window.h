#pragma once

#include "window.h"
#include "motor_model.h"

class pendulum_window : public window {
 public:
  pendulum_window(int motorIdx, double length, double angle)
      : _motorPort(motorIdx),
        _pendulum_length(length),
        _home_angle(angle),
        _theta(angle),
        window("Pendulum (Motor " + std::to_string(motorIdx) + ")", 1000, 400) {
          reset();
        }

  pendulum_window(const pendulum_window &other) : pendulum_window(other._motorPort, other._pendulum_length, other._theta) {}

  virtual void render(cv::Mat &img);

  void position_update();
  void physics_update();
  void draw_pendulum(cv::Mat &img);
  void draw_base(cv::Mat &img);
  void draw_graph(cv::Mat &img);

  void reset();

 private:
  int    _motorPort;
  double _pendulum_length;
  double _home_angle;
  double _theta = 0, _dtheta = 0, _position = 0, _velocity = 0, _acceleration = 0;
  double _time = 0;
  cv::Point _origin{ 0, 0 };
  cv::Mat _graph_mat;

  motor_model _motor_model{ 5330 / 16, 2.7, 3.4 * 16, 131 };
  double _spool_radius = 0.0762;  // 6in diam = 3in radius
  double _mass = 50;

  const double _kG     = 9.81;  // gravity, ms^-2
  const double _kScale = 200;   // metre to pixels
  const double _max_time = 3;
};
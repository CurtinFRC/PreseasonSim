#include "pendulum_window.h"

#include <opencv2/imgproc.hpp>
#include "mockdata/PWMData.h"
#include "mockdata/EncoderData.h"

#include <usage.h>

void pendulum_window::render(cv::Mat &img) {
  // double pwm_speed = HALSIM_GetPWMSpeed(_motorPort);
  position_update();
  physics_update();

  _origin = cv::Point{ width() / 2 + (int)(_position * _kScale), 3 * height() / 4 };

  if (_origin.x > width() || _origin.x < 0)
    reset();
  // else if (_theta > 3.1415 / 2.0 || _theta < -3.1415 / 2.0)
  //   reset();
  else {
    draw_graph(img);
    draw_pendulum(img);
    draw_base(img);

    cv::putText(img, window_name(), cv::Point{10, 30}, cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar{127, 127, 127},
                1.5);
    _time += dt();
  }
}

void pendulum_window::draw_pendulum(cv::Mat &img) {
  double    pixel_length = _pendulum_length * _kScale;
  cv::Point tip = _origin + cv::Point{(int)(pixel_length * sin(_theta)), (int)(-pixel_length * cos(_theta))};
  cv::Point tip_ideal = _origin + cv::Point{ 0, (int)(-pixel_length) };

  cv::line(img, _origin, tip_ideal, cv::Scalar{120, 120, 200}, 1);
  cv::line(img, _origin, tip, cv::Scalar{0, 255, 0}, 4);
}

void pendulum_window::draw_base(cv::Mat &img) {
  cv::Point off{(int)(0.25 * _kScale), 0};

  cv::line(img, _origin - off, _origin + off, cv::Scalar{120, 120, 120}, 4);
}

void pendulum_window::draw_graph(cv::Mat &img) {
  int x0 = width() / 20;
  int y0 = height() / 2;
  
  int maxheight = 3 * height() / 4;
  int maxwidth = 9 * width() / 10;

  int x = x0 + static_cast<int>(_time / _max_time * maxwidth);
  int y = y0 + static_cast<int>(_theta / (3.1415 / 3) * maxheight);
  cv::Point dot{x, y};

  if (_time <= _max_time)
    cv::circle(_graph_mat, dot, 2, cv::Scalar{ 120, 120, 120 }, -1);

  _graph_mat.copyTo(img);
  cv::line(img, cv::Point{ x0, y0 }, cv::Point{ x0 + maxwidth, y0 }, cv::Scalar{ 100, 100, 100 }, 1);
}

void pendulum_window::position_update() {
  double speed = HALSIM_GetPWMSpeed(_motorPort);
  double angular_vel = _velocity / (6.28 * _spool_radius);
  double acc = _motor_model.get_acceleration(speed * 12, angular_vel, _spool_radius, _mass);

  _acceleration = acc;
  _velocity += acc * dt();
  _position += _velocity * dt() + 0.5 * _acceleration * dt() * dt();
  // _position += speed * dt();
  // _acceleration = (speed - _velocity) / dt();
  // _velocity = speed;
}

void pendulum_window::physics_update() {
  double theta_dprime = (-_acceleration * cos(_theta) + _kG * sin(_theta)) / _pendulum_length;
  _dtheta += theta_dprime * dt();
  _theta += _dtheta * dt() + 0.5 * theta_dprime * dt() * dt();

  HALSIM_SetEncoderCount(_motorPort, _theta / (2*3.141593) * 1024);
}

void pendulum_window::reset() {
  _theta = _home_angle;
  _dtheta = 0;
  _position = 0;
  _velocity = 0;
  _acceleration = 0;
  _time = 0;
  _graph_mat = cv::Mat::zeros(height(), width(), CV_8UC3);

  usage::pendulum_reset();
}
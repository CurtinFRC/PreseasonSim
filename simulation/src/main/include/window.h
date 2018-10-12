#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <chrono>
#include <iostream>

class window {
public:
  window(std::string name, int width, int height) : 
    _window_name(name), _width(width), _height(height), _image(height, width, CV_8UC3) {}

  ~window() {
    if (_running)
      stop();
    std::cout << "[SIM] WARN! Destructed: " << _window_name << std::endl;
  }

  using clock = std::chrono::high_resolution_clock;

  void start() {
    if (!_running) {
      std::cout << "[SIM] Starting " << _window_name << std::endl;
      _running = true;
      _pending = true;
    }
  }

  void stop() {
    if (_running) {
      std::cout << "[SIM] Stopping " << _window_name << std::endl;
      _running = false;
      _pending = true;
    }
  }

  bool is_running() const {
    return _running;
  }

  std::string window_name() const {
    return _window_name;
  }

  int width() const {
    return _width;
  }

  int height() const {
    return _height;
  }

  virtual void on_open() {}
  virtual void render(cv::Mat &img) {};
  virtual void on_close() {}

  double dt() const {
    return _elapsed;
  }

  void update() {
    if (_pending) {
      if (_running) {
        // Start window
        cv::namedWindow(_window_name.c_str());
        on_open();
      } else {
        // Stop window
        on_close();
        cv::destroyWindow(_window_name.c_str());
      }
      _pending = false;
    }

    if (_running) {
      cv::namedWindow(_window_name.c_str());
      auto now = clock::now();
      if (_elapsed == 0)
        _elapsed = 1.0 / 45.0;
      else
        _elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(now - _last).count();

      _image = cv::Mat::zeros(_image.size(), _image.type());
      render(_image);
      cv::imshow(_window_name.c_str(), _image);
      _last = now;
    }
  }

private:
  std::string _window_name;
  int _width, _height;
  bool _running = false;
  bool _pending = false;
  cv::Mat _image;
  double _elapsed = 0;
  std::chrono::time_point<clock> _last;
};
#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <thread>

class threaded_window {
public:
  threaded_window(std::string name, int width, int height) : 
    _window_name(name), _width(width), _height(height) {}

  ~threaded_window() {
    if (_running)
      stop();
  }

  void start() {
    _running = true;
    _thread = std::thread(&threaded_window::threadfunc, this);
  }

  void stop() {
    _running = false;
    _thread.join();
  }

  bool is_running() const {
    return _running;
  }

  std::string window_name() const {
    return _window_name;
  }

  double framerate() const {
    return _framerate;
  }

  void set_show(bool show) {
    _show = show;
  }

  virtual void on_open() {}
  virtual void render(cv::Mat &img) = 0;
  virtual void on_close() {}

private:
  void threadfunc() {
    cv::namedWindow(_window_name.c_str());
    on_open();
    cv::Mat image(_height, _width, CV_8UC3);
    while (is_running()) {
      image = cv::Mat::zeros(image.size(), image.type());
      render(image);
      if (_show)
        cv::imshow(_window_name.c_str(), image);
      cv::waitKey(static_cast<int>(1000.0 / _framerate));
    }
    cv::destroyWindow(_window_name.c_str());
    on_close();
  }

  std::string _window_name;
  std::thread _thread;
  int _width, _height;
  double _framerate = 45;
  bool _running;
  bool _show = true;
};
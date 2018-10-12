#include "tank_window.h"
#include "usage.h"

#include "mockdata/PWMData.h"

#include <iostream>
#include <opencv2/imgproc.hpp>

static cv::Scalar rightColour{0, 0, 255};
static cv::Scalar leftColour{255, 0, 0};
static cv::Scalar frontColour{0, 255, 0};

void tank_window::render(cv::Mat &img) {
  double left  = -HALSIM_GetPWMSpeed(_leftPWM) * 4;
  double right = HALSIM_GetPWMSpeed(_rightPWM) * 4;

  double ang = angular(left, right);
  double lin = linear(left, right);

  _heading += ang * dt();
  _x += lin * dt() * cos(_heading);
  _y += lin * dt() * sin(_heading);

  drawRobot(img, left, right);
}

void tank_window::drawRobot(cv::Mat &img, double lspeed, double rspeed) {
  cv::circle(img, toWorld(0, 0), 2, cv::Scalar{255, 255, 255}, -1);
  drawBox(img, cv::Scalar{255, 255, 255}, 2, -1, -1, 2, 2);
  drawBox(img, frontColour, 2, 1, -1, 0.05, 2);  // Front

  drawBox(img, leftColour * std::abs(lspeed), 4, -1, -1, 2, 0.1);        // Left fill
  drawBox(img, rightColour * std::abs(rspeed), 4, -1, 1 - 0.2, 2, 0.1);  // Right fill

  drawBox(img, leftColour, 1, -1, -1, 2, 0.2);        // Left Outline
  drawBox(img, rightColour, 1, -1, 1 - 0.2, 2, 0.2);  // Right Outline
}

void tank_window::drawBox(cv::Mat &img, cv::Scalar col, int thick, double x1, double y1, double w, double h) {
  cv::line(img, toWorld(x1, y1), toWorld(x1 + w, y1), col, thick);
  cv::line(img, toWorld(x1 + w, y1), toWorld(x1 + w, y1 + h), col, thick);
  cv::line(img, toWorld(x1 + w, y1 + h), toWorld(x1, y1 + h), col, thick);
  cv::line(img, toWorld(x1, y1 + h), toWorld(x1, y1), col, thick);
}

double tank_window::linear(double left, double right) {
  return (right + left);
}

double tank_window::angular(double left, double right) {
  return -(right - left);
}

cv::Point tank_window::toWorld(double x, double y) {
  cv::Point origin{static_cast<int>(width() / 2.0), static_cast<int>(height() / 2.0)};
  cv::Point robot{static_cast<int>(50 * (_x + x * cos(_heading) - y * sin(_heading))),
                  static_cast<int>(50 * (_y + x * sin(_heading) + y * cos(_heading)))};

  return origin + robot;
}
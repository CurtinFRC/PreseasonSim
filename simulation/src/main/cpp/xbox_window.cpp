#include "xbox_window.h"

#include <opencv2/imgproc.hpp>

static inline double convAxis(int val) {
  // Deadzone
  if (val > 480 && val < 520) return 0.0;

  return static_cast<double>(val) / 500 - 1;
}

static bool dragging = false;

static void clickCallback(int event, int x, int y, int flags, void *data) {
  sim_xbox_window *ptr = static_cast<sim_xbox_window *>(data);
  if (event == CV_EVENT_LBUTTONDOWN) {
    ptr->on_left_click(x, y);
    dragging = true;
  } else if (event == CV_EVENT_LBUTTONUP)
    dragging = false;
  else if (event == CV_EVENT_RBUTTONDOWN)
    ptr->on_right_click(x, y);
  else if (event == CV_EVENT_MOUSEMOVE && dragging)
    ptr->on_left_click(x, y);
}

void sim_xbox_window::on_open() {
  cv::setMouseCallback(window_name().c_str(), clickCallback, (void *)this);
}
void sim_xbox_window::render(cv::Mat &img) {
  cv::Scalar outer_colour{ 255, 255, 255 };

  double ir = 5;
  cv::Point il_off{ static_cast<int>(r * axes.axes[0]), static_cast<int>(r * axes.axes[1]) };
  cv::Point ir_off{ static_cast<int>(r * axes.axes[4]), static_cast<int>(r * axes.axes[5]) };
  cv::Scalar inner_colour{ 50, 50, 255 }, line_colour{ 100, 100, 100 };

  cv::line(img, cl - cv::Point{(int)r, 0}, cl + cv::Point{(int)r, 0}, line_colour);
  cv::line(img, cl - cv::Point{0, (int)r}, cl + cv::Point{0, (int)r}, line_colour);
  cv::circle(img, cl, r, outer_colour, 3);
  cv::circle(img, cl + il_off, ir, inner_colour, CV_FILLED);

  cv::line(img, cr - cv::Point{(int)r, 0}, cr + cv::Point{(int)r, 0}, line_colour);
  cv::line(img, cr - cv::Point{0, (int)r}, cr + cv::Point{0, (int)r}, line_colour);
  cv::circle(img, cr, r, outer_colour, 3);
  cv::circle(img, cr + ir_off, ir, inner_colour, CV_FILLED);

  cv::putText(img, "Xbox Controller", cv::Point{ 10, 30 }, CV_FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar{ 127, 127, 127 }, 1.5);
  HALSIM_SetJoystickAxes(0, &axes);
}

bool sim_xbox_window::inside(cv::Point center, double radius, int x, int y, double *off_x, double *off_y) {
  cv::Point offset = cv::Point{x, y} - center;
  if (off_x != nullptr)
    *off_x = static_cast<double>(offset.x) / radius;
  if (off_y != nullptr)
    *off_y = static_cast<double>(offset.y) / radius;

  return std::sqrt(offset.x * offset.x + offset.y * offset.y) <= radius;
}

void sim_xbox_window::on_left_click(int x, int y) {
  double off_x, off_y;
  if (inside(cl, r, x, y, &off_x, &off_y)) {
    // Left joystick
    axes.axes[0] = off_x;
    axes.axes[1] = off_y;
  } else if (inside(cr, r, x, y, &off_x, &off_y)) {
    // Right joystick
    axes.axes[4] = off_x;
    axes.axes[5] = off_y;
  }
}

void sim_xbox_window::on_right_click(int x, int y) {
  if (inside(cl, r, x, y, nullptr, nullptr)) {
    // Left joystick
    axes.axes[0] = 0;
    axes.axes[1] = 0;
  } else if (inside(cr, r, x, y, nullptr, nullptr)) {
    // Right joystick
    axes.axes[4] = 0;
    axes.axes[5] = 0;
  }
}
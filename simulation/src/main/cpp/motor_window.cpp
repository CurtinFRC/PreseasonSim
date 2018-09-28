#include <opencv2/imgproc.hpp>

#include "motor_window.h"
#include "mockdata/PWMData.h"

void sim_motor_window::render(cv::Mat &img) {
  double pwm_speed = HALSIM_GetPWMSpeed(pwm);
  double delta_rot = pwm_speed * 4 * (static_cast<double>(framerate()) / 1000);
  rots += delta_rot;

  double rad = 85;
  cv::Point centre{ 125, 125 };
  cv::Point endOffset{ (int)(rad*cos(rots*6.28)), (int)(rad*sin(rots*6.28)) };
  cv::Scalar colour{ 255, 255, 255 };

  cv::circle(img, centre, rad, colour, 4);
  cv::line(img, centre, centre + endOffset, colour, 3);
  cv::putText(img, window_name(), cv::Point{ 10, 30 }, cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar{ 127, 127, 127 }, 1.5);
  cv::putText(img, std::to_string(pwm_speed), cv::Point{ 10, 240 }, cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar{ 127, 127, 127 }, 1.5);
}
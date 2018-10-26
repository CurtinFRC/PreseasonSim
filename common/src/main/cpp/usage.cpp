#include "usage.h"

#include <algorithm>
#include <vector>

// DRIVETRAIN

static std::vector<std::pair<int, int>>      _drivetrains;
static std::vector<std::function<void(int)>> _drivetrain_callbacks;

void usage::drivetrain(int left, int right) {
  _drivetrains.emplace_back(left, right);

  std::for_each(_drivetrain_callbacks.begin(), _drivetrain_callbacks.end(),
                [](auto it) { it(_drivetrains.size() - 1); });
}

void usage::on_drivetrain(std::function<void(int)> cb) {
  _drivetrain_callbacks.push_back(cb);
}

std::pair<int, int> usage::get_drivetrain(int idx) {
  return _drivetrains[idx];
}

// XBOX

static std::vector<std::function<void(int,bool)>> _xbox_callbacks;

void usage::xbox(int port, bool enable) {
  std::for_each(_xbox_callbacks.begin(), _xbox_callbacks.end(), [&](auto it) { it(port, enable); });
}

void usage::on_xbox(std::function<void(int,bool)> cb) {
  _xbox_callbacks.push_back(cb);
}
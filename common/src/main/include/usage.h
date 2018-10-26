#pragma once

#include <functional>
#include <utility>

namespace usage {
void                on_drivetrain(std::function<void(int)> callback);
void                drivetrain(int leftPWM, int rightPWM);
std::pair<int, int> get_drivetrain(int idx);

void on_xbox(std::function<void(int, bool)> callback);
void xbox(int port=0, bool enable=true);

void on_pendulum(std::function<void(int,double,double)> callback);
void on_pendulum_reset(std::function<void()> callback);
void pendulum(int port, double len=1, double angle=0);
void pendulum_reset();
}  // namespace usage
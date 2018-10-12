#pragma once

#include <functional>
#include <utility>

namespace usage {
    void drivetrain(int leftPWM, int rightPWM);

    void on_drivetrain(std::function<void(int)> callback);
    std::pair<int, int> get_drivetrain(int idx);
}
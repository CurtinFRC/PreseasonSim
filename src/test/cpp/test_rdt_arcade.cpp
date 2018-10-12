#include <gtest/gtest.h>
#include <mockdata/DriverStationData.h>
#include <mockdata/PWMData.h>

#include "Robot.h"

#ifdef SESSION_2_ACT_2
class RDT : public ::testing::Test {
 protected:
  void SetUp() override {
    robot.RobotInit();
  }

  void set_joys(double lx, double ly, double rx, double ry) {
    HAL_JoystickAxes axes{6};
    axes.count = 6;

    axes.axes[0] = lx;
    axes.axes[1] = ly;

    axes.axes[4] = rx;
    axes.axes[5] = ry;

    HALSIM_SetJoystickAxes(0, &axes);

    robot.RobotPeriodic();
  }

  void set_all_joys(double x, double y) {
    set_joys(x, y, x, y);
  }

  double left() {
    return -HALSIM_GetPWMSpeed(0);
  }

  double right() {
    return HALSIM_GetPWMSpeed(1);
  }

  Robot robot;
};

TEST_F(RDT, NoThrottle) {
  set_all_joys(0, 0);

  ASSERT_DOUBLE_EQ(0, left());
  ASSERT_DOUBLE_EQ(0, right());
}

TEST_F(RDT, Forward) {
  set_all_joys(0, -0.5);

  ASSERT_DOUBLE_EQ(left(), right());
  ASSERT_GT(left(), 0);
}

TEST_F(RDT, Reverse) {
  set_all_joys(0, 0.5);

  ASSERT_DOUBLE_EQ(left(), right());
  ASSERT_LT(left(), 0);
}

TEST_F(RDT, TurnsRight) {
  set_all_joys(0.5, -1.0);

  ASSERT_GT(left(), right());
  ASSERT_GT(right(), 0);
}

TEST_F(RDT, TurnsLeft) {
  set_all_joys(-0.5, -1.0);

  ASSERT_GT(right(), left());
  ASSERT_GT(left(), 0);
}

TEST_F(RDT, TurnOnSpotClockwise) {
  set_all_joys(1.0, 0);
  ASSERT_DOUBLE_EQ(right(), -left());
  ASSERT_GT(left(), right());
}

TEST_F(RDT, TurnOnSpotCounterClockwise) {
  set_all_joys(-1.0, 0);
  ASSERT_DOUBLE_EQ(-right(), left());
  ASSERT_GT(right(), left());
}
#endif
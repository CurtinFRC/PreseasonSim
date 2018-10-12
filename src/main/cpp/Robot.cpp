#include "Robot.h"

#include <stack.h>

#include <iostream>

void Robot::RobotInit() {
  std::cout << sizeof(void*) << std::endl;
  std::string data = "Hello World";
  std::cout << data << std::endl;
  stack::print_bytes();
  stack::print_calls();
}

void Robot::RobotPeriodic() {
}
#include "sim_main.h"
#include "motor_window.h"
#include "xbox_window.h"

#include "mockdata/PWMData.h"
#include "hal/HAL.h"

#include <iostream>

static void pwm_init_callback(const char* name, void* param, const struct HAL_Value* value) {
  int pwm = (int)param;
  // You should _never_ allocate a new object without deleting / freeing it at some point, but 
  // we purposefully want these to outlive the scope of run() since they own threads, and we want
  // them to run forever until the simulation is ended, at which point the OS picks up the mess.
  (new sim_motor_window(pwm))->start();
}

void sim_main::run() {
  std::cout << "Simulation Started" << std::endl;
  HAL_Initialize(500, 0);

  for (int i = 0; i < 10; i++)
    HALSIM_RegisterPWMInitializedCallback(i, &pwm_init_callback, (void *)i, false);

  (new sim_xbox_window())->start();
  std::cout << "Simulation Initialized!" << std::endl;
}
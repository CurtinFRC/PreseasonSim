#include "stack.h"

#include <inttypes.h>
#include <iostream>

void stack::print_bytes(int depth) {
  void *p     = nullptr;
  char *addr  = (char *)(void *)&p;
  int   width = 16;

  std::cout << std::endl;
  std::cout << "====== SYSTEM STACK ======" << std::endl;

  for (int i = 0; i < depth; i++) {
    for (int j = 0; j < width; j++) {
      char *target = addr + (j + width * i);
      printf(" %c", *target);
    }
    std::cout << std::endl;
  }

  std::cout << "========== END ==========" << std::endl;
  std::cout << std::endl;
}

void stack::print_calls() {
  std::vector<std::string> bt = stack::backtrace_get(0);
  std::cout << std::endl;
  std::cout << "====== CALL STACK ======" << std::endl;

  for (auto it = bt.begin(); it != bt.end(); it++) {
    std::cout << *it << std::endl;
  }

  std::cout << "========== END ==========" << std::endl;
  std::cout << std::endl;
}
#pragma once

#include <string>
#include <vector>

namespace stack {
void                     print_bytes(int depth = 16);
void                     print_calls();
std::vector<std::string> backtrace_get(int skip);
}  // namespace stack
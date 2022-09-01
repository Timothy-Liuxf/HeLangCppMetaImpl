#include <helang-meta/helang-meta.hpp>

using namespace helang::meta;
using namespace helang::meta::literals;

#include <iostream>

int main() {
  u8 a = 1_ | 2_ | 3_;
  u8 b = a[1_ | 2_];
  std::cout << b << std::endl;
  return 0;
}

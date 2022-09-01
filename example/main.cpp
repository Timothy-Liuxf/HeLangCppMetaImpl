// This file is part of the project HelangCppMetaImpl.
//
// Copyright (C) 2022 Timothy Liu
//
// MIT License

#include <helang-meta/helang-meta-core.hpp>
#include <helang-meta/helang-meta.hpp>

using namespace helang::meta;
using namespace helang::meta::literals;

#include <iostream>

int main() {
  {
    u8 a = 1_ | 2_ | 3_;
    print(a);  // 1_ | 2_ | 3_
    endl(std::cout);
    println(a[1_]);  // 1_
  }
  {
    u8 a = 1_ | 2_ | 3_;
    u8 b = a[2_ | 3_];
    println(b);  // 2_ | 3_
  }
  {
    sprintln(72_ | 101_ | 108_ | 108_ | 111_ | 44_ | 32_ | 76_ | 105_ | 116_ |
             97_ | 110_ | 103_ | 46_);
  }
  return 0;
}

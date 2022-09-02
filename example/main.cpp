// This file is part of the project HelangCppMetaImpl.
//
// Copyright (C) 2022 Timothy Liu
//
// MIT License

#include <helang-meta/helang-meta-core.hpp>
#include <helang-meta/helang-meta.hpp>

using namespace helang::meta;
using namespace helang::meta::literals;

#include <cstdio>
#include <iostream>

int main() {
  {
    u8 a = 1_ | 2_ | 3_;
    print(a);         // 1_ | 2_ | 3_
    endl(std::cout);  // Newline
    println(a[1_]);   // 1_
  }
  {
    u8 a = 1_ | 2_ | 3_;
    u8 b = a[2_ | 3_];
    println(b);  // 2_ | 3_
  }
  {
    u8 a = 1_ | 2_ | 3_;
    println(a[0_]);  // 1_ | 2_ | 3_
  }
  {
    sprintln(72_ | 101_ | 108_ | 108_ | 111_ | 44_ | 32_ | 76_ | 105_ | 116_ |
             97_ | 110_ | 103_ | 46_);  // Hello, Litang.
  }
  {
    u8 a = 888_ | 888_ | 888_ | 888_ | 888_ | 888_;
    u8 b = a[1_ | 2_ | 5_].replace<0>();  // 0_ | 0_ | 888_ | 888_ | 0_ | 888_
    println(b);
  }
  {
    u8 a = 1_ | 2_ | 3_;
    println(a[0_]);
    println(a[0_].replace<888>());
  }
  {
    u8 a = 1_ | 2_ | 3_;
    auto arr = a.to_array();
    for (auto num : arr.array) {
      std::printf("%d\n", num);
    }
  }
  {
    u8 a = 1_;
    u8 b = 1_ | 2_ | 3_;
    u8 c = 2_ | 4_ | 6_;
    [[maybe_unused]] u8 d = 5_ | 9_;
    println(a + b);  // 2_ | 3_ | 4_
    println(b + c);  // 3_ | 6_ | 9_
    println(b + a);  // 2_ | 3_ | 4_
    println(b - c);  // -1_ | -2_ | -3_
    println(a - b);  // 0_ | -1_ | -2_
    // println(b + d);  // ERROR
  }
  {
    u8 a = 1_ | 2_;
    u8 b = 3_ | 4_ | 5_;
    u8 c = 3_ | 6_ | 9_;

    println(a * b);  // 1_ * 3_ + 2_ * 4_ + 0_ * 5_ = 11_
    println(b * c);  // 3_ * 3_ + 4_ * 6_ + 5_ * 9_ = 78_
  }
  return 0;
}

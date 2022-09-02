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

static void test0() {
  u8 a = 1_ | 2_ | 3_;
  print(a);         // Output: 1_ | 2_ | 3_
  endl(std::cout);  // Output: Newline
  println(a[1_]);   // Output: 1_
  // a = 4_ | 5_ | 6_;  // Compile ERROR
}

static void test1() {
  u8 a = 1_ | 2_ | 3_;
  u8 b = a[2_ | 3_];  // b: 2_ | 3_
  println(b);         // Output: 2_ | 3_
  // print(a[4_]);       // Compile ERROR
}

static void test2() {
  u8 a = 1_ | 2_ | 3_;
  println(a[0_]);  // Output:  1_ | 2_ | 3_
}

static void test3() {
  sprintln(72_ | 101_ | 108_ | 108_ | 111_ | 44_ | 32_ | 76_ | 105_ | 116_ |
           97_ | 110_ | 103_ | 46_);  // Output: Hello, Litang.
}

static void test4() {
  u8 a = 888_ | 888_ | 888_ | 888_ | 888_ | 888_;
  u8 b = a[1_ | 2_ | 5_].replace<0>();  // b = 0_ | 0_ | 888_ | 888_ | 0_ | 888_
  println(b);                           // Output: the value of b
}

static void test5() {
  u8 a = 1_ | 2_ | 3_;
  println(a[0_]);                 // Output: 1_ | 2_ | 3_
  println(a[0_].replace<888>());  // Output: 888_ | 888_ | 888_
  u8 b = 5_dian;                  // b = 0_ | 0_ | 0_ | 0_ | 0_
  println(b);                     // Output: the value of b
}

static void test6() {
  u8 a = 1_ | 2_ | 3_;
  auto cyber = a.to_array();
  for (auto pm : cyber.array) {
    std::cout << pm << ' ';
  }
  endl(std::cout);
  // Output: 1 2 3
}

static void test7() {
  u8 a = 1_;
  u8 b = 1_ | 2_ | 3_;
  u8 c = 2_ | 4_ | 6_;
  [[maybe_unused]] u8 d = 5_ | 9_;
  println(a + b);    // Output: 2_ | 3_ | 4_
  println(b + c);    // Output: 3_ | 6_ | 9_
  println(b + a);    // Output: 2_ | 3_ | 4_
  println(b - c);    // Output: -1_ | -2_ | -3_
  println(a - b);    // Output: 0_ | -1_ | -2_
  println(+a + -b);  // Output: 0_ | -1_ | -2_
  // println(b + d);    // Compile ERROR
}

static void test8() {
  u8 a = 1_;
  u8 b = 1_ | 2_ | 3_;
  u8 c = 2_ | 4_ | 6_;
  [[maybe_unused]] u8 d = 5_ | 9_;
  println(a + b);  // Output: 2_ | 3_ | 4_
  println(b + c);  // Output: 3_ | 6_ | 9_
  println(b + a);  // Output: 2_ | 3_ | 4_
  println(b - c);  // Output: -1_ | -2_ | -3_
  println(a - b);  // Output: 0_ | -1_ | -2_
  // println(b + d);  // Compile ERROR
}

static void test9() {
  u8 a = 1_ | 2_;
  u8 b = 3_ | 4_ | 5_;
  u8 c = 3_ | 6_ | 9_;

  println(a * b);          // 1_ * 3_ + 2_ * 4_ + 0_ * 5_ = 11_
  println(b * c);          // 3_ * 3_ + 4_ * 6_ + 5_ * 9_ = 78_
  println(a * b | b * c);  // Output: 11_ | 78_
}

[[maybe_unused]] static void forceConDemo() {
  u8 forceCon =
      68_dian [1_ | 2_ | 6_ | 7_ | 11_ | 52_ | 57_ | 58_ | 65_].replace<10>();
  println(forceCon);
}

#undef TEST
#define TEST(n)                                          \
  do {                                                   \
    std::cout << "========== TEST" #n " ==========\n\n"; \
    test##n();                                           \
    endl(std::cout);                                     \
  } while (0)

int main() {
  endl(std::cout);
  TEST(0);
  TEST(1);
  TEST(2);
  TEST(3);
  TEST(4);
  TEST(5);
  TEST(6);
  TEST(7);
  TEST(8);
  TEST(9);
  return 0;
}

// This file is part of the project HelangCppMetaImpl.
//
// Copyright (C) 2022 Timothy Liu
//
// MIT License

#include <helang-meta/helang-meta-core.hpp>

using namespace helang::meta;
using namespace helang::meta::literals;

constexpr u8 a = 1_ | 2_ | 3_ | 4_ | 5_;
constexpr u8 b = a[1_ | 2_ | 3_];
constexpr u8 c = a | a[0_] | a | b;
auto arr_wrap = (a | b | c).to_array();

// This file is part of the project HelangCppMetaImpl.
//
// Copyright (C) 2022 Timothy Liu
//
// MIT License

#ifndef HELANG_META_HPP_
#define HELANG_META_HPP_

#include <iostream>

#include "helang-meta-core.hpp"

HELANG_META_NAMESPACE_BEGIN

template <int... vals>
inline void print(u8<vals...> u8vec) {
  std::cout << u8vec.to_string();
}

template <int... vals>
inline void wprint(u8<vals...> u8vec) {
  std::wcout << u8vec.to_wstring();
}

template <int... vals>
inline void println(u8<vals...> u8vec) {
  print(u8vec);
  endl(std::cout);
}

template <int... vals>
inline void wprintln(u8<vals...> u8vec) {
  wprint(u8vec);
  endl(std::wcout);
}

template <int... vals>
inline void sprint(u8<vals...> u8vec) {
  std::cout << u8vec.to_str_string();
}

template <int... vals>
inline void swprint(u8<vals...> u8vec) {
  std::wcout << u8vec.to_str_wstring();
}

template <int... vals>
inline void sprintln(u8<vals...> u8vec) {
  sprint(u8vec);
  endl(std::cout);
}

template <int... vals>
inline void swprintln(u8<vals...> u8vec) {
  swprint(u8vec);
  endl(std::wcout);
}

namespace detail {

template <typename u8idx, typename u8val>
inline void print(u8_indexer<u8idx, u8val> u8vec) {
  std::cout << u8vec.to_u8();
}

template <typename u8idx, typename u8val>
inline void wprint(u8_indexer<u8idx, u8val> u8vec) {
  std::wcout << u8vec.to_u8();
}

template <typename u8idx, typename u8val>
inline void println(u8_indexer<u8idx, u8val> u8vec) {
  print(u8vec);
  endl(std::cout);
}

template <typename u8idx, typename u8val>
inline void wprintln(u8_indexer<u8idx, u8val> u8vec) {
  wprint(u8vec);
  endl(std::wcout);
}

template <typename u8idx, typename u8val>
inline void sprint(u8_indexer<u8idx, u8val> u8vec) {
  sprint(u8vec.to_u8());
}

template <typename u8idx, typename u8val>
inline void swprint(u8_indexer<u8idx, u8val> u8vec) {
  swprint(u8vec.to_u8());
}

template <typename u8idx, typename u8val>
inline void sprintln(u8_indexer<u8idx, u8val> u8vec) {
  sprint(u8vec);
  endl(std::cout);
}

template <typename u8idx, typename u8val>
inline void swprintln(u8_indexer<u8idx, u8val> u8vec) {
  swprint(u8vec);
  endl(std::wcout);
}

using detail::print;
using detail::println;
using detail::wprint;
using detail::wprintln;

using detail::sprint;
using detail::sprintln;
using detail::swprint;
using detail::swprintln;

}  // namespace detail

HELANG_META_NAMESPACE_END

#endif  // !HELANG_META_HPP_

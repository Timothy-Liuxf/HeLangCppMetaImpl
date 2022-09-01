// This file is part of the project HelangCppMetaImpl.
//
// Copyright (C) 2022 Timothy Liu
//
// MIT License

#ifndef HELANG_META_CORE_HPP_
#error The header <helang-meta-utils.ipp> cannot be included directly. Please include <helang-meta.hpp> instead.
#endif  // !HELANG_META_CORE_HPP_

#ifndef HELANG_META_UTILS_IPP_
#define HELANG_META_UTILS_IPP_

// C++ Standard

#ifdef _MSC_VER

#if _MSVC_LANG < 201703L
#error Helang is an advanced language in another universe, which do not support too low C++ standards. Please use C++17 or higher.
#endif

#define HELANG_META_HAS_CXX98
#define HELANG_META_HAS_CXX03
#define HELANG_META_HAS_CXX11
#define HELANG_META_HAS_CXX14
#define HELANG_META_HAS_CXX17

#if _MSVC_LANG >= 202002L
#define HELANG_META_HAS_CXX20
#endif

#else  // _MSC_VER

#if __cplusplus < 201703L
#error Helang is an advanced language in another universe, which do not support too low C++ standards. Please use C++17 or higher.
#endif

#define HELANG_META_HAS_CXX98
#define HELANG_META_HAS_CXX03
#define HELANG_META_HAS_CXX11
#define HELANG_META_HAS_CXX14
#define HELANG_META_HAS_CXX17

#if __cplusplus >= 202002L
#define HELANG_META_HAS_CXX20
#endif

#endif  // _MSC_VER

// Keywords

#if defined(HELANG_META_HAS_CXX20)
#define HELANG_META_CONSTEVAL consteval
#elif defined(HELANG_META_HAS_CXX17)
#define HELANG_META_CONSTEVAL constexpr
#endif

// namespaces

#define HELANG_META_NAMESPACE_BEGIN \
  namespace helang {                \
  namespace meta {

#define HELANG_META_NAMESPACE_END \
  }                               \
  }

#define HELANG_META_NAMESPACE ::helang::meta::

#endif  // !HELANG_META_UTILS_IPP_

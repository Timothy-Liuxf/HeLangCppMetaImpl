// This file is part of the project HelangCppMetaImpl.
//
// Copyright (C) 2022 Timothy Liu
//
// MIT License

#ifndef HELANG_META_CORE_HPP_
#define HELANG_META_CORE_HPP_

#include <cstddef>
#include <string>
#include <type_traits>
#include <utility>

#include "helang-meta-utils.ipp"

HELANG_META_NAMESPACE_BEGIN

namespace detail {

template <typename indexer, typename u8vec>
struct u8_indexer;

template <int... vals>
struct u8_impl {
  constexpr u8_impl() noexcept = default;

  template <int... val>
  [[nodiscard]] HELANG_META_CONSTEVAL auto operator|(
      u8_impl<val...>) const noexcept;

  template <int... val>
  [[nodiscard]] HELANG_META_CONSTEVAL auto operator[](
      u8_impl<val...>) const noexcept;
};

}  // namespace detail

template <int... vals>
struct u8 : detail::u8_impl<vals...> {
  static_assert(std::is_trivial_v<detail::u8_impl<vals...>>,
                "As a meta-universe language, u8 in helang must be trivial.");

  using base_t = detail::u8_impl<vals...>;

  using base_t::u8_impl;
  template <int... idxs, int... origin_vals>
  constexpr u8(
      const detail::u8_indexer<detail::u8_impl<idxs...>,
                               detail::u8_impl<origin_vals...>>&) noexcept;

  using base_t::operator|;
  using base_t::operator[];

  [[nodiscard]] std::string to_string() const {
    if constexpr (sizeof...(vals) == 0) {
      return {};
    } else {
      int nums[] = {vals...};
      std::string res;
      for (auto itr = std::begin(nums); itr != std::end(nums) - 1; ++itr) {
        res += std::to_string(*itr) + "_ | ";
      }
      res += std::to_string(*(std::end(nums) - 1)) + '_';
      return res;
    }
  }

  [[nodiscard]] std::wstring to_wstring() const {
    if constexpr (sizeof...(vals) == 0) {
      return {};
    } else {
      int nums[] = {vals...};
      std::wstring res;
      for (auto itr = std::begin(nums); itr != std::end(nums) - 1; ++itr) {
        res += std::to_wstring(*itr) + L"_ | ";
      }
      res += std::to_wstring(*(std::end(nums) - 1)) + L'_';
      return res;
    }
  }

 private:
  template <typename CharT>
  [[nodiscard]] std::basic_string<CharT> to_str_basic_string() const {
    if constexpr (sizeof...(vals) == 0) {
      return {};
    } else {
      return {
          static_cast<typename std::basic_string<CharT>::value_type>(vals)...};
    }
  }

 public:
  [[nodiscard]] std::string to_str_string() const {
    return to_str_basic_string<std::string::value_type>();
  }

  [[nodiscard]] std::wstring to_str_wstring() const {
    return to_str_basic_string<std::wstring::value_type>();
  }
};

template <int... vals>
u8(const u8<vals...>&) -> u8<vals...>;

namespace literals {

namespace detail {

template <int, char...>
struct charseq_to_int_impl;

template <int val>
struct charseq_to_int_impl<val> : std::integral_constant<int, val> {};

template <int val, char ch, char... chs>
struct charseq_to_int_impl<val, ch, chs...>
    : charseq_to_int_impl<val * 10 + (ch - '0'), chs...> {
  static_assert(ch >= '0' && ch <= '9',
                "The characters in a u8 literal must be digits!");
};

template <char... chs>
struct charseq_to_int : charseq_to_int_impl<0, chs...> {};
}  // namespace detail

template <char... chs>
HELANG_META_CONSTEVAL u8<detail::charseq_to_int<chs...>::value>
operator""_() noexcept {
  return {};
}
}  // namespace literals

namespace detail {

// Join two u8s

template <typename, typename>
struct join_u8;

template <int... left_vals, int... right_vals>
struct join_u8<u8_impl<left_vals...>, u8_impl<right_vals...>>
    : std::enable_if<true, u8_impl<left_vals..., right_vals...>> {};

// Append a number to a u8

template <typename, int>
struct append_u8;

template <int... vals, int val>
struct append_u8<u8_impl<vals...>, val>
    : std::enable_if<true, u8_impl<vals..., val>> {};

// Add a number onto a u8

template <typename, typename, int>
struct addnum_u8_impl;

template <int... added, int first_unadded, int... unadded, int addnum>
struct addnum_u8_impl<u8_impl<added...>, u8_impl<first_unadded, unadded...>,
                      addnum>
    : addnum_u8_impl<u8_impl<added..., first_unadded + addnum>,
                     u8_impl<unadded...>, addnum> {};

template <int... added, int addnum>
struct addnum_u8_impl<u8_impl<added...>, u8_impl<>, addnum>
    : std::enable_if<true, u8_impl<added...>> {};

template <typename, int>
struct addnum_u8;

template <int... vals, int val>
struct addnum_u8<u8_impl<vals...>, val>
    : addnum_u8_impl<u8_impl<>, u8_impl<vals...>, val> {};

template <typename>
struct to_u8;

template <int... vals>
struct to_u8<u8_impl<vals...>> : std::enable_if<true, u8<vals...>> {};

// Core operation: operator|

template <int... left_vals>
template <int... right_vals>
HELANG_META_CONSTEVAL auto u8_impl<left_vals...>::operator|(
    u8_impl<right_vals...> right) const noexcept {
  return typename to_u8<typename join_u8<std::decay_t<decltype(*this)>,
                                         decltype(right)>::type>::type{};
}

// Indexer: operator[]

template <typename u8vec, int idx>
struct u8_at_idx;

template <int first_val, int... vals, int idx>
struct u8_at_idx<u8_impl<first_val, vals...>, idx>
    : u8_at_idx<u8_impl<vals...>, idx - 1> {
  static_assert(idx > 1, "Indexes in multi_indexer must be at least 1!");
};

template <int first_val, int... vals>
struct u8_at_idx<u8_impl<first_val, vals...>, 1>
    : std::integral_constant<int, first_val> {};

template <typename u8idxs, typename u8vals>
struct indexer_to_u8;

template <int... idxs, int... vals>
struct indexer_to_u8<u8_impl<idxs...>, u8_impl<vals...>>
    : std::enable_if<true, u8<u8_at_idx<u8_impl<vals...>, idxs>::value...>> {};

template <int... vals>
struct indexer_to_u8<u8_impl<0>, u8_impl<vals...>>
    : std::enable_if<true, u8<vals...>> {};

template <int... idxs, int... vals>
struct u8_indexer<u8_impl<idxs...>, u8_impl<vals...>> {
  friend struct u8_impl<vals...>;

  HELANG_META_CONSTEVAL explicit operator auto() const noexcept {
    return to_u8();
  }
  HELANG_META_CONSTEVAL auto to_u8() const noexcept {
    return typename indexer_to_u8<u8_impl<idxs...>, u8_impl<vals...>>::type{};
  }

  std::string to_string() const { return to_u8().to_string(); }
  std::string to_wstring() const { return to_u8().to_wstring(); }

  std::string to_str_string() const { return to_u8().to_str_string(); }
  std::wstring to_str_wstring() const { return to_u8().to_str_wstring(); }

 private:
  constexpr u8_indexer() noexcept = default;
};

template <int... vals>
template <int... idxs>
HELANG_META_CONSTEVAL auto u8_impl<vals...>::operator[](
    u8_impl<idxs...> idx) const noexcept {
  return u8_indexer<decltype(idx), std::decay_t<decltype(*this)>>{};
}

}  // namespace detail

template <int... vals>
template <int... idxs, int... origin_vals>
constexpr u8<vals...>::u8(
    const detail::u8_indexer<detail::u8_impl<idxs...>,
                             detail::u8_impl<origin_vals...>>&) noexcept {}

template <int... idxs, int... origin_vals>
u8(const detail::u8_indexer<detail::u8_impl<idxs...>,
                            detail::u8_impl<origin_vals...>>&)
    -> u8<detail::u8_at_idx<detail::u8_impl<origin_vals...>, idxs>::value...>;

template <typename Ostream, int... vals>
inline Ostream& operator<<(Ostream& out, const u8<vals...>& u8vec) {
  out << u8vec.to_string();
  return out;
}

HELANG_META_NAMESPACE_END

#endif  // !HELANG_META_CORE_HPP_

/*
  SDLXX - Modern C++ wrapper for Simple DirectMedia Layer
  Copyright (C) 2019-2021 Egor Makarenko <egormkn@yandex.ru>

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgement in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 * \file
 * \brief Header for the BitMask template that represents a bit mask of enumeration values.
 */

#ifndef SDLXX_CORE_UTILS_BITMASK_H
#define SDLXX_CORE_UTILS_BITMASK_H

#include <functional>
#include <initializer_list>
#include <numeric>
#include <type_traits>

namespace sdlxx::core {

/**
 * A helper structure to enable overloaded operators
 * See https://blog.bitwigglers.org/using-enum-classes-as-type-safe-bitmasks/
 */
template <typename E>
struct BitMaskOperators : std::false_type {};

template <typename E>
struct BitMask {
  using ValueType = std::underlying_type_t<E>;

  ValueType value{};

  constexpr BitMask() = default;

  constexpr BitMask(E enum_value) : value(static_cast<ValueType>(enum_value)) {}  // NOLINT

  constexpr explicit BitMask(ValueType new_value) : value(new_value) {}

  constexpr BitMask(const std::initializer_list<E>& list) {
    return std::accumulate(std::cbegin(list), std::cend(list), static_cast<E>(0), std::bit_or<>{});
  }

  constexpr BitMask<E> operator|(E enum_value) const {
    return BitMask<E>{value | static_cast<ValueType>(enum_value)};
  }

  constexpr BitMask<E> operator&(E enum_value) const {
    return BitMask<E>{value & static_cast<ValueType>(enum_value)};
  }

  constexpr BitMask<E> operator^(E enum_value) const {
    return BitMask<E>{value ^ static_cast<ValueType>(enum_value)};
  }

  constexpr bool IsSet(E enum_value) const {
    return (value & static_cast<ValueType>(enum_value)) == static_cast<ValueType>(enum_value);
  }
};

template <typename E>
constexpr typename std::enable_if<BitMaskOperators<E>::value, BitMask<E>>::type operator|(E lhs,
                                                                                          E rhs) {
  using ValueType = std::underlying_type_t<E>;
  return BitMask<E>{static_cast<ValueType>(lhs) | static_cast<ValueType>(rhs)};
}

template <typename E>
constexpr typename std::enable_if<BitMaskOperators<E>::value, BitMask<E>>::type operator&(E lhs,
                                                                                          E rhs) {
  using ValueType = std::underlying_type_t<E>;
  return BitMask<E>{static_cast<ValueType>(lhs) & static_cast<ValueType>(rhs)};
}

template <typename E>
constexpr typename std::enable_if<BitMaskOperators<E>::value, BitMask<E>>::type operator^(E lhs,
                                                                                          E rhs) {
  using ValueType = std::underlying_type_t<E>;
  return BitMask<E>{static_cast<ValueType>(lhs) ^ static_cast<ValueType>(rhs)};
}

template <typename E>
constexpr typename std::enable_if<BitMaskOperators<E>::value, BitMask<E>>::type operator~(E lhs) {
  using ValueType = std::underlying_type_t<E>;
  return BitMask<E>{~static_cast<ValueType>(lhs)};
}

}  // namespace sdlxx::core

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define ENABLE_BITMASK_OPERATORS(e) \
  template <>                       \
  struct sdlxx::core::BitMaskOperators<e> : std::true_type {};

#endif  // SDLXX_CORE_UTILS_BITMASK_H

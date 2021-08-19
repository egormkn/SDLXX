/*!
  @file relops.hpp
  Simple DirectMedia Layer C++ Bindings
  @copyright (C) 2016 Tristan Brindle <t.c.brindle@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SDLXX_DETAIL_RELOPS_HPP
#define SDLXX_DETAIL_RELOPS_HPP

#include <type_traits>

namespace sdl {
namespace detail {

    // The void_t trick
    template <typename... T>
    using void_t = void;

    template <typename Func, typename Ret, typename... Args>
    using check_signature_t = std::is_convertible<
            decltype(std::declval<Func>()(std::declval<Args>()...)), Ret>;

    template <typename, typename, typename = void>
            struct check_signature : std::false_type {};

    template <typename Func, typename Ret, typename... Args>
    struct check_signature<Func, Ret(Args...),
            void_t<check_signature_t<Func, Ret, Args...>>>
            : std::true_type {};

    template <typename T>
    using equality_comparison_t =
        decltype(std::declval<T>() == std::declval<T>());

    template <typename T, typename = void>
    struct is_equality_comparable : std::false_type {};

    template <typename T>
    struct is_equality_comparable<T, void_t<equality_comparison_t<T>>>
        : std::true_type {};

    template <typename T>
    using check_equality_comparable_t =
        std::enable_if_t<is_equality_comparable<T>::value, void>;

    template <typename T>
    using less_than_comparison_t =
        decltype(std::declval<T>() < std::declval<T>());

    template <typename T, typename = void>
    struct is_less_than_comparable : std::false_type {};

    template <typename T>
    struct is_less_than_comparable<T, void_t<less_than_comparison_t<T>>>
        : std::true_type {};

    template <typename T>
    using check_less_than_comparable_t =
        std::enable_if_t<is_less_than_comparable<T>::value, void>;

} // end namespace detail

//! @cond
template <typename T, typename = detail::check_equality_comparable_t<T>>
constexpr bool operator!=(const T& lhs, const T& rhs) {
    return !(lhs == rhs);
}

template <typename T, typename = detail::check_less_than_comparable_t<T>>
constexpr bool operator>(const T& lhs, const T& rhs) {
    return rhs < lhs;
}

template <typename T, typename = detail::check_less_than_comparable_t<T>>
constexpr bool operator<=(const T& lhs, const T& rhs) {
    return !(rhs < lhs);
}

template <typename T, typename = detail::check_less_than_comparable_t<T>>
constexpr bool operator>=(const T& lhs, const T& rhs) {
    return !(lhs < rhs);
}

//! @endcond

} // end namespace detail

#endif

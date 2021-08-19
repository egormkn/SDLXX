/*!
  @file wrapper.hpp
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

#include <sdl++/stdinc.hpp>

#include <type_traits>

#ifndef SDLXX_DETAIL_WRAPPER_HPP
#define SDLXX_DETAIL_WRAPPER_HPP

namespace sdl {
namespace detail {

    template <typename CppType>
    struct c_type {
        using type = CppType;
    };

    template <typename CppType>
    using c_type_t = typename c_type<CppType>::type;

    template <typename T,
              typename = std::enable_if_t<std::is_fundamental<T>::value ||
                                          std::is_enum<T>::value ||
                                          std::is_pointer<T>::value>>
    auto to_c_value(T arg) {
        return static_cast<c_type_t<T>>(arg);
    }

    inline auto to_c_value(bool arg) { return arg ? SDL_TRUE : SDL_FALSE; }

    inline auto to_c_value(const string& arg) { return arg.c_str(); }

    template <typename CType>
    struct cpp_type {
        using type = CType;
    };

    template <typename CType>
    using cpp_type_t = typename cpp_type<CType>::type;

    template <typename T,
              typename = std::enable_if_t<std::is_fundamental<T>::value ||
                                          std::is_enum<T>::value ||
                                          std::is_pointer<T>::value>>
    auto from_c_value(T arg) {
        return static_cast<cpp_type_t<T>>(arg);
    }

    inline auto from_c_value(SDL_bool arg) { return arg == SDL_TRUE; }

    inline auto from_c_value(char* c_str) {
        string s;
        if (c_str) {
            s = c_str;
            SDL_free(c_str);
        }
        return s;
    }

    struct void_return_tag {};
    struct value_return_tag {};

    template <typename CFunc, typename... CppArgs>
    auto do_c_call(value_return_tag, CFunc c_function, CppArgs&&... args) {
        return from_c_value(
            c_function(to_c_value(std::forward<CppArgs>(args))...));
    }

    template <typename CFunc, typename... CppArgs>
    void do_c_call(void_return_tag, CFunc c_function, CppArgs&&... args) {
        c_function(to_c_value(std::forward<CppArgs>(args))...);
    }

    template <typename CFunc, typename... CppArgs>
    auto c_call(CFunc c_function, CppArgs&&... args) {
        constexpr bool is_void_return =
            std::is_same<std::result_of_t<CFunc(decltype(
                             to_c_value(std::forward<CppArgs>(args)))...)>,
                         void>::value;
        using return_tag = std::conditional_t<is_void_return, void_return_tag,
                                              value_return_tag>;
        return do_c_call(return_tag{}, c_function,
                         std::forward<CppArgs>(args)...);
    }
}
}

#endif

/*
  SDLXX - Modern C++ wrapper for Simple DirectMedia Layer (SDL2)

  Copyright (C) 2019-2021 Egor Makarenko <egormkn@yandex.ru>

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

/**
 * \file
 * \brief Header for the Time class that represents a time interval.
 */

#ifndef SDLXX_CORE_TIME_H
#define SDLXX_CORE_TIME_H

#include <cstdint>

namespace sdlxx {

class Time {
public:
  constexpr Time() = default;

  constexpr float AsSeconds() const;

  constexpr int32_t AsMilliseconds() const;

  constexpr int64_t AsMicroseconds() const;

  static constexpr Time Seconds(float value);

  static constexpr Time Milliseconds(int32_t value);

  static constexpr Time Microseconds(int64_t value);

private:
  int64_t microseconds = 0;

  explicit constexpr Time(int64_t microseconds);
};

constexpr float Time::AsSeconds() const { return static_cast<float>(microseconds / 1000000.0L); }

constexpr int32_t Time::AsMilliseconds() const { return static_cast<int32_t>(microseconds / 1000); }

constexpr int64_t Time::AsMicroseconds() const { return microseconds; }

constexpr Time Time::Seconds(float value) { return Time{static_cast<int64_t>(value * 1000000)}; }

constexpr Time Time::Milliseconds(int32_t value) {
  return Time{static_cast<int64_t>(value * 1000)};
}

constexpr Time Time::Microseconds(int64_t value) { return Time{static_cast<int64_t>(value)}; }

constexpr Time::Time(int64_t microseconds) : microseconds(microseconds) {}

}  // namespace sdlxx

#endif  // SDLXX_CORE_TIME_H

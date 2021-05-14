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
 * @file Timer.h
 * @author Egor Makarenko
 * @brief Class that represents the time management routines
 */

#pragma once

#ifndef SDLXX_CORE_TIMER_H
#define SDLXX_CORE_TIMER_H

#include <cstdint>
#include <functional>

namespace sdlxx::core {

/**
 * @brief Class that represents the time management routines
 */
class Timer {
public:
  /**
   * @brief Get the number of milliseconds since the library initialization
   *
   * @return uint32_t The number of milliseconds since the library
   * initialization
   *
   * @note This value wraps if the program runs for more than ~49 days
   */
  static uint32_t getTicks();

  /**
   * @brief Get the current value of the high resolution counter
   *
   * @return uint64_t The current value of the high resolution counter
   */
  static uint64_t getPerformanceCounter();

  /**
   * @brief Get the count per second of the high resolution counter
   *
   * @return uint64_t The count per second of the high resolution counter
   */
  static uint64_t getPerformanceFrequency();

  /**
   * @brief Wait a specified number of milliseconds before returning
   *
   * @param milliseconds A number of milliseconds to wait
   */
  static void delay(uint32_t milliseconds);

  /**
   * Function prototype for the timer callback function.
   *
   * The callback function is passed the current timer interval and returns
   * the next timer interval. If the returned value is the same as the one
   * passed in, the periodic alarm continues, otherwise a new alarm is
   * scheduled. If the callback returns 0, the periodic alarm is cancelled.
   */
  using Callback = std::function<uint32_t(uint32_t, void*)>;

  /**
   * @brief Construct a new timer and add it to the pool of timers already
   * running.
   *
   * @param interval The current timer interval
   * @param callback The timer callback function
   * @param param Attached user data
   */
  Timer(uint32_t interval, Callback callback, void* param);

  /**
   * @brief Stop and destroy the timer
   */
  ~Timer();

private:
  // Timer ID
  int id;

  // Deleted copy constructor
  Timer(const Timer&) = delete;

  // Deleted copy assignment operator
  Timer& operator=(const Timer&) = delete;
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_TIMER_H

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
 * \brief Header for the Timer class and time management routines.
 */

#pragma once

#ifndef SDLXX_CORE_TIMER_H
#define SDLXX_CORE_TIMER_H

#include <cstdint>
#include <functional>

#include "sdlxx/core/exception.h"

namespace sdlxx::core {

/**
 * \brief A class for Timer-related exceptions.
 */
class TimerException : public Exception {
  using Exception::Exception;
};

/**
 * \brief A class that represents the timer.
 */
class Timer {
public:
  /**
   * \brief Get the number of milliseconds since the library initialization.
   *
   * \return uint32_t The number of milliseconds since the library initialization.
   *
   * \note This value wraps if the program runs for more than ~49 days.
   *
   * \upstream SDL_GetTicks
   */
  static uint32_t GetTicks();

  /**
   * \brief Compare ticks values, and return true if \a lhs has passed \a rhs.
   *
   * e.g. if you want to wait 100 ms, you could do this:
   *  uint32_t timeout = Timer::GetTicks() + 100;
   *  while (!Timer::TicksPassed(Timer::GetTicks(), timeout)) {
   *      ... do work until timeout has elapsed
   *  }
   *
   * \upstream SDL_TICKS_PASSED
   */
  static bool TicksPassed(uint32_t lhs, uint32_t rhs);

  /**
   * \brief Get the current value of the high resolution counter.
   *
   * \return uint64_t The current value of the high resolution counter.
   *
   * \upstream SDL_GetPerformanceCounter
   */
  static uint64_t GetPerformanceCounter();

  /**
   * \brief Get the count per second of the high resolution counter.
   *
   * \return uint64_t The count per second of the high resolution counter.
   *
   * \upstream SDL_GetPerformanceFrequency
   */
  static uint64_t GetPerformanceFrequency();

  /**
   * \brief Wait a specified number of milliseconds before returning.
   *
   * \param milliseconds A number of milliseconds to wait.
   *
   * \upstream SDL_Delay
   */
  static void Delay(uint32_t milliseconds);

  /**
   * \brief Function prototype for the timer callback function.
   *
   * The callback function is passed the current timer interval and returns
   * the next timer interval. If the returned value is the same as the one
   * passed in, the periodic alarm continues, otherwise a new alarm is
   * scheduled. If the callback returns 0, the periodic alarm is cancelled.
   *
   * \upstream SDL_TimerCallback
   */
  using Callback = std::function<uint32_t(uint32_t, void*)>;

  /**
   * \upstream SDL_TimerID
   */
  using Id = int;

  /**
   * \brief Construct a new timer and add it to the pool of timers already running.
   *
   * \param interval The current timer interval.
   * \param callback The timer callback function.
   * \param param Attached user data.
   *
   * \upstream SDL_AddTimer
   */
  Timer(uint32_t interval, Callback callback, void* param);

  /**
   * \brief Stop and destroy the timer
   *
   * \upstream SDL_RemoveTimer
   */
  ~Timer();

private:
  Id id;  ///< Timer ID

  // Deleted copy constructor
  Timer(const Timer&) = delete;

  // Deleted copy assignment operator
  Timer& operator=(const Timer&) = delete;
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_TIMER_H

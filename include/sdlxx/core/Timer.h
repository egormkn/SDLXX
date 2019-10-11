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

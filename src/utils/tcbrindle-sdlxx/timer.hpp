/*!
  @file timer.hpp
  Header for wrappers of the SDL time management routines.

  @copyright (C) 2014-2016 Tristan Brindle <t.c.brindle@gmail.com>

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

#ifndef SDLXX_TIMER_HPP
#define SDLXX_TIMER_HPP

#include "SDL_timer.h"

#include "macros.hpp"
#include "stdinc.hpp"

#include <chrono>

namespace sdl {

/*!
  @defgroup Timer Timer Support

  This category contains functions for handling the SDL time management
  routines.
  @{
 */

/*!
 An STL-compatible clock type.

 `sdl::clock` is a clock type which models the standard library concepts
 [Clock](http://en.cppreference.com/w/cpp/concept/Clock) and
 [TrivialClock](http://en.cppreference.com/w/cpp/concept/TrivialClock).

 This clock counts the number of milliseconds since the SDL library was
 initialized. In order to use it, you will need to create an `sdl::init_guard`
 with the `sdl::init_flags::timer` flag set.

 @note This clock has a fairly low resolution, and a short rollover period
 (approximately 49 days). It is mostly intended to serve as a bridge between the
 SDL and STL notions of time. One of the standard library-provided clocks, for
 example `std::chrono::high_resolution_clock`, may be better suited for
 general purpose use.
 */
struct clock {
    //! @cond
    using rep = uint32_t;
    using period = std::milli;
    using duration = std::chrono::duration<rep, period>;
    using time_point = std::chrono::time_point<clock>;
    //! @endcond

    //! sdl::clock is monotonically increasing and not affected by changes to
    //! the system clock.
    //! @warning sdl::clock will roll over if the program runs for more than ~49
    //! days.
    constexpr static bool is_steady = true;

    //! Returns a `time_point` representing the current value of the clock
    static time_point now() noexcept {
        return time_point{duration{SDL_GetTicks()}};
    }
};

/*!
 A specialization of `std::chrono::time_point` used to represent timestamps
 in sdl++.

 The value itself is mostly meaningless.
 */
using time_point = clock::time_point;

/*!
 A specialization of `std::chrono::duration` used to represent a time interval
 in sdl++.

 Note that the standard library provides converting constructors between
 compatible duration types, so it's possible to (for example) pass a value of
 `std::chrono::seconds` to a function expecting an `sdl::duration`.
 */
using duration = clock::duration;

/*!
 Returns the number of ticks of the high performance counter since SDL was
 initialized.

 Depending on the platform, this may or may not have a higher resolution than
 `sdl::clock::now()`. Note that unfortunately SDL does not expose the high-
 frequency tick period as a compile-time constant, so we cannot have a
 high-res version of sdl::clock.

 @note The standard library provides `std::chrono::high_resolution_clock`,
 which should be preferred to using this function.

 @sa sdl::get_performance_frequency()
 */
inline uint64_t get_performance_counter() {
    return ::SDL_GetPerformanceCounter();
}

/*!
 Get the ticks per second of the high performance counter.

 @sa sdl::get_performance_counter()
 */
inline uint64_t get_performance_frequency() {
    return ::SDL_GetPerformanceFrequency();
}

/*!
 Wait a specfied time interval before returning.

 @note The standard library provides `std::this_thread::sleep_for()` and
 `std::this_thread::sleep_until()` which may be preferred to this function.
 */
inline void delay(duration interval) { ::SDL_Delay(interval.count()); }

/*!
 The type of callable expected by `make_timeout()`.

 The callback is passed the current timer interval and returns the next timer
 interval.  If the returned value is the same as the one passed in, the periodic
 alarm continues, otherwise a new alarm is  scheduled. If the callback returns
 `nullopt` or a duration of zero, the callback will not be fired again.
 */
using timeout_callback_t = optional<duration>(duration);

namespace detail {

    template <typename Func>
    class timeout_t {
        // FIXME: Work out why this fails on MSVC
        // static_assert(detail::check_signature<Func,
        // timeout_callback_t>::value,
        //              "Supplied callback is not callable or does not match "
        //              "expected type "
        //              sdl::optional<sdl::duration>(sdl::duration)");

    public:
        timeout_t(duration interval, Func&& callback)
            : callback(std::forward<Func>(callback)),
              id{::SDL_AddTimer(interval.count(), run_callback, this)} {
            SDLXX_CHECK(id != 0);
        }

        // Not default constructable, move-only
        timeout_t(timeout_t&&) = default;
        timeout_t& operator=(timeout_t&&) = default;

        ~timeout_t() { ::SDL_RemoveTimer(id); }

    private:
        static uint32_t run_callback(uint32_t interval, void* param) {
            auto self = static_cast<timeout_t*>(param);
            return optional<duration>{self->callback(duration{interval})}
                .value_or(duration::zero())
                .count();
        }

        Func callback;
        int id;
    };

} // end namespace detail

/*!
 Add a new timer to the pool of timers already running.

 The supplied callback will be called when (or soon after) the given interval
 has elapsed, and will be passed the actual time interval as its argument.
 The callable must return the delay until the next timeout, or the special
 duration value zero to signify that it should not be called again.

 This function returns a callback handle, the destructor of which takes care of
 removing the callback. This means that you must keep the return value of this
 function alive for as long as you want the callback to be called.

 @note This means that to do anything useful you *must* capture the result of
 this function. Simply calling

 ````
 make_timer(1s, functor);
 ````

 will result in the timeout being added and then immediately removed when the
 temporary return value of the function is destroyed. Instead you should say

 ````
 auto handle = make_timer(1s, functor);
 ````

 The callback will then be run regularly for as long as the variable `handle`
 is in scope.

 @warning The callback will be called in a different thread. Be very careful
 about what you do inside the callback function.

 @param interval An `sdl::duration` after which the callback will be called
 @param callback A callable (a function, functor, lambda etc) which can be
 called with a single argument of type `sdl::duration` and which returns an
 `sdl::duration`.

 @returns A move-only RAII handle representing the callback.

 @throws sdl::error If the callback could not be added
 */
template <typename Func>
SDLXX_ATTR_WARN_UNUSED_RESULT auto make_timeout(duration interval,
                                                Func&& callback) {
    return detail::timeout_t<Func>{interval, std::forward<Func>(callback)};
}

} // end namespace sdl

#endif // SDLXX_TIMER_HPP

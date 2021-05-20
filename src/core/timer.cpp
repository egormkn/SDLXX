#include "sdlxx/core/timer.h"

#include <SDL_timer.h>

using namespace std::literals;
using namespace sdlxx::core;

uint32_t Timer::GetTicks() { return SDL_GetTicks(); }

bool Timer::TicksPassed(uint32_t lhs, uint32_t rhs) { return (int32_t)(lhs - rhs) <= 0; }

uint64_t Timer::GetPerformanceCounter() { return SDL_GetPerformanceCounter(); }

uint64_t Timer::GetPerformanceFrequency() { return SDL_GetPerformanceFrequency(); }

void Timer::Delay(uint32_t milliseconds) { SDL_Delay(milliseconds); }

Timer::Timer(uint32_t interval, Callback callback, void* param) {
  SDL_TimerCallback timer_callback = *callback.target<SDL_TimerCallback>();
  id = SDL_AddTimer(interval, timer_callback, param);
  if (id == 0) {
    throw std::runtime_error("Failed to create a timer: "s + SDL_GetError());
  }
}

Timer::~Timer() { SDL_RemoveTimer(id); }

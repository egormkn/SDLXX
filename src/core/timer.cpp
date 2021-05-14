#include <SDL_timer.h>
#include <sdlxx/core/timer.h>

using namespace sdlxx::core;

uint32_t Timer::getTicks() { return SDL_GetTicks(); }

uint64_t Timer::getPerformanceCounter() { return SDL_GetPerformanceCounter(); }

uint64_t Timer::getPerformanceFrequency() {
  return SDL_GetPerformanceFrequency();
}

void Timer::delay(uint32_t milliseconds) { SDL_Delay(milliseconds); }

Timer::Timer(uint32_t interval, Callback callback, void* param) {
  SDL_TimerCallback timer_callback = *callback.target<SDL_TimerCallback>();
  id = SDL_AddTimer(interval, timer_callback, param);
  if (id == 0) {
    throw std::runtime_error("Failed to create a timer: " +
                             std::string(SDL_GetError()));
  }
}

Timer::~Timer() { [[maybe_unused]] bool removed = SDL_RemoveTimer(id); }

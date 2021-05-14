#include <sdlxx/core/events.h>

using namespace sdlxx::core;

void Events::pump() { SDL_PumpEvents(); }

int Events::add(const std::vector<Event>& events) {
  const int numevents = events.size();
  int num_added =
      SDL_PeepEvents(const_cast<SDL_Event*>(events.data()), numevents,
                     SDL_ADDEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
  if (num_added < 0) {
    throw std::runtime_error("Failed to add events to the event queue");
  }
  return num_added;
}

std::vector<Event> Events::peek(int numevents, Type minType, Type maxType) {
  std::vector<SDL_Event> events;
  int num_peeked = SDL_PeepEvents(events.data(), numevents, SDL_PEEKEVENT,
                                  static_cast<uint32_t>(minType),
                                  static_cast<uint32_t>(maxType));
  if (num_peeked < 0) {
    throw std::runtime_error("Failed to peek events from the event queue");
  }
  return events;
}

std::vector<Event> Events::get(int numevents, Type minType, Type maxType) {
  std::vector<SDL_Event> events;
  int num_got = SDL_PeepEvents(events.data(), numevents, SDL_PEEKEVENT,
                               static_cast<uint32_t>(minType),
                               static_cast<uint32_t>(maxType));
  if (num_got < 0) {
    throw std::runtime_error("Failed to get events from the event queue");
  }
  return events;
}

bool Events::inQueue(Type type) {
  return SDL_HasEvent(static_cast<uint32_t>(type));
}

bool Events::inQueue(Type minType, Type maxType) {
  return SDL_HasEvents(static_cast<uint32_t>(minType),
                       static_cast<uint32_t>(maxType));
}

void Events::flush(Type type) { SDL_FlushEvent(static_cast<uint32_t>(type)); }

void Events::flush(Type minType, Type maxType) {
  SDL_FlushEvents(static_cast<uint32_t>(minType),
                  static_cast<uint32_t>(maxType));
}

bool Events::inQueue() { return SDL_PollEvent(NULL); }

std::optional<Event> Events::poll() {
  SDL_Event event;
  int is_polled = SDL_PollEvent(&event);
  if (!is_polled) {
    return std::nullopt;
  }
  return {event};
}

Event Events::wait() {
  SDL_Event event;
  int is_polled = SDL_WaitEvent(&event);
  if (!is_polled) {
    throw std::runtime_error("Failed to wait for an event");
  }
  return event;
}

std::optional<Event> Events::wait(int timeout) {
  SDL_Event event;
  int is_polled = SDL_WaitEventTimeout(&event, timeout);
  if (!is_polled) {
    return std::nullopt;
  }
  return {event};
}

bool Events::push(Event event) {
  int return_code = SDL_PushEvent(&event);
  if (return_code < 0) {
    throw std::runtime_error("Failed to push event to the event queue");
  }
  return return_code != 0;
}

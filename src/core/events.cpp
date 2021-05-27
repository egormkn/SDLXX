#include "sdlxx/core/events.h"

#include <SDL_events.h>

using namespace std;
using namespace sdlxx::core;

void Events::Pump() { SDL_PumpEvents(); }

int Events::Add(std::vector<Event> events) {
  if (events.empty()) {
    return 0;
  }
  SDL_Event* data = events.data();
  int size = events.size();
  int num_added = SDL_PeepEvents(data, size, SDL_ADDEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
  if (num_added < 0) {
    throw EventException("Failed to add events to the event queue");
  }
  return num_added;
}

std::vector<Event> Events::Peek(int numevents, Type minType, Type maxType) {
  std::vector<Event> events(numevents);
  int num_peeked = SDL_PeepEvents(events.data(), events.size(), SDL_PEEKEVENT,
                                  static_cast<Uint32>(minType), static_cast<Uint32>(maxType));
  if (num_peeked < 0) {
    throw EventException("Failed to peek events from the event queue");
  }
  events.resize(num_peeked);
  return events;
}

std::vector<Event> Events::Get(int numevents, Type minType, Type maxType) {
  std::vector<Event> events(numevents);
  int num_got = SDL_PeepEvents(events.data(), events.size(), SDL_GETEVENT,
                               static_cast<Uint32>(minType), static_cast<Uint32>(maxType));
  if (num_got < 0) {
    throw EventException("Failed to geek events from the event queue");
  }
  events.resize(num_got);
  return events;
}

bool Events::InQueue(Type type) { return SDL_HasEvent(static_cast<Uint32>(type)) == SDL_TRUE; }

bool Events::InQueue(Type minType, Type maxType) {
  return SDL_HasEvents(static_cast<Uint32>(minType), static_cast<Uint32>(maxType)) == SDL_TRUE;
}

bool Events::IsEmpty() { return SDL_PollEvent(NULL) == 0; }

void Events::Flush(Type type) { SDL_FlushEvent(static_cast<Uint32>(type)); }

void Events::Flush(Type minType, Type maxType) {
  SDL_FlushEvents(static_cast<Uint32>(minType), static_cast<Uint32>(maxType));
}

bool Events::Poll(Event* event) {
  int return_code = SDL_PollEvent(event);
  return (return_code != 0);
}

bool Events::Wait(Event* event) {
  int return_code = SDL_WaitEvent(event);
  if (return_code == 0) {
    throw EventException("Error while waiting for events");
  }
  return true;
}

bool Events::WaitTimeout(Event* event, int timeout) {
  int return_code = SDL_WaitEventTimeout(event, timeout);
  return (return_code != 0);
}

bool Events::Push(SDL_Event* event) {
  int return_code = SDL_PushEvent(event);
  if (return_code < 0) {
    throw EventException("Failed to push event to the event queue");
  }
  return return_code != 0;
}

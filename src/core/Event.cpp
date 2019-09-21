#include "Event.h"

SDLXX::Event::Event() {
    event = new SDL_Event;
}

SDLXX::Event::~Event() {
    delete event;
}

bool SDLXX::Event::hasNext() {
    return SDL_PollEvent(event) == 1;
}

SDL_Event &SDLXX::Event::getEvent() {
    return *event;
}

Uint32 SDLXX::Event::getType() {
    return event->type;
}

bool SDLXX::Event::pushEvent() {
    int result = SDL_PushEvent(event);
    if (result < 0) {
        throw Exception("Failed to add an event to queue", SDL_GetError());
    }
    return result == 1;
}

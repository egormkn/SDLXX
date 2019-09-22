#include <sdlxx/core/Event.h>

sdlxx::core::Event::Event() {
    event = new SDL_Event;
}

sdlxx::core::Event::~Event() {
    delete event;
}

bool sdlxx::core::Event::hasNext() {
    return SDL_PollEvent(event) == 1;
}

SDL_Event &sdlxx::core::Event::getEvent() {
    return *event;
}

Uint32 sdlxx::core::Event::getType() {
    return event->type;
}

bool sdlxx::core::Event::pushEvent() {
    int result = SDL_PushEvent(event);
    if (result < 0) {
        throw Exception("Failed to add an event to queue", SDL_GetError());
    }
    return result == 1;
}

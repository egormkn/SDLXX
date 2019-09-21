#ifndef SDLXX_OBJECT_H
#define SDLXX_OBJECT_H

#include "Event.h"
#include "Renderer.h"
#include "Point.h"

namespace SDLXX {
    class Object {
    protected:
        Object() = default;

    public:
        virtual void update(Uint32 t, Uint32 dt, const Dimensions &windowDimensions) = 0;

        virtual void render(Renderer &renderer) = 0;

        virtual bool handleEvent(Event &e) = 0;

        virtual ~Object() {}
    };
}

#endif // SDLXX_OBJECT_H

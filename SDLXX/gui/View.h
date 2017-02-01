#ifndef SDLXX_VIEW_H
#define SDLXX_VIEW_H

#include "../base/Event.h"

namespace SDLXX {
    class View {
    public:
        View(int w, int h) {
            width = w;
            height = h;
        }

        void handleEvent(const Event &e) {

        }

        virtual void onClick() {}
        virtual void onMouseOver() {}
        virtual void onMouseOut() {}

    private:
        int width, height;
    };
}

#endif // SDLXX_VIEW_H

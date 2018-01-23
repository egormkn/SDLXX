#ifndef SDLXX_SCENEMANAGER_H
#define SDLXX_SCENEMANAGER_H

#include <stack>
#include <algorithm>
#include "Window.h"
#include "Scene.h"

namespace SDLXX {
    class SceneManager {
    public:
        SceneManager(Window &w);

        ~SceneManager();

        void push(Scene *s);

        void pop();

        void setWindow(Window &w);

        Window &getWindow();

        void clear();

        void run();

    private:
        int* a, b;
        Window *window = nullptr;
        std::stack<Scene *> scenes;
    };
}

#endif // SDLXX_SCENEMANAGER_H

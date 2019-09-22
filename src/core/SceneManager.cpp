#include <sdlxx/core/SceneManager.h>

sdlxx::core::SceneManager::SceneManager(sdlxx::core::Window &w) {
    window = &w;
}

sdlxx::core::SceneManager::~SceneManager() {
    clear();
    window = nullptr;
}

void sdlxx::core::SceneManager::push(sdlxx::core::Scene *s) {
    scenes.push(s);
}

void sdlxx::core::SceneManager::pop() {
    scenes.pop();
}

void sdlxx::core::SceneManager::setWindow(sdlxx::core::Window &w) {
    window = &w;
}

sdlxx::core::Window &sdlxx::core::SceneManager::getWindow() {
    return *window;
}

void sdlxx::core::SceneManager::clear() {
    while (scenes.size() > 0) {
        Scene *scene = scenes.top();
        if (scene->isInitialized()) {
            scene->setFinished(true);
            scene->setInitialized(false);
            scene->onDestroy();
        }
        delete scene;
        scenes.pop();
    }
}

void sdlxx::core::SceneManager::run() {
    Uint32 t = 0, dt = 10, accumulator = 0;
    Uint32 currentTime = SDL_GetTicks();

    Event e;
    //State previous, current;

    while (scenes.size() > 0) {
        Uint32 newTime = SDL_GetTicks();
        Uint32 frameTime = std::min(newTime - currentTime, (Uint32) 250);
        currentTime = newTime;

        Scene *currentScene = scenes.top();

        if (currentScene->isFinished()) {
            Scene *intent = nullptr;
            if(currentScene->hasIntent()) {
                intent = currentScene->getIntent();
            }
            currentScene->setInitialized(false);
            currentScene->onDestroy();
            delete currentScene;
            scenes.pop();
            if(intent != nullptr) {
                scenes.push(intent);
            }
            continue;
        }

        if(currentScene->hasIntent()) {
            Log::log("[MANAGER] Pushing new intent");
            currentScene->setInitialized(false);
            currentScene->setFinished(false);
            currentScene->onDestroy();
            scenes.push(currentScene->getIntent());
            continue;
        }

        if (!currentScene->isInitialized()) {
            currentScene->onCreate(*window);
            currentScene->setInitialized(true);
            currentScene->setFinished(false);
        }

        while (e.hasNext()) {
            if(e.getType() == SDL_QUIT) {
                clear(); // FIXME: Do we really need to quit?
            } else if(!currentScene->isFinished()) {
                currentScene->handleEvent(e);
            }
        }

        if(scenes.size() == 0) {
            break;
        }

        accumulator += frameTime;

        while (accumulator >= dt) {
            //previous = current;
            //integrate( current, t, dt );
            if(!currentScene->isFinished()) {
                currentScene->update(t, dt);
            }
            t += dt;
            accumulator -= dt;
            /*std::string str = "Game FPS: " + std::to_string((frameTime == 0 ? 0 : (int) (1000.0 / frameTime)));
            window->setTitle(str);*/
        }

        const Uint32 alpha = (Uint32) (accumulator / dt);

        //State state;
        //state.x = current.x * alpha + previous.x * (1 - alpha);
        //state.v = current.v * alpha + previous.v * (1 - alpha);
        // render( state );
        if(!currentScene->isFinished()) {
            currentScene->render(window->getRenderer());
        }
    }
}

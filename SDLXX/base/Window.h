#pragma once
#ifndef SDLXX_WINDOW_H
#define SDLXX_WINDOW_H

#include "../SDLXX.h"
#include "../Exception.h"
#include "Renderer.h"
#include "Point.h"
#include <string>

namespace SDLXX {
    class Window {
    public:
        Window(SDL_Window *w) : window(w) {
            SDL_Renderer *windowRenderer = SDL_GetRenderer(w);
            if(windowRenderer != nullptr) {
                renderer = new Renderer(windowRenderer);
            }
        }

        Window(const void *data) {
            window = SDL_CreateWindowFrom(data);
            if(window == nullptr) {
                throw Exception("Window was not initialized", SDL_GetError());
            }
        }

        Window(const std::string &title, int posX = SDL_WINDOWPOS_UNDEFINED, int posY = SDL_WINDOWPOS_UNDEFINED, int width = 640, int height = 480, Uint32 flags = 0) {
            window = SDL_CreateWindow(title.c_str(), posX, posY, width, height, flags);
            if(window == nullptr) {
                throw Exception("Window was not initialized", SDL_GetError());
            }
        }

        ~Window() {
            if(renderer != nullptr) {
                delete renderer;
                renderer = nullptr;
            }
            if(window != nullptr) {
                SDL_DestroyWindow(window);
                window = nullptr;
            }
        }

        SDL_Window *getSDLWindow() const {
            return window;
        }

        Renderer &setRenderer(int driver, Uint32 flags) {
            if(renderer != nullptr) {
                throw Exception("Window already has a renderer");
            }
            renderer = new Renderer(window, driver, flags);
            if(renderer == nullptr) {
                throw Exception("Renderer could not be created", SDL_GetError());
            }
            return *renderer;
        }

        Renderer &getRenderer() const {
            return *renderer;
        }

        SDL_Renderer *getSDLRenderer() {
            return renderer->getSDLRenderer();
        }

        void setTitle(const std::string &title) {
            SDL_SetWindowTitle(window, title.c_str());
        }

        void minimize() {
            SDL_MinimizeWindow(window);
        }

        void maximize() {
            SDL_MaximizeWindow(window);
        }

        void restore() {
            SDL_RestoreWindow(window);
        }

        Dimensions getDimensions() {
            int w, h;
            SDL_GetWindowSize(window, &w, &h);
            return Dimensions(w, h);
        }


    private:
        SDL_Window *window = nullptr;
        Renderer *renderer = nullptr;
    };
}

#endif // SDLXX_WINDOW_H





/*
SDL_CreateWindow
SDL_CreateWindowAndRenderer
SDL_CreateWindowFrom
SDL_DestroyWindow
SDL_DisableScreenSaver
SDL_EnableScreenSaver
SDL_GL_CreateContext
SDL_GL_DeleteContext
SDL_GL_ExtensionSupported
SDL_GL_GetAttribute
SDL_GL_GetCurrentContext
SDL_GL_GetCurrentWindow
SDL_GL_GetDrawableSize
SDL_GL_GetProcAddress
SDL_GL_GetSwapInterval
SDL_GL_LoadLibrary
SDL_GL_MakeCurrent
SDL_GL_ResetAttributes
SDL_GL_SetAttribute
SDL_GL_SetSwapInterval
SDL_GL_SwapWindow
SDL_GL_UnloadLibrary
SDL_GetClosestDisplayMode
SDL_GetCurrentDisplayMode
SDL_GetCurrentVideoDriver
SDL_GetDesktopDisplayMode
SDL_GetDisplayBounds
SDL_GetDisplayDPI
SDL_GetDisplayMode
SDL_GetDisplayName
SDL_GetDisplayUsableBounds
SDL_GetGrabbedWindow
SDL_GetNumDisplayModes
SDL_GetNumVideoDisplays
SDL_GetNumVideoDrivers
SDL_GetVideoDriver
SDL_GetWindowBordersSize
SDL_GetWindowBrightness
SDL_GetWindowData
SDL_GetWindowDisplayIndex
SDL_GetWindowDisplayMode
SDL_GetWindowFlags
SDL_GetWindowFromID
SDL_GetWindowGammaRamp
SDL_GetWindowGrab
SDL_GetWindowID
SDL_GetWindowMaximumSize
SDL_GetWindowMinimumSize
SDL_GetWindowOpacity
SDL_GetWindowPixelFormat
SDL_GetWindowPosition
SDL_GetWindowSize
SDL_GetWindowSurface
SDL_GetWindowTitle
SDL_GetWindowWMInfo
SDL_HideWindow
SDL_IsScreenSaverEnabled
SDL_MaximizeWindow
SDL_MinimizeWindow
SDL_RaiseWindow
SDL_RestoreWindow
SDL_SetWindowBordered
SDL_SetWindowBrightness
SDL_SetWindowData
SDL_SetWindowDisplayMode
SDL_SetWindowFullscreen
SDL_SetWindowGammaRamp
SDL_SetWindowGrab
SDL_SetWindowHitTest
SDL_SetWindowIcon
SDL_SetWindowInputFocus
SDL_SetWindowMaximumSize
SDL_SetWindowMinimumSize
SDL_SetWindowModalFor
SDL_SetWindowOpacity
SDL_SetWindowPosition
SDL_SetWindowResizable
SDL_SetWindowSize
SDL_SetWindowTitle
SDL_ShowMessageBox
SDL_ShowSimpleMessageBox
SDL_ShowWindow
SDL_UpdateWindowSurface
SDL_UpdateWindowSurfaceRects
SDL_VideoInit
SDL_VideoQuit
 */
#pragma once

#ifndef SDLXX_CORE_WINDOW_HPP
#define SDLXX_CORE_WINDOW_HPP

#include "SDLXX_core.h"
#include "Exception.h"
#include "Renderer.h"
#include "Point.h"
#include <string>

namespace sdlxx::core {

    class Window {
    public:
        Window(SDL_Window *w);

        Window(const void *data);

        Window(const std::string &title, int posX = SDL_WINDOWPOS_UNDEFINED, int posY = SDL_WINDOWPOS_UNDEFINED, int width = 640, int height = 480, Uint32 flags = 0);

        ~Window();

        SDL_Window *getSDLWindow() const;

        Renderer &setRenderer(int driver, Uint32 flags);

        Renderer &getRenderer() const;

        SDL_Renderer *getSDLRenderer();

        void setTitle(const std::string &title);

        void minimize();

        void maximize();

        void restore();

        Dimensions getDimensions();


    private:
        SDL_Window *window = nullptr;
        Renderer *renderer = nullptr;
    };
}

#endif // SDLXX_CORE_WINDOW_H





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

#pragma once
#ifndef SDLXX_WINDOW_H
#define SDLXX_WINDOW_H

#include "../SDLXX.h"
#include "../Exception.h"
#include "Renderer.h"
#include <string>

namespace SDLXX {
    class Window {
    public:
        Window(SDL_Window *w);

        Window(const std::string &title, int posX, int posY, int width, int height, Uint32 flags);

        ~Window();

        SDL_Window *getSDLWindow() const {
            return window;
        }

        Renderer &setRenderer(int driver, Uint32 flags) {
            if(renderer != nullptr) {
                throw Exception("Window already has a renderer");
            }
            renderer = new Renderer(SDL_CreateRenderer(window, driver, flags));
            if(renderer == nullptr) {
                throw Exception("Renderer could not be created", SDL_GetError());
            }
            return *renderer; // TODO Check
        }

        Renderer &getRenderer() const {
            return *renderer; // TODO Check
        }

        SDL_Renderer *getSDLRenderer() {
            return renderer->getSDLRenderer();
        }

        void setTitle(const std::string &title) {
            SDL_SetWindowTitle(window, title.c_str());
        }

        void minimize();

        void maximize();

        void restore();
/*
        void setWidth(int width) {

        }

        // Event handler
        void handle(const SDL_Event &e) {
            //If an event was detected for this window
            if(e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID) {
                //Caption update flag
                bool updateCaption = false;

                switch (e.window.event) {
                    //Window appeared
                    case SDL_WINDOWEVENT_SHOWN:
                        mShown = true;
                        break;

                        //Window disappeared
                    case SDL_WINDOWEVENT_HIDDEN:
                        mShown = false;
                        break;

                        //Get new dimensions and repaint
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        mWidth = e.window.data1;
                        mHeight = e.window.data2;
                        SDL_RenderPresent(mRenderer);
                        break;

                        //Repaint on expose
                    case SDL_WINDOWEVENT_EXPOSED:
                        SDL_RenderPresent(mRenderer);
                        break;

                        //Mouse enter
                    case SDL_WINDOWEVENT_ENTER:
                        mMouseFocus = true;
                        updateCaption = true;
                        break;

                        //Mouse exit
                    case SDL_WINDOWEVENT_LEAVE:
                        mMouseFocus = false;
                        updateCaption = true;
                        break;

                        //Keyboard focus gained
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        mKeyboardFocus = true;
                        updateCaption = true;
                        break;

                        //Keyboard focus lost
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        mKeyboardFocus = false;
                        updateCaption = true;
                        break;

                        //Window minimized
                    case SDL_WINDOWEVENT_MINIMIZED:
                        mMinimized = true;
                        break;

                        //Window maxized
                    case SDL_WINDOWEVENT_MAXIMIZED:
                        mMinimized = false;
                        break;

                        //Window restored
                    case SDL_WINDOWEVENT_RESTORED:
                        mMinimized = false;
                        break;

                        //Hide on close
                    case SDL_WINDOWEVENT_CLOSE:
                        SDL_HideWindow(mWindow);
                        break;
                }

                //Update window caption with new data
                if(updateCaption) {
                    std::stringstream caption;
                    caption << "SDL Tutorial - ID: " << mWindowID << " MouseFocus:" << ((mMouseFocus) ? "On" : "Off")
                            << " KeyboardFocus:" << ((mKeyboardFocus) ? "On" : "Off");
                    SDL_SetWindowTitle(mWindow, caption.str().c_str());
                }
            }
        }

        //Focuses on window
        void focus() {
            //Restore window if needed
            if(!mShown) {
                SDL_ShowWindow(mWindow);
            }

            //Move window forward
            SDL_RaiseWindow(mWindow);
        }

        //Shows windows contents
        void render() {
            if(!mMinimized) {
                //Clear screen
                SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(mRenderer);

                //Update screen
                SDL_RenderPresent(mRenderer);
            }
        }

        //Deallocates internals
        void free() {
            if(mWindow != nullptr) {
                SDL_DestroyWindow(mWindow);
            }

            mMouseFocus = false;
            mKeyboardFocus = false;
            mWidth = 0;
            mHeight = 0;
        }
*/

    private:
        SDL_Window *window = nullptr;
        Renderer *renderer = nullptr;
    };
}

#endif // SDLXX_WINDOW_H
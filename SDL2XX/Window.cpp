/*
 *
 *
 * class LWindow {
public:
    //Intializes internals
    LWindow();

    //Creates window
    bool init();

    //Handles window events
    void handleEvent(SDL_Event &e);

    //Focuses on window
    void focus();

    //Shows windows contents
    void render();

    //Deallocates internals
    void free();

    //Window dimensions
    int getWidth();

    int getHeight();

    //Window focii
    bool hasMouseFocus();

    bool hasKeyboardFocus();

    bool isMinimized();

    bool isShown();

private:
    //Window data
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    int mWindowID;

    //Window dimensions
    int mWidth;
    int mHeight;

    //Window focus
    bool mMouseFocus;
    bool mKeyboardFocus;
    bool mFullScreen;
    bool mMinimized;
    bool mShown;
};

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//Our custom windows
LWindow gWindows[TOTAL_WINDOWS];

LWindow::LWindow() {
    //Initialize non-existant window
    mWindow = NULL;
    mRenderer = NULL;

    mMouseFocus = false;
    mKeyboardFocus = false;
    mFullScreen = false;
    mShown = false;
    mWindowID = -1;

    mWidth = 0;
    mHeight = 0;
}

bool LWindow::init() {
    //Create window
    mWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(mWindow != NULL) {
        mMouseFocus = true;
        mKeyboardFocus = true;
        mWidth = SCREEN_WIDTH;
        mHeight = SCREEN_HEIGHT;

        //Create renderer for window
        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(mRenderer == NULL) {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            SDL_DestroyWindow(mWindow);
            mWindow = NULL;
        } else {
            //Initialize renderer color
            SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

            //Grab window identifier
            mWindowID = SDL_GetWindowID(mWindow);

            //Flag as opened
            mShown = true;
        }
    } else {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
    }

    return mWindow != NULL && mRenderer != NULL;
}

void LWindow::handleEvent(SDL_Event &e) {
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

void LWindow::focus() {
    //Restore window if needed
    if(!mShown) {
        SDL_ShowWindow(mWindow);
    }

    //Move window forward
    SDL_RaiseWindow(mWindow);
}

void LWindow::render() {
    if(!mMinimized) {
        //Clear screen
        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mRenderer);

        //Update screen
        SDL_RenderPresent(mRenderer);
    }
}

void LWindow::free() {
    if(mWindow != NULL) {
        SDL_DestroyWindow(mWindow);
    }

    mMouseFocus = false;
    mKeyboardFocus = false;
    mWidth = 0;
    mHeight = 0;
}

int LWindow::getWidth() {
    return mWidth;
}

int LWindow::getHeight() {
    return mHeight;
}

bool LWindow::hasMouseFocus() {
    return mMouseFocus;
}

bool LWindow::hasKeyboardFocus() {
    return mKeyboardFocus;
}

bool LWindow::isMinimized() {
    return mMinimized;
}

bool LWindow::isShown() {
    return mShown;
}

 */
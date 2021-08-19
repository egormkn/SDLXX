
  void printDebugInfo() {
    SDL_DisplayMode current;
    for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {
      std::stringstream s;
      if (SDL_GetCurrentDisplayMode(i, &current) != 0) {
        s << "Could not get display mode for video display #" << i << ": "
          << SDL_GetError();
      } else {
        s << "Display #" << i << ": " << current.w << "x" << current.h
          << "px @ " << current.refresh_rate << "hz";
      }
      Log::log(s.str());
    }
  }

  static void setHint(const std::string& name, const std::string& value);

  static void setMainReady();

  static void setScreensaverEnabled(bool enabled) {
    if (enabled) {
      SDL_EnableScreenSaver();
    } else {
      SDL_DisableScreenSaver();
    }
  }

  // static int winRTRunApp(MainFunction mainFunction, void* reserved);

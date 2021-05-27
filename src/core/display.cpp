#include "sdlxx/core/display.h"

#include <SDL_video.h>

using namespace sdlxx::core;

static_assert(static_cast<SDL_DisplayEventID>(Display::EventID::NONE) == SDL_DISPLAYEVENT_NONE);
static_assert(static_cast<SDL_DisplayEventID>(Display::EventID::ORIENTATION) ==
              SDL_DISPLAYEVENT_ORIENTATION);
static_assert(static_cast<SDL_DisplayEventID>(Display::EventID::CONNECTED) ==
              SDL_DISPLAYEVENT_CONNECTED);
static_assert(static_cast<SDL_DisplayEventID>(Display::EventID::DISCONNECTED) ==
              SDL_DISPLAYEVENT_DISCONNECTED);

static_assert(static_cast<SDL_DisplayOrientation>(Display::Orientation::UNKNOWN) ==
              SDL_ORIENTATION_UNKNOWN);
static_assert(static_cast<SDL_DisplayOrientation>(Display::Orientation::LANDSCAPE) ==
              SDL_ORIENTATION_LANDSCAPE);
static_assert(static_cast<SDL_DisplayOrientation>(Display::Orientation::LANDSCAPE_FLIPPED) ==
              SDL_ORIENTATION_LANDSCAPE_FLIPPED);
static_assert(static_cast<SDL_DisplayOrientation>(Display::Orientation::PORTRAIT) ==
              SDL_ORIENTATION_PORTRAIT);
static_assert(static_cast<SDL_DisplayOrientation>(Display::Orientation::PORTRAIT_FLIPPED) ==
              SDL_ORIENTATION_PORTRAIT_FLIPPED);

std::vector<std::string> Display::GetVideoDrivers() {
  int num_drivers = SDL_GetNumVideoDrivers();
  std::vector<std::string> result;
  result.reserve(num_drivers);
  for (int i = 0; i < num_drivers; ++i) {
    result.push_back(SDL_GetVideoDriver(i));
  }
  return result;
}

void Display::VideoInit(const std::string& driver_name) {
  int return_code = SDL_VideoInit(driver_name.empty() ? NULL : driver_name.c_str());
  if (return_code == -1) {
    throw DisplayException("Could not initialize the video subsystem");
  }
}

void Display::VideoQuit() { SDL_VideoQuit(); }

std::optional<std::string> Display::GetCurrentVideoDriver() {
  if (auto driver_name = SDL_GetCurrentVideoDriver(); driver_name != NULL) {
    return driver_name;
  } else {
    return std::nullopt;
  }
}

std::vector<Display> Display::GetVideoDisplays() {
  int num_displays = SDL_GetNumVideoDisplays();
  std::vector<Display> result;
  result.reserve(num_displays);
  for (int i = 0; i < num_displays; ++i) {
    result.push_back(Display(i));
  }
  return result;
}

std::string Display::GetName() const {
  if (auto name = SDL_GetDisplayName(index); name != NULL) {
    return name;
  } else {
    throw DisplayException("Invalid display index: " + std::to_string(index));
  }
}

int Display::GetIndex() const { return index; }

Rectangle Display::GetBounds() const {
  SDL_Rect bounds;
  if (int return_code = SDL_GetDisplayBounds(index, &bounds); return_code != -1) {
    return {bounds.x, bounds.y, bounds.w, bounds.h};
  } else {
    throw DisplayException("Invalid display index: " + std::to_string(index));
  }
}

Rectangle Display::GetUsableBounds() const {
  SDL_Rect bounds;
  if (int return_code = SDL_GetDisplayUsableBounds(index, &bounds); return_code != -1) {
    return {bounds.x, bounds.y, bounds.w, bounds.h};
  } else {
    throw DisplayException("Invalid display index: " + std::to_string(index));
  }
}

Display::DPI Display::GetDPI() const {
  DPI dpi;
  if (int return_code = SDL_GetDisplayDPI(index, &dpi.ddpi, &dpi.hdpi, &dpi.vdpi);
      return_code != -1) {
    return dpi;
  } else {
    throw DisplayException(
        "No DPI information is available or the display index is out of range: " +
        std::to_string(index));
  }
}

Display::Orientation Display::GetOrientation() const {
  return static_cast<Display::Orientation>(SDL_GetDisplayOrientation(index));
}

std::vector<Display::Mode> Display::GetModes() const {
  int num_modes = SDL_GetNumDisplayModes(index);
  std::vector<Display::Mode> result;
  result.reserve(num_modes);
  for (int i = 0; i < num_modes; ++i) {
    SDL_DisplayMode mode;
    int return_code = SDL_GetDisplayMode(index, i, &mode);
    if (return_code == -1) {
      throw DisplayException(
          "No display mode information is available or the display index is out of range: " +
          std::to_string(index) + ", mode " + std::to_string(i));
    }
    result.push_back({mode.format, mode.w, mode.h, mode.refresh_rate, mode.driverdata});
  }
  return result;
}

Display::Mode Display::GetDesktopMode() const {
  SDL_DisplayMode mode;
  int return_code = SDL_GetDesktopDisplayMode(index, &mode);
  if (return_code == -1) {
    throw DisplayException(
        "No display mode information is available or the display index is out of range: " +
        std::to_string(index) + ", desktop mode");
  }
  return {mode.format, mode.w, mode.h, mode.refresh_rate, mode.driverdata};
}

Display::Mode Display::GetCurrentMode() const {
  SDL_DisplayMode mode;
  int return_code = SDL_GetCurrentDisplayMode(index, &mode);
  if (return_code == -1) {
    throw DisplayException(
        "No display mode information is available or the display index is out of range: " +
        std::to_string(index) + ", current mode");
  }
  return {mode.format, mode.w, mode.h, mode.refresh_rate, mode.driverdata};
}

std::optional<Display::Mode> Display::GetClosestMode(Display::Mode mode) const {
  SDL_DisplayMode request = {mode.format, mode.w, mode.h, mode.refresh_rate, mode.driverdata};
  SDL_DisplayMode response;
  if (SDL_GetClosestDisplayMode(index, &request, &response) != NULL) {
    return Display::Mode{response.format, response.w, response.h, response.refresh_rate,
                         response.driverdata};
  } else {
    return std::nullopt;
  }
}

bool Display::IsScreenSaverEnabled() { return SDL_IsScreenSaverEnabled() == SDL_TRUE; }

void Display::EnableScreenSaver() { SDL_EnableScreenSaver(); }

void Display::DisableScreenSaver() { SDL_DisableScreenSaver(); }

Display::Display(int index) : index(index) {}

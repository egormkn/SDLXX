#include "sdlxx/core/display.h"

#include <SDL_rect.h>
#include <SDL_stdinc.h>
#include <SDL_video.h>

using namespace sdlxx;

#define ASSERT_DISPLAYEVENTID(x) \
  static_assert(static_cast<SDL_DisplayEventID>(Display::EventID::x) == SDL_DISPLAYEVENT_##x);

ASSERT_DISPLAYEVENTID(NONE);
ASSERT_DISPLAYEVENTID(ORIENTATION);
ASSERT_DISPLAYEVENTID(CONNECTED);
ASSERT_DISPLAYEVENTID(DISCONNECTED);

#define ASSERT_DISPLAYORIENTATION(x)                                            \
  static_assert(static_cast<SDL_DisplayOrientation>(Display::Orientation::x) == \
                SDL_ORIENTATION_##x);

ASSERT_DISPLAYORIENTATION(UNKNOWN);
ASSERT_DISPLAYORIENTATION(LANDSCAPE);
ASSERT_DISPLAYORIENTATION(LANDSCAPE_FLIPPED);
ASSERT_DISPLAYORIENTATION(PORTRAIT);
ASSERT_DISPLAYORIENTATION(PORTRAIT_FLIPPED);

std::vector<std::string> Display::GetVideoDrivers() {
  int num_drivers = SDL_GetNumVideoDrivers();
  std::vector<std::string> result;
  result.reserve(num_drivers);
  for (int i = 0; i < num_drivers; ++i) {
    result.emplace_back(SDL_GetVideoDriver(i));
  }
  return result;
}

void Display::VideoInit(const std::string& driver_name) {
  int return_code = SDL_VideoInit(driver_name.empty() ? nullptr : driver_name.c_str());
  if (return_code == -1) {
    throw DisplayException("Could not initialize the video subsystem");
  }
}

void Display::VideoQuit() { SDL_VideoQuit(); }

std::optional<std::string> Display::GetCurrentVideoDriver() {
  if (const auto* driver_name = SDL_GetCurrentVideoDriver(); driver_name != nullptr) {
    return driver_name;
  }
  return std::nullopt;
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
  if (const auto* name = SDL_GetDisplayName(index); name != nullptr) {
    return name;
  }
  throw DisplayException("Invalid display index: " + std::to_string(index));
}

int Display::GetIndex() const { return index; }

Rectangle Display::GetBounds() const {
  SDL_Rect bounds;
  if (int return_code = SDL_GetDisplayBounds(index, &bounds); return_code != -1) {
    return {bounds.x, bounds.y, bounds.w, bounds.h};
  }
  throw DisplayException("Invalid display index: " + std::to_string(index));
}

Rectangle Display::GetUsableBounds() const {
  SDL_Rect bounds;
  if (int return_code = SDL_GetDisplayUsableBounds(index, &bounds); return_code != -1) {
    return {bounds.x, bounds.y, bounds.w, bounds.h};
  }
  throw DisplayException("Invalid display index: " + std::to_string(index));
}

Display::DPI Display::GetDPI() const {
  DPI dpi{};
  if (int return_code = SDL_GetDisplayDPI(index, &dpi.ddpi, &dpi.hdpi, &dpi.vdpi);
      return_code != -1) {
    return dpi;
  }
  throw DisplayException("No DPI information is available or the display index is out of range: " +
                         std::to_string(index));
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
  if (SDL_GetClosestDisplayMode(index, &request, &response) != nullptr) {
    return Display::Mode{response.format, response.w, response.h, response.refresh_rate,
                         response.driverdata};
  }
  return std::nullopt;
}

bool Display::IsScreenSaverEnabled() { return SDL_IsScreenSaverEnabled() == SDL_TRUE; }

void Display::EnableScreenSaver() { SDL_EnableScreenSaver(); }

void Display::DisableScreenSaver() { SDL_DisableScreenSaver(); }

Display::Display(int index) : index(index) {}

/*
  SDLXX - Modern C++ wrapper for Simple DirectMedia Layer
  Copyright (C) 2019-2021 Egor Makarenko <egormkn@yandex.ru>

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgement in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 * \file
 * \brief Header for the Display class that represents a display.
 */

#pragma once

#ifndef SDLXX_CORE_DISPLAY_H
#define SDLXX_CORE_DISPLAY_H

#include <optional>
#include <string>
#include <vector>

#include "sdlxx/core/dimensions.h"
#include "sdlxx/core/exception.h"
#include "sdlxx/core/rectangle.h"

namespace sdlxx::core {

/**
 * \brief A class for Display-related exceptions.
 */
class DisplayException : public Exception {
  using Exception::Exception;
};

/**
 * \brief A class that represents a display.
 */
class Display {
public:
  /**
   * \brief A structure that defines a display mode.
   *
   * \sa Display::GetNumModes()
   * \sa Display::GetMode(int)
   * \sa Display::GetDesktopMode()
   * \sa Display::GetCurrentMode()
   * \sa Display::GetClosestMode()
   * \sa Window::SetDisplayMode()
   * \sa Window::GetDisplayMode()
   *
   * \upstream SDL_DisplayMode
   */
  struct Mode {
    uint32_t format;  /**< pixel format */
    int w;            /**< width, in screen coordinates */
    int h;            /**< height, in screen coordinates */
    int refresh_rate; /**< refresh rate (or zero for unspecified) */
    void* driverdata; /**< driver-specific data, initialize to 0 */
  };

  /**
   * \brief A structure that represents display DPI values.
   */
  struct DPI {
    float ddpi;
    float hdpi;
    float vdpi;
  };

  /**
   * \brief Event subtype for display events.
   *
   * \upstream SDL_DisplayEventID
   */
  enum class EventID {
    NONE,        /**< Never used */
    ORIENTATION, /**< Display orientation has changed to data1 */
    CONNECTED,   /**< Display has been added to the system */
    DISCONNECTED /**< Display has been removed from the system */
  };

  /**
   * \upstream SDL_DisplayOrientation
   */
  enum class Orientation {
    UNKNOWN,           /**< The display orientation can't be determined */
    LANDSCAPE,         /**< The display is in landscape mode, with the right side up,
                            relative to portrait mode */
    LANDSCAPE_FLIPPED, /**< The display is in landscape mode, with the left side up,
                            relative to portrait mode */
    PORTRAIT,          /**< The display is in portrait mode */
    PORTRAIT_FLIPPED   /**< The display is in portrait mode, upside down */
  };

  /**
   * \brief Get the names of video drivers compiled into SDL.
   *
   * \note The video drivers are presented in the order in which
   *       they are normally checked during initialization.
   *
   * \return A vector of names of video drivers.
   *
   * \upstream SDL_GetNumVideoDrivers
   * \upstream SDL_GetVideoDriver
   */
  static std::vector<std::string> GetVideoDrivers();

  /**
   * \brief Initialize the video subsystem, optionally specifying a video driver.
   *
   * \param driver_name Initialize a specific driver by name, or empty string for the
   *                    default video driver.
   *
   * \throw Exception on error.
   *
   * This function initializes the video subsystem; setting up a connection
   * to the window manager, etc, and determines the available display modes
   * and pixel formats, but does not initialize a window or graphics mode.
   *
   * \sa VideoQuit()
   *
   * \upstream SDL_VideoInit
   */
  static void VideoInit(const std::string& driver_name = "");

  /**
   * \brief Shut down the video subsystem.
   *
   * This function closes all windows, and restores the original video mode.
   *
   * \sa VideoInit()
   *
   * \upstream SDL_VideoQuit
   */
  static void VideoQuit();

  /**
   * \brief Get the name of the currently initialized video driver.
   *
   * \return The name of the current video driver or std::nullopt if no driver
   *         has been initialized.
   *
   * \sa GetVideoDrivers()
   *
   * \upstream SDL_GetCurrentVideoDriver
   */
  static std::optional<std::string> GetCurrentVideoDriver();

  /**
   * \brief Get available video displays.
   *
   * \return A vector of available video displays.
   *
   * \upstream SDL_GetNumVideoDisplays
   */
  static std::vector<Display> GetVideoDisplays();

  /**
   * \brief Get the name of a display in UTF-8 encoding.
   *
   * \return The name of a display.
   *
   * \sa GetVideoDisplays()
   *
   * \upstream SDL_GetDisplayName
   */
  std::string GetName() const;

  /**
   * \brief Get the index of a display.
   *
   * \return The index of a display.
   */
  int GetIndex() const;

  /**
   * \brief Get the desktop area represented by a display, with the primary
   *        display located at (0, 0).
   *
   * \sa GetVideoDisplays()
   *
   * \upstream SDL_GetDisplayBounds
   */
  Rectangle GetBounds() const;

  /**
   * \brief Get the usable desktop area represented by a display, with the
   *        primary display located at (0, 0).
   *
   * This is the same area as GetBounds() reports, but with portions
   * reserved by the system removed. For example, on Mac OS X, this subtracts
   * the area occupied by the menu bar and dock.
   *
   * Setting a window to be fullscreen generally bypasses these unusable areas,
   * so these are good guidelines for the maximum space available to a
   * non-fullscreen window.
   *
   * \sa GetBounds()
   * \sa GetVideoDisplays()
   *
   * \upstream SDL_GetDisplayUsableBounds
   */
  Rectangle GetUsableBounds() const;

  /**
   * \brief Get the dots/pixels-per-inch for a display.
   *
   * \note Diagonal, horizontal and vertical DPI can all be returned.
   *
   * \sa GetVideoDisplays()
   *
   * \upstream SDL_GetDisplayDPI
   */
  DPI GetDPI() const;

  /**
   * \brief Get the orientation of a display.
   *
   * \return The orientation of the display, or \ref Orientation::UNKNOWN if it isn't available.
   *
   * \sa GetVideoDisplays()
   *
   * \upstream SDL_GetDisplayOrientation
   */
  Orientation GetOrientation() const;

  /**
   * \brief Get information about available display modes.
   *
   * \note The display modes are sorted in this priority:
   *       \li bits per pixel -> more colors to fewer colors
   *       \li width -> largest to smallest
   *       \li height -> largest to smallest
   *       \li refresh rate -> highest to lowest
   *
   * \upstream SDL_GetNumDisplayModes
   * \upstream SDL_GetDisplayMode
   */
  std::vector<Mode> GetModes() const;

  /**
   * \brief Get information about the desktop display mode.
   *
   * \upstream SDL_GetDesktopDisplayMode
   */
  Mode GetDesktopMode() const;

  /**
   * \brief Get information about the current display mode.
   *
   * \upstream SDL_GetCurrentDisplayMode
   */
  Mode GetCurrentMode() const;

  /**
   * \brief Get the request match to the requested display mode.
   *
   * \param request The desired display mode.
   *
   * The available display modes are scanned, and the request mode matching the
   * requested mode is returned. The mode format and refresh_rate default
   * to the desktop mode if they are 0. The modes are scanned with size
   * being first priority, format being second priority, and
   * finally checking the refresh_rate. If all the available modes are too
   * small, then std::nullopt is returned.
   *
   * \sa GetModes()
   *
   * \upstream SDL_GetClosestDisplayMode
   */
  std::optional<Mode> GetClosestMode(Mode request) const;

  /**
   * \brief Returns whether the screensaver is currently enabled (default off).
   *
   * \sa EnableScreenSaver()
   * \sa DisableScreenSaver()
   *
   * \upstream SDL_IsScreenSaverEnabled
   */
  static bool IsScreenSaverEnabled();

  /**
   * \brief Allow the screen to be blanked by a screensaver.
   *
   * \sa IsScreenSaverEnabled()
   * \sa DisableScreenSaver()
   *
   * \upstream SDL_EnableScreenSaver
   */
  static void EnableScreenSaver();

  /**
   * \brief Prevent the screen from being blanked by a screensaver.
   *
   * \sa IsScreenSaverEnabled()
   * \sa EnableScreenSaver()
   *
   * \upstream SDL_DisableScreenSaver
   */
  static void DisableScreenSaver();

private:
  int index;  ///< Display index

  explicit Display(int index);

  friend class Window;
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_DISPLAY_H

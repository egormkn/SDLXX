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
 * \brief Header for the Window class that represents a graphical window.
 */

#pragma once

#ifndef SDLXX_CORE_WINDOW_H
#define SDLXX_CORE_WINDOW_H

#include <memory>
#include <string>
#include <unordered_set>

#include "sdlxx/core/dimensions.h"
#include "sdlxx/core/display.h"
#include "sdlxx/core/gl.h"
#include "sdlxx/core/point.h"
#include "sdlxx/core/surface.h"

// Declaration of the underlying type
struct SDL_Window;

namespace sdlxx::core {

/**
 * \brief A class for Window exceptions.
 */
class WindowException : public Exception {
  using Exception::Exception;
};

/**
 * \brief A class that represents a graphical window.
 *
 * \upstream SDL_Window
 */
class Window {
public:
  /**
   * \brief A type alias for the window ID.
   */
  using Id = uint32_t;

  /**
   * \brief An enumeration of window flags.
   *
   * \upstream SDL_WindowFlags
   */
  enum class Flag : uint32_t {
    FULLSCREEN = 0x00000001,    /**< fullscreen window */
    OPENGL = 0x00000002,        /**< window usable with OpenGL context */
    SHOWN = 0x00000004,         /**< window is visible */
    HIDDEN = 0x00000008,        /**< window is not visible */
    BORDERLESS = 0x00000010,    /**< no window decoration */
    RESIZABLE = 0x00000020,     /**< window can be resized */
    MINIMIZED = 0x00000040,     /**< window is minimized */
    MAXIMIZED = 0x00000080,     /**< window is maximized */
    INPUT_GRABBED = 0x00000100, /**< window has grabbed input focus */
    INPUT_FOCUS = 0x00000200,   /**< window has input focus */
    MOUSE_FOCUS = 0x00000400,   /**< window has mouse focus */
    FULLSCREEN_DESKTOP = (FULLSCREEN | 0x00001000),
    FOREIGN = 0x00000800,       /**< window not created by SDL */
    ALLOW_HIGHDPI = 0x00002000, /**< window should be created in high-DPI mode if supported.
                                     On macOS NSHighResolutionCapable must be set true in the
                                     application's Driver.plist for this to have any effect. */
    MOUSE_CAPTURE = 0x00004000, /**< window has mouse captured (unrelated to INPUT_GRABBED) */
    ALWAYS_ON_TOP = 0x00008000, /**< window should always be above others */
    SKIP_TASKBAR = 0x00010000,  /**< window should not be added to the taskbar */
    UTILITY = 0x00020000,       /**< window should be treated as a utility window */
    TOOLTIP = 0x00040000,       /**< window should be treated as a tooltip */
    POPUP_MENU = 0x00080000,    /**< window should be treated as a popup menu */
    VULKAN = 0x10000000,        /**< window usable for Vulkan surface */
    METAL = 0x20000000          /**< window usable for Metal view */
  };

  /**
   * \brief A type alias for a set of window flags.
   */
  using Flags = std::unordered_set<Flag>;

  /**
   * \brief An enumeration of window events.
   *
   * \upstream SDL_WindowEventID
   */
  enum class EventID {
    NONE,         /**< Never used */
    SHOWN,        /**< Window has been shown */
    HIDDEN,       /**< Window has been hidden */
    EXPOSED,      /**< Window has been exposed and should be redrawn */
    MOVED,        /**< Window has been moved to data1, data2 */
    RESIZED,      /**< Window has been resized to data1 x data2 */
    SIZE_CHANGED, /**< The window size has changed, either as a result of an API call
                       or through the system or user changing the window size. */
    MINIMIZED,    /**< Window has been minimized */
    MAXIMIZED,    /**< Window has been maximized */
    RESTORED,     /**< Window has been restored to normal size and position */
    ENTER,        /**< Window has gained mouse focus */
    LEAVE,        /**< Window has lost mouse focus */
    FOCUS_GAINED, /**< Window has gained keyboard focus */
    FOCUS_LOST,   /**< Window has lost keyboard focus */
    CLOSE,        /**< The window manager requests that the window be closed */
    TAKE_FOCUS,   /**< Window is being offered a focus (should SetWindowInputFocus() on itself
                       or a subwindow, or ignore) */
    HIT_TEST      /**< Window had a hit test that wasn't SDL_HITTEST_NORMAL. */
  };

  /**
   * \brief Window position that is a default position given by OS.
   * \upstream SDL_WINDOWPOS_UNDEFINED
   */
  static const int WINDOW_POS_UNDEFINED = 0x1FFF0000u;

  /**
   * \brief Window position that specifies the center of the screen.
   * \upstream SDL_WINDOWPOS_CENTERED
   */
  static const int WINDOW_POS_CENTERED = 0x2FFF0000u;

  /**
   * \brief Create a window with the specified position, dimensions, and flags.
   *
   * \param title The title of the window, in UTF-8 encoding.
   * \param width The width of the window, in screen coordinates.
   * \param height The height of the window, in screen coordinates.
   * \param flags The set of window flags.
   * \param position_x The x position of the window, WINDOW_POS_CENTERED, or WINDOW_POS_UNDEFINED.
   * \param position_y The y position of the window, WINDOW_POS_CENTERED, or WINDOW_POS_UNDEFINED.
   *
   * If the window is created with the Flag::ALLOW_HIGHDPI flag, its size
   * in pixels may differ from its size in screen coordinates on platforms with
   * high-DPI support (e.g. iOS and Mac OS X). Use GetSize() to query
   * the client area's size in screen coordinates, and GL::Context::GetDrawableSize(),
   * Vulkan::Context::GetDrawableSize(), or Renderer::GetOutputSize() to query the
   * drawable size in pixels.
   *
   * If the window is created with any of the Flag::OPENGL or Flag::VULKAN flags, then the
   * corresponding LoadLibrary function (GL::LoadLibrary or Vulkan::LoadLibrary) is called and the
   * corresponding UnloadLibrary function is called by ~Window().
   *
   * If Flag::VULKAN is specified and there isn't a working Vulkan driver,
   * Window() will fail because Vulkan::LoadLibrary() will fail.
   *
   * If Flag::METAL is specified on an OS that does not support Metal,
   * Window() will fail.
   *
   * \note On non-Apple devices, SDL requires you to either not link to the
   *       Vulkan loader or link to a dynamic library version. This limitation
   *       may be removed in a future version of SDL.
   *
   * \throw WindowException on error.
   *
   * \upstream SDL_CreateWindow
   */
  Window(const std::string& title, int width, int height, const Flags& flags = {},
         int position_x = WINDOW_POS_CENTERED, int position_y = WINDOW_POS_CENTERED);

  /**
   * \brief Create a new window from an existing native window.
   *
   * \param data A pointer to driver-dependent window creation data,
   *             typically your native window cast to a void*
   *
   * \throw WindowException on error.
   *
   * \upstream SDL_CreateWindowFrom
   */
  explicit Window(const void* data);

  /**
   * \brief Create an empty window
   */
  Window() = default;

  /**
   * \brief Get an existing window from a stored Id.
   *
   * \throw WindowException on error.
   *
   * \param id The numeric Id of a window.
   *
   * \todo Check destructor
   *
   * \upstream SDL_GetWindowFromID
   */
  explicit Window(Id id);

  /**
   * \brief Get the numeric Id of a window, for logging purposes.
   *
   * \return uint32_t The numeric Id of a window
   *
   * \upstream SDL_GetWindowID
   */
  Id GetId() const;

  /**
   * \brief Get the window flags.
   *
   * \return Flags Set of window flags.
   *
   * \upstream SDL_GetWindowFlags
   */
  Flags GetFlags() const;

  /**
   * \brief Get the display associated with a window.
   *
   * \return the display containing the center of the window.
   *
   * \throws Exception on error
   *
   * \upstream SDL_GetWindowDisplayIndex
   */
  Display GetDisplay() const;

  /**
   * \brief Set the display mode used when a fullscreen window is visible to a default display mode.
   *
   * By default the window's dimensions and the desktop format and refresh rate are used.
   *
   * \throws WindowException when setting the display mode failed.
   *
   * \sa GetDisplayMode()
   * \sa SetFullscreen()
   *
   * \upstream SDL_SetWindowDisplayMode
   */
  void SetDefaultDisplayMode();

  /**
   * \brief Set the display mode used when a fullscreen window is visible.
   *
   * By default the window's dimensions and the desktop format and refresh rate are used.
   *
   * \param mode The mode to use.
   *
   * \throws WindowException when setting the display mode failed.
   *
   * \sa GetDisplayMode()
   * \sa SetFullscreen()
   *
   * \upstream SDL_SetWindowDisplayMode
   */
  void SetDisplayMode(const Display::Mode& mode);

  /**
   * \brief Get information about the display mode used when a fullscreen window is visible.
   *
   * \sa SetDisplayMode()
   * \sa SetFullscreen()
   *
   * \return Display mode that is used when a fullscreen window is visible.
   *
   * \upstream SDL_GetWindowDisplayMode
   */
  Display::Mode GetDisplayMode() const;

  /**
   *  \brief Get the pixel format associated with the window.
   *
   *  \upstream SDL_GetWindowPixelFormat
   */
  uint32_t GetPixelFormat() const;

  /**
   * \brief Set the title of a window, in UTF-8 format.
   *
   * \param title The new window title.
   *
   * \upstream SDL_SetWindowTitle
   */
  void SetTitle(const std::string& title);

  /**
   * \brief Get the title of a window, in UTF-8 format.
   *
   * \return std::string The window title.
   *
   * \upstream SDL_GetWindowTitle
   */
  std::string GetTitle() const;

  /**
   * \brief Set the icon for a window.
   *
   * \param icon The icon for the window.
   *
   * \upstream SDL_SetWindowIcon
   */
  void SetIcon(const Surface& icon);

  /**
   * \brief Associate an arbitrary named pointer with a window.
   *
   * \param name     The name of the pointer.
   * \param userdata The associated pointer.
   *
   * \return The previous value associated with 'name'.
   *
   * \note The name is case-sensitive.
   *
   * \sa GetData()
   *
   * \upstream SDL_SetWindowData
   */
  void* SetData(const std::string& name, void* userdata);

  /**
   * \brief Retrieve the data pointer associated with a window.
   *
   * \param name The name of the pointer.
   *
   * \return The value associated with 'name'
   *
   * \sa SetData()
   *
   * \upstream SDL_GetWindowData
   */
  void* GetData(const std::string& name) const;

  /**
   * \brief Set the position of a window.
   *
   * \param position The X and Y coordinates of the window in screen coordinates,
   *                 or WINDOW_POS_CENTERED or WINDOW_POS_UNDEFINED.
   *
   * \note The window coordinate origin is the upper left corner of the display.
   *
   * \sa GetPosition()
   *
   * \upstream SDL_SetWindowPosition
   */
  void SetPosition(Point position);

  /**
   * \brief Get the position of a window.
   *
   * \return Point The X and Y coordinates of the window, in screen coordinates.
   *
   * \sa SetPosition()
   *
   * \upstream SDL_GetWindowPosition
   */
  Point GetPosition() const;

  /**
   * \brief Set the size of a window's client area.
   *
   * \param dimensions The width and height of the window, in screen coordinates. Must be >0.
   *
   * \note Fullscreen windows automatically match the size of the display mode,
   *       and you should use SetDisplayMode() to change their size.
   *
   * The window size in screen coordinates may differ from the size in pixels, if
   * the window was created with Flag::ALLOW_HIGHDPI on a platform with
   * high-dpi support (e.g. iOS or OS X). Use GL::Context::GetDrawableSize() or
   * Renderer::GetOutputSize() to get the real client area size in pixels.
   *
   * \sa GetSize()
   * \sa SetDisplayMode()
   *
   * \upstream SDL_SetWindowSize
   */
  void SetSize(Dimensions dimensions);

  /**
   * \brief Get the size of a window's client area
   *
   * \return Dimensions The width and height of the window, in screen coordinates.
   *
   * The window size in screen coordinates may differ from the size in pixels, if
   * the window was created with Flag::ALLOW_HIGHDPI on a platform with
   * high-dpi support (e.g. iOS or OS X). Use GL::Context::GetDrawableSize() or
   * Renderer::GetOutputSize() to get the real client area size in pixels.
   *
   * \sa SetSize()
   *
   * \upstream SDL_GetWindowSize
   */
  Dimensions GetSize() const;

  /**
   * \brief A structure to represent window border size.
   */
  struct Borders {
    int top, left, bottom, right;
  };

  /**
   * \brief Get the size of a window's borders (decorations) around the client area.
   *
   * \note if this function fails, the size values will be initialized to 0, 0, 0, 0,
   *       as if the window was borderless.
   *
   * \upstream SDL_GetWindowBordersSize
   */
  Borders GetBordersSize() const;

  /**
   * \brief Set the minimum size of a window's client area.
   *
   * \param dimensions The minimum width and height of the window, must be >0
   *
   * \note You can't change the minimum size of a fullscreen window, it
   *       automatically matches the size of the display mode.
   *
   * \upstream SDL_SetWindowMinimumSize
   */
  void SetMinimumSize(Dimensions dimensions);

  /**
   * \brief Get the minimum size of a window's client area.
   *
   * \return Dimensions The minimum width and height of the window.
   *
   * \upstream SDL_GetWindowMinimumSize
   */
  Dimensions GetMinimumSize() const;

  /**
   * \brief Set the maximum size of a window's client area.
   *
   * \param dimensions The maximum width and height of the window, must be >0
   *
   * \note You can't change the maximum size of a fullscreen window, it
   *       automatically matches the size of the display mode.
   *
   * \upstream SDL_SetWindowMaximumSize
   */
  void SetMaximumSize(Dimensions dimensions);

  /**
   * \brief Get the maximum size of a window's client area.
   *
   * \return Dimensions The maximum width and height of the window.
   *
   * \upstream SDL_GetWindowMaximumSize
   */
  Dimensions GetMaximumSize() const;

  /**
   * \brief Set the border state of a window
   *
   * This will add or remove the window's Flag::BORDERLESS flag and add or remove the
   * border from the actual window. This is a no-op if the window's border
   * already matches the requested state.
   *
   * \param is_bordered false to remove border, true to add border
   *
   * \note You can't change the border state of a fullscreen window
   *
   * \upstream SDL_SetWindowBordered
   */
  void SetBordered(bool is_bordered);

  /**
   * \brief Set the user-is_resizable state of a window
   *
   * This will add or remove the window's Flag::RESIZABLE flag and allow/disallow user
   * resizing of the window. This is a no-op if the window's is_resizable state
   * already matches the requested state.
   *
   * \param is_resizable true to allow resizing, false to disallow.
   *
   * \note You can't change the is_resizable state of a fullscreen window.
   *
   * \upstream SDL_SetWindowResizable
   */
  void SetResizable(bool is_resizable);

  /**
   * \brief Show a window
   *
   * \upstream SDL_ShowWindow
   */
  void Show();

  /**
   * \brief Hide a window
   *
   * \upstream SDL_HideWindow
   */
  void Hide();

  /**
   * \brief Raise a window above other windows and set the input focus
   *
   * \upstream SDL_RaiseWindow
   */
  void Raise();

  /**
   * \brief Make window as large as possible
   *
   * \upstream SDL_MaximizeWindow
   */
  void Maximize();

  /**
   * \brief Minimize a window to an iconic representation
   *
   * \upstream SDL_MinimizeWindow
   */
  void Minimize();

  /**
   * \brief Restore the size and position of a minimized or maximized window
   *
   * \upstream SDL_RestoreWindow
   */
  void Restore();

  /**
   * \brief Set a window's fullscreen state to a "real" fullscreen with a videomode change
   *
   * \upstream SDL_SetWindowFullscreen
   */
  void SetFullscreen();

  /**
   * \brief Set a window's fullscreen state to a "fake" fullscreen that takes the size of the
   * desktop
   *
   * \upstream SDL_SetWindowFullscreen
   */
  void SetFullscreenDesktop();

  /**
   * \brief Set a window's fullscreen state to a windowed mode.
   *
   * \upstream SDL_SetWindowFullscreen
   */
  void SetWindowed();

  /**
   * \brief Get the Surface associated with the window.
   *
   * A new surface will be created with the optimal format for the window, if necessary.
   * This surface will be freed when the window is destroyed.
   *
   * \note You may not combine this with 3D or the rendering API on this window.
   *
   * \sa UpdateSurface()
   * \sa UpdateSurfaceRectangles()
   *
   * \return Surface The window's framebuffer surface.
   *
   * \throw WindowException on error.
   *
   * \upstream SDL_GetWindowSurface
   */
  Surface GetSurface() const;

  /**
   * \brief Copy the window surface to the screen.
   *
   * \throw WindowException on error.
   *
   * \sa GetSurface()
   * \sa UpdateSurfaceRects()
   *
   * \upstream SDL_UpdateWindowSurface
   */
  void UpdateSurface();

  /**
   * \brief Copy a number of rectangles on the window surface to the screen.
   *
   * \throw WindowException on error.
   *
   * \sa GetSurface()
   * \sa UpdateSurface()
   *
   * \upstream SDL_UpdateWindowSurfaceRects
   */
  void UpdateSurfaceRectangles(const std::vector<Rectangle>& rectangles);

  /**
   * \brief Set a window's input grab mode.
   *
   * \param is_grabbed This is true to grab input, and false to release input.
   *
   * If the caller enables a grab while another window is currently grabbed,
   * the other window loses its grab in favor of the caller's window.
   *
   * \sa GetGrab()
   *
   * \upstream SDL_SetWindowGrab
   */
  void SetGrab(bool is_grabbed);

  /**
   * \brief Get a window's input grab mode.
   *
   * \return This returns true if input is grabbed, and false otherwise.
   *
   * \sa SetGrab()
   *
   * \upstream SDL_GetWindowGrab
   */
  bool GetGrab() const;

  /**
   * \brief Get the window that currently has an input grab enabled.
   *
   * \todo Check destructor
   *
   * \return This returns the window if input is grabbed, and NULL otherwise.
   *
   * \sa SetGrab()
   *
   * \upstream SDL_GetGrabbedWindow
   */
  static Window& GetGrabbed();

  /**
   * \brief Set the brightness (gamma correction) for a window.
   *
   * \throw WindowException if setting the brightness isn't supported.
   *
   * \sa GetBrightness()
   * \sa SetGammaRamp()
   *
   * \upstream SDL_SetWindowBrightness
   */
  void SetBrightness(float brightness);

  /**
   * \brief Get the brightness (gamma correction) for a window.
   *
   * \return The last brightness value passed to SetBrightness()
   *
   * \sa SetBrightness()
   *
   * \upstream SDL_GetWindowBrightness
   */
  float GetBrightness() const;

  /**
   * \brief Set the opacity for a window
   *
   * \param opacity Opacity (0.0f - transparent, 1.0f - opaque)
   *                This will be clamped internally between 0.0f and 1.0f.
   *
   * \throw WindowException if setting the opacity isn't supported.
   *
   * \sa GetOpacity()
   *
   * \upstream SDL_SetWindowOpacity
   */
  void SetOpacity(float opacity);

  /**
   * \brief Get the opacity of a window.
   *
   * If transparency isn't supported on this platform, opacity will be reported as 1.0f.
   *
   * \throw WindowException on error (invalid window, etc).
   *
   * \return Opacity (0.0f - transparent, 1.0f - opaque)
   *
   * \sa SDL_GetWindowOpacity()
   */
  float GetOpacity() const;

  // TODO: SDL_SetWindowModalFor, SDL_SetWindowInputFocus, SDL_SetWindowGammaRamp,
  // SDL_GetWindowGammaRamp, SDL_HitTestResult, SDL_HitTest, SDL_SetWindowHitTest

  /**
   * \brief Get the raw pointer to SDL_Window.
   *
   * After this operation you are responsible for freeing the memory of the window.
   *
   * \return A pointer to the SDL_Window
   */
  SDL_Window* Release();

  // Friend declarations
  friend class Renderer;
  friend class GL::Context;

protected:
  struct Deleter {
    void operator()(SDL_Window* ptr) const;
  };

  std::unique_ptr<SDL_Window, Deleter> window_ptr;
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_WINDOW_H

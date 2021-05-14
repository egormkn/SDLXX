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
 * \file window.h
 *
 * \brief A class that represents a graphical window.
 */

#pragma once

#ifndef SDLXX_CORE_WINDOW_H
#define SDLXX_CORE_WINDOW_H

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "sdlxx/core/dimensions.h"
#include "sdlxx/core/display.h"
#include "sdlxx/core/point.h"
#include "sdlxx/core/renderer.h"

namespace sdlxx::core {

// class Surface;  // Forward declaration of a Surface class

/**
 * \brief A class that represents a graphical window.
 */
class Window {  // See SDL_Window
public:
  /**
   * \brief A type alias for the window ID.
   */
  using Id = uint32_t;

  /**
   * \brief An enumeration of window flags.
   */
  enum class Flag : uint32_t {  // See SDL_WindowFlags
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
                                     application's Info.plist for this to have any effect. */
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
   */
  enum class EventID {  // See SDL_WindowEventID
    NONE,               /**< Never used */
    SHOWN,              /**< Window has been shown */
    HIDDEN,             /**< Window has been hidden */
    EXPOSED,            /**< Window has been exposed and should be redrawn */
    MOVED,              /**< Window has been moved to data1, data2 */
    RESIZED,            /**< Window has been resized to data1 x data2 */
    SIZE_CHANGED,       /**< The window size has changed, either as a result of an API call
                             or through the system or user changing the window size. */
    MINIMIZED,          /**< Window has been minimized */
    MAXIMIZED,          /**< Window has been maximized */
    RESTORED,           /**< Window has been restored to normal size and position */
    ENTER,              /**< Window has gained mouse focus */
    LEAVE,              /**< Window has lost mouse focus */
    FOCUS_GAINED,       /**< Window has gained keyboard focus */
    FOCUS_LOST,         /**< Window has lost keyboard focus */
    CLOSE,              /**< The window manager requests that the window be closed */
    TAKE_FOCUS,         /**< Window is being offered a focus (should SetWindowInputFocus() on itself
                             or a subwindow, or ignore) */
    HIT_TEST            /**< Window had a hit test that wasn't SDL_HITTEST_NORMAL. */
  };

  /**
   * \brief Window position that is a default position given by OS.
   */
  static const int WINDOW_POS_UNDEFINED = 0x1FFF0000u;  // See SDL_WINDOWPOS_UNDEFINED

  /**
   * \brief Window position that specifies the center of the screen.
   */
  static const int WINDOW_POS_CENTERED = 0x2FFF0000u;  // See SDL_WINDOWPOS_CENTERED

  /**
   * \brief Create a window with the specified position, dimensions, and flags.
   *
   * \param title The title of the window, in UTF-8 encoding.
   * \param width The width of the window, in screen coordinates.
   * \param height The height of the window, in screen coordinates.
   * \param flags The set of window \ref Flags "flags".
   * \param position_x The x position of the window, WINDOW_POS_CENTERED, or WINDOW_POS_UNDEFINED.
   * \param position_y The y position of the window, WINDOW_POS_CENTERED, or WINDOW_POS_UNDEFINED.
   *
   * If the window is created with the \ref Flag::ALLOW_HIGHDPI flag, its size
   * in pixels may differ from its size in screen coordinates on platforms with
   * high-DPI support (e.g. iOS and Mac OS X). Use \ref GetSize() to query
   * the client area's size in screen coordinates, and \ref GL::GetDrawableSize(),
   * \ref Vulkan::GetDrawableSize(), or \ref Renderer::GetOutputSize() to query the
   * drawable size in pixels.
   *
   * If the window is created with any of the \ref Flag::OPENGL or
   * \ref Flag::VULKAN flags, then the corresponding LoadLibrary function
   * (\ref GL::LoadLibrary or \ref Vulkan::LoadLibrary) is called and the
   * corresponding UnloadLibrary function is called by \ref ~Window().
   *
   * If \ref Flag::VULKAN is specified and there isn't a working Vulkan driver,
   * \ref Window() will fail because \ref Vulkan::LoadLibrary() will fail.
   *
   * If \ref Flag::METAL is specified on an OS that does not support Metal,
   * \ref Window() will fail.
   *
   * \note On non-Apple devices, SDL requires you to either not link to the
   *       Vulkan loader or link to a dynamic library version. This limitation
   *       may be removed in a future version of SDL.
   */
  Window(const std::string& title, int width, int height, const Flags& flags = {},
         int position_x = WINDOW_POS_CENTERED, int position_y = WINDOW_POS_CENTERED);

  /**
   * \brief Create a new window from an existing native window.
   *
   * \param data A pointer to driver-dependent window creation data,
   *             typically your native window cast to a void*
   */
  explicit Window(const void* data);

  /**
   * \brief Get an existing window by a stored Id.
   *
   * \param id The numeric Id of a window.
   */
  explicit Window(Id id);

  /**
   * \brief Get the numeric Id of a window, for logging purposes.
   *
   * \return uint32_t The numeric Id of a window
   */
  Id GetId() const;

  /**
   * \brief Get the window flags.
   *
   * \return Flags Set of window flags.
   */
  Flags GetFlags() const;

  /**
   * \brief Destroy the window
   */
  ~Window();

  /**
   * \brief Get the display index associated with a window.
   *
   * \return the display index of the display containing the center of the
   *          window.
   * \throws Exception on error
   */
  Display GetDisplay() const;

  /**
   * \brief Set the display mode used when a fullscreen window is visible.
   *
   * By default the window's dimensions and the desktop format and refresh rate
   * are used.
   *
   * \param mode The mode to use, or NULL for the default mode.
   *
   * \throws Exception when setting the display mode failed (-1).
   *
   * \sa GetDisplayMode()
   * \sa SetFullscreen()
   */
  void SetDisplayMode(const Display::Mode& mode);

  /**
   * \brief Set the default display mode to be used when a fullscreen window is visible.
   *
   * By default the window's dimensions and the desktop format and refresh rate
   * are used.
   *
   * \throws Exception when setting the display mode failed (-1).
   *
   * \sa GetDisplayMode()
   * \sa SetFullscreen()
   */
  void SetDefaultDisplayMode();

  /**
   *  \brief Get information about the display mode used when a fullscreen
   *         window is visible.
   *
   *  \sa SetDisplayMode()
   *  \sa SetFullscreen()
   */
  Display::Mode GetDisplayMode() const;

  /**
   *  \brief Get the pixel format associated with the window.
   */
  uint32_t GetPixelFormat() const;

  /**
   * \brief Set the title of a window, in UTF-8 format.
   *
   * \param title The new window title.
   */
  void SetTitle(const std::string& title);

  /**
   * \brief Get the title of a window, in UTF-8 format.
   *
   * \return std::string The window title.
   */
  std::string GetTitle() const;

  /**
   * \brief Set the icon for a window.
   *
   * \param icon The icon for the window.
   */
  void SetIcon(std::shared_ptr<Surface> icon);

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
   */
  void* GetData(const std::string& name) const;

  /**
   * \brief Set the position of a window.
   *
   * \param position The X and Y coordinates of the window in screen coordinates,
   *                 or \ref WINDOW_POS_CENTERED or \ref WINDOW_POS_UNDEFINED.
   *
   * \note The window coordinate origin is the upper left corner of the display.
   *
   * \sa GetPosition()
   */
  void SetPosition(const Point& position);

  /**
   * \brief Get the position of a window.
   *
   * \return Point The X and Y coordinates of the window, in screen coordinates.
   *
   * \sa SetPosition()
   */
  Point GetPosition() const;

  /**
   * \brief Set the size of a window's client area.
   *
   * \param dimensions The width and height of the window, in screen coordinates. Must be >0.
   *
   * \note Fullscreen windows automatically match the size of the display mode,
   *       and you should use \ref SetDisplayMode() to change their size.
   *
   * The window size in screen coordinates may differ from the size in pixels, if
   * the window was created with \ref Flag::ALLOW_HIGHDPI on a platform with
   * high-dpi support (e.g. iOS or OS X). Use \ref GL::GetDrawableSize() or
   * \ref Renderer::GetOutputSize() to get the real client area size in pixels.
   *
   * \sa GetSize()
   * \sa SetDisplayMode()
   */
  void SetSize(Dimensions dimensions);

  /**
   * \brief Get the size of a window's client area
   *
   * \return Dimensions Window dimensions.
   *
   * The window size in screen coordinates may differ from the size in pixels, if
   * the window was created with \ref Flag::ALLOW_HIGHDPI on a platform with
   * high-dpi support (e.g. iOS or OS X). Use \ref GL::GetDrawableSize() or
   * \ref Renderer::GetOutputSize() to get the real client area size in pixels.
   *
   * \sa SetSize()
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
   *       as if the window in question was borderless.
   */
  Borders GetBorders() const;

  /**
   * \brief Set the minimum size of a window's client area.
   *
   * \param dimensions The minimum width and height of the window, must be >0
   *
   * \note You can't change the minimum size of a fullscreen window, it
   *       automatically matches the size of the display mode.
   */
  void SetMinimumSize(Dimensions dimensions);

  /**
   * \brief Get the minimum size of a window's client area.
   */
  Dimensions GetMinimumSize() const;

  /**
   * \brief Set the maximum size of a window's client area.
   *
   * \param dimensions The maximum width and height of the window, must be >0
   *
   * \note You can't change the maximum size of a fullscreen window, it
   *       automatically matches the size of the display mode.
   */
  void SetMaximumSize(Dimensions dimensions);

  /**
   * \brief Get the maximum size of a window's client area.
   */
  Dimensions GetMaximumSize() const;

  // TODO: Below

  /**
   * @brief Set the border state of a window
   *
   * This will add or remove the window's BORDERLESS flag and add or remove the
   * border from the actual window. This is a no-op if the window's border
   * already matches the requested state.
   *
   * @param bordered false to remove border, true to add border
   *void setResizable(bool resizable)
   * @note You can't change the border state of a fullscreen window
   */
  void setBordered(bool bordered);

  /**
   * @brief Set the user-resizable state of a window
   *
   * This will add or remove the window's RESIZABLE flag and allow/disallow user
   * resizing of the window. This is a no-op if the window's resizable state
   * already matches the requested state.
   *
   * @param resizable true to allow resizing, false to disallow.
   *
   * @note You can't change the resizable state of a fullscreen window.
   */
  void setResizable(bool resizable);

  /**
   * @brief Show a window
   */
  void show();

  /**
   * @brief Hide a window
   */
  void hide();

  /**
   * @brief Raise a window above other windows and set the input focus
   */
  void raise();

  /**
   * @brief Make window as large as possible
   */
  void maximize();

  /**
   * @brief Minimize a window to an iconic representation
   */
  void minimize();

  /**
   * @brief Restore the size and position of a minimized or maximized window
   */
  void restore();

  /**
   * @brief Set a window's fullscreen state
   *
   * @param options Window options
   */
  void setFullscreen(const Flags& flags = {});

  /**
   * @brief Get the surface associated with the window
   *
   * A new surface will be created with the optimal format for the window,
   * if necessary. This surface will be freed when the window is destroyed.
   *
   * @note You may not combine this with 3D or the rendering API on this window
   *
   * @return std::shared_ptr<Surface> The window's framebuffer surface
   */
  std::shared_ptr<Surface> getSurface();

  /**
   * @brief Copy the window surface to the screen
   */
  void updateSurface();

  // TODO: window surface methods, set/get grab and other methods

  /**
   * @brief Get the renderer associated with the window.
   *
   * If no renderer is associated with the window, a new one will be created.
   *
   * @param driver The index of the rendering driver to initialize, or -1 to
   * initialize the first one supporting the requested options.
   * @param options The set of requested options
   *
   * @return Renderer The renderer that is associated with the window
   */
  std::shared_ptr<Renderer> getRenderer(int driver = -1,
                                        const std::unordered_set<Renderer::Option>& options = {});

private:
  void* window_ptr = nullptr;

  friend class Renderer;

  std::shared_ptr<Renderer> renderer;

  friend class Surface;

  std::shared_ptr<Surface> surface;

  // Deleted copy constructor
  // This class is not copyable
  Window(const Window&) = delete;

  // Deleted copy assignment operator
  // This class is not copyable
  Window& operator=(const Window&) = delete;

  Window(Window&& other) = delete;

  Window& operator=(Window&&) = delete;
};

Window::Flags operator|(const Window::Flag& lhs, const Window::Flag& rhs);

Window::Flags operator|(Window::Flags&& lhs, const Window::Flag& rhs);

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_WINDOW_H

/**
 * @file Window.h
 * @author Egor Makarenko
 * @brief Class that represents graphical windows
 */

#pragma once

#ifndef SDLXX_CORE_WINDOW_H
#define SDLXX_CORE_WINDOW_H

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include <sdlxx/core/Dimensions.h>
#include <sdlxx/core/Renderer.h>

namespace sdlxx::core {

/**
 * @brief Class that represents graphical windows
 */
class Window {
public:
  /**
   * @brief An enumeration of window options
   */
  enum class Option {
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
    FOREIGN = 0x00000800, /**< window not created by SDL */
    ALLOW_HIGHDPI =
        0x00002000, /**< window should be created in high-DPI mode if supported.
                     * On macOS NSHighResolutionCapable must be set true in the
                     * application's Info.plist for this to have any effect.
                     */
    MOUSE_CAPTURE = 0x00004000, /**< window has mouse captured
                                              (unrelated to INPUT_GRABBED) */
    ALWAYS_ON_TOP = 0x00008000, /**< window should always be above others */
    SKIP_TASKBAR = 0x00010000, /**< window should not be added to the taskbar */
    UTILITY = 0x00020000, /**< window should be treated as a utility window */
    TOOLTIP = 0x00040000, /**< window should be treated as a tooltip */
    POPUP_MENU = 0x00080000, /**< window should be treated as a popup menu */
    VULKAN = 0x10000000      /**< window usable for Vulkan surface */
  };

  /**
   * @brief An enumeration of window events
   */
  enum class Event {
    NONE,         /**< Never used */
    SHOWN,        /**< Window has been shown */
    HIDDEN,       /**< Window has been hidden */
    EXPOSED,      /**< Window has been exposed and should be
                                       redrawn */
    MOVED,        /**< Window has been moved to data1, data2
                   */
    RESIZED,      /**< Window has been resized to data1xdata2 */
    SIZE_CHANGED, /**< The window size has changed, either as
                                       a result of an API call or through the
                                       system or user changing the window size.
                                   */
    MINIMIZED,    /**< Window has been minimized */
    MAXIMIZED,    /**< Window has been maximized */
    RESTORED,     /**< Window has been restored to normal size
                                       and position */
    ENTER,        /**< Window has gained mouse focus */
    LEAVE,        /**< Window has lost mouse focus */
    FOCUS_GAINED, /**< Window has gained keyboard focus */
    FOCUS_LOST,   /**< Window has lost keyboard focus */
    CLOSE,        /**< The window manager requests that the window be
                                     closed */
    TAKE_FOCUS,   /**< Window is being offered a focus (should
                                     SetWindowInputFocus() on itself or a
                                     subwindow, or ignore) */
    HIT_TEST      /**< Window had a hit test that wasn't
                                     SDL_HITTEST_NORMAL. */
  };

  /**
   * @brief Window position that specifies the center of the screen
   */
  static const int WINDOW_CENTERED;

  /**
   * @brief Window position that is a default position given by OS
   */
  static const int WINDOW_UNDEFINED;

  /**
   * @brief Construct a new window
   *
   * @param title the title of the window, in UTF-8 encoding
   * @param width the width of the window, in screen coordinates
   * @param height the height of the window, in screen coordinates
   * @param options set of window options
   * @param position_x the x position of the window, WINDOW_CENTERED, or
   * WINDOW_UNDEFINED
   * @param position_y the y position of the window, WINDOW_CENTERED, or
   * WINDOW_UNDEFINED
   */
  Window(const std::string& title, int width, int height,
         const std::unordered_set<Option>& options = {},
         int position_x = WINDOW_UNDEFINED, int position_y = WINDOW_UNDEFINED);

  /**
   * @brief Construct a new window from an existing native window
   *
   * @param data a pointer to driver-dependent window creation data, typically
   * your native window cast to a void*
   */
  Window(const void* data);

  /**
   * @brief Get window id for logging purposes
   *
   * @return uint32_t window id
   */
  uint32_t getId() const;

  /**
   * @brief Destroy the window
   */
  ~Window();

  /**
   * @brief Change window title
   *
   * @param title new window title
   */
  void setTitle(const std::string& title);

  /**
   * @brief Minimize window
   */
  void minimize();

  /**
   * @brief Maximize window
   */
  void maximize();

  /**
   * @brief Restore window size
   */
  void restore();

  /**
   * @brief Create a new renderer and attach it to this window
   *
   * @return Renderer that is attached to this window
   */
  std::shared_ptr<Renderer> createRenderer(
      int driver_index = -1,
      const std::unordered_set<Renderer::Option>& options = {});

  /**
   * @brief Get the renderer attached to this window
   *
   * @return Renderer that is attached to this window
   */
  std::shared_ptr<Renderer> getRenderer() const;

  /**
   * @brief Get the size of a window's client area
   *
   * @return Dimensions Window dimensions
   */
  Dimensions getDimensions() const;

private:
  void* window = nullptr;
  std::shared_ptr<Renderer> renderer;

  static std::unordered_map<uint32_t, void*> active_windows;
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_WINDOW_H

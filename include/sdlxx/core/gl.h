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
 * \brief Header for the OpenGL support functions.
 */

#ifndef SDLXX_CORE_GL_H
#define SDLXX_CORE_GL_H

#include <string>

#include "sdlxx/core/dimensions.h"
#include "sdlxx/core/exception.h"

namespace sdlxx::core {

class Window;

/**
 * \brief A class for OpenGL exceptions.
 */
class GlException : public Exception {
  using Exception::Exception;
};

/**
 * \brief OpenGL support functions.
 */
namespace GL {

/**
 * \brief OpenGL configuration attributes.
 * \upstream SDL_GLattr
 */
enum class Attribute {
  RED_SIZE,
  GREEN_SIZE,
  BLUE_SIZE,
  ALPHA_SIZE,
  BUFFER_SIZE,
  DOUBLEBUFFER,
  DEPTH_SIZE,
  STENCIL_SIZE,
  ACCUM_RED_SIZE,
  ACCUM_GREEN_SIZE,
  ACCUM_BLUE_SIZE,
  ACCUM_ALPHA_SIZE,
  STEREO,
  MULTISAMPLEBUFFERS,
  MULTISAMPLESAMPLES,
  ACCELERATED_VISUAL,
  RETAINED_BACKING,
  CONTEXT_MAJOR_VERSION,
  CONTEXT_MINOR_VERSION,
  CONTEXT_EGL,
  CONTEXT_FLAGS,
  CONTEXT_PROFILE_MASK,
  SHARE_WITH_CURRENT_CONTEXT,
  FRAMEBUFFER_SRGB_CAPABLE,
  CONTEXT_RELEASE_BEHAVIOR,
  CONTEXT_RESET_NOTIFICATION,
  CONTEXT_NO_ERROR
};

/**
 * \upstream SDL_GLprofile
 */
enum class Profile {
  CORE = 0x0001,
  COMPATIBILITY = 0x0002,
  ES = 0x0004 /**< GLX_CONTEXT_ES2_PROFILE_BIT_EXT */
};

/**
 * \brief Dynamically load an OpenGL library.
 *
 * \param path The platform dependent OpenGL library name, or empty string to use the
 *             default OpenGL library.
 *
 * \throw GlException if the library couldn't be loaded.
 *
 * This should be done after initializing the video driver, but before creating any OpenGL windows.
 * If no OpenGL library is loaded, the default library will be loaded upon creation of the first
 * OpenGL window.
 *
 * \note If you do this, you need to retrieve all of the GL functions used in
 *       your program from the dynamic library using GL::GetProcAddress().
 *
 * \sa GL::GetProcAddress()
 * \sa GL::UnloadLibrary()
 *
 * \upstream SDL_GL_LoadLibrary
 */
void LoadLibrary(const std::string& path = "");

/**
 * \brief Get the address of an OpenGL function.
 * \upstream SDL_GL_GetProcAddress
 */
void* GetProcAddress(const std::string& proc);

/**
 * \brief Unload the OpenGL library previously loaded by GL::LoadLibrary().
 *
 * \sa GL::LoadLibrary()
 *
 * \upstream SDL_GL_UnloadLibrary
 */
void UnloadLibrary();

/**
 * \brief A class for OpenGL context.
 * \upstream SDL_GLContext
 */
class Context {
public:
  /**
   * \upstream SDL_GLcontextFlag
   */
  enum class Flag {
    DEBUG = 0x0001,
    FORWARD_COMPATIBLE = 0x0002,
    ROBUST_ACCESS = 0x0004,
    RESET_ISOLATION = 0x0008
  };

  /**
   * \upstream SDL_GLcontextReleaseFlag
   */
  enum class ReleaseFlag { RELEASE_BEHAVIOR_NONE = 0x0000, RELEASE_BEHAVIOR_FLUSH = 0x0001 };

  /**
   * \upstream SDL_GLContextResetNotification
   */
  enum class ResetNotification { RESET_NO_NOTIFICATION = 0x0000, RESET_LOSE_CONTEXT = 0x0001 };

  /**
   * \brief Return true if an OpenGL extension is supported for the current context.
   *
   * \upstream SDL_GL_ExtensionSupported
   */
  static bool ExtensionSupported(const std::string& extension);

  /**
   * \brief Reset all previously set OpenGL context attributes to their default values.
   * \upstream SDL_GL_ResetAttributes
   */
  static void ResetAttributes();

  /**
   * \brief Set an OpenGL window attribute before window creation.
   *
   * \throw GlException if the attribute could not be set.
   *
   * \upstream SDL_GL_SetAttribute
   */
  static void SetAttribute(Attribute attr, int value);

  /**
   * \brief Get the actual value for an attribute from the current context.
   *
   * \throw GlException if the attribute could not be retrieved.
   *
   * \return The value of the attribute.
   *
   * \upstream SDL_GL_GetAttribute
   */
  static int GetAttribute(Attribute attr);

  /**
   * \brief Create an OpenGL context for use with an OpenGL window, and make it current.
   *
   * \upstream SDL_GL_CreateContext
   */
  explicit Context(Window& window);

  /**
   * \brief Delete an OpenGL context.
   *
   * \sa GL::CreateContext()
   *
   * \upstream SDL_GL_DeleteContext
   */
  ~Context();

  /**
   * \brief Set up an OpenGL context for rendering into an OpenGL window.
   *
   * \note The context must have been created with a compatible window.
   *
   * \upstream SDL_GL_MakeCurrent
   */
  void MakeCurrent(Window& window);

  /**
   * \brief Get the currently active OpenGL window.
   *
   * \todo Think about the implementation
   *
   * \upstream SDL_GL_GetCurrentWindow
   */
  static Window& GetCurrentWindow();

  /**
   * \brief Get the currently active OpenGL context.
   *
   * \upstream SDL_GL_GetCurrentContext
   */
  static void* GetCurrentContext();

  /**
   * \brief Get the size of a window's underlying drawable in pixels (for use with glViewport).
   *
   * \param window Window from which the drawable size should be queried
   *
   * This may differ from Window::GetSize() if we're rendering to a high-DPI drawable, i.e. the
   * window was created with SDL_WINDOW_ALLOW_HIGHDPI on a platform with high-DPI support (Apple
   * calls this "Retina"), and not disabled by the SDL_HINT_VIDEO_HIGHDPI_DISABLED hint.
   *
   * \sa Window::GetSize()
   * \sa Window::Window()
   *
   * \upstream SDL_GL_GetDrawableSize
   */
  static Dimensions GetDrawableSize(Window& window);

  /**
   * \brief Set the swap interval for the current OpenGL context.
   *
   * \param interval 0 for immediate updates, 1 for updates synchronized with the
   *                 vertical retrace. If the system supports it, you may
   *                 specify -1 to allow late swaps to happen immediately
   *                 instead of waiting for the next retrace.
   *
   * \throw GlException if setting the swap interval is not supported.
   *
   * \sa GetSwapInterval()
   *
   * \upstream SDL_GL_SetSwapInterval
   */
  static void SetSwapInterval(int interval);

  /**
   * \brief Get the swap interval for the current OpenGL context.
   *
   * \return 0 if there is no vertical retrace synchronization, 1 if the buffer
   *         swap is synchronized with the vertical retrace, and -1 if late
   *         swaps happen immediately instead of waiting for the next retrace.
   *         If the system can't determine the swap interval, or there isn't a
   *         valid current context, this will return 0 as a safe default.
   *
   * \sa SetSwapInterval()
   *
   * \upstream SDL_GL_GetSwapInterval
   */
  static int GetSwapInterval();

  /**
   * \brief Swap the OpenGL buffers for a window, if double-buffering is supported.
   *
   * \upstream SDL_GL_SwapWindow
   */
  static void SwapWindow(Window& window);

  // Deleted copy constructor
  Context(const Context& other) = delete;

  // Deleted copy assignment operator
  Context& operator=(const Context& other) = delete;

  // Deleted move constructor
  Context(Context&& other) = delete;

  // Deleted move assignment operator
  Context& operator=(Context&& other) = delete;

private:
  void* context_ptr = nullptr;
};

}  // namespace GL

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_GL_H

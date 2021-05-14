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
 * \file gl.h
 *
 * \brief OpenGL support functions.
 */

#pragma once

#ifndef SDLXX_CORE_GL_H
#define SDLXX_CORE_GL_H

#include <string>

namespace sdlxx::core {

/**
 * \brief OpenGL support functions.
 */
namespace GL {
  /**
   *  \brief OpenGL context type.
   */
  using Context = void*;  // See SDL_GLContext

  /**
   *  \brief OpenGL configuration attributes.
   */
  enum class Attribute {  // See SDL_GLattr
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

  enum class Profile {  // See SDL_GLprofile
    CORE = 0x0001,
    COMPATIBILITY = 0x0002,
    ES = 0x0004 /**< GLX_CONTEXT_ES2_PROFILE_BIT_EXT */
  };

  enum class ContextFlag {  // See SDL_GLcontextFlag
    CONTEXT_DEBUG_FLAG = 0x0001,
    CONTEXT_FORWARD_COMPATIBLE_FLAG = 0x0002,
    CONTEXT_ROBUST_ACCESS_FLAG = 0x0004,
    CONTEXT_RESET_ISOLATION_FLAG = 0x0008
  };

  enum class ContextReleaseFlag {  // See SDL_GLcontextReleaseFlag
    CONTEXT_RELEASE_BEHAVIOR_NONE = 0x0000,
    CONTEXT_RELEASE_BEHAVIOR_FLUSH = 0x0001
  };

  enum class ContextResetNotification {  // See SDL_GLContextResetNotification
    CONTEXT_RESET_NO_NOTIFICATION = 0x0000,
    CONTEXT_RESET_LOSE_CONTEXT = 0x0001
  };

  /**
   * \brief Dynamically load an OpenGL library.
   *
   * \param path The platform dependent OpenGL library name, or empty string to use the
   *             default OpenGL library.
   *
   *  \return 0 on success, or -1 if the library couldn't be loaded.
   *
   *  This should be done after initializing the video driver, but before
   *  creating any OpenGL windows.  If no OpenGL library is loaded, the default
   *  library will be loaded upon creation of the first OpenGL window.
   *
   *  \note If you do this, you need to retrieve all of the GL functions used in
   *        your program from the dynamic library using SDL_GL_GetProcAddress().
   *
   *  \sa SDL_GL_GetProcAddress()
   *  \sa SDL_GL_UnloadLibrary()
   */
  extern DECLSPEC int SDLCALL SDL_GL_LoadLibrary(const char* path);

  /**
   *  \brief Get the address of an OpenGL function.
   */
  extern DECLSPEC void* SDLCALL SDL_GL_GetProcAddress(const char* proc);

  /**
   *  \brief Unload the OpenGL library previously loaded by SDL_GL_LoadLibrary().
   *
   *  \sa SDL_GL_LoadLibrary()
   */
  extern DECLSPEC void SDLCALL SDL_GL_UnloadLibrary(void);

  /**
   *  \brief Return true if an OpenGL extension is supported for the current
   *         context.
   */
  extern DECLSPEC SDL_bool SDLCALL SDL_GL_ExtensionSupported(const char* extension);

  /**
   *  \brief Reset all previously set OpenGL context attributes to their default values
   */
  extern DECLSPEC void SDLCALL SDL_GL_ResetAttributes(void);

  /**
   *  \brief Set an OpenGL window attribute before window creation.
   *
   *  \return 0 on success, or -1 if the attribute could not be set.
   */
  extern DECLSPEC int SDLCALL SDL_GL_SetAttribute(SDL_GLattr attr, int value);

  /**
   *  \brief Get the actual value for an attribute from the current context.
   *
   *  \return 0 on success, or -1 if the attribute could not be retrieved.
   *          The integer at \c value will be modified in either case.
   */
  extern DECLSPEC int SDLCALL SDL_GL_GetAttribute(SDL_GLattr attr, int* value);

  /**
   *  \brief Create an OpenGL context for use with an OpenGL window, and make it
   *         current.
   *
   *  \sa SDL_GL_DeleteContext()
   */
  extern DECLSPEC SDL_GLContext SDLCALL SDL_GL_CreateContext(SDL_Window* window);

  /**
   *  \brief Set up an OpenGL context for rendering into an OpenGL window.
   *
   *  \note The context must have been created with a compatible window.
   */
  extern DECLSPEC int SDLCALL SDL_GL_MakeCurrent(SDL_Window* window, SDL_GLContext context);

  /**
   *  \brief Get the currently active OpenGL window.
   */
  extern DECLSPEC SDL_Window* SDLCALL SDL_GL_GetCurrentWindow(void);

  /**
   *  \brief Get the currently active OpenGL context.
   */
  extern DECLSPEC SDL_GLContext SDLCALL SDL_GL_GetCurrentContext(void);

  /**
   *  \brief Get the size of a window's underlying drawable in pixels (for use
   *         with glViewport).
   *
   *  \param window   Window from which the drawable size should be queried
   *  \param w        Pointer to variable for storing the width in pixels, may be NULL
   *  \param h        Pointer to variable for storing the height in pixels, may be NULL
   *
   * This may differ from SDL_GetWindowSize() if we're rendering to a high-DPI
   * drawable, i.e. the window was created with SDL_WINDOW_ALLOW_HIGHDPI on a
   * platform with high-DPI support (Apple calls this "Retina"), and not disabled
   * by the SDL_HINT_VIDEO_HIGHDPI_DISABLED hint.
   *
   *  \sa SDL_GetWindowSize()
   *  \sa SDL_CreateWindow()
   */
  extern DECLSPEC void SDLCALL SDL_GL_GetDrawableSize(SDL_Window* window, int* w, int* h);

  /**
   *  \brief Set the swap interval for the current OpenGL context.
   *
   *  \param interval 0 for immediate updates, 1 for updates synchronized with the
   *                  vertical retrace. If the system supports it, you may
   *                  specify -1 to allow late swaps to happen immediately
   *                  instead of waiting for the next retrace.
   *
   *  \return 0 on success, or -1 if setting the swap interval is not supported.
   *
   *  \sa SDL_GL_GetSwapInterval()
   */
  extern DECLSPEC int SDLCALL SDL_GL_SetSwapInterval(int interval);

  /**
   *  \brief Get the swap interval for the current OpenGL context.
   *
   *  \return 0 if there is no vertical retrace synchronization, 1 if the buffer
   *          swap is synchronized with the vertical retrace, and -1 if late
   *          swaps happen immediately instead of waiting for the next retrace.
   *          If the system can't determine the swap interval, or there isn't a
   *          valid current context, this will return 0 as a safe default.
   *
   *  \sa SDL_GL_SetSwapInterval()
   */
  extern DECLSPEC int SDLCALL SDL_GL_GetSwapInterval(void);

  /**
   * \brief Swap the OpenGL buffers for a window, if double-buffering is
   *        supported.
   */
  extern DECLSPEC void SDLCALL SDL_GL_SwapWindow(SDL_Window* window);

  /**
   *  \brief Delete an OpenGL context.
   *
   *  \sa SDL_GL_CreateContext()
   */
  extern DECLSPEC void SDLCALL SDL_GL_DeleteContext(SDL_GLContext context);
  };

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_GL_H

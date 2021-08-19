/*
  SDLXX - Modern C++ wrapper for Simple DirectMedia Layer (SDL2)

  Copyright (C) 2019-2021 Egor Makarenko <egormkn@yandex.ru>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 * \file
 * \brief Header for the CoreApi class that initializes the video API.
 */

#ifndef SDLXX_CORE_API_H
#define SDLXX_CORE_API_H

#include <cstdint>
#include <functional>
#include <optional>
#include <string>

#include "sdlxx/core/exception.h"
#include "sdlxx/utils/bitmask.h"
#include "sdlxx/core/version.h"

namespace sdlxx {

/**
 * \brief A class for CoreApi-related exceptions.
 */
class CoreApiException : public Exception {
  using Exception::Exception;
};

/**
 * \brief A class that initializes the video API.
 */
class CoreApi {
public:
  /**
   * \brief An enumeration of library flags.
   *
   * \upstream SDL_INIT_TIMER
   * \upstream SDL_INIT_AUDIO
   * \upstream SDL_INIT_VIDEO
   * \upstream SDL_INIT_JOYSTICK
   * \upstream SDL_INIT_HAPTIC
   * \upstream SDL_INIT_GAMECONTROLLER
   * \upstream SDL_INIT_EVENTS
   * \upstream SDL_INIT_SENSOR
   * \upstream SDL_INIT_NOPARACHUTE
   * \upstream SDL_INIT_EVERYTHING
   */
  enum class Flag : uint32_t {
    TIMER = 0x00000001U,     ///< Timer subsystem NOLINT(hicpp-uppercase-literal-suffix)
    AUDIO = 0x00000010U,     ///< Audio subsystem
    VIDEO = 0x00000020U,     ///< Video subsystem; automatically initializes the events subsystem
    JOYSTICK = 0x00000200U,  ///< Joystick subsystem; automatically initializes the events subsystem
    HAPTIC = 0x00001000U,    ///< Haptic (force feedback) subsystem
    GAMECONTROLLER = 0x00002000U,  ///< Controller subsystem;
                                   ///< automatically initializes the joystick subsystem
    EVENTS = 0x00004000U,          ///< Events subsystem
    SENSOR = 0x00008000U,          ///< Sensor subsystem
    NOPARACHUTE = 0x00100000U,     ///< Compatibility; this flag is ignored.
    EVERYTHING = TIMER | AUDIO | VIDEO | JOYSTICK | HAPTIC | GAMECONTROLLER | EVENTS |
                 SENSOR  ///< All subsystems
  };

  /**
   * \brief An enumeration of hint priorities.
   *
   * \upstream SDL_HintPriority
   */
  enum class HintPriority {
    DEFAULT,  ///< Low priority, used for default values
    NORMAL,   ///< Medium priority
    OVERRIDE  ///< High priority
  };

  /**
   * \brief Get the SDL version the project is compiled against.
   *
   * This is determined by what header the compiler used.
   * Note that if you dynamically linked the library, you might have a slightly newer or older
   * version at runtime. That version can be determined with Version::GetLinkedSdlVersion().
   *
   * This function may be called safely at any time.
   *
   * \return Version Version of SDL the project was compiled against.
   *
   * \upstream SDL_VERSION
   * \upstream SDL_COMPILEDVERSION
   * \upstream SDL_MAJOR_VERSION
   * \upstream SDL_MINOR_VERSION
   * \upstream SDL_PATCHLEVEL
   */
  static Version GetCompiledSdlVersion();

  /**
   * \brief Get the SDL version the project is linked against.
   *
   * If you are linking to SDL dynamically, then it is possible that the
   * current version will be different than the version you compiled against.
   *
   * This function may be called safely at any time.
   *
   * \return Version Version of SDL the project was linked against.
   *
   * \upstream SDL_GetVersion
   */
  static Version GetLinkedSdlVersion();

  /**
   * \brief Get the code revision of SDL that is linked against the project.
   *
   * Returns an arbitrary string (a hash value) uniquely identifying the
   * exact revision of the SDL library in use, and is only useful in comparing
   * against other revisions. It is NOT an incrementing number.
   *
   * \upstream SDL_GetRevision
   */
  static std::string GetRevision();

  /**
   * \brief Get the revision number of SDL that is linked against the project.
   *
   * Returns a number uniquely identifying the exact revision of the SDL
   * library in use. It is an incrementing number based on commits to hg.libsdl.org.
   *
   * \upstream SDL_GetRevisionNumber
   */
  static int GetRevisionNumber();

  /**
   * \brief Construct the CoreApi object that initializes the specified parts of the library.
   *
   * This object must be constructed before using most other library functions.
   *
   * \param flags Parts of the library that should be initialized.
   *
   * \note Some flags may automatically initialize other.
   *
   * \upstream SDL_Init
   */
  explicit CoreApi(BitMask<Flag> flags);

  /**
   * \brief Destroy the CoreApi object cleaning up all initialized parts of the library.
   *
   * \upstream SDL_Quit
   */
  ~CoreApi();

  /**
   * \brief Initialize specific SDL subsystems.
   *
   * Flag initialization is ref-counted, you must call CoreApi::QuitSubSystem() for each
   * CoreApi::InitSubSystem() to correctly shutdown a subsystem manually (or destroy CoreApi object
   * to force shutdown). If a subsystem is already loaded then this call will increase the ref-count
   * and return.
   *
   * \upstream SDL_InitSubSystem
   */
  void InitSubSystem(BitMask<Flag> flags);

  /**
   * \brief Clean up specific SDL subsystems
   *
   * Flag initialization is ref-counted, you must call CoreApi::QuitSubSystem() for each
   * CoreApi::InitSubSystem() to correctly shutdown a subsystem manually (or destroy CoreApi object
   * to force shutdown). If a subsystem is loaded multiple times then this call will decrease the
   * ref-count and return.
   *
   * If you start a subsystem using a call to that subsystem's init function instead of constructing
   * CoreApi object or calling CoreApi::InitSubSystem(), CoreApi::QuitSubSystem() and
   * CoreApi::WasInit() will not work. You will need to use that subsystem's quit function directly
   * instead.
   *
   * \upstream SDL_QuitSubSystem
   */
  void QuitSubSystem(BitMask<Flag> flags);

  /**
   * \brief Get a set of subsystems which have previously been initialized.
   *
   * If you start a subsystem using a call to that subsystem's init function instead of constructing
   * CoreApi object or calling CoreApi::InitSubSystem(), CoreApi::QuitSubSystem() and
   * CoreApi::WasInit() will not work. You will need to use that subsystem's quit function directly
   * instead.
   *
   * \return A set of subsystems which have previously been initialized.
   *
   * \upstream SDL_WasInit
   */
  BitMask<Flag> WasInit() const;

  /**
   * \brief Return true if specified subsystem has previously been initialized.
   *
   * If you start a subsystem using a call to that subsystem's init function instead of constructing
   * CoreApi object or calling CoreApi::InitSubSystem(), CoreApi::QuitSubSystem() and
   * CoreApi::WasInit() will not work. You will need to use that subsystem's quit function directly
   * instead.
   *
   * \return true if specified subsystem has previously been initialized.
   * \return false otherwise.
   *
   * \upstream SDL_WasInit
   */
  bool WasInit(Flag flag) const;

  /**
   * \brief Set a hint with a specific priority. If priority is not specified, normal priority will
   * be used.
   *
   * The priority controls the behavior when setting a hint that already has a value. Hints will
   * replace existing hints of their priority and lower. Environment variables are considered to
   * have override priority.
   *
   * \param name The name of the hint
   * \param value The value of the hint
   * \param priority The priority of the hint or CoreApi::HintPriority::NORMAL
   *
   * \return true if hint was set
   * \return false otherwise
   *
   * \upstream SDL_SetHint
   * \upstream SDL_SetHintWithPriority
   */
  static bool SetHint(const std::string& name, const std::string& value,
                      HintPriority priority = HintPriority::NORMAL);

  /**
   * \brief Get a hint value
   *
   * \param name The name of the hint
   *
   * \return The string value of a hint variable wrapped in optional type.
   *
   * \upstream SDL_GetHint
   */
  static std::optional<std::string> GetHint(const std::string& name);

  /**
   * \brief Get a hint as a boolean value
   *
   * \param name The name of the hint
   * \param default_value
   *
   * \return true if hint value is set to true
   * \return false if hint value is set to false
   * \return default_value if hint value is unset
   *
   * \upstream SDL_GetHintBoolean
   */
  static bool GetHint(const std::string& name, bool default_value);

  /**
   * \brief type definition of the hint callback function.
   *
   * \param userdata
   * \param name
   * \param oldValue
   * \param newValue
   *
   * \upstream SDL_HintCallback
   */
  using HintCallback = std::function<void(void*, const char*, const char*, const char*)>;

  /**
   * \brief Add a function to watch a particular hint
   *
   * \param name The hint to watch
   * \param callback The function to call when the hint value changes
   * \param userdata A pointer to pass to the callback function
   *
   * \upstream SDL_AddHintCallback
   */
  static void AddHintCallback(const std::string& name, HintCallback callback, void* userdata);

  /**
   * \brief Remove a function watching a particular hint
   *
   * \param name The hint being watched
   * \param callback The function being called when the hint value changes
   * \param userdata A pointer being passed to the callback function
   *
   * \upstream SDL_DelHintCallback
   */
  static void DelHintCallback(const std::string& name, HintCallback callback, void* userdata);

  /**
   * \brief Clear all hints
   *
   * This function is called during destruction of CoreApi object to free stored hints.
   *
   * \upstream SDL_ClearHints
   */
  static void ClearHints();

  // Deleted copy constructor
  CoreApi(const CoreApi& other) = delete;

  // Deleted copy assignment operator
  CoreApi& operator=(const CoreApi& other) = delete;

  // Deleted move constructor
  CoreApi(CoreApi&& other) = delete;

  // Deleted move assignment operator
  CoreApi& operator=(CoreApi&& other) = delete;
};

}  // namespace sdlxx

ENABLE_BITMASK_OPERATORS(sdlxx::CoreApi::Flag);

#endif  // SDLXX_CORE_API_H

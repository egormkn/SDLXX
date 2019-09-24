/**
 * @file SDLXX_core.h
 *
 * Core SDLXX object for library initialization
 */

#pragma once

#ifndef SDLXX_CORE_H
#define SDLXX_CORE_H

#include <optional>
#include <string>
#include <unordered_set>

namespace sdlxx::core {

/**
 * @brief Main object that allows to work with SDLXX library
 */
class SDLXX {
public:
  enum class Subsystem : uint32_t {
    /** Timer subsystem */
    TIMER = 0x00000001u,  // SDL_INIT_TIMER
    /** Audio subsystem */
    AUDIO = 0x00000010u,  // SDL_INIT_AUDIO
    /** Video subsystem; automatically initializes the events subsystem */
    VIDEO = 0x00000020u,  // SDL_INIT_VIDEO
    /** Joystick subsystem; automatically initializes the events subsystem */
    JOYSTICK = 0x00000200u,  // SDL_INIT_JOYSTICK
    /** Haptic (force feedback) subsystem */
    HAPTIC = 0x00001000u,  // SDL_INIT_HAPTIC,
    /** Controller subsystem; automatically initializes the joystick subsystem
     */
    GAMECONTROLLER = 0x00002000u,  // SDL_INIT_GAMECONTROLLER
    /** Events subsystem */
    EVENTS = 0x00004000u,  // SDL_INIT_EVENTS
    /** Sensor subsystem */
    SENSOR = 0x00008000u,  // SDL_INIT_SENSOR
    /** All subsystems */
    EVERYTHING = TIMER | AUDIO | VIDEO | JOYSTICK | HAPTIC | GAMECONTROLLER |
                 EVENTS | SENSOR,  // SDL_INIT_EVERYTHING
    // _ = SDL_INIT_NOPARACHUTE /* Compatibility; this value is ignored */
  };

  /**
   * @brief An enumeration of hint priorities
   */
  enum class HintPriority {
    /** Low priority, used for default values */
    DEFAULT,  // SDL_HINT_DEFAULT
    /** Medium priority */
    NORMAL,  // SDL_HINT_NORMAL
    /** High priority */
    OVERRIDE  // SDL_HINT_OVERRIDE
  };

  /**
   * @brief Class that contains information about the version of a library
   *
   * Represents the library's version as three levels: major revision
   * (increments with massive changes, additions, and enhancements), minor
   * revision (increments with backwards-compatible changes to the major
   * revision), and patchlevel (increments with fixes to the minor revision).
   */
  class Version {
  public:
    /**
     * @brief Major revision (increments with massive changes, additions, and
     * enhancements)
     */
    const uint8_t major_version;
    /**
     * @brief Minor revision (increments with backwards-compatible changes to
     * the major revision)
     */
    const uint8_t minor_version;
    /**
     * @brief Patchlevel (increments with fixes to the minor revision)
     */
    const uint8_t patch_version;

    Version(uint8_t major, uint8_t minor, uint8_t patch);

    /**
     * @brief Get the SDL version the SDLXX library was compiled against
     *
     * This is determined by what header the compiler used. Note that if you
     * dynamically linked the library, you might have a slightly newer or older
     * version at runtime. That version can be determined with
     * SDLXX::Version::getLinkedSdlVersion()
     *
     * @return Version of SDL the library was compiled against
     */
    static Version getCompiledSdlVersion();

    /**
     * @brief Get the version of SDL that is linked against the SDLXX library.
     *
     * If you are linking to SDL dynamically, then it is possible that the
     * current version will be different than the version you compiled against.
     *
     * @return Version of SDL the library was linked against
     */
    static Version getLinkedSdlVersion();
  };

  /**
   * @brief Construct a new SDLXX object that initializes the SDL library.
   *
   * This object must be constructed before using most other SDLXX functions.
   *
   * @param subsystems Subsystems that should be initialized. Note that some
   * subsystems may automatically initialize other.
   */
  explicit SDLXX(const std::unordered_set<Subsystem>& subsystems = {});

  /**
   * @brief Destroy the SDLXX object cleaning up all initialized subsystems.
   */
  ~SDLXX();

  /**
   * @brief Initialize specific SDL subsystem
   *
   * Subsystem initialization is ref-counted, you must call
   * SDLXX::quitSubsystem() for each SDLXX::initSubsystem() to correctly
   * shutdown a subsystem manually (or destroy SDLXX object to force shutdown).
   * If a subsystem is already loaded then this call will
   * increase the ref-count and return.
   */
  void initSubsystem(const Subsystem& subsystem);

  /**
   * @brief Initialize specific SDL subsystems
   *
   * Subsystem initialization is ref-counted, you must call
   * SDLXX::quitSubsystem() for each SDLXX::initSubsystem() to correctly
   * shutdown a subsystem manually (or destroy SDLXX object to force shutdown).
   * If a subsystem is already loaded then this call will
   * increase the ref-count and return.
   */
  void initSubsystem(const std::unordered_set<Subsystem>& subsystems);

  /**
   * @brief Clean up specific SDL subsystem
   *
   * Subsystem initialization is ref-counted, you must call
   * SDLXX::quitSubsystem() for each SDLXX::initSubsystem() to correctly
   * shutdown a subsystem manually (or destroy SDLXX object to force shutdown).
   * If a subsystem is loaded multiple times then this call will
   * decrease the ref-count and return.
   *
   * If you start a subsystem using a call to that subsystem's init function
   * instead of constructing SDLXX object or calling SDLXX::initSubsystem(),
   * SDLXX::quitSubsystem() and SDLXX::wasInit() will not work. You will need to
   * use that subsystem's quit function directly instead.
   */
  void quitSubsystem(const Subsystem& subsystem);

  /**
   * @brief Clean up specific SDL subsystems
   *
   * Subsystem initialization is ref-counted, you must call
   * SDLXX::quitSubsystem() for each SDLXX::initSubsystem() to correctly
   * shutdown a subsystem manually (or destroy SDLXX object to force shutdown).
   * If a subsystem is loaded multiple times then this call will
   * decrease the ref-count and return.
   *
   * If you start a subsystem using a call to that subsystem's init function
   * instead of constructing SDLXX object or calling SDLXX::initSubsystem(),
   * SDLXX::quitSubsystem() and SDLXX::wasInit() will not work. You will need to
   * use that subsystem's quit function directly instead.
   */
  void quitSubsystem(const std::unordered_set<Subsystem>& subsystems);

  /**
   * @brief Return a subset of specified subsystems which have previously been
   * initialized, or a set of subsystems, if no subsystems were specified.
   *
   * If you start a subsystem using a call to that subsystem's init function
   * instead of constructing SDLXX object or calling SDLXX::initSubsystem(),
   * SDLXX::quitSubsystem() and SDLXX::wasInit() will not work. You will need to
   * use that subsystem's quit function directly instead.
   *
   * @return Subset of specified subsystems which have previously been
   * initialized
   */
  std::unordered_set<Subsystem> wasInit(
      const std::unordered_set<Subsystem>& subsystems = {});

  /**
   * @brief Return true if a specified subsystem has previously been initialized
   *
   * If you start a subsystem using a call to that subsystem's init function
   * instead of constructing SDLXX object or calling SDLXX::initSubsystem(),
   * SDLXX::quitSubsystem() and SDLXX::wasInit() will not work. You will need to
   * use that subsystem's quit function directly instead.
   *
   * @return true if a specified subsystem has previously been initialized
   * @return false otherwise
   */
  bool wasInit(const Subsystem& subsystem);

  /**
   * @brief Set a hint with a specific priority. If priority is not specified,
   * normal priority will be used.
   *
   * The priority controls the behavior when setting a hint that already
   * has a value. Hints will replace existing hints of their priority and
   * lower. Environment variables are considered to have override priority.
   *
   * @param name The name of the hint
   * @param value The value of the hint
   * @param priority The priority of the hint or SDLXX::HintPriority::NORMAL
   *
   * @return true if hint was set
   * @return false otherwise
   */
  static bool setHint(const std::string& name, const std::string& value,
                      const HintPriority& priority = HintPriority::NORMAL);

  /**
   * @brief Get a hint value
   *
   * @param name The name of the hint
   * @return The string value of a hint variable wrapped in optional type.
   */
  static std::optional<std::string> getHint(const std::string& name);

  /**
   * @brief Get a hint as a boolean value
   *
   * @param name The name of the hint
   * @return true if hint value is set to true
   * @return false otherwise
   */
  static std::optional<bool> getHintBoolean(const std::string& name);

  /**
   * @brief Clear all hints
   *
   * This function is called during destruction of SDLXX to free stored hints.
   */
  static void clearHints();

  // TODO: Implement methods for hint callbacks

private:
  // Initialization status
  static bool initialized;

  // Deleted copy constructor
  // This class is not copyable
  SDLXX(const SDLXX& other) = delete;

  // Deleted assignment operator
  // This class is not copyable
  SDLXX& operator=(const SDLXX& other) = delete;

  // Deleted move constructor
  // This class is not movable
  SDLXX(SDLXX&& other) = delete;

  // Deleted move assignment operator
  // This class is not movable
  SDLXX& operator=(SDLXX&& other) = delete;
};
}  // namespace sdlxx::core

#endif  // SDLXX_CORE_H

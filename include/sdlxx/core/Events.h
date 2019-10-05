/**
 * @file Events.h
 * @author Egor Makarenko
 * @brief Class that allows to work with events
 */

#pragma once

#ifndef SDLXX_CORE_EVENTS_H
#define SDLXX_CORE_EVENTS_H

#include <cstdint>
#include <optional>
#include <vector>

// TODO: Try to get rid of SDL dependency (seems to be impossible)
#include <SDL_events.h>

namespace sdlxx::core {

using Event = SDL_Event;

/**
 * @brief Class that allows to work with events
 */
class Events {
public:
  /**
   * @brief An enumeration of event types
   */
  enum Type : uint32_t {
    /** Unused (do not remove) */
    FIRSTEVENT = 0,

    /* === Application events === */

    /** User-requested quit */
    QUIT = 0x100,

    /**
     * The application is being terminated by the OS
     * Called on iOS in applicationWillTerminate()
     * Called on Android in onDestroy()
     */
    APP_TERMINATING,

    /**
     * The application is low on memory, free memory if possible.
     * Called on iOS in applicationDidReceiveMemoryWarning()
     * Called on Android in onLowMemory()
     */
    APP_LOWMEMORY,

    /**
     * The application is about to enter the background
     * Called on iOS in applicationWillResignActive()
     * Called on Android in onPause()
     */
    APP_WILLENTERBACKGROUND,

    /**
     * The application did enter the background and may not get CPU for some
     * time
     * Called on iOS in applicationDidEnterBackground()
     * Called on Android in onPause()
     */
    APP_DIDENTERBACKGROUND,

    /**
     * The application is about to enter the foreground
     * Called on iOS in applicationWillEnterForeground()
     * Called on Android in onResume()
     */
    APP_WILLENTERFOREGROUND,

    /** The application is now interactive
     * Called on iOS in applicationDidBecomeActive()
     * Called on Android in onResume()
     */
    APP_DIDENTERFOREGROUND,

    /* === Display events === */

    /** Display state change */
    DISPLAYEVENT = 0x150,

    /* === Window events === */

    /** Window state change */
    WINDOWEVENT = 0x200,

    /** System specific event */
    SYSWMEVENT,

    /* === Keyboard events === */

    /** Key pressed */
    KEYDOWN = 0x300,

    /** Key released */
    KEYUP,

    /** Keyboard text editing (composition) */
    TEXTEDITING,

    /** Keyboard text input */
    TEXTINPUT,

    /**
     * Keymap changed due to a system event such as an input language or
     * keyboard layout change.
     */
    KEYMAPCHANGED,

    /* === Mouse events === */

    /** Mouse moved */
    MOUSEMOTION = 0x400,

    /** Mouse button pressed */
    MOUSEBUTTONDOWN,

    /** Mouse button released */
    MOUSEBUTTONUP,

    /** Mouse wheel motion */
    MOUSEWHEEL,

    /* === Joystick events === */

    /** Joystick axis motion */
    JOYAXISMOTION = 0x600,

    /** Joystick trackball motion */
    JOYBALLMOTION,

    /** Joystick hat position change */
    JOYHATMOTION,

    /** Joystick button pressed */
    JOYBUTTONDOWN,

    /** Joystick button released */
    JOYBUTTONUP,

    /** A new joystick has been inserted into the system */
    JOYDEVICEADDED,

    /** An opened joystick has been removed */
    JOYDEVICEREMOVED,

    /* === Game controller events === */

    /** Game controller axis motion */
    CONTROLLERAXISMOTION = 0x650,

    /** Game controller button pressed */
    CONTROLLERBUTTONDOWN,

    /** Game controller button released */
    CONTROLLERBUTTONUP,

    /** A new Game controller has been inserted into the system */
    CONTROLLERDEVICEADDED,

    /** An opened Game controller has been removed */
    CONTROLLERDEVICEREMOVED,

    /** The controller mapping was updated */
    CONTROLLERDEVICEREMAPPED,

    /* === Touch events === */
    FINGERDOWN = 0x700,
    FINGERUP,
    FINGERMOTION,

    /* === Gesture events === */
    DOLLARGESTURE = 0x800,
    DOLLARRECORD,
    MULTIGESTURE,

    /* === Clipboard events === */

    /** The clipboard changed */
    CLIPBOARDUPDATE = 0x900,

    /* === Drag and drop events === */

    /** The system requests a file open */
    DROPFILE = 0x1000,

    /** text/plain drag-and-drop event */
    DROPTEXT,

    /** A new set of drops is beginning (NULL filename) */
    DROPBEGIN,

    /** Current set of drops is now complete (NULL filename) */
    DROPCOMPLETE,

    /* === Audio hotplug events === */

    /** A new audio device is available */
    AUDIODEVICEADDED = 0x1100,

    /** An audio device has been removed. */
    AUDIODEVICEREMOVED,

    /* === Sensor events === */

    /** A sensor was updated */
    SENSORUPDATE = 0x1200,

    /* === Render events === */

    /**
     * The render targets have been reset and their contents need to be updated
     */
    RENDER_TARGETS_RESET = 0x2000,

    /** The device has been reset and all textures need to be recreated */
    RENDER_DEVICE_RESET,

    /**
     * Events ::USEREVENT through ::LASTEVENT are for your use,
     * and should be allocated with RegisterEvents()
     */
    USEREVENT = 0x8000,

    /**
     * This last event is only for bounding internal arrays
     */
    LASTEVENT = 0xFFFF
  };

  /**
   * @brief Pumps the event loop, gathering events from the input devices.
   *
   * This function updates the event queue and internal input device state.
   *
   * @note This should only be run in the thread that sets the video mode.
   */
  static void pump();

  /**
   * @brief Add events to the back of the event queue.
   *
   * This function is thread-safe.
   *
   * @param events Vector of events to add to the queue
   * @return int The number of events actually added
   */
  static int add(const std::vector<Event>& events);

  /**
   * @brief Peek up to @c numevents events at the front of the event queue,
   * within the specified minimum and maximum type.
   *
   * This function is thread-safe.
   *
   * @param numevents Maximum number of events to peek
   * @param minType, maxType Range of event types
   * @return std::vector<Event> Events from the event queue
   */
  static std::vector<Event> peek(int numevents, Type minType, Type maxType);

  /**
   * @brief Get up to @c numevents events at the front of the event queue,
   * within the specified minimum and maximum type, and remove them from the
   * queue.
   *
   * This function is thread-safe.
   *
   * @param numevents Maximum number of events to get
   * @param minType, maxType Range of event types
   * @return std::vector<Event> Events removed from the event queue
   */
  static std::vector<Event> get(int numevents, Type minType, Type maxType);

  /**
   * @brief Checks to see if certain event type is in the event queue.
   *
   * @param type Event type
   * @return true if queue contains events with specified type
   * @return false otherwise
   */
  static bool inQueue(Type type);

  /**
   * @brief Checks to see if certain event types are in the event queue.
   *
   * @param minType, maxType Range of event types
   * @return true if queue contains events within specified type range
   * @return false otherwise
   */
  static bool inQueue(Type minType, Type maxType);

  /**
   * @brief Clear events from the event queue
   *
   * This function only affects currently queued events. If you want to make
   * sure that all pending OS events are flushed, you can call Events::get()
   * on the main thread immediately before the flush call.
   *
   * @param type Event type
   */
  static void flush(Type type);

  /**
   * @brief Clear events from the event queue
   *
   * This function only affects currently queued events. If you want to make
   * sure that all pending OS events are flushed, you can call Events::get()
   * on the main thread immediately before the flush call.
   *
   * @param minType, maxType Range of event types
   */
  static void flush(Type minType, Type maxType);

  /**
   * @brief Checks to see if event queue contains some events
   *
   * @return true if event queue contains some events
   * @return false if event queue is empty
   */
  static bool inQueue();

  /**
   * @brief Poll for currently pending events.
   *
   * @return std::optional<Event> Optional event that was polled from the
   * queue
   */
  static std::optional<Event> poll();

  /**
   * @brief Wait indefinitely for the next available event.
   *
   * @return Event Event that was polled from the queue
   */
  static Event wait();

  /**
   * @brief Wait for the next available event until the specified timeout
   *
   * @param timeout Timeout in milliseconds
   * @return std::optional<Event> An optional event that was polled from the
   * queue
   */
  static std::optional<Event> wait(int timeout);

  /**
   * @brief Add an event to the event queue.
   *
   * @param event The event to add to the event queue
   * @return true if event was added to the queue
   * @return false if event was filtered
   */
  static bool push(Event event);
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_EVENT_H

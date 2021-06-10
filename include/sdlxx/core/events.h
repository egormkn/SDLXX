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
 * \brief Header for the Events class that handles events.
 */

#ifndef SDLXX_CORE_EVENTS_H
#define SDLXX_CORE_EVENTS_H

#include <cstdint>
#include <vector>

#include "sdlxx/core/exception.h"

// Declaration of the underlying type
union SDL_Event;

namespace sdlxx {

/**
 * \brief Type alias for SDL_Event
 * \upstream SDL_Event
 */
using Event = SDL_Event;

/**
 * \brief A class for Event-related exceptions.
 */
class EventException : public Exception {
  using Exception::Exception;
};

/**
 * \brief Class that handles events.
 */
class Events {
public:
  /**
   * General keyboard/mouse state definitions
   *
   * \upstream SDL_RELEASED
   * \upstream SDL_PRESSED
   */
  enum class ButtonState { RELEASED = 0, PRESSED = 1 };

  /**
   * \brief The types of events that can be delivered.
   * \upstream SDL_EventType
   */
  enum Type : uint32_t {
    FIRSTEVENT = 0, /**< Unused (do not remove) */

    /* === Application events === */
    QUIT = 0x100, /**< User-requested quit */

    APP_TERMINATING, /**< The application is being terminated by the OS
                          Called on iOS in applicationWillTerminate()
                          Called on Android in onDestroy() */

    APP_LOWMEMORY, /**< The application is low on memory, free memory if possible.
                        Called on iOS in applicationDidReceiveMemoryWarning()
                        Called on Android in onLowMemory() */

    APP_WILLENTERBACKGROUND, /**< The application is about to enter the background
                                  Called on iOS in applicationWillResignActive()
                                  Called on Android in onPause() */

    APP_DIDENTERBACKGROUND, /**< The application did enter the background and may not Get CPU for
                                 some time Called on iOS in applicationDidEnterBackground() Called
                                 on Android in onPause() */

    APP_WILLENTERFOREGROUND, /**< The application is about to enter the foreground
                                  Called on iOS in applicationWillEnterForeground()
                                  Called on Android in onResume() */

    APP_DIDENTERFOREGROUND, /**< The application is now interactive
                                 Called on iOS in applicationDidBecomeActive()
                                 Called on Android in onResume() */

    LOCALECHANGED, /**< The user's locale preferences have changed. */

    /* === Display events === */
    DISPLAYEVENT = 0x150, /**< Display state change */

    /* === Window events === */
    WINDOWEVENT = 0x200, /**< Window state change */
    SYSWMEVENT,          /**< System specific event */

    /* === Keyboard events === */
    KEYDOWN = 0x300, /**< Key pressed */
    KEYUP,           /**< Key released */
    TEXTEDITING,     /**< Keyboard text editing (composition) */
    TEXTINPUT,       /**< Keyboard text input */
    KEYMAPCHANGED,   /**< Keymap changed due to a system event such as an input language or keyboard
                          layout change. */

    /* === Mouse events === */
    MOUSEMOTION = 0x400, /**< Mouse moved */
    MOUSEBUTTONDOWN,     /**< Mouse button pressed */
    MOUSEBUTTONUP,       /**< Mouse button released */
    MOUSEWHEEL,          /**< Mouse wheel motion */

    /* === Joystick events === */
    JOYAXISMOTION = 0x600, /**< Joystick axis motion */
    JOYBALLMOTION,         /**< Joystick trackball motion */
    JOYHATMOTION,          /**< Joystick hat position change */
    JOYBUTTONDOWN,         /**< Joystick button pressed */
    JOYBUTTONUP,           /**< Joystick button released */
    JOYDEVICEADDED,        /**< A new joystick has been inserted into the system */
    JOYDEVICEREMOVED,      /**< An opened joystick has been removed */

    /* === Game controller events === */
    CONTROLLERAXISMOTION = 0x650, /**< Game controller axis motion */
    CONTROLLERBUTTONDOWN,         /**< Game controller button pressed */
    CONTROLLERBUTTONUP,           /**< Game controller button released */
    CONTROLLERDEVICEADDED,        /**< A new Game controller has been inserted into the system */
    CONTROLLERDEVICEREMOVED,      /**< An opened Game controller has been removed */
    CONTROLLERDEVICEREMAPPED,     /**< The controller mapping was updated */
    CONTROLLERTOUCHPADDOWN,       /**< Game controller touchpad was touched */
    CONTROLLERTOUCHPADMOTION,     /**< Game controller touchpad finger was moved */
    CONTROLLERTOUCHPADUP,         /**< Game controller touchpad finger was lifted */
    CONTROLLERSENSORUPDATE,       /**< Game controller sensor was updated */

    /* === Touch events === */
    FINGERDOWN = 0x700,
    FINGERUP,
    FINGERMOTION,

    /* === Gesture events === */
    DOLLARGESTURE = 0x800,
    DOLLARRECORD,
    MULTIGESTURE,

    /* === Clipboard events === */
    CLIPBOARDUPDATE = 0x900, /**< The clipboard changed */

    /* === Drag and drop events === */
    DROPFILE = 0x1000, /**< The system requests a file open */
    DROPTEXT,          /**< text/plain drag-and-drop event */
    DROPBEGIN,         /**< A new set of drops is beginning (NULL filename) */
    DROPCOMPLETE,      /**< Current set of drops is now complete (NULL filename) */

    /* === Audio hotplug events === */
    AUDIODEVICEADDED = 0x1100, /**< A new audio device is available */
    AUDIODEVICEREMOVED,        /**< An audio device has been removed. */

    /* === Sensor events === */
    SENSORUPDATE = 0x1200, /**< A sensor was updated */

    /* === Render events === */
    RENDER_TARGETS_RESET =
        0x2000, /**< The render targets have been reset and their contents need to be updated */
    RENDER_DEVICE_RESET, /**< The device has been reset and all textures need to be recreated */

    /** Events ::USEREVENT through ::LASTEVENT are for your use,
     *  and should be allocated with Events::Register()
     */
    USEREVENT = 0x8000,

    /**
     *  This last event is only for bounding internal arrays
     */
    LASTEVENT = 0xFFFF
  };

  // TODO: SDL_CommonEvent, SDL_DisplayEvent, SDL_WindowEvent, SDL_KeyboardEvent,
  // SDL_TextEditingEvent, SDL_TextInputEvent, SDL_MouseMotionEvent, SDL_MouseButtonEvent,
  // SDL_MouseWheelEvent, SDL_JoyAxisEvent, SDL_JoyBallEvent, SDL_JoyHatEvent, SDL_JoyButtonEvent,
  // SDL_JoyDeviceEvent, SDL_ControllerAxisEvent, SDL_ControllerButtonEvent,
  // SDL_ControllerDeviceEvent, SDL_ControllerTouchpadEvent, SDL_ControllerSensorEvent,
  // SDL_AudioDeviceEvent, SDL_TouchFingerEvent, SDL_MultiGestureEvent, SDL_DollarGestureEvent,
  // SDL_DropEvent, SDL_SensorEvent, SDL_QuitEvent, SDL_OSEvent, SDL_UserEvent, SDL_SysWMEvent

  /**
   * \brief Pump the event loop, gathering events from the input devices.
   *
   * This function updates the event queue and internal input device state.
   *
   * \note This should only be run in the thread that sets the video mode.
   *
   * \upstream SDL_PumpEvents
   */
  static void Pump();

  /**
   * \brief Add events to the back of the event queue.
   *
   * This function is thread-safe.
   *
   * \param events Vector of events to Add to the queue
   * \return int The number of events actually added
   *
   * \throw EventException if there was some error.
   *
   * \upstream SDL_PeepEvents
   */
  static int Add(std::vector<Event> events);

  /**
   * \brief Peek up to \c numevents events at the front of the event queue,
   * within the specified minimum and maximum type.
   *
   * This function is thread-safe.
   *
   * \param numevents Maximum number of events to peek.
   * \param min_type, max_type Range of event types.
   *
   * \return std::vector<Event> Events from the front of event queue.
   *
   * \throw EventException if there was some error.
   *
   * \upstream SDL_PeepEvents
   */
  static std::vector<Event> Peek(int numevents, Type min_type = Type::FIRSTEVENT,
                                 Type max_type = Type::LASTEVENT);

  /**
   * \brief Get up to \c numevents events at the front of the event queue,
   * within the specified minimum and maximum type, and remove them from the
   * queue.
   *
   * This function is thread-safe.
   *
   * \param numevents Maximum number of events to Get
   * \param min_type, max_type Range of event types
   *
   * \return std::vector<Event> Events removed from the event queue.
   *
   * \throw EventException if there was some error.
   *
   * \upstream SDL_PeepEvents
   */
  static std::vector<Event> Get(int numevents, Type min_type = Type::FIRSTEVENT,
                                Type max_type = Type::LASTEVENT);

  /**
   * \brief Checks to see if certain event type is in the event queue.
   *
   * \param type Event type.
   * \return true if queue contains events with specified type.
   * \return false otherwise.
   *
   * \upstream SDL_HasEvent
   */
  static bool InQueue(Type type);

  /**
   * \brief Checks to see if certain event types are in the event queue.
   *
   * \param min_type, max_type Range of event types.
   * \return true if queue contains events within specified type range.
   * \return false otherwise.
   *
   * \upstream SDL_HasEvents
   */
  static bool InQueue(Type min_type, Type max_type);

  /**
   * \brief Checks to see if event queue is empty.
   *
   * \return true if event queue is empty.
   * \return false if event queue contains some events.
   *
   * \upstream SDL_PollEvent
   */
  static bool IsEmpty();

  /**
   * \brief Clear events from the event queue.
   *
   * This function only affects currently queued events. If you want to make
   * sure that all pending OS events are flushed, you can call Events::Pump()
   * on the main thread immediately before the Flush call.
   *
   * \param type Event type
   *
   * \upstream SDL_FlushEvent
   */
  static void Flush(Type type);

  /**
   * \brief Clear events from the event queue.
   *
   * This function only affects currently queued events. If you want to make
   * sure that all pending OS events are flushed, you can call Events::Pump()
   * on the main thread immediately before the Flush call.
   *
   * \param min_type, max_type Range of event types
   *
   * \upstream SDL_FlushEvents
   */
  static void Flush(Type min_type, Type max_type);

  /**
   * \brief Poll for currently pending events.
   *
   * \param event If not nullptr, the next event is removed from the queue and stored in that area.
   *
   * \return true if event that was polled from the queue
   * \return false otherwise
   *
   * \upstream SDL_PollEvent
   */
  static bool Poll(Event* event);

  /**
   * \brief Wait indefinitely for the next available event.
   *
   * \param event If not nullptr, the next event is removed from the queue and stored in that area.
   *
   * \return true if event was polled from the queue (always)
   *
   * \throw EventException if there was an error while waiting for events.
   *
   * \upstream SDL_WaitEvent
   */
  static bool Wait(Event* event);

  /**
   * \brief Waits until the specified timeout (in milliseconds) for the next available event.
   *
   * \param timeout The timeout (in milliseconds) to wait for next event.
   *
   * \return true if event was polled from the queue, false if the timeout was reached
   *
   * \throw EventException if there was an error while waiting for events.
   *
   * \upstream SDL_WaitEventTimeout
   */
  static bool WaitTimeout(Event* event, int timeout);

  /**
   * \brief Add an event to the event queue.
   *
   * \param event The event to copy to the event queue.
   *
   * \return true if event was added to the queue.
   * \return false if event was filtered.
   *
   * \throw EventException if the event queue was full or there was some other error.
   *
   * \upstream SDL_PushEvent
   */
  static bool Push(Event* event);

  // TODO: SDL_EventFilter, SDL_SetEventFilter, SDL_GetEventFilter, SDL_AddEventWatch,
  // SDL_DelEventWatch, SDL_FilterEvents, SDL_EventState, SDL_GetEventState, SDL_RegisterEvents
};

}  // namespace sdlxx

#endif  // SDLXX_CORE_EVENTS_H

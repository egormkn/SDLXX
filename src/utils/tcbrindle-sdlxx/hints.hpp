/*
  @file hints.cpp

  Simple DirectMedia Layer C++ Bindings
  @copyright (C) 2014 Tristan Brindle <t.c.brindle@gmail.com>

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

#ifndef SDLXX_HINTS_HPP
#define SDLXX_HINTS_HPP

#include "SDL_hints.h"

#include "detail/wrapper.hpp"
#include "macros.hpp"

#include <algorithm>
#include <array>

namespace sdl {

/*!
 @defgroup Hints Configuration Variables

 This category contains functions to set and get configuration hints, as well as
 listing each of them alphabetically.

 The convention for naming hints is `sdl::hint::x`, where "SDL_X" is the
 environment variable that can be used to override the default.

 In general these hints are just that - they may or may not be supported or
 applicable on any given platform, but they provide a way for an application or
 user to give the library a hint as to how they would like the library to work.

@{
*/

//! Hints understood by SDL
enum class hint {
    /*!
     A variable controlling how 3D acceleration is used to accelerate the SDL
     screen surface.

     SDL can try to accelerate the SDL screen surface by using streaming
     textures with a 3D rendering engine.  This variable controls whether and
     how this is done.

     This variable can be set to the following values:
        - "0": Disable 3D acceleration
        - "1": Enable 3D acceleration, using the default renderer.
        - "X": Enable 3D acceleration, using X where X is one of the
               valid rendering drivers.  (e.g. "direct3d", "opengl", etc.)

     By default SDL tries to make a best guess for each platform whether
     to use acceleration or not.
    */
    framebuffer_acceleration,

    /*!
     A variable specifying which render driver to use.

     If the application doesn't pick a specific renderer to use, this variable
     specifies the name of the preferred renderer.  If the preferred renderer
     can't be initialized, the normal default renderer is used.

     This variable is case insensitive and can be set to the following
     values:
         - "direct3d"
         - "opengl"
         - "opengles2"
         - "opengles"
         - "software"

     The default varies by platform, but it's the first one in the list that
     is available on the current platform.
    */
    render_driver,

    /*!
     A variable controlling whether the OpenGL render driver uses shaders if
     they are available.

     This variable can be set to the following values:
         - "0": Disable shaders
         - "1": Enable shaders

     By default shaders are used if OpenGL supports them.
    */
    render_opengl_shaders,

    /*!
     A variable controlling whether the Direct3D device is initialized for
     thread-safe operations.

     This variable can be set to the following values:
         - "0": Thread-safety is not enabled (faster)
         - "1": Thread-safety is enabled

     By default the Direct3D device is created with thread-safety disabled.
    */
    render_direct3d_threadsafe,

    /*!
     A variable controlling whether to enable Direct3D 11+'s Debug Layer.

     This variable does not have any effect on the Direct3D 9 based renderer.

     This variable can be set to the following values:
         - "0": Disable Debug Layer use
         - "1": Enable Debug Layer use

     By default, SDL does not use Direct3D Debug Layer.
    */
    render_direct3d11_debug,

    /*!
     A variable controlling the scaling quality

     This variable can be set to the following values:
         - "0" or "nearest": Nearest pixel sampling
         - "1" or "linear": Linear filtering (supported by OpenGL and Direct3D)
         - "2" or "best": Currently this is the same as "linear"

     By default nearest pixel sampling is used
    */
    render_scale_quality,

    /*!
     A variable controlling whether updates to the SDL screen surface should be
     synchronized with the vertical refresh, to avoid tearing.

     This variable can be set to the following values:
         - "0": Disable vsync
         - "1": Enable vsync

     By default SDL does not sync screen surface updates with vertical refresh.
    */
    render_vsync,

    /*!
     A variable controlling whether the screensaver is enabled.

     This variable can be set to the following values:
         - "0": Disable screensaver
         - "1": Enable screensaver

     By default SDL will disable the screensaver.
    */
    video_allow_screensaver,

    /*!
     A variable controlling whether the X11 VidMode extension should be used.

     This variable can be set to the following values:
         - "0": Disable XVidMode
         - "1": Enable XVidMode

     By default SDL will use XVidMode if it is available.
    */
    video_x11_xvidmode,

    /*!
     A variable controlling whether the X11 Xinerama extension should be used.

     This variable can be set to the following values:
         - "0": Disable Xinerama
         - "1": Enable Xinerama

     By default SDL will use Xinerama if it is available.
    */
    video_x11_xinerama,

    /*!
     A variable controlling whether the X11 XRandR extension should be used.

     This variable can be set to the following values:
         - "0": Disable XRandR
         - "1": Enable XRandR

     By default SDL will not use XRandR because of window manager issues.
    */
    video_x11_xrandr,

    /*!
     A variable controlling whether the X11 _NET_WM_PING protocol should be
     supported.

     This variable can be set to the following values:
         - "0": Disable _NET_WM_PING
         - "1": Enable _NET_WM_PING

     By default SDL will use _NET_WM_PING, but for applications that know they
     will not always be able to respond to ping requests in a timely manner they
     can turn it off to avoid the window manager thinking the app is hung.
     The hint is checked in during window construction.
    */
    video_x11_net_wm_ping,

    /*!
     A variable controlling whether the window frame and title bar are
     interactive when the cursor is hidden

     This variable can be set to the following values:
         - "0": The window frame is not interactive when the cursor is hidden
                (no move, resize, etc)
         - "1": The window frame is interactive when the cursor is hidden

     By default SDL will allow interaction with the window frame when the
     cursor is hidden
    */
    window_frame_usable_while_cursor_hidden,

    /*!
     A variable controlling whether the windows message loop is processed by SDL

     This variable can be set to the following values:
         - "0": The window message loop is not run
         - "1": The window message loop is processed in `sdl::pump_events()`

     By default SDL will process the windows message loop
    */
    windows_enable_messageloop,

    /*!
     A variable controlling whether grabbing input grabs the keyboard

     This variable can be set to the following values:
         - "0": Grab will affect only the mouse
         - "1": Grab will affect mouse and keyboard

     By default SDL will not grab the keyboard so system shortcuts still work.
    */
    grab_keyboard,

    /*!
    A variable controlling whether relative mouse mode is implemented using
    mouse warping

    This variable can be set to the following values:
        - "0": Relative mouse mode uses raw input
        - "1": Relative mouse mode uses mouse warping

     By default SDL will use raw input for relative mouse mode
    */
    mouse_relative_warp_mode,

    /*!
     Minimize your SDL_Window if it loses key focus when in fullscreen mode.
     Defaults to true.
    */
    video_minimize_on_focus_loss,

    /*!
     A variable controlling whether the idle timer is disabled on iOS.

     When an iOS app does not receive touches for some time, the screen is
     dimmed automatically. For games where the accelerometer is the only input
     this is problematic. This functionality can be disabled by setting this
     hint.

     As of SDL 2.0.4, `sdl::enable_screen_saver()` and
     `sdl::disable_screen_saver()` accomplish the same thing on iOS. They should
     be preferred over this hint.

     This variable can be set to the following values:
         - "0": Enable idle timer
         - "1": Disable idle timer
    */
    idle_timer_disabled,

    /*!
     A variable controlling which orientations are allowed on iOS.

     In some circumstances it is necessary to be able to explicitly control
     which UI orientations are allowed.

     This variable is a space delimited list of the following values:
     "LandscapeLeft", "LandscapeRight", "Portrait" "PortraitUpsideDown"
     */
    orientations,

    /*!
     A variable controlling whether the Android/iOS built-in accelerometer
     should be listed as a joystick device, rather than listing actual joysticks
     only.

     This variable can be set to the following values:
       - "0": List only real joysticks and accept input from them
       - "1": List real joysticks along with the accelerometer as if it
              were a 3 axis joystick (the default).
    */
    accelerometer_as_joystick,

    /*!
     A variable that lets you disable the detection and use of Xinput gamepad
     devices

     The variable can be set to the following values:
        - "0": Disable XInput detection (only uses direct input)
        - "1": Enable XInput detection (the default)
    */
    xinput_enabled,

    /*!
     A variable that causes SDL to use the old axis and button mapping for
     XInput devices.

     This hint is for backwards compatibility only and will be removed in SDL
     2.1

     The default value is "0".  This hint must be set before `sdl::init()`.
    */
    xinput_use_old_joystick_mapping,

    /*!
     A variable that lets you manually hint extra gamecontroller db entries

     The variable should be newline delimited rows of gamecontroller config
     data, see SDL_gamecontroller.h

     This hint must be set before calling
     `sdl::init(sdl::init_flags::gamecontroller)`
     You can update mappings after the system is initialized with
     SDL_GameControllerMappingForGUID() and SDL_GameControllerAddMapping()
    */
    gamecontrollerconfig,

    /*!
     A variable that lets you enable joystick (and gamecontroller) events even
     when your app is in the background.

     The variable can be set to the following values:
       - "0": Disable joystick & gamecontroller input events when the
              application is in the background.
       - "1": Enable joystick & gamecontroller input events when the
              application is in the background.

     The default value is "0".  This hint may be set at any time.
    */
    joystick_allow_background_events,

    /*!
     If set to "0" then never set the top most bit on a SDL Window,
     even if the video mode expects it.

     @note This is a debugging aid for developers and not expected to be used
     by end users. The default is "1"

     This variable can be set to the following values:
       - "0": don't allow topmost
       -  "1": allow topmost
    */
    allow_topmost,

    /*!
     A variable that controls the timer resolution, in milliseconds.

     The higher resolution the timer, the more frequently the CPU services
     timer interrupts, and the more precise delays are, but this takes up
     power and CPU time.  This hint is only used on Windows 7 and earlier.

     See this blog post for more information:
     http://randomascii.wordpress.com/2013/07/08/windows-timer-resolution-megawatts-wasted/

     If this variable is set to "0", the system timer resolution is not set.

     The default value is "1". This hint may be set at any time.
    */
    timer_resolution,

    /*!
     A string specifying SDL's threads stack size in bytes or "0" for
     the backend's default size

     Use this hint in case you need to set SDL's threads stack size to other
     than the default.
     This is specially useful if you build SDL against a non glibc libc library
     (such as musl) which provides a relatively small default thread stack size
     (a few kilobytes versus the default 8MB glibc uses).
     Support for this hint is currently available only in the pthread backend.
    */
    thread_stack_size,

    /*!
     If set to 1, then do not allow high-DPI windows. ("Retina" on Mac
     and iOS)
    */
    video_highdpi_disabled,

    /*!
     A variable that determines whether ctrl+click should generate a
     right-click event on Mac

     If present, holding ctrl while left clicking will generate a right click
     event when on Mac.
    */
    mac_ctrl_click_emulate_right_click,

    /*!
     A variable specifying which shader compiler to preload when using
     the Chrome ANGLE binaries

     SDL has EGL and OpenGL ES2 support on Windows via the ANGLE project. It
     can use two different sets of binaries, those compiled by the user from
     source  or those provided by the Chrome browser. In the later case, these
     binaries require that SDL loads a DLL providing the shader compiler.

     This variable can be set to the following values:
      - "d3dcompiler_46.dll": default, best for Vista or later.
      - "d3dcompiler_43.dll": for XP support.
      - "none": do not load any library, useful if you compiled ANGLE from
                source and included the compiler in your binaries.

    */
    video_win_d3dcompiler,

    /*!
     A variable that is the address of another SDL_Window* (as a hex
     string formatted with "%p").

     If this hint is set before SDL_CreateWindowFrom() and the SDL_Window* it
     is set to has `sdl::window_flags::opengl` set (and running on WGL only,
     currently), then two things will occur on the newly
     created SDL_Window:

      1. Its pixel format will be set to the same pixel format as this
         SDL_Window.  This is needed for example when sharing an OpenGL context
         across multiple windows.

      2. The flag `sdl::window_flags::opengl will be set on the new window so it
         can be used for OpenGL rendering.

      This variable can be set to the following values:
      The address (as a string "%p") of the SDL_Window* that new windows
      created with `SDL_CreateWindowFrom()` should share a pixel format with.
    */
    video_window_share_pixel_format,

    /*!
     A URL to a WinRT app's privacy policy

     All network-enabled WinRT apps must make a privacy policy available to
     its users. On Windows 8, 8.1, and RT, Microsoft mandates that this policy
     be available in the Windows Settings charm, as accessed from within the
     app. SDL provides code to add a URL-based link there, which can point to
     the app's privacy policy.

     To setup a URL to an app's privacy policy, set
     `sdl::hint::privacy_policy_url` before calling any `sdl::init()` functions.
     The contents of the hint should be a valid URL, for example,
     "http://www.example.com".

     The default value is "", which will prevent SDL from adding a privacy
     policy link to the Settings charm.  This hint should only be set during app
     init.

     The label text of an app's "Privacy Policy" link may be customized via
     another hint, `sdl::hint::winrt_privacy_policy_label`.

     Please note that on Windows Phone, Microsoft does not provide standard
     UI for displaying a privacy policy link, and as such,
     `sdl::hint::winrt_privacy_policy_url` will not get used on that platform.
     Network-enabled phone apps should display their privacy policy through some
     other, in-app means.
    */
    winrt_privacy_policy_url,

    /*!
     Label text for a WinRT app's privacy policy link

     Network-enabled WinRT apps must include a privacy policy.  On Windows 8,
     8.1, and RT,  Microsoft mandates that this policy be available via the
     Windows Settings charm.

     SDL provides code to add a link there, with its label text being set via
     the optional hint, `sdl::hint::winrt_privacy_policy_label`.

     Please note that a privacy policy's contents are not set via this hint.
     A separate hint, `sdl::hint::winrt_privacy_policy_url`, is used to link to
     the actual text of the policy.

     The contents of this hint should be encoded as a UTF8 string.

     The default value is "Privacy Policy".  This hint should only be set during
     app initialization, preferably before any calls to `sdl::init()`.

     For additional information on linking to a privacy policy, see the
     documentation for `sdl::hint::winrt_privacy_policy_url`.
    */
    winrt_privacy_policy_label,

    /*!
     Allows back-button-press events on Windows Phone to be marked as
     handled

     Windows Phone devices typically feature a Back button.  When pressed,
     the OS will emit back-button-press events, which apps are expected to
     handle in an appropriate manner.  If apps do not explicitly mark these
     events as 'Handled', then the OS will invoke its default behavior for
     unhandled back-button-press events, which on Windows Phone 8 and 8.1 is to
     terminate the app (and attempt to switch to the previous app, or to the
     device's home screen).

     Setting `sdl::hint::winrt_handle_back_button` to "1" will cause SDL
     to mark back-button-press events as Handled, if and when one is sent to
     the app.

     Internally, Windows Phone sends back button events as parameters to
     special back-button-press callback functions.  Apps that need to respond
     to back-button-press events are expected to register one or more
     callback functions for such, shortly after being launched (during the
     app's initialization phase).  After the back button is pressed, the OS
     will invoke these callbacks.  If the app's callback(s) do not explicitly
     mark the event as handled by the time they return, or if the app never
     registers one of these callback, the OS will consider the event
     un-handled, and it will apply its default back button behavior (terminate
     the app).

     SDL registers its own back-button-press callback with the Windows Phone
     OS.  This callback will emit a pair of SDL key-press events (SDL_KEYDOWN
     and SDL_KEYUP), each with a scancode of SDL_SCANCODE_AC_BACK, after
     which  it will check the contents of the hint,
     `sdl::hint::winrt_handle_back_button`.
     If the hint's value is set to "1", the back button event's Handled
     property will get set to 'true'.  If the hint's value is set to something
     else, or if it is unset, SDL will leave the event's Handled property
     alone.  (By default, the OS sets this property to 'false', to note.)

     SDL apps can either set `sdl::hint::winrt_handle_back_button` well before a
     back button is pressed, or can set it in direct-response to a back button
     being pressed.

     In order to get notified when a back button is pressed, SDL apps should
     register a callback function with SDL_AddEventWatch(), and have it
     listen for SDL_KEYDOWN events that have a scancode of SDL_SCANCODE_AC_BACK.
     (Alternatively, SDL_KEYUP events can be listened-for.  Listening for
      either event type is suitable.)  Any value of
      `sdl::hint::winrt_handle_back_button` set by such a callback, will be
      applied to the OS' current  back-button-press event.

     More details on back button behavior in Windows Phone apps can be found
     at the following page, on Microsoft's developer site:
     http://msdn.microsoft.com/en-us/library/windowsphone/develop/jj247550(v=vs.105).aspx
    */
    winrt_handle_back_button,

    /*!
     A variable that dictates policy for fullscreen Spaces on Mac OS X.

     This hint only applies to Mac OS X.

     The variable can be set to the following values:
       - "0": Disable Spaces support (`sdl::window_flags::fullscreen_desktop`
              won't use them and `sdl::window_flags::resizable` windows won't
              offer the "fullscreen" button on their titlebars).
       - "1": Enable Spaces support (`sdl::window_flags::fullscreen_desktop`
              will use them and `sdl::window_flags::resizable` windows will
              offer the "fullscreen" button on their titlebars).

     The default value is "1". Spaces are disabled regardless of this hint if
     the OS isn't at least Mac OS X Lion (10.7). This hint must be set before
     any windows are created.
    */
    video_mac_fullscreen_spaces,

    /*!
     When set don't force the SDL app to become a foreground process

     This hint only applies to Mac OS X.
    */
    mac_background_app,

    /*!
     Android APK expansion main file version. Should be a string number
     like "1", "2" etc.

     Must be set together with
     sdl::hint::android_apk_expansion_patch_file_version.

     If both hints were set then `SDL_RWFromFile()` will look into expansion
     files after a given relative path was not found in the internal storage and
     assets.

     By default this hint is not set and the APK expansion files are not
     searched.
    */
    android_apk_expansion_main_file_version,

    /*!
     Android APK expansion patch file version. Should be a string
     number like "1", "2" etc.

     Must be set together with
     sdl::hint::android_apk_expansion_main_file_version.

     If both hints were set then `SDL_RWFromFile()` will look into expansion
     files after a given relative path was not found in the internal storage and
     assets.

     By default this hint is not set and the APK expansion files are not
     searched.
    */
    android_apk_expansion_patch_file_version,

    /*!
     A variable to control whether certain IMEs should handle text
     editing internally instead of sending `SDL_TEXTEDITING` events.

     The variable can be set to the following values:
         - "0": `SDL_TEXTEDITING` events are sent, and it is the application's
                responsibility to render the text from these events and
                differentiate it somehow from committed text. (default)
         - "1": If supported by the IME then `SDL_TEXTEDITING` events are not
                sent, and text that is being composed will be rendered in its
                own UI.
    */
    ime_internal_editing,

    /*!
     A variable to control whether mouse and touch events are to be
     treated together or separately

     The variable can be set to the following values:
       - "0: Mouse events will be handled as touch events, and touch will
             raise fake mouse events. This is the behaviour of SDL <= 2.0.3.
             (default)
       - "1": Mouse events will be handled separately from pure touch events.

     The value of this hint is used at runtime, so it can be changed at any
     time.
    */
    android_separate_mouse_and_touch,

    /*!
     Override the binding element for keyboard inputs for Emscripten builds

     This hint only applies to the emscripten platform

     The variable can be one of
         - "#window": The javascript window object (this is the default)
         - "#document": The javascript document object
         - "#screen": the javascript window.screen object
         - "#canvas": the WebGL canvas element

     Any other string without a leading # sign applies to the element on
     the page with that ID.
    */
    emscripten_keyboard_element,

    /*!
      Tell SDL not to catch the SIGINT or SIGTERM signals.

     This hint only applies to Unix-like platforms.

     The variable can be set to the following values:
       - "0": SDL will install a SIGINT and SIGTERM handler, and when it
              catches a signal, convert it into an SDL_QUIT event.
       - "1": SDL will not install a signal handler at all.
     */
    no_signal_handlers,

    /*!
      Tell SDL not to generate window-close events for Alt+F4 on Windows.

     The variable can be set to the following values:
        - "0": SDL will generate a window-close event when it sees Alt+F4.
        - "1": SDL will only do normal key handling for Alt+F4.
    */
    windows_no_close_on_alt_f4
};

//!@cond
inline const char* to_c_value(hint h) {
    switch (h) {
    case hint::framebuffer_acceleration:
        return SDL_HINT_FRAMEBUFFER_ACCELERATION;
    case hint::render_driver:
        return SDL_HINT_RENDER_DRIVER;
    case hint::render_opengl_shaders:
        return SDL_HINT_RENDER_OPENGL_SHADERS;
    case hint::render_direct3d_threadsafe:
        return SDL_HINT_RENDER_DIRECT3D_THREADSAFE;
    case hint::render_direct3d11_debug:
        return SDL_HINT_RENDER_DIRECT3D11_DEBUG;
    case hint::render_scale_quality:
        return SDL_HINT_RENDER_SCALE_QUALITY;
    case hint::render_vsync:
        return SDL_HINT_RENDER_VSYNC;
    case hint::video_allow_screensaver:
        return SDL_HINT_VIDEO_ALLOW_SCREENSAVER;
    case hint::video_x11_xvidmode:
        return SDL_HINT_VIDEO_X11_XVIDMODE;
    case hint::video_x11_xinerama:
        return SDL_HINT_VIDEO_X11_XINERAMA;
    case hint::video_x11_xrandr:
        return SDL_HINT_VIDEO_X11_XRANDR;
    case hint::video_x11_net_wm_ping:
        return SDL_HINT_VIDEO_X11_NET_WM_PING;
    case hint::window_frame_usable_while_cursor_hidden:
        return SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN;
    case hint::windows_enable_messageloop:
        return SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP;
    case hint::grab_keyboard:
        return SDL_HINT_GRAB_KEYBOARD;
    case hint::mouse_relative_warp_mode:
        return SDL_HINT_MOUSE_RELATIVE_MODE_WARP;
    case hint::video_minimize_on_focus_loss:
        return SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS;
    case hint::idle_timer_disabled:
        return SDL_HINT_IDLE_TIMER_DISABLED;
    case hint::orientations:
        return SDL_HINT_ORIENTATIONS;
    case hint::accelerometer_as_joystick:
        return SDL_HINT_ACCELEROMETER_AS_JOYSTICK;
    case hint::xinput_enabled:
        return SDL_HINT_XINPUT_ENABLED;
    case hint::xinput_use_old_joystick_mapping:
        return SDL_HINT_XINPUT_USE_OLD_JOYSTICK_MAPPING;
    case hint::gamecontrollerconfig:
        return SDL_HINT_GAMECONTROLLERCONFIG;
    case hint::joystick_allow_background_events:
        return SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS;
    case hint::allow_topmost:
        return SDL_HINT_ALLOW_TOPMOST;
    case hint::timer_resolution:
        return SDL_HINT_TIMER_RESOLUTION;
    case hint::thread_stack_size:
        return SDL_HINT_THREAD_STACK_SIZE;
    case hint::video_highdpi_disabled:
        return SDL_HINT_VIDEO_HIGHDPI_DISABLED;
    case hint::mac_ctrl_click_emulate_right_click:
        return SDL_HINT_MAC_CTRL_CLICK_EMULATE_RIGHT_CLICK;
    case hint::video_win_d3dcompiler:
        return SDL_HINT_VIDEO_WIN_D3DCOMPILER;
    case hint::video_window_share_pixel_format:
        return SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT;
    case hint::windows_no_close_on_alt_f4:
        return SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4;
    case hint::winrt_privacy_policy_label:
        return SDL_HINT_WINRT_PRIVACY_POLICY_LABEL;
    case hint::winrt_privacy_policy_url:
        return SDL_HINT_WINRT_PRIVACY_POLICY_URL;
    case hint::winrt_handle_back_button:
        return SDL_HINT_WINRT_HANDLE_BACK_BUTTON;
    case hint::video_mac_fullscreen_spaces:
        return SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES;
    case hint::mac_background_app:
        return SDL_HINT_MAC_BACKGROUND_APP;
    case hint::android_apk_expansion_main_file_version:
        return SDL_HINT_ANDROID_APK_EXPANSION_MAIN_FILE_VERSION;
    case hint::android_apk_expansion_patch_file_version:
        return SDL_HINT_ANDROID_APK_EXPANSION_PATCH_FILE_VERSION;
    case hint::ime_internal_editing:
        return SDL_HINT_IME_INTERNAL_EDITING;
    case hint::android_separate_mouse_and_touch:
        return SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH;
    case hint::emscripten_keyboard_element:
        return SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT;
    case hint::no_signal_handlers:
        return SDL_HINT_NO_SIGNAL_HANDLERS;
    default:
        SDL_assert(false);
    }
    // Keep g++ happy
    return nullptr;
}
//!@endcond

//! Priority passed to `sdl::set_hint()`
//! Hints will replace existing hints of their priority and lower. Environment
//! variables are considered to have override priority.
enum class hint_priority {
    hint_default = SDL_HINT_DEFAULT,
    hint_normal = SDL_HINT_NORMAL,
    hint_override = SDL_HINT_OVERRIDE
};

namespace detail {
    template <>
    struct c_type<hint_priority> {
        using type = SDL_HintPriority;
    };
}

/*!
 Set a hint with optional priority

 The priority controls the behavior when setting a hint that already
 has a value.  Hints will replace existing hints of their priority and
 lower.  Environment variables are considered to have override priority.

 @return `true` if the hint was set, `false` otherwise
*/
inline bool set_hint(hint name, const char* value,
                     hint_priority priority = hint_priority::hint_normal) {
    return detail::c_call(::SDL_SetHintWithPriority, name, value, priority);
}

/*!
 Get a hint

 @return The string value of a hint variable.
*/
inline const char* get_hint(hint name) {
    return detail::c_call(::SDL_GetHint, name);
}

/*!
 Clear all hints

 This function is called during SDL shutdown to free stored hints.
*/
inline void clear_hints() { ::SDL_ClearHints(); }

//! The type expected by a hint callback
using hint_callback_t = void(sdl::hint, const char*, const char*);

namespace detail {

    template <typename Func>
    class hint_callback {
        // FIXME: Causes ICE on MSVC
        // static_assert(
        //    detail::check_signature<Func, hint_callback_t>::value,
        //    "Supplied callback is not callable or does not match "
        //    "expected type void(sdl::hint, const char*, const char*)");

        static void run_callback(void* user_data, const char* /* name */,
                                 const char* old_value, const char* new_value) {
            auto self = static_cast<hint_callback*>(user_data);
            self->func(self->name, old_value, new_value);
        }

    public:
        hint_callback(hint name, Func&& func)
            : func(std::forward<Func>(func)), name(name) {
            c_call(::SDL_AddHintCallback, name, run_callback, this);
        }

        ~hint_callback() {
            c_call(::SDL_DelHintCallback, name, run_callback, this);
        }

        hint_callback(hint_callback&&) = default;
        hint_callback& operator=(hint_callback&&) = default;

    private:
        Func func;
        hint name;
    };

} // namespace detail

//! Use this function to add a function to watch a particular hint.
template <typename Func>
SDLXX_ATTR_WARN_UNUSED_RESULT auto add_hint_callback(hint name, Func&& func) {
    return detail::hint_callback<Func>{name, std::forward<Func>(func)};
}

} // end namespace sdl

#endif // SDLXX_HINTS_HPP

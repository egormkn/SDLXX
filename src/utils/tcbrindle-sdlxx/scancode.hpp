/*
  @file scancode.hpp
  Defines keyboard scancodes.
  @copyright (C) 2014-2016 Tristan Brindle <t.c.brindle@gmail.com>

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

#ifndef SDLXX_SCANCODE_HPP
#define SDLXX_SCANCODE_HPP

#include "SDL_scancode.h"

#include <type_traits>

namespace sdl {

/*! @ingroup Keyboard
 The SDL keyboard scancode representation.

 Values of this type are used to represent keyboard keys, among other places
 in the \link SDL_Keysym::scancode key.keysym.scancode \endlink field of the
 SDL_Event structure.

 The values in this enumeration are based on the [USB usage page standard](
 http://www.usb.org/developers/devclass_docs/Hut1_12v2.pdf)
 */
enum class scancode : std::underlying_type_t<SDL_Scancode> {
    unknown = SDL_SCANCODE_UNKNOWN,

    /*!
     @name Usage page 0x07

     These values are from usage page 0x07 (USB keyboard page).
     */
    /* @{ */

    a = SDL_SCANCODE_A,
    b = SDL_SCANCODE_B,
    c = SDL_SCANCODE_C,
    d = SDL_SCANCODE_D,
    e = SDL_SCANCODE_E,
    f = SDL_SCANCODE_F,
    g = SDL_SCANCODE_G,
    h = SDL_SCANCODE_H,
    i = SDL_SCANCODE_I,
    j = SDL_SCANCODE_J,
    k = SDL_SCANCODE_K,
    l = SDL_SCANCODE_L,
    m = SDL_SCANCODE_M,
    n = SDL_SCANCODE_N,
    o = SDL_SCANCODE_O,
    p = SDL_SCANCODE_P,
    q = SDL_SCANCODE_Q,
    r = SDL_SCANCODE_R,
    s = SDL_SCANCODE_S,
    t = SDL_SCANCODE_T,
    u = SDL_SCANCODE_U,
    v = SDL_SCANCODE_V,
    w = SDL_SCANCODE_W,
    x = SDL_SCANCODE_X,
    y = SDL_SCANCODE_Y,
    z = SDL_SCANCODE_Z,

    _1 = SDL_SCANCODE_1,
    _2 = SDL_SCANCODE_2,
    _3 = SDL_SCANCODE_3,
    _4 = SDL_SCANCODE_4,
    _5 = SDL_SCANCODE_5,
    _6 = SDL_SCANCODE_6,
    _7 = SDL_SCANCODE_7,
    _8 = SDL_SCANCODE_8,
    _9 = SDL_SCANCODE_9,
    _0 = SDL_SCANCODE_0,

    _return = SDL_SCANCODE_RETURN,
    enter = SDL_SCANCODE_RETURN,
    escape = SDL_SCANCODE_ESCAPE,
    backspace = SDL_SCANCODE_BACKSPACE,
    tab = SDL_SCANCODE_TAB,
    space = SDL_SCANCODE_SPACE,

    minus = SDL_SCANCODE_MINUS,
    equals = SDL_SCANCODE_EQUALS,
    leftbracket = SDL_SCANCODE_LEFTBRACKET,
    rightbracket = SDL_SCANCODE_RIGHTBRACKET,
    /*! Located at the lower left of the return key on ISO keyboards and at the
     * right end of the QWERTY row on ANSI keyboards. Produces REVERSE SOLIDUS
     * (backslash) and VERTICAL LINE in a US layout, REVERSE SOLIDUS and
     * VERTICAL
     * LINE in a UK Mac layout, NUMBER SIGN and TILDE in a UK Windows layout,
     * DOLLAR SIGN and POUND SIGN in a Swiss German layout, NUMBER SIGN and
     * APOSTROPHE in a German layout, GRAVE ACCENT and POUND SIGN in a French
     * Mac
     * layout, and ASTERISK and MICRO SIGN in a French Windows layout.
    */
    backslash = SDL_SCANCODE_BACKSLASH,
    nonushash =
        SDL_SCANCODE_NONUSHASH, /*!< ISO USB keyboards actually use this code
                                     instead of 49 for the same key, but all
                                     OSes I've seen treat the two codes
                                     identically. So, as an implementor, unless
  your keyboard generates both of those
                                 *   codes and your OS treats them differently,
                                 *   you should generate SDL_SCANCODE_BACKSLASH
                                 *   instead of this code. As a user, you
                                 *   should not rely on this code because SDL
                                 *   will never generate it with most (all?)
                                 *   keyboards.
                                 */
    semicolon = SDL_SCANCODE_SEMICOLON,
    apostrophe = SDL_SCANCODE_APOSTROPHE,
    grave =
        SDL_SCANCODE_GRAVE, /**< Located in the top left corner (on both ANSI
                             *   and ISO keyboards). Produces GRAVE ACCENT and
                             *   TILDE in a US Windows layout and in US and UK
                             *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                             *   and NOT SIGN in a UK Windows layout, SECTION
                             *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                             *   layouts on ISO keyboards, SECTION SIGN and
                             *   DEGREE SIGN in a Swiss German layout (Mac:
                             *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                             *   DEGREE SIGN in a German layout (Mac: only on
                             *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                             *   French Windows layout, COMMERCIAL AT and
                             *   NUMBER SIGN in a French Mac layout on ISO
                             *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                             *   SIGN in a Swiss German, German, or French Mac
                             *   layout on ANSI keyboards.
                             */
    comma = SDL_SCANCODE_COMMA,
    period = SDL_SCANCODE_PERIOD,
    slash = SDL_SCANCODE_SLASH,

    capslock = SDL_SCANCODE_CAPSLOCK,

    f1 = SDL_SCANCODE_F1,
    f2 = SDL_SCANCODE_F2,
    f3 = SDL_SCANCODE_F3,
    f4 = SDL_SCANCODE_F4,
    f5 = SDL_SCANCODE_F5,
    f6 = SDL_SCANCODE_F6,
    f7 = SDL_SCANCODE_F7,
    f8 = SDL_SCANCODE_F8,
    f9 = SDL_SCANCODE_F9,
    f10 = SDL_SCANCODE_F10,
    f11 = SDL_SCANCODE_F11,
    f12 = SDL_SCANCODE_F12,

    printscreen = SDL_SCANCODE_PRINTSCREEN,
    scrolllock = SDL_SCANCODE_SCROLLLOCK,
    pause = SDL_SCANCODE_PAUSE,
    insert =
        SDL_SCANCODE_INSERT, /**< insert on PC, help on some Mac keyboards (but
                                  does send code 73, not 117) */
    home = SDL_SCANCODE_HOME,
    pageup = SDL_SCANCODE_PAGEUP,
    _delete = SDL_SCANCODE_DELETE,
    del = SDL_SCANCODE_DELETE,
    end = SDL_SCANCODE_END,
    pagedown = SDL_SCANCODE_PAGEDOWN,
    right = SDL_SCANCODE_RIGHT,
    left = SDL_SCANCODE_LEFT,
    down = SDL_SCANCODE_DOWN,
    up = SDL_SCANCODE_UP,

    numlockclear =
        SDL_SCANCODE_NUMLOCKCLEAR, /**< num lock on PC, clear on Mac keyboards
                                    */
    kp_divide = SDL_SCANCODE_KP_DIVIDE,
    kp_multiply = SDL_SCANCODE_KP_MULTIPLY,
    kp_minus = SDL_SCANCODE_KP_MINUS,
    kp_plus = SDL_SCANCODE_KP_PLUS,
    kp_enter = SDL_SCANCODE_KP_ENTER,
    kp_1 = SDL_SCANCODE_KP_1,
    kp_2 = SDL_SCANCODE_KP_2,
    kp_3 = SDL_SCANCODE_KP_3,
    kp_4 = SDL_SCANCODE_KP_4,
    kp_5 = SDL_SCANCODE_KP_5,
    kp_6 = SDL_SCANCODE_KP_6,
    kp_7 = SDL_SCANCODE_KP_7,
    kp_8 = SDL_SCANCODE_KP_8,
    kp_9 = SDL_SCANCODE_KP_9,
    kp_0 = SDL_SCANCODE_KP_0,
    kp_period = SDL_SCANCODE_KP_PERIOD,

    nonusbackslash =
        SDL_SCANCODE_NONUSBACKSLASH, /**< This is the additional key that ISO
                                      *   keyboards have over ANSI ones,
                                      *   located between left shift and Y.
                                      *   Produces GRAVE ACCENT and TILDE in a
                                      *   US or UK Mac layout, REVERSE SOLIDUS
                                      *   (backslash) and VERTICAL LINE in a
                                      *   US or UK Windows layout, and
                                      *   LESS-THAN SIGN and GREATER-THAN SIGN
                                      *   in a Swiss German, German, or French
                                      *   layout. */
    application =
        SDL_SCANCODE_APPLICATION, /**< windows contextual menu, compose */
    power =
        SDL_SCANCODE_POWER, /**< The USB document says this is a status flag,
                             *   not a physical key - but some Mac keyboards
                             *   do have a power key. */
    kp_equals = SDL_SCANCODE_KP_EQUALS,
    f13 = SDL_SCANCODE_F13,
    f14 = SDL_SCANCODE_F14,
    f15 = SDL_SCANCODE_F15,
    f16 = SDL_SCANCODE_F16,
    f17 = SDL_SCANCODE_F17,
    f18 = SDL_SCANCODE_F18,
    f19 = SDL_SCANCODE_F19,
    f20 = SDL_SCANCODE_F20,
    f21 = SDL_SCANCODE_F21,
    f22 = SDL_SCANCODE_F22,
    f23 = SDL_SCANCODE_F23,
    f24 = SDL_SCANCODE_F24,
    execute = SDL_SCANCODE_EXECUTE,
    help = SDL_SCANCODE_HELP,
    menu = SDL_SCANCODE_MENU,
    select = SDL_SCANCODE_SELECT,
    stop = SDL_SCANCODE_STOP,
    again = SDL_SCANCODE_AGAIN, /**< redo */
    redo = SDL_SCANCODE_AGAIN,
    undo = SDL_SCANCODE_UNDO,
    cut = SDL_SCANCODE_CUT,
    copy = SDL_SCANCODE_COPY,
    paste = SDL_SCANCODE_PASTE,
    find = SDL_SCANCODE_FIND,
    mute = SDL_SCANCODE_MUTE,
    volumeup = SDL_SCANCODE_VOLUMEUP,
    volumedown = SDL_SCANCODE_VOLUMEDOWN,
    /* not sure whether there's a reason to enable these */
    /*     SDL_SCANCODE_LOCKINGCAPSLOCK = 130,  */
    /*     SDL_SCANCODE_LOCKINGNUMLOCK = 131, */
    /*     SDL_SCANCODE_LOCKINGSCROLLLOCK = 132, */
    kp_comma = SDL_SCANCODE_KP_COMMA,
    equalsas400 = SDL_SCANCODE_KP_EQUALSAS400,

    international1 =
        SDL_SCANCODE_INTERNATIONAL1, /**< used on Asian keyboards, see
                                          footnotes in USB doc */
    international2 = SDL_SCANCODE_INTERNATIONAL2,
    international3 = SDL_SCANCODE_INTERNATIONAL3, /**< Yen */
    international4 = SDL_SCANCODE_INTERNATIONAL4,
    international5 = SDL_SCANCODE_INTERNATIONAL5,
    international6 = SDL_SCANCODE_INTERNATIONAL6,
    international7 = SDL_SCANCODE_INTERNATIONAL7,
    international8 = SDL_SCANCODE_INTERNATIONAL8,
    international9 = SDL_SCANCODE_INTERNATIONAL9,
    lang1 = SDL_SCANCODE_LANG1, /**< Hangul/English toggle */
    lang2 = SDL_SCANCODE_LANG2, /**< Hanja conversion */
    lang3 = SDL_SCANCODE_LANG3, /**< Katakana */
    lang4 = SDL_SCANCODE_LANG4, /**< Hiragana */
    lang5 = SDL_SCANCODE_LANG5, /**< Zenkaku/Hankaku */
    lang6 = SDL_SCANCODE_LANG6, /**< reserved */
    lang7 = SDL_SCANCODE_LANG7, /**< reserved */
    lang8 = SDL_SCANCODE_LANG8, /**< reserved */
    lang9 = SDL_SCANCODE_LANG9, /**< reserved */

    alterase = SDL_SCANCODE_ALTERASE, /**< Erase-Eaze */
    sysreq = SDL_SCANCODE_SYSREQ,
    cancel = SDL_SCANCODE_CANCEL,
    clear = SDL_SCANCODE_CLEAR,
    prior = SDL_SCANCODE_PRIOR,
    return2 = SDL_SCANCODE_RETURN2,
    separator = SDL_SCANCODE_SEPARATOR,
    out = SDL_SCANCODE_OUT,
    oper = SDL_SCANCODE_OPER,
    clearagain = SDL_SCANCODE_CLEARAGAIN,
    crsel = SDL_SCANCODE_CRSEL,
    exsel = SDL_SCANCODE_EXSEL,

    kp_00 = SDL_SCANCODE_KP_00,
    kp_000 = SDL_SCANCODE_KP_000,
    thousandsseparator = SDL_SCANCODE_THOUSANDSSEPARATOR,
    decimalseparator = SDL_SCANCODE_DECIMALSEPARATOR,
    currencyunit = SDL_SCANCODE_CURRENCYUNIT,
    currencysubunit = SDL_SCANCODE_CURRENCYSUBUNIT,
    kp_leftparen = SDL_SCANCODE_KP_LEFTPAREN,
    kp_rightparen = SDL_SCANCODE_KP_RIGHTPAREN,
    kp_leftbrace = SDL_SCANCODE_KP_LEFTBRACE,
    kp_rightbrace = SDL_SCANCODE_KP_RIGHTBRACE,
    kp_tab = SDL_SCANCODE_KP_TAB,
    kp_backspace = SDL_SCANCODE_KP_BACKSPACE,
    kp_a = SDL_SCANCODE_KP_A,
    kp_b = SDL_SCANCODE_KP_B,
    kp_c = SDL_SCANCODE_KP_C,
    kp_d = SDL_SCANCODE_KP_D,
    kp_e = SDL_SCANCODE_KP_E,
    kp_f = SDL_SCANCODE_KP_F,
    kp_xor = SDL_SCANCODE_KP_XOR,
    kp_power = SDL_SCANCODE_KP_POWER,
    kp_percent = SDL_SCANCODE_KP_PERCENT,
    kp_less = SDL_SCANCODE_KP_LESS,
    kp_greater = SDL_SCANCODE_KP_GREATER,
    kp_ampersand = SDL_SCANCODE_KP_AMPERSAND,
    kp_dblampersand = SDL_SCANCODE_KP_DBLAMPERSAND,
    kp_verticalbar = SDL_SCANCODE_KP_VERTICALBAR,
    kp_dblverticalbar = SDL_SCANCODE_KP_DBLVERTICALBAR,
    kp_colon = SDL_SCANCODE_KP_COLON,
    kp_hash = SDL_SCANCODE_KP_HASH,
    kp_space = SDL_SCANCODE_KP_SPACE,
    kp_at = SDL_SCANCODE_KP_AT,
    kp_exclam = SDL_SCANCODE_KP_EXCLAM,
    kp_memstore = SDL_SCANCODE_KP_MEMSTORE,
    kp_memrecall = SDL_SCANCODE_KP_MEMRECALL,
    kp_memclear = SDL_SCANCODE_KP_MEMCLEAR,
    kp_memadd = SDL_SCANCODE_KP_MEMADD,
    kp_memsubtract = SDL_SCANCODE_KP_MEMSUBTRACT,
    kp_memmultiply = SDL_SCANCODE_KP_MEMMULTIPLY,
    kp_memdivide = SDL_SCANCODE_KP_MEMDIVIDE,
    kp_plusminus = SDL_SCANCODE_KP_PLUSMINUS,
    kp_clear = SDL_SCANCODE_KP_CLEAR,
    kp_clearentry = SDL_SCANCODE_KP_CLEARENTRY,
    kp_binary = SDL_SCANCODE_KP_BINARY,
    kp_octal = SDL_SCANCODE_KP_OCTAL,
    kp_decimal = SDL_SCANCODE_KP_DECIMAL,
    kp_hexadecimal = SDL_SCANCODE_KP_HEXADECIMAL,

    lctrl = SDL_SCANCODE_LCTRL,
    lshift = SDL_SCANCODE_LSHIFT,
    lalt = SDL_SCANCODE_LALT, /**< alt, option */
    lgui = SDL_SCANCODE_LGUI, /**< windows, command (apple), meta */
    rctrl = SDL_SCANCODE_RCTRL,
    rshift = SDL_SCANCODE_RSHIFT,
    ralt = SDL_SCANCODE_RALT, /**< alt gr, option */
    rgui = SDL_SCANCODE_RGUI, /**< windows, command (apple), meta */

    mode = SDL_SCANCODE_MODE, /**< I'm not sure if this is really not covered
                                *   by any of the above, but since there's a
                                *   special KMOD_MODE for it I'm adding it here
                                */

    /* @} */ /* Usage page 0x07 */

    /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */

    audionext = SDL_SCANCODE_AUDIONEXT,
    audioprev = SDL_SCANCODE_AUDIOPREV,
    audiostop = SDL_SCANCODE_AUDIOSTOP,
    audioplay = SDL_SCANCODE_AUDIOPLAY,
    audiomute = SDL_SCANCODE_AUDIOMUTE,
    mediaselect = SDL_SCANCODE_MEDIASELECT,
    www = SDL_SCANCODE_WWW,
    mail = SDL_SCANCODE_MAIL,
    calculator = SDL_SCANCODE_CALCULATOR,
    computor = SDL_SCANCODE_COMPUTER,
    ac_search = SDL_SCANCODE_AC_SEARCH,
    ac_home = SDL_SCANCODE_AC_HOME,
    ac_back = SDL_SCANCODE_AC_BACK,
    ac_forward = SDL_SCANCODE_AC_FORWARD,
    ac_stop = SDL_SCANCODE_AC_STOP,
    ac_refresh = SDL_SCANCODE_AC_REFRESH,
    ac_bookmarks = SDL_SCANCODE_AC_BOOKMARKS,

    /* @} */ /* Usage page 0x0C */

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
    /* @{ */

    brightnessdown = SDL_SCANCODE_BRIGHTNESSDOWN,
    brightnessup = SDL_SCANCODE_BRIGHTNESSUP,
    displayswitch =
        SDL_SCANCODE_DISPLAYSWITCH, /**< display mirroring/dual display
                                         switch, video mode switch */
    kbdillumtoggle = SDL_SCANCODE_KBDILLUMTOGGLE,
    kbdillumdown = SDL_SCANCODE_KBDILLUMDOWN,
    kbdillumup = SDL_SCANCODE_KBDILLUMUP,
    eject = SDL_SCANCODE_EJECT,
    sleep = SDL_SCANCODE_SLEEP,

    app1 = SDL_SCANCODE_APP1,
    app2 = SDL_SCANCODE_APP2,

    /* @} */ /* Walther keys */

    /* Add any other keys here. */

    _num_scancodes =
        SDL_NUM_SCANCODES /**< not a key, just marks the number of scancodes
                                     for array bounds */
};

} // end namespace sdl

#endif // SDLXX_SCANCODE_HPP

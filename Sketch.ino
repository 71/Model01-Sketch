// -*- mode: c++ -*-

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


#include "Kaleidoscope.h"

#include "Kaleidoscope-EEPROM-Settings.h"

#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-Leader.h"

#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-LEDEffect-Breathe.h"
#include "Kaleidoscope-LEDEffect-Chase.h"
#include "Kaleidoscope-LEDEffect-Rainbow.h"
#include "Kaleidoscope-LED-Palette-Theme.h"
#include "Kaleidoscope-Colormap.h"

#include "Kaleidoscope-HostPowerManagement.h"
#include "Kaleidoscope-HostOS.h"
#include "Kaleidoscope-Syster.h"
#include "Kaleidoscope-Unicode.h"

#include "Kaleidoscope/hid.h"
#include "CustomKeys.h"


/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */
enum { MACRO_VERSION_INFO,
       MACRO_CHANGE_OS,
       MACRO_TO_AUX_LAYER,
     };


/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   keeping NUM and FN consistent and accessible on all layers
  *
  * The PROG key is special, since it is how you indicate to the board that you
  * want to flash the firmware. However, it can be remapped to a regular key.
  * When the keyboard boots, it first looks to see whether the PROG key is held
  * down; if it is, it simply awaits further flashing instructions. If it is
  * not, it continues loading the rest of the firmware and the keyboard
  * functions normally, with whatever binding you have set to PROG. More detail
  * here: https://community.keyboard.io/t/how-the-prog-key-gets-you-into-the-bootloader/506/8
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */
enum { PRIMARY,
       FUNCTION,
       AUX,
     };


/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

DEFINE_CUSTOM_KEY(2Underscore,  Key_2,              LSHIFT(Key_Minus), Consumer_MediaSelection);
DEFINE_CUSTOM_KEY(3Minus,       Key_3,              Key_Minus,         Consumer_MediaSelectComputer);
DEFINE_CUSTOM_KEY(4Slash,       Key_4,              Key_Slash,         Consumer_MediaSelectTV);
DEFINE_CUSTOM_KEY(5Pipe,        Key_5,              Key_Pipe,          Consumer_MediaSelectWww);
DEFINE_CUSTOM_KEY(7Equals,      Key_7,              Key_Equals,        Consumer_MediaSelectDvd);
DEFINE_CUSTOM_KEY(8Ampersand,   Key_8,              LSHIFT(Key_7),     Consumer_MediaSelectTelephone);
DEFINE_CUSTOM_KEY(9Question,    Key_9,              LSHIFT(Key_Slash), Consumer_MediaSelectProgramGuide);
DEFINE_CUSTOM_KEY(0Hash,        Key_0,              LSHIFT(Key_3),     Consumer_MediaSelectVideoPhone);
DEFINE_CUSTOM_KEY(PlusDollar,   LSHIFT(Key_Equals), LSHIFT(Key_4),     Consumer_MediaSelectMessages);
DEFINE_CUSTOM_KEY(TimesAt,      LSHIFT(Key_8),      LSHIFT(Key_2),     Consumer_MediaSelectGames);
DEFINE_CUSTOM_KEY(CommaLParen,  Key_Comma,          LSHIFT(Key_9),     Consumer_MediaSelectCd);
DEFINE_CUSTOM_KEY(PeriodRParen, Key_Period,         LSHIFT(Key_0),     Consumer_MediaSelectVcr);

KEYMAPS(
  [PRIMARY] = KEYMAP_STACKED
  (Key_Escape,      Key_1,         CustomKey_2Underscore, CustomKey_3Minus, CustomKey_4Slash,      CustomKey_5Pipe,        CustomKey_PlusDollar,
   Key_Backtick,    Key_X,         Key_Y,                 Key_D,            CustomKey_CommaLParen, CustomKey_PeriodRParen, Key_Tab,
   Key_PageUp,      Key_A,         Key_T,                 Key_H,            Key_E,                 Key_B,
   Key_PageDown,    Key_P,         Key_V,                 Key_G,            Key_W,                 Key_K,                  LEAD(0),
   Key_LeftControl, Key_Backspace, Key_LeftGui,           Key_LeftShift,
   ShiftToLayer(FUNCTION),

   CustomKey_TimesAt, Key_6,       CustomKey_7Equals, CustomKey_8Ampersand, CustomKey_9Question, CustomKey_0Hash, ___,
   Key_Enter,         Key_Z,       Key_Q, Key_M,      Key_L,                Key_U,               ___,
                      Key_F,       Key_S, Key_N,      Key_O,                Key_I,               ___,
   SYSTER,            Key_J,       Key_R, Key_C,      Key_Semicolon,        Key_Quote,           ___,
   Key_RightShift,    Key_LeftAlt, Key_Spacebar,      Key_Enter,
   M(MACRO_TO_AUX_LAYER)),

  [FUNCTION] = KEYMAP_STACKED
  (XXX,              Key_F1,           Key_F2,      Key_F3,     Key_F4,               Key_F5,                Key_LEDEffectNext,
   Key_Tab,          XXX,              Key_mouseUp, XXX,        Key_LeftBracket,      Key_RightBracket,      XXX,
   Key_Home,         Key_mouseL,       Key_mouseDn, Key_mouseR, Key_LeftCurlyBracket, Key_RightCurlyBracket,
   Key_End,          Key_PrintScreen,  XXX,         XXX,        LSHIFT(Key_Comma),    LSHIFT(Key_Period),    XXX,
   Key_RightControl, Key_Delete,       XXX,         XXX,
   ___,

   M(MACRO_CHANGE_OS), Key_F6,                     Key_F7,                   Key_F8,                   Key_F9,                 Key_F10,                 Key_F11,
   Key_mouseScrollUp,  Consumer_ScanPreviousTrack, Consumer_VolumeDecrement, Consumer_VolumeIncrement, Consumer_ScanNextTrack, Consumer_PlaySlashPause, Key_F12,
                       Key_LeftArrow,              Key_DownArrow,            Key_UpArrow,              Key_RightArrow,         XXX,                     XXX,
   Key_mouseScrollDn,  XXX,                        Key_BacklightDown,        Key_BacklightUp,          XXX,                    XXX,                     XXX,
   Key_mouseBtnL,      Key_Lang1,                  Key_mouseBtnR,            Key_mouseBtnM,
   ___),

   [AUX] = KEYMAP
   (___, ___, ___, ___, ___, ___, ___,           Key_Esc, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,           ___,     ___, Key_1, Key_Keypad2, Key_Keypad3, ___, ___,
    ___, ___, ___, ___, ___, ___,                 Key_Keypad0, Key_Keypad4, Key_Keypad5, Key_Keypad6, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,           ___,     ___, Key_Keypad7, Key_Keypad8, Key_Keypad9, ___, Key_Enter,
    ___, ___, ___, ___,                          ___,     ___, ___, ___,
    ___,                                         ___)
)

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */
const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    if (keyToggledOn(keyState)) {
      Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
      Macros.type(PSTR(BUILD_INFORMATION));
    }
    break;

  case MACRO_CHANGE_OS:
    if (keyToggledOn(keyState)) {
      HostOS.os(HostOS.os() == kaleidoscope::hostos::LINUX   ? kaleidoscope::hostos::WINDOWS
              : HostOS.os() == kaleidoscope::hostos::WINDOWS ? kaleidoscope::hostos::OSX
              :                                                kaleidoscope::hostos::LINUX);
    }
    break;

  case MACRO_TO_AUX_LAYER:
    if (keyToggledOn(keyState)) {
      Layer.activate(FUNCTION);
      Layer.activate(AUX);
    } else if (keyToggledOff(keyState)) {
      Layer.deactivate(AUX);
      Layer.deactivate(FUNCTION);
    }
    break;
  }

  return MACRO_NONE;
}

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    LEDControl.paused = true;
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

void systerAction(kaleidoscope::plugin::Syster::action_t action, const char *symbol) {
  switch (action) {
  case kaleidoscope::plugin::Syster::StartAction:
    handleKeyswitchEvent(Key_Slash, UNKNOWN_KEYSWITCH_LOCATION, IS_PRESSED | INJECTED);
    kaleidoscope::hid::sendKeyboardReport();
    handleKeyswitchEvent(Key_Slash, UNKNOWN_KEYSWITCH_LOCATION, WAS_PRESSED | INJECTED);
    kaleidoscope::hid::sendKeyboardReport();
    break;

  case kaleidoscope::plugin::Syster::EndAction:
    handleKeyswitchEvent(Key_Backspace, UNKNOWN_KEYSWITCH_LOCATION, IS_PRESSED | INJECTED);
    kaleidoscope::hid::sendKeyboardReport();
    handleKeyswitchEvent(Key_Backspace, UNKNOWN_KEYSWITCH_LOCATION, WAS_PRESSED | INJECTED);
    kaleidoscope::hid::sendKeyboardReport();
    break;

  case kaleidoscope::plugin::Syster::SymbolAction:
    if (symbol[0] == 'u') {
      uint32_t u = 0;

      for (unsigned i = 1; symbol[i]; i++) {
        if (symbol[i] >= '0' && symbol[i] <= '9')
          u = u * 10 + symbol[i] - '0';
        else
          return;
      }

      Unicode.type(u);
    } else if (symbol[0] == 'x') {
      uint32_t u = 0;

      for (unsigned i = 1; symbol[i]; i++) {
        if (symbol[i] >= '0' && symbol[i] <= '9')
          u = u * 16 + symbol[i] - '0';
        else if (symbol[i] >= 'a' && symbol[i] <= 'f')
          u = u * 16 + symbol[i] - 'a' + 10;
        else
          return;
      }

      Unicode.type(u);
    } else if (symbol[0] == 'o' && symbol[1] == 's') {
      if (symbol[2] == 'l')
        HostOS.os(kaleidoscope::hostos::LINUX);
      else if (symbol[2] == 'w')
        HostOS.os(kaleidoscope::hostos::WINDOWS);
      else if (symbol[2] == 'x')
        HostOS.os(kaleidoscope::hostos::OSX);
      else
        Macros.type(
            HostOS.os() == kaleidoscope::hostos::LINUX   ? PSTR("linux osl")
          : HostOS.os() == kaleidoscope::hostos::WINDOWS ? PSTR("windows osw")
          : HostOS.os() == kaleidoscope::hostos::OSX     ? PSTR("osx osx")
          : PSTR("unknown"));
    }
    break;
  }
}


// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,

  // LEDControl provides support for other LED modes
  LEDControl,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,

  // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
  // and slowly moves the rainbow across your keyboard
  LEDRainbowWaveEffect,

  // The rainbow effect changes the color of all of the keyboard's keys at the same time
  // running through all the colors of the rainbow.
  LEDRainbowEffect,

  // The chase effect follows the adventure of a blue pixel which chases a red pixel across
  // your keyboard. Spoiler: the blue pixel never catches the red pixel
  LEDChaseEffect,

  // The breathe effect slowly pulses all of the LEDs on your keyboard
  LEDBreatheEffect,

  // The LED Palette Theme plugin provides a shared palette for other plugins,
  // like Colormap below
  LEDPaletteTheme,

  // The Colormap effect makes it possible to set up per-layer colormaps
  ColormapEffect,

  // The macros plugin adds support for macros
  Macros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // Allow arbitrary unicode to be sent to the OS.
  HostOS,
  Unicode,
  Syster,

  // Allow custom keys to be created.
  CustomKeys
);


void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();

  // We need to tell the Colormap plugin how many layers we want to have custom
  // maps for. To make things simple, we set it to five layers, which is how
  // many editable layers we have (see above).
  ColormapEffect.max_layers(3);

  REGISTER_CUSTOM_KEYS(
    CustomKey_2Underscore,
    CustomKey_3Minus,
    CustomKey_4Slash,
    CustomKey_5Pipe,
    CustomKey_7Equals,
    CustomKey_8Ampersand,
    CustomKey_9Question,
    CustomKey_0Hash,
    CustomKey_PlusDollar,
    CustomKey_TimesAt,
    CustomKey_CommaLParen,
    CustomKey_PeriodRParen);
}

void loop() {
  Kaleidoscope.loop();
}

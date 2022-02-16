// -*- mode: c++ -*-

#include <Kaleidoscope.h>

// Plugins:
#include <Kaleidoscope-CharShift.h>             // https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-CharShift.html
#include <Kaleidoscope-HostPowerManagement.h>   // https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-HostPowerManagement.html
#include <Kaleidoscope-LED-ActiveModColor.h>    // https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-LED-ActiveModColor.html
#include <Kaleidoscope-LEDControl.h>            // https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-LEDControl.html
#include <Kaleidoscope-LEDEffect-Rainbow.h>     // https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-LEDEffect-Rainbow.html
#include <Kaleidoscope-LEDEffect-SolidColor.h>  // https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-LEDEffect-SolidColor.html
#include <Kaleidoscope-Macros.h>                // https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-Macros.html

// Enums used below.

enum macros {
  MACRO_CYCLE_LED,
};

enum layers {
  PRIMARY,
  QWERTY,
  FN_L,
  FN_R,
  FN_BOTH,
};

#include "./Keymaps.h"

/**
 * Implementation of macros.
 */
const macro_t* macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {
  case MACRO_CYCLE_LED:
    if (keyToggledOn(keyState)) {
      LEDControl.next_mode();

      if (LEDControl.get_mode_index() == 2) {
        Layer.activate(QWERTY);
      } else {
        Layer.deactivate(QWERTY);
      }
    }
    break;
  }

  return MACRO_NONE;
}

/**
 * toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    LEDControl.disable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.enable();
    LEDControl.refreshAll();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    break;
  }
}

/**
 * hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/**
 * A solid white color, which also activates the QWERTY layer when
 * entered.
 */
static kaleidoscope::plugin::LEDSolidColor solidWhite(150, 150, 150);

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // Led modes:
  LEDControl,
  LEDOff,
  LEDRainbowWaveEffect,
  solidWhite,
  ActiveModColorEffect,

  // Misc:
  HostPowerManagement,

  // Macros and keys:
  Macros,
  CharShift
);


void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowWaveEffect.brightness(150);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();

  // Register custom keys.
  setupKeymaps();
}

void loop() {
  Kaleidoscope.loop();
}

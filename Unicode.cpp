#include "Unicode.h"
#include "Kaleidoscope.h"
#include "Kaleidoscope/hid.h"

namespace kaleidoscope {
namespace plugin {
uint8_t Unicode::input_delay_;

void Unicode::start(void) {
  switch (::HostOS.os()) {
  case hostos::LINUX:
    hid::pressRawKey(Key_LeftControl);
    hid::pressRawKey(Key_LeftShift);
    hid::pressRawKey(Key_U);
    hid::sendKeyboardReport();
    hid::releaseRawKey(Key_LeftControl);
    hid::releaseRawKey(Key_LeftShift);
    hid::releaseRawKey(Key_U);
    hid::sendKeyboardReport();
    break;
  case hostos::WINDOWS:
    hid::pressRawKey(Key_LeftAlt);
    hid::sendKeyboardReport();
    hid::pressRawKey(Key_Keypad0);
    hid::sendKeyboardReport();
    hid::releaseRawKey(Key_Keypad0);
    hid::sendKeyboardReport();
    break;
  case hostos::OSX:
    hid::pressRawKey(Key_LeftAlt);
    break;
  default:
    unicodeCustomStart();
    break;
  }
}

void Unicode::input(void) {
  switch (::HostOS.os()) {
  case hostos::LINUX:
  case hostos::WINDOWS:
    break;
  case hostos::OSX:
    hid::pressRawKey(Key_LeftAlt);
    break;
  default:
    unicodeCustomInput();
    break;
  }
  delay(input_delay_);
}

void Unicode::end(void) {
  switch (::HostOS.os()) {
  case hostos::LINUX:
    hid::pressRawKey(Key_Spacebar);
    hid::sendKeyboardReport();
    hid::releaseRawKey(Key_Spacebar);
    hid::sendKeyboardReport();
    break;
  case hostos::WINDOWS:
  case hostos::OSX:
    hid::releaseRawKey(Key_LeftAlt);
    hid::sendKeyboardReport();
    break;
  default:
    unicodeCustomEnd();
    break;
  }
}

void Unicode::typeCode(uint32_t unicode) {
  if (::HostOS.os() == hostos::WINDOWS) {
    Serial.print("Typing unicode ");
    Serial.println(unicode);
    unicodeRecursiveKeypadInput(unicode);
    return;
  }

  bool on_zero_start = true;
  for (int8_t i = 7; i >= 0; i--) {
    if (i <= 3) {
      on_zero_start = false;
    }
    uint8_t digit = ((unicode >> (i * 4)) & 0xF);
    if (digit == 0) {
      if (on_zero_start == false) {
        Key key = hexToKey(digit);
        input();
        hid::pressRawKey(key);
        hid::sendKeyboardReport();
        input();
        hid::releaseRawKey(key);
        hid::sendKeyboardReport();
      }
    } else {
      Key key = hexToKey(digit);
      input();
      hid::pressRawKey(key);
      hid::sendKeyboardReport();
      input();
      hid::releaseRawKey(key);
      hid::sendKeyboardReport();
      on_zero_start = false;
    }
    delay(5);
  }
}

void Unicode::type(uint32_t unicode) {
  start();
  typeCode(unicode);
  end();
}

}
}

__attribute__((weak)) Key hexToKey(uint8_t hex) {
  uint8_t m;
  if (hex == 0x0) {
    return Key_0;
  }
  if (hex < 0xA) {
    m = Key_1.keyCode + (hex - 0x1);
  } else {
    m = Key_A.keyCode + (hex - 0xA);
  }
  return { m, KEY_FLAGS };
}

__attribute__((weak)) void unicodeCustomStart(void) {
}

__attribute__((weak)) void unicodeCustomEnd(void) {
}

__attribute__((weak)) void unicodeCustomInput(void) {
}

__attribute__((weak)) void unicodeRecursiveKeypadInput(uint32_t unicode) {
  if (unicode == 0)
    return;

  unicodeRecursiveKeypadInput(unicode / 10);
  delay(5);

  uint8_t digit = unicode % 10;
  Key key = digit == 0 ? Key_Keypad0 : (Key) { (Key_Keypad1.keyCode + digit - 1), KEY_FLAGS };

  kaleidoscope::plugin::Unicode::input();
  kaleidoscope::hid::pressRawKey(key);
  kaleidoscope::hid::sendKeyboardReport();
  kaleidoscope::plugin::Unicode::input();
  kaleidoscope::hid::releaseRawKey(key);
  kaleidoscope::hid::sendKeyboardReport();
}

kaleidoscope::plugin::Unicode Unicode;

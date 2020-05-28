#pragma once

#include <Kaleidoscope-HostOS.h>

namespace kaleidoscope {
namespace plugin {
class Unicode : public kaleidoscope::Plugin {
 public:
  Unicode(void) {}

  static void start(void);
  static void input(void);
  static void end(void);

  static void type(uint32_t unicode);
  static void typeCode(uint32_t unicode);

  static void input_delay(uint8_t delay) {
    input_delay_ = delay;
  }
  static uint8_t input_delay() {
    return input_delay_;
  }
 private:
  static uint8_t input_delay_;
};
}
}

Key hexToKey(uint8_t hex);

void unicodeCustomStart(void);
void unicodeCustomEnd(void);
void unicodeCustomInput(void);
void unicodeRecursiveKeypadInput(uint32_t unicode);

extern kaleidoscope::plugin::Unicode Unicode;

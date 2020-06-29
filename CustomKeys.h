#include "Kaleidoscope.h"
#include "Kaleidoscope/hid.h"

// Find extra keys you don't need to assign to 'appearAs':
// https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs_consumerctl.h
#define DEFINE_CUSTOM_KEY(keyName, unshifted, shifted, appearAs) \
  constexpr CustomKey CustomKey_ ## keyName PROGMEM = CustomKey(appearAs, unshifted, shifted)

#define REGISTER_CUSTOM_KEYS(...)                    \
  static const CustomKey __custom_keys[] PROGMEM = { \
    __VA_ARGS__,                                     \
    {Key_NoKey, Key_NoKey, Key_NoKey},               \
  };                                                 \
  CustomKeys.setCustomKeys(__custom_keys)

struct CustomKey {
  const Key appear_as, unshifted, shifted;

  constexpr CustomKey(Key appearAs, Key unshifted, Key shifted)
    : appear_as(appearAs), unshifted(unshifted), shifted(shifted)
  {}

  constexpr operator Key() const {
    return appear_as;
  }
};

class CustomKeys : public kaleidoscope::Plugin {
 public:
  CustomKeys() {}

  kaleidoscope::EventHandlerResult onKeyswitchEvent(Key& mapped_key, KeyAddr key_addr, uint8_t key_state);

  void setCustomKeys(const CustomKey* customKeys) {
    custom_keys_ = customKeys;
  }

 private:
  const CustomKey* custom_keys_;
  bool is_active_, is_shifted_, will_unshift_;
};

extern CustomKeys CustomKeys;

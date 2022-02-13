#include "CustomKeys.h"

kaleidoscope::EventHandlerResult CustomKeys::onKeyswitchEvent(Key& mapped_key, KeyAddr key_addr, uint8_t key_state) {
  if (mapped_key == Key_LeftShift || mapped_key == Key_RightShift) {
    will_unshift_ = !keyIsPressed(key_state);

    if (is_active_)
      return kaleidoscope::EventHandlerResult::EVENT_CONSUMED;
    else
      is_shifted_ = keyIsPressed(key_state);
  }

  // Try to find the current key in the dictionary
  Key orig;
  uint8_t i = 0;

  for (;;) {
    orig.setRaw(custom_keys_[i].appear_as.getRaw());

    if (orig.getRaw() == Key_NoKey.getRaw())
      return kaleidoscope::EventHandlerResult::OK;

    if (orig.getRaw() == mapped_key.getRaw())
      break;

    i++;
  }

  is_active_ = keyIsPressed(key_state);

  if (!is_active_) {
    if (will_unshift_)
      is_shifted_ = false;

    will_unshift_ = false;

    return kaleidoscope::EventHandlerResult::OK;
  }

  // We found it, so now we manipulate keys to make things work well.
  if (is_shifted_) {
    mapped_key.setRaw(custom_keys_[i].shifted.getRaw());

    // If the custom key requires Shift to not be pressed, we have to virtually release it here.
    if (!(mapped_key.getFlags() & SHIFT_HELD)) {
      if (keyIsPressed(key_state)) {
        kaleidoscope::Runtime.hid().keyboard().releaseKey(Key_LeftShift);
        kaleidoscope::Runtime.hid().keyboard().releaseKey(Key_RightShift);
      } else {
        return kaleidoscope::EventHandlerResult::EVENT_CONSUMED;
      }
    }
  } else {
    mapped_key.setRaw(custom_keys_[i].unshifted.getRaw());

    // If the custom key requires Shift to be pressed, there is actually nothing to do,
    // since the SHIFT_HELD flag will be passed along the key.
  }

  return kaleidoscope::EventHandlerResult::OK;
}

class CustomKeys CustomKeys;

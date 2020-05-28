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
    orig.raw = pgm_read_word(&custom_keys_[i].appear_as.raw);

    if (orig.raw == Key_NoKey.raw)
      return kaleidoscope::EventHandlerResult::OK;

    if (orig.raw == mapped_key.raw)
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
    mapped_key = { .raw = pgm_read_word(&custom_keys_[i].shifted.raw) };

    // If the custom key requires Shift to not be pressed, we have to virtually release it here.
    if (!(mapped_key.flags & SHIFT_HELD)) {
      if (keyIsPressed(key_state)) {
        kaleidoscope::hid::releaseKey(Key_LeftShift);
        kaleidoscope::hid::releaseKey(Key_RightShift);
      } else {
        return kaleidoscope::EventHandlerResult::EVENT_CONSUMED;
      }
    }
  } else {
    mapped_key = { .raw = pgm_read_word(&custom_keys_[i].unshifted.raw) };

    // If the custom key requires Shift to be pressed, there is actually nothing to do,
    // since the SHIFT_HELD flag will be passed along the key.
  }

  return kaleidoscope::EventHandlerResult::OK;
}

typeof(CustomKeys) CustomKeys;

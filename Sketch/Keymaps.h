// Automatically generated by ../generateKeymaps.ts. Do not edit.

KEYMAPS(
  [PRIMARY] = KEYMAP
  (Key_Escape, Key_1, CS(0), CS(1), CS(2), CS(3), CS(4), CS(5), Key_6, Key_7, CS(6), CS(7), CS(8), XXX,
   CS(9), Key_X, Key_Y, Key_D, Key_Comma, Key_Period, Key_Tab, XXX, Key_Z, Key_Q, Key_M, Key_L, Key_U, XXX,
   XXX, Key_A, Key_T, Key_H, Key_E, Key_B, Key_F, Key_S, Key_N, Key_O, Key_I, Key_PageUp,
   Key_LeftGui, Key_P, Key_V, Key_G, Key_W, Key_K, XXX, Key_RightAlt, Key_J, Key_R, Key_C, Key_Semicolon, Key_Quote, Key_PageDown,
   Key_LeftShift, Key_Spacebar, Key_LeftAlt, Key_LeftControl, Key_LeftControl, Key_LeftAlt, Key_Enter, Key_LeftShift,
   ShiftToLayer(FN_L), ShiftToLayer(FN_R)),

  [QWERTY] = KEYMAP
  (___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
   ___, Key_Q, Key_W, Key_E, Key_R, Key_T, ___, ___, Key_Y, Key_U, Key_I, Key_O, Key_P, ___,
   XXX, Key_A, Key_S, Key_D, Key_F, Key_G, Key_H, Key_J, Key_K, Key_L, ___, ___,
   ___, Key_Z, Key_X, Key_C, Key_V, Key_B, ___, ___, Key_N, Key_M, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___, ___,
   ___, ___),

  [FN_L] = KEYMAP
  (XXX, LGUI(Key_1), LGUI(Key_2), LGUI(Key_3), LGUI(Key_4), LGUI(Key_5), M(MACRO_CYCLE_LED), XXX, Key_F6, Key_F7, Key_F8, Key_F9, Key_F10, Key_F11,
   LGUI(CS(9)), LGUI(Key_X), LGUI(Key_Y), LGUI(Key_D), LSHIFT(Key_9), LSHIFT(Key_0), LGUI(Key_Tab), ___, ___, ___, ___, ___, ___, ___,
   XXX, Key_Backspace, Key_Delete, XXX, Key_LeftBracket, Key_RightBracket, ___, ___, ___, ___, ___, ___,
   LGUI(Key_LeftGui), Key_PrintScreen, Key_Backtick, Key_Backslash, Key_LeftCurlyBracket, Key_RightCurlyBracket, ___, ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___, ___,
   ___, ___),

  [FN_R] = KEYMAP
  (XXX, Key_F1, Key_F2, Key_F3, Key_F4, Key_F5, M(MACRO_CYCLE_LED), XXX, LGUI(Key_6), LGUI(Key_7), LGUI(Key_8), LGUI(Key_9), LGUI(Key_0), Key_F11,
   ___, ___, ___, ___, ___, ___, ___, ___, Consumer_ScanPreviousTrack, Consumer_VolumeDecrement, Consumer_VolumeIncrement, Consumer_ScanNextTrack, Consumer_PlaySlashPause, Key_F12,
   ___, ___, ___, ___, ___, ___, XXX, Key_LeftArrow, Key_DownArrow, Key_UpArrow, Key_RightArrow, XXX,
   ___, ___, ___, ___, ___, ___, ___, LGUI(Key_RightAlt), LGUI(Key_J), LGUI(Key_R), LGUI(Key_C), LGUI(Key_Semicolon), LGUI(Key_Quote), LGUI(Key_PageDown),
   ___, ___, ___, ___, ___, ___, ___, ___,
   ___, ___),

  [FN_BOTH] = KEYMAP
  (___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___, ___,
   ___, ___),
);

inline void setupKeymaps() {
  CS_KEYS(
    kaleidoscope::plugin::CharShift::KeyPair(Key_2, Key_Minus),
    kaleidoscope::plugin::CharShift::KeyPair(Key_3, LSHIFT(Key_Minus)),
    kaleidoscope::plugin::CharShift::KeyPair(Key_4, Key_Slash),
    kaleidoscope::plugin::CharShift::KeyPair(Key_5, Key_Pipe),
    kaleidoscope::plugin::CharShift::KeyPair(LSHIFT(Key_8), LSHIFT(Key_4)),
    kaleidoscope::plugin::CharShift::KeyPair(LSHIFT(Key_Equals), LSHIFT(Key_2)),
    kaleidoscope::plugin::CharShift::KeyPair(Key_8, Key_Equals),
    kaleidoscope::plugin::CharShift::KeyPair(Key_9, LSHIFT(Key_Slash)),
    kaleidoscope::plugin::CharShift::KeyPair(Key_0, LSHIFT(Key_3)),
    kaleidoscope::plugin::CharShift::KeyPair(LSHIFT(Key_Backtick), LSHIFT(Key_5)),
  );
}

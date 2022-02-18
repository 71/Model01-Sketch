# Model 01 Sketch

My sketch for the [Model 01](https://shop.keyboard.io/products/model-01-keyboard),
built with [Kaleidoscope](https://github.com/keyboardio/Kaleidoscope).

## Layout

Layers:
- Primary
- Qwerty
- Fn Left
- Fn Right
- Fn Both

```
Escape         1          2-Minus   3-Underscore  4-Slash      5-Pipe        Times-Dollar                     Plus-At      6        7        8-Equals  9-Question  0-Hash  _
^              ^          ^         ^             ^            ^             ^                                ^            ^        ^        ^         ^           ^       ^
_              #1         #2        #3            #4           #5            M(CYCLE_LED)                     _            F6       F7       F8        F9          F10     F11
_              F1         F2        F3            F4           F5            M(CYCLE_LED)                     _            #6       #7       #8        #9          #0      F11
^              ^          ^         ^             ^            ^             ^                                ^            ^        ^        ^         ^           ^       ^


Tilde-Percent  X          Y         D             Comma        Period        Tab                              _            Z        Q        M         L           U       _
^              Q          W         E             R            T             ^                                ^            Y        U        I         O           P       ^
^              ^          ^         ^             LeftParen    RightParen    ^                                ^            ^        ^        ^         ^           ^       ^
^              ^          ^         ^             ^            ^             ^                                ^            Prev     VolDown  VolUp     Next        Play    F12
^              ^          ^         ^             ^            ^             ^                                ^            ^        ^        ^         ^           ^       ^


_              A          T         H             E            B             -                                -            F        S        N         O           I       PageUp
_              A          S         D             F            G             -                                -            H        J        K         L           ^       ^
_              Backspace  Delete    _             LeftBracket  RightBracket  -                                -            ^        ^        ^         ^           ^       ^
^              ^          ^         ^             ^            ^             -                                -            _        Left     Down      Up          Right   _
^              ^          ^         ^             ^            ^             -                                -            ^        ^        ^         ^           ^       ^


LeftGui        P          V         G             W            K             _                                RightAlt     J        R        C         Semicolon   Quote   PageDown
^              Z          X         C             V            B             ^                                ^            N        M        ^         ^           ^       ^
^              PrtScreen  Backtick  Backslash     LeftCurly    RightCurly    ^                                ^            ^        ^        ^         ^           ^       ^
^              ^          ^         ^             ^            ^             ^                                ^            ^        ^        ^         ^           ^       ^
^              ^          ^         ^             ^            ^             ^                                ^            ^        ^        ^         ^           ^       ^


-              -          -         LeftShift     Spacebar     LeftAlt       LeftControl                      LeftControl  LeftAlt  Enter    LeftShift -           -       -
-              -          -         ^             ^            ^             ^                                ^            ^        ^        ^         -           -       -
-              -          -         ^             ^            ^             ^                                ^            ^        ^        ^         -           -       -
-              -          -         ^             ^            ^             ^                                ^            ^        ^        ^         -           -       -
-              -          -         ^             ^            ^             ^                                ^            ^        ^        ^         -           -       -


                                                                   ShiftToLayer(FN_L)                         ShiftToLayer(FN_R)
                                                                   ^                                          ^
                                                                   ^                                          ^
                                                                   ^                                          ^
                                                                   ^                                          ^
```

The [`generateKeymaps`](./generateKeymaps.ts) script can be used to convert the above text to an actual Kaleidoscope keymap.

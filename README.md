# Kaleidoscope-LEDEffect-Plasma

A pastel palette morphs slowly on your keyboardio.

I've wanted to adapt this to the keyboardio for a long time. It is a heavily modified version of an older
Arduino LED file I have kicking around my machine. I think it generates very pretty effects.


## Using the extension

To use the plugin, include the header, and tell the firmware to use either (or
both!) of the effects:

```c++
#include <Kaleidoscope-LEDControl.h>
#include <Kaleidoscope-LEDEffect-Plasma.h>

KALEIDOSCOPE_INIT_PLUGINS(LEDPlasmaEffect);

void setup() {
  Kaleidoscope.setup();
}
```

## Plugin methods

## Dependencies

* [Kaleidoscope-LEDControl](https://github.com/keyboardio/Kaleidoscope-LEDControl)

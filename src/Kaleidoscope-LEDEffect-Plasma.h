/* Kaleidoscope-LEDEffect-Plasma - Plasma LED effects for Kaleidoscope.
 * Copyright (C) 2017-2018  Keyboard.io, Inc.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "Kaleidoscope-LEDControl.h"

namespace kaleidoscope {
class LEDPlasmaEffect : public LEDMode {
 public:
  LEDPlasmaEffect(void) {}

  void brightness(byte);
  byte brightness(void) {
    return plasma_value;
  }
  void update_delay(byte);
  byte update_delay(void) {
    return plasma_update_delay;
  }
  void update(void) final;

 private:
  uint16_t plasma_hue = 0;   //  stores 0 to 614

  uint8_t plasma_steps = 1;  //  number of hues we skip in a 360 range per update
  uint16_t plasma_last_update = 0;
  uint16_t plasma_update_delay = 40; // delay between updates (ms)

  byte plasma_saturation = 255;
  byte plasma_value = 50;
};


class LEDPlasmaWaveEffect : public LEDMode {
 public:
  LEDPlasmaWaveEffect(void) {}

  void brightness(byte);
  byte brightness(void) {
    return plasma_value;
  }
  void update_delay(byte);
  byte update_delay(void) {
    return plasma_update_delay;
  }
  void update(void) final;

 private:
  uint16_t plasma_hue = 0;  //  stores 0 to 614

  uint8_t plasma_wave_steps = 1;  //  number of hues we skip in a 360 range per update
  uint16_t plasma_last_update = 0;
  uint16_t plasma_update_delay = 40; // delay between updates (ms)

  byte plasma_saturation = 255;
  byte plasma_value = 50;
};
}

extern kaleidoscope::LEDPlasmaEffect LEDPlasmaEffect;
extern kaleidoscope::LEDPlasmaWaveEffect LEDPlasmaWaveEffect;

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

#include "Kaleidoscope-LEDEffect-Plasma.h"

namespace kaleidoscope {

#define MS_PER_FRAME 100  // 40 = 25 fps

  float phase = 0.0;
  float phaseIncrement = 0.06;  // Controls the speed of the moving points. Higher == faster. I like 0.08 ..03 change to .02
  float colorStretch = 0.007;    // Higher numbers will produce tighter color bands. I like 0.11 . ok try .11 instead of .03

  struct Point {
    float x;
    float y;
  };



void LEDPlasmaEffect::update(void) {
  // limit the frame rate; one frame every 64 ms
  static uint8_t prev_time = 0;
  uint8_t now = Kaleidoscope.millisAtCycleStart() / MS_PER_FRAME;
  if (now != prev_time) {
      prev_time = now;
  } else {
      return;
  }

  phase += phaseIncrement;

  Point p1 = { (sin(phase*1.000)+1.0) * 4.5, (sin(phase*1.310)+1.0) * 4.0 };
  Point p2 = { (sin(phase*1.770)+1.0) * 4.5, (sin(phase*2.865)+1.0) * 4.0 };
  Point p3 = { (sin(phase*0.250)+1.0) * 4.5, (sin(phase*0.750)+1.0) * 4.0 };

  byte row, col;
  uint8_t rcount = 0;
  for( row=0; row< ROWS; row++ ) {
    float row_f = float(row);  // Optimization: Keep a floating point value of the row number, instead of recasting it repeatedly.

    for( col=0; col< COLS; col++ ) {
      float col_f = float(col);  // Optimization.

      // Calculate the distance between this LED, and p1.
      Point dist1 = { col_f - p1.x, row_f - p1.y };  // The vector from p1 to this LED.
      float distance1 = sqrt( dist1.x*dist1.x + dist1.y*dist1.y );

      // Calculate the distance between this LED, and p2.
      Point dist2 = { col_f - p2.x, row_f - p2.y };  // The vector from p2 to this LED.
      float distance2 = sqrt( dist2.x*dist2.x + dist2.y*dist2.y );

      // Calculate the distance between this LED, and p3.
      Point dist3 = { col_f - p3.x, row_f - p3.y };  // The vector from p3 to this LED.
      float distance3 = sqrt( dist3.x*dist3.x + dist3.y*dist3.y );

      // Warp the distance with a sin() function. As the distance value increases, the LEDs will get light,dark,light,dark,etc...
      // You can use a cos() for slightly different shading, or experiment with other functions. Go crazy!
      uint8_t color_1 = distance1;  // range: 0.0...1.0
      uint8_t color_2 = distance2;
      uint8_t color_3 = distance3;
      uint8_t color_4 = (cos( distance1 * distance2 * colorStretch )) + 2.0 * 0.5;

      // Square the color_f value to weight it towards 0. The image will be darker and have higher contrast.
      color_1 *= color_1 * color_4;
      color_2 *= color_2 * color_4;
      color_3 *= color_3 * color_4;
      color_4 *= color_4;

      color_1 = constrain(color_1, 8, 190);
      color_2 = constrain(color_2, 8, 190);
      color_3 = constrain(color_3, 8, 190);
      cRGB plasma{color_1, color_2, color_3};

      ::LEDControl.setCrgbAt(row, col, plasma);

    }
  }
}

void LEDPlasmaEffect::brightness(byte brightness) {
  plasma_value = brightness;
}

void LEDPlasmaEffect::update_delay(byte delay) {
  plasma_update_delay = delay;
}


// ---------

void LEDPlasmaWaveEffect::update(void) {
  uint16_t now = millis();
  if ((now - plasma_last_update) < plasma_update_delay) {
    return;
  } else {
    plasma_last_update = now;
  }

  for (uint8_t i = 0; i < LED_COUNT; i++) {
    uint16_t key_hue = plasma_hue + 16 * (i / 4);
    if (key_hue >= 255)          {
      key_hue -= 255;
    }
    cRGB plasma = hsvToRgb(key_hue, plasma_saturation, plasma_value);
    ::LEDControl.setCrgbAt(i, plasma);
  }
  plasma_hue += plasma_wave_steps;
  if (plasma_hue >= 255) {
    plasma_hue -= 255;
  }
}

void LEDPlasmaWaveEffect::brightness(byte brightness) {
  plasma_value = brightness;
}

void LEDPlasmaWaveEffect::update_delay(byte delay) {
  plasma_update_delay = delay;
}
}

kaleidoscope::LEDPlasmaEffect LEDPlasmaEffect;
kaleidoscope::LEDPlasmaWaveEffect LEDPlasmaWaveEffect;

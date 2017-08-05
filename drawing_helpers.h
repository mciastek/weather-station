#ifndef DRAWING_HELPERS_H_
#define DRAWING_HELPERS_H_

#include <math.h>
#include <Adafruit_NeoPixel.h>

#include "globals.h"

#define MAX_POSITIVE_TEMP 40
#define MAX_NEGATIVE_TEMP 25

int getChannelValue(int value, int maxValue = MAX_POSITIVE_TEMP) {
  int parsedValue = ((value * 255) / maxValue);

  return (parsedValue <= 255) ? 255 - parsedValue : 255;
}

int *getColorByTemp(int temp) {
  static int rgb[3];

  if (temp < 0) {
    temp = temp * -1;

    rgb[0] = getChannelValue(temp, MAX_NEGATIVE_TEMP);
    rgb[1] = getChannelValue(temp, MAX_NEGATIVE_TEMP);
    rgb[2] = 255;
  } else if (temp > 0) {
    rgb[0] = 255;
    rgb[1] = getChannelValue(temp);
    rgb[2] = getChannelValue(temp);
  } else {
    rgb[0] = 255;
    rgb[1] = 255;
    rgb[2] = 255;
  }

  return rgb;
}

void drawDigits(int *pixel_matrix, Adafruit_NeoPixel pixels, int *rgb) {
  for (int i = 0; i < NUMPIXELS; i++) {
    if (pixel_matrix[i] == 1) {
      pixels.setPixelColor(i, pixels.Color(rgb[0], rgb[1], rgb[2]));
    } else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }

    pixels.show();
  }
}

#endif

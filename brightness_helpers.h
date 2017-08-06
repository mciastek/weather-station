#ifndef BRIGHTNESS_HELPERS_H_
#define BRIGHTNESS_HELPERS_H_

#include <Adafruit_NeoPixel.h>

#include "globals.h"

#define MAX_VOLTAGE 5.0

int getBrightnessValue(float value) {
  int newValue = ((value * BRIGHTNESS) / MAX_VOLTAGE);

  return (newValue <= BRIGHTNESS) ? newValue : BRIGHTNESS;
}

void setAutoBrightness() {
  int sensorValue = analogRead(PHOTORESISTOR_PIN);

  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);

  int newBrightness = getBrightnessValue(voltage);

  if (DEBUG_MODE == 1) {
    Serial.println("");
    Serial.print("Brightness value: ");
    Serial.print(newBrightness);
  }
  delay(1000);
}

#endif

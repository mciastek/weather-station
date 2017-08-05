#ifndef ICONS_HELPERS_H
#define ICONS_HELPERS_H

#include "globals.h"

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <SD.h>
#include <string.h>

String errorIcon = "["
  "[0,0,0],"
  "[0,0,0],"
  "[233,30,99],"
  "[233,30,99],"
  "[233,30,99],"
  "[233,30,99],"
  "[0,0,0],"
  "[0,0,0],"
  "[0,0,0],"
  "[233,30,99],"
  "[233,30,99],"
  "[0,0,0],"
  "[0,0,0],"
  "[0,0,0],"
  "[233,30,99],"
  "[0,0,0],"
  "[233,30,99],"
  "[233,30,99],"
  "[233,30,99],"
  "[233,30,99],"
  "[0,0,0],"
  "[0,0,0],"
  "[0,0,0],"
  "[233,30,99],"
  "[233,30,99],"
  "[0,0,0],"
  "[233,30,99],"
  "[233,30,99],"
  "[233,30,99],"
  "[0,0,0],"
  "[0,0,0],"
  "[233,30,99],"
  "[233,30,99],"
  "[0,0,0],"
  "[0,0,0],"
  "[233,30,99],"
  "[233,30,99],"
  "[233,30,99],"
  "[0,0,0],"
  "[233,30,99],"
  "[233,30,99],"
  "[0,0,0],"
  "[0,0,0],"
  "[0,0,0],"
  "[233,30,99],"
  "[233,30,99],"
  "[233,30,99],"
  "[233,30,99],"
  "[0,0,0],"
  "[233,30,99],"
  "[0,0,0],"
  "[0,0,0],"
  "[0,0,0],"
  "[233,30,99],"
  "[233,30,99],"
  "[0,0,0],"
  "[0,0,0],"
  "[0,0,0],"
  "[233,30,99],"
  "[233,30,99],"
  "[233,30,99],"
  "[233,30,99],"
  "[0,0,0],"
  "[0,0,0]"
"]";

void drawIcon(Adafruit_NeoPixel pixels, JsonArray& iconArray) {
  int index = 0;

  for (JsonArray::iterator it = iconArray.begin(); it != iconArray.end(); ++it) {
    JsonArray& rgb = it->as<JsonArray&>();


    pixels.setPixelColor(index, pixels.Color(rgb[0], rgb[1], rgb[2]));
    pixels.show();

    index++;
  }
};

void drawIconFromName(String name, Adafruit_NeoPixel pixels) {
  const size_t bufferSize = 64 * JSON_ARRAY_SIZE(3) + JSON_ARRAY_SIZE(64) + JSON_OBJECT_SIZE(1) + 530;
  DynamicJsonBuffer jsonBuffer(bufferSize);

  String fileName = name + ".txt";

  File iconFile = SD.open(fileName);

  if (iconFile) {
    if (DEBUG_MODE == 1) {
      Serial.println("");
      Serial.print("Reading 01d.txt");
    }

    String output = iconFile.readString();

    JsonArray& iconArray = jsonBuffer.parseArray(output);

    if (DEBUG_MODE == 1) {
      Serial.println("");
      Serial.print(output);
    }

    drawIcon(pixels, iconArray);

    iconFile.close();
  } else {
    JsonArray& iconArray = jsonBuffer.parseArray(errorIcon);

    drawIcon(pixels, iconArray);

    if (DEBUG_MODE == 1) {
      Serial.println("");
      Serial.print("No " + fileName + " file!");
    }
  }
};

#endif

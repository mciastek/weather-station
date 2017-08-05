#ifndef WEATHER_HELPERS_H_
#define WEATHER_HELPERS_H_

#include "globals.h"

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "digits_helpers.h"
#include "drawing_helpers.h"
#include "icons_helpers.h"

const char* request_url = API_HOST "?q=" CITY "&units=" UNITS "&appid=" OPEN_WEATHER_API_KEY;

const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 380;

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel temperaturePixels = Adafruit_NeoPixel(NUMPIXELS, FIRST_PIXELS_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel iconPixels = Adafruit_NeoPixel(NUMPIXELS, SECOND_PIXELS_PIN, NEO_GRB + NEO_KHZ800);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

int pixel_matrix[NUMPIXELS] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 1,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

int parseTemperature(int temp) {
  return (temp < 0) ? ((temp > 99) ? 99 : temp * -1) : temp;
}

float getTemperature() {
  float temp = 0.0;

  if (temp != 85.0 || temp != (-127.0)) {
    DS18B20.requestTemperatures();
    temp = DS18B20.getTempCByIndex(0);
  }

  return temp;
}

void getRemoteWeather() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(request_url);

    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      DynamicJsonBuffer jsonBuffer(bufferSize);

      JsonObject& parsed = jsonBuffer.parseObject(payload);

      if (DEBUG_MODE == 1) {
        Serial.println("");
        Serial.println("Response from OpenWeather API:");
        Serial.println(payload);
      }

      JsonObject& main = parsed["main"];
      JsonArray& weather = parsed["weather"];

      JsonObject& firstMeasure = weather[0];

      const char *icon = firstMeasure["icon"];
      int temp = main["temp"];
      int *rgb = getColorByTemp(temp);

      temp = parseTemperature(temp);

      if (DEBUG_MODE == 1) {
        Serial.println("");
        Serial.print("Temperature: ");
        Serial.print(temp);
      }

      insertNumberIntoMatrix(pixel_matrix, temp);
      drawDigits(pixel_matrix, temperaturePixels, rgb);
      drawIconFromName(icon, iconPixels);
    }

    http.end();
  }

  delay(HOUR);
}

void getInternalTemperature() {
  int temp = (int)getTemperature();

  int *rgb = getColorByTemp(temp);

  temp = parseTemperature(temp);

  if (DEBUG_MODE == 1) {
    Serial.println("");
    Serial.print("Temperature: ");
    Serial.print(temp);
  }

  insertNumberIntoMatrix(pixel_matrix, temp);
  drawDigits(pixel_matrix, temperaturePixels, rgb);
  drawIconFromName("home", iconPixels);

  delay(5 * MINUTE);
}

#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

#include "config.h"
#include "globals.h"
#include "digits_helpers.h"
#include "drawing_helpers.h"

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const char* request_url = API_HOST "?q=" CITY "&units=" UNITS "&appid=" OPEN_WEATHER_API_KEY;

const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 380;

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

void getWeather() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(request_url);

    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      DynamicJsonBuffer jsonBuffer(bufferSize);
      
      JsonObject& parsed = jsonBuffer.parseObject(payload);

      Serial.println("");
      Serial.println(payload);

      JsonObject& main = parsed["main"];

      int temp = main["temp"];
      int *rgb = getColorByTemp(temp);

      if (temp < 0) {
        temp = temp * -1;
      } else if (temp > 99) {
        temp = 99;
      }

      Serial.println(temp);

      insertNumberIntoMatrix(pixel_matrix, temp);
      drawPixels(pixel_matrix, pixels, rgb);
    }

    http.end();
  }

  delay(HOUR);
}

void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(ESP.getChipId(), HEX);
  Serial.println(ESP.getFlashChipId(), HEX);

  Serial.println(ESP.getFlashChipSize());
  Serial.println(ESP.getFlashChipSpeed());

  Serial.print("Connecting to: ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Device IP: ");
  Serial.print(WiFi.localIP());

//  insertNumberIntoMatrix(pixel_matrix, 12);

//  for (int m = 0; m < MATRIX_ROWS; m++) {
//      for (int n = 0; n < MATRIX_COLS; n++) {
//          Serial.print(pixel_matrix[m * MATRIX_COLS + n]);   
//      }
//      Serial.println("");
//  } 

  pixels.begin();
  pixels.setBrightness(32);
}

void loop() {
  getWeather();
}

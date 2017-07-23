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

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const char* city = "Warsaw";
const char* openWeatherAPIKey = "e346bfcf6b7024626b87816a351e43a7";
const char* openWeatherAPIHost = "http://api.openweathermap.org/data/2.5/weather";

const int hour = 3600000;

const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 380;

int pixel_matrix[NUMPIXELS] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
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

    http.begin("http://api.openweathermap.org/data/2.5/weather?q=Warsaw&units=metric&appid=e346bfcf6b7024626b87816a351e43a7");

    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      DynamicJsonBuffer jsonBuffer(bufferSize);
      
      JsonObject& parsed = jsonBuffer.parseObject(payload);

      Serial.println("");
      Serial.println(payload);

      JsonObject& main = parsed["main"];

      int temp = main["temp"];

      Serial.println(temp);
    }

    http.end();
  }

  delay(hour);
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

//  char *digits = getDigits(12);
//  int first = digits[0];
//  int second = digits[1];
//
//  Serial.print("First: ");
//  Serial.print(first);
//  Serial.println("");
//  Serial.print(second);

  insertNumberIntoMatrix(pixel_matrix, 12);

  for (int m = 0; m < MATRIX_ROWS; m++) {
      for (int n = 0; n < MATRIX_COLS; n++) {
          Serial.print(pixel_matrix[m * MATRIX_COLS + n]);   
      }
      Serial.println("");
  } 

  pixels.begin();
  pixels.setBrightness(32);
}

void loop() {
  
  for (int i = 0; i < NUMPIXELS; i++) {
    if (pixel_matrix[i] == 1) {
      pixels.setPixelColor(i, pixels.Color(0,150,0));
    }

    pixels.show();
  }
  
//  char *digits = getDigits(12);
//
//  printf("%s", digit[0]);
//  printf("%s", digit[1]);
//  int i, j;

//  for (i = 0; i < NUMPIXELS; i++) {
//    if (digit[i] == 1) {
//      pixels.setPixelColor(i, pixels.Color(0,150,0));
//    }
//
//    pixels.show();
//  }
}

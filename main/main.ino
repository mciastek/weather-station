#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "ciasteczkowo-kolonia";
const char* password = "ciastkowifi12";

const char* city = "Warsaw";
const char* openWeatherAPIKey = "e346bfcf6b7024626b87816a351e43a7";
const char* openWeatherAPIHost = "http://api.openweathermap.org/data/2.5/weather";

const int hour = 3600000;

const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 380;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(ESP.getChipId(), HEX);
  Serial.println(ESP.getFlashChipId(), HEX);

  Serial.println(ESP.getFlashChipSize());
  Serial.println(ESP.getFlashChipSpeed());

  Serial.print("Connecting to: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Device IP: ");
  Serial.print(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
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

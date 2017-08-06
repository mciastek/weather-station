#ifndef GLOBALS_H_
#define GLOBALS_H_

#define DEBUG_MODE 1

#define MATRIX_ROWS 8
#define MATRIX_COLS 8

#define NUM_ROWS 5
#define NUM_COLS 3

#define NUM_SIZE NUM_ROWS * NUM_COLS

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define FIRST_PIXELS_PIN 4
#define SECOND_PIXELS_PIN 2

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS MATRIX_ROWS * MATRIX_COLS

#define BRIGHTNESS 64

#define HOUR 3600000
#define MINUTE 60000

#define CITY "Warsaw"
#define UNITS "metric"
#define API_HOST "http://api.openweathermap.org/data/2.5/weather"

// Dallas temperature meter PIN
#define ONE_WIRE_BUS D1

#define CS_PIN 15

#define PHOTORESISTOR_PIN A0

#endif

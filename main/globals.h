#ifndef GLOBALS_H_
#define GLOBALS_H_

#define MATRIX_ROWS 8
#define MATRIX_COLS 8

#define NUM_ROWS 5
#define NUM_COLS 3

#define NUM_SIZE NUM_ROWS * NUM_COLS

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS MATRIX_ROWS * MATRIX_COLS

#define HOUR 3600000

#endif

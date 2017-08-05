#ifndef DIGITS_HELPERS_H_
#define DIGITS_HELPERS_H_

#include "globals.h"
#include "numbers.h"

const int numberPosX = 2;
const int numberPosY = 4;

int getNumLength(unsigned int number) {
  return (int)(log10((float)number)) + 1;
}

char *getDigits(unsigned int number) {
    unsigned int length = getNumLength(number);
    char * arr = (char *) malloc(length * sizeof(char));
    int i = length - 1;
    do {
        arr[i] = number % 10;
        number /= 10;
        i--;
    } while (number != 0);
    return arr;
}

int *getDigitMatrix(int digit) {
    switch(digit) {
        case 1:
            return one;
        case 2:
            return two;
        case 3:
            return three;
        case 4:
            return four;
        case 5:
            return five;
        case 6:
            return six;
        case 7:
            return seven;
        case 8:
            return eight;
        case 9:
            return nine;
        default:
            return zero;
    }
}

void insertNumberIntoMatrix(int *matrix, int num) {
  char *digits = getDigits(num);
  int digitsSize = getNumLength(num);

  for (int i = 0; i < NUMPIXELS; i++) {
      for (int j = 0; j < digitsSize; j++) {
          int *numMatrix = getDigitMatrix(digits[j]);

          for (int k = 0; k < NUM_SIZE; k++) {
              int columnOffset = (digitsSize == 1) ? 1 : j;
              int numRow = (int)(k / NUM_COLS);
              int numColumn = k % NUM_COLS;

              int newRow = numRow + numberPosX;
              int newColumn = numColumn + (columnOffset * numberPosY);

              int newIndex = (newRow * MATRIX_COLS) + newColumn;

              if (matrix[newIndex] != 1) {
                  matrix[newIndex] = numMatrix[k];
              }
          }
      }
  }

  if (DEBUG_MODE == 1) {
    Serial.println("");

    for (int m = 0; m < MATRIX_ROWS; m++) {
      for (int n = 0; n < MATRIX_COLS; n++) {
        Serial.print(matrix[m * MATRIX_COLS + n]);
      }

      Serial.println("");
   }
  }

  free(digits);
}

#endif

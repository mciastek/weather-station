#ifndef DIGITS_HELPERS_H_
#define DIGITS_HELPERS_H_

#include "globals.h"
#include "numbers.h"

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
  int digits_size = getNumLength(num);

  int posX = 2;
  int posY = 4;

  for (int i = 0; i < NUMPIXELS; i++) {
      for (int j = 0; j < digits_size; j++) {
          int *num_matrix = getDigitMatrix(digits[j]);

          for (int k = 0; k < NUM_SIZE; k++) {
              int num_row = (int)(k / NUM_COLS);
              int num_column = k % NUM_COLS;

              int new_row = num_row + posX;
              int new_column = num_column + (j * posY);

              int new_index = (new_row * MATRIX_COLS) + new_column;

              if (matrix[new_index] != 1) {
                  matrix[new_index] = num_matrix[k];
              }
          }
      }
  }

  free(digits);
}

#endif

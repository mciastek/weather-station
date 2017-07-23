#include<stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_ROWS 5
#define NUM_COLS 3

#define NUM_SIZE NUM_ROWS * NUM_COLS

int main() {
char * convertNumberIntoArray(unsigned int number) {
    unsigned int length = (int)(log10((float)number)) + 1;
    char * arr = (char *) malloc(length * sizeof(char));
    int i = length - 1;
    do {
        arr[i] = number % 10;
        number /= 10;
        i--;
    } while (number != 0);
    return arr;
}

int * toArray(int number)
{
    int n = log10(number) + 1;
    int i;
    int *numberArray = calloc(n, sizeof(int));
    for ( i = n - 1; i >= 0; i--, number /= 10 )
    {
        numberArray[i] = number % 10;
    }
    return numberArray;
}

int one[NUM_SIZE] = {
  0,0,1,
  0,0,1,
  0,0,1,
  0,0,1,
  0,0,1
};

int two[NUM_SIZE] = {
  1,1,1,
  0,0,1,
  1,1,1,
  1,0,0,
  1,1,1
};

int digit_matrix[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

int *getDigitMatrix(int digit) {
    switch(digit) {
        case 1:
            return one;
        case 2:
            return two;
        default:
            return one;
    }
}

char *digits = convertNumberIntoArray(12);
int digits_size = sizeof(digits) / sizeof(int);

int posX = 2;
int posY = 4;

for (int i = 0; i < 64; i++) {
    // if (i == 15) {
    //     digit_matrix[i] = 1;
    // }
    // if (i > 15) {
        for (int j = 0; j < digits_size; j++) {
            int *num_matrix = getDigitMatrix(digits[j]);

            for (int k = 0; k < NUM_SIZE; k++) {
                int num_row = (int)(k / NUM_COLS);
                int num_column = k % NUM_COLS;

                int new_row = num_row + posX;
                // int new_column = num_column + (NUM_COLS * (j + posY));
                int new_column = num_column + (j * posY);

                // printf("%i", new_column);

                int new_index = (new_row * 8) + new_column;

                if (digit_matrix[new_index] != 1) {
                    digit_matrix[new_index] = num_matrix[k];
                }
                // digit_matrix[new_index] = num_matrix[k];
            }
        }
    // }
}

for (int m = 0; m < 8; m++) {
    for (int n = 0; n < 8; n++) {
        printf("%i", digit_matrix[m * 8 + n]);
    }
    printf("\n");
}

// for (int i = 0; i < digits_size; i++) {
//     printf("%i", digits[i]);
// }
}

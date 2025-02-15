/**
 * @file test350.c
 * @author M. Z.
 * @brief Converting a number in other bases to decimal
 * @version 0.1
 * @date 2025-02-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BASE_2 2
#define BASE_8 8
#define BASE_16 16

int convertToDecimal(char *numToConvert, uint8_t baseFrom, int sizeOfNum);

int main(void) {
  char numberToConvert[] = "111100";

  /*Please pay attection to the difference of sizeof and strlen in next 3
   * illustration of thefunction*/

  printf("%s in the base %d equals %d in base 10\n", numberToConvert, BASE_2,
         convertToDecimal(numberToConvert, BASE_2, sizeof(numberToConvert)));

  numberToConvert[0] = '7';
  numberToConvert[1] = '4';
  numberToConvert[2] = '\0';

  printf(
      "%s in the base %d equals %d in base 10\n", numberToConvert, BASE_8,
      convertToDecimal(numberToConvert, BASE_8, strlen(numberToConvert) + 1));

  strcpy(numberToConvert, "3C");

  printf(
      "%s in the base %d equals %d in base 10\n", numberToConvert, BASE_16,
      convertToDecimal(numberToConvert, BASE_16, strlen(numberToConvert) + 1));

  return 0;
}

int convertToDecimal(char *numToConvert, uint8_t baseFrom, int sizeOfNum) {
  int result = 0;
  int toThePowerOf = 0;

  /*Index starts from 0, and we want to avoid NULL character*/

  for (int i = (sizeOfNum - 2); i >= 0; --i) {
    if (isalpha(numToConvert[i])) {
      int charCode = ((int)tolower(numToConvert[i])) - 'a' + 10;
      result += charCode * pow(baseFrom, toThePowerOf);
    } else {
      result += (numToConvert[i] - '0') * pow(baseFrom, toThePowerOf);
    }
    toThePowerOf++;
  }

  return result;
}

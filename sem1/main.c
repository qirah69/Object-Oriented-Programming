#include <stdio.h>
#include <string.h>

short read_morse_codes(char fileName[], char result[][7]) {
  memset(result, 0, 128 * 7 * sizeof(char));
  FILE *fp = fopen(fileName, "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    return 1;
  }
  char line[9];
  while (!feof(fp)) {
    fgets(line, 9, fp);
    strcpy(result[line[0]], line + 2);
  }
  return 0;
}

int main() {
  char MorseLUT[128][7];
  if (read_morse_codes("morse.txt", MorseLUT)) {
    printf("Error reading Morse codes\n");
  } else {
    for (short i = 0; i < 128; i++) {
      if (strlen(MorseLUT[i]) > 0) {
        printf("%c: %s\n", i, MorseLUT[i]);
      }
    }
  }
  return 0;
}


#include "main.c"
#include <stdio.h>
void find_all(const char *str, char character, int *positions, unsigned int cap,
              unsigned int *l) {
  // the problem must include the my_strchr function that you implemented in the
  // previous problem. You can use it to find the first occurrence of character
  // in str, and then continue searching for the next occurrences until you
  // reach the end of the string or until you have found cap occurrences.

  // str - a C string in which we will search the character;

  // character - the character to be searched;

  // positions - [in/out] param. Array containing all the positions on which the
  // character character occurs in the string str. First fill this array with
  // -1!

  // cap - the capacity of the positions array (the maximum number of elements
  // that you can add in the array). If there are more occurrences of character
  // in str you can and should only store the positions for the first cap ones.

  // l - [in/out] parameter. The length of the positions array (the number of
  // elements currently in the array - i.e. the number of times character occurs
  // in str ).
  while (*str != '\0' && *l < cap) {
    const char *pos = my_strchr(str, character);
    if (pos == NULL) {
      break; // No more occurrences found
    }
    positions[*l] = pos - str; // Store the position
    (*l)++;                    // Increment the length
    str = pos + 1;             // Move past the current occurrence
  }
}

int main1() {
  char str[] = "hello world, hello!";
  char target = 'o';
  int positions[10]; // Assuming we want to find up to 10 occurrences
  unsigned int length = 0;
  int cap = 10;
  find_all(str, target, positions, cap, &length);
  printf("Character '%c' found at positions: ", target);
  return 0;
}

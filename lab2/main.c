#include <stdio.h>
const char *my_strchr(const char *str, char character) {
  while (*str != '\0') {     // loop until we reach the end of the string
    if (*str == character) { // check if the current character matches the
                             // target character
      return str; // if it does, return a pointer to this position in the string
    }
    str++; // move to the next character
  }
  return NULL; // if we reach the end of the string without finding the
               // character, return NULL
}

int main() {
  char test_string[] = "Hello, World!";
  char target_char = 'o';
  printf("The first occurrence of '%c' in \"%s\" is at position: %ld\n",
         target_char, test_string,
         my_strchr(test_string, target_char) - test_string);
}

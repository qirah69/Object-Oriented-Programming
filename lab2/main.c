/**
 * @file main.c
 * @brief Custom implementation of strchr.
 */

#include <stdio.h>
#include <stdlib.h>
/**
 *@brief recreation of strchr function, which searches for the first
 * occurrence of a character in a string
 *
 *@param str the string to search through
 *@param character the character to search for
 *
 *@return a pointer to the first occurrence of the character in the string, or
 * NULL if the character is not found
 */

const char *my_strchr(const char *str, char character) {
  while (*str != '\0') {
    if (*str == character) {
      return str + 1;
    }
    str++;
  }
  return NULL;
}

/**
 *@breif main function to test the my_strchr function
 *
 *@param none
 *
 *@return 0 on successful execution
 */

int main() {
  int buffer_size = 100;
  char *string = malloc(buffer_size * sizeof(char));

  if (string == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
  }

  char character;
  printf("Enter a string: ");
  fgets(string, 100, stdin);
  printf("Enter a character to search for: ");
  scanf("%c", &character);
  const char *result = my_strchr(string, character);
  if (result != NULL) {
    printf("Character '%c' found at position: %ld\n", character, result);
  } else {
    printf("Character '%c' not found in the string.\n", character);
  }
  free(string);
  return 0;
}

#include <stdio.h>
int main() {
  char name[100];
  int year;
  printf("Enter your name: \n");
  fgets(name, 100, stdin);
  printf("Enter the year you were born in: ");
  scanf("%d", &year);
  printf("Hello, %s\n", name);
  int age = 2026 - year;
  printf("Your age is: %d\n", age);
}

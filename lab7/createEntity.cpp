#include "entity.h"
#include "lifeForms.h"
#include <string>

entity *createEntity(const std::string &s) {
  if (s == "E")
    return new empty(0, 0);
  if (s == "P")
    return new plant(0, 0);
  if (s[0] == 'F') {
    int age = std::stoi(s.substr(1));
    return new fox(0, 0, age);
  }
  if (s[0] == 'G') {
    int age = std::stoi(s.substr(1));
    return new gopher(0, 0, age);
  }
  return nullptr;
}

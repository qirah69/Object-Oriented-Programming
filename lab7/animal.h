#pragma once
#include "entity.h"

class animal : public entity {
protected:
  unsigned int age;

public:
  animal(int r, int c, unsigned int a) : entity(r, c), age(a) {}
  virtual ~animal() = default;
  unsigned int getAge() const { return age; }
  void setAge(unsigned int a) { age = a; }
};

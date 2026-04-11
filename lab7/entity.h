#pragma once
#include "entityType.h"
#include <iostream>
#include <string>
class simGrid;

class entity;
entity *createEntity(const std::string &s);

class entity {
protected:
  int row;
  int col;

public:
  entity(int r, int c) : row(r), col(c) {}
  virtual ~entity() = default;
  virtual entityType what() const = 0;
  virtual std::string toString() const = 0;
  virtual entity *next(simGrid &grid) = 0;
  friend std::ostream &operator<<(std::ostream &os, const entity &e) {
    os << e.toString();
    return os;
  }
  friend std::istream &operator>>(std::istream &is, entity *&e) {
    std::string inputStr;
    is >> inputStr;
    e = createEntity(inputStr);
    return is;
  }
};

#pragma once
#include "animal.h"
#include "entity.h"
#include <string>

class empty : public entity {
public:
  empty(int r, int c) : entity(r, c) {}
  entityType what() const override { return entityType::EMPTY; }
  std::string toString() const override { return "E"; }
  entity *next(simGrid &grid) override { return this; }
};

class plant : public entity {
public:
  plant(int r, int c) : entity(r, c) {}
  entityType what() const override { return entityType::PLANT; }
  std::string toString() const override { return "P"; }
  entity *next(simGrid &grid) override { return this; }
};

class fox : public animal {
public:
  fox(int r, int c, unsigned int a) : animal(r, c, a) {}
  entityType what() const override { return entityType::FOX; }
  std::string toString() const override { return "F" + std::to_string(age); }
  entity *next(simGrid &grid) override { return this; }
};

class gopher : public animal {
public:
  gopher(int r, int c, unsigned int a) : animal(r, c, a) {}
  entityType what() const override { return entityType::GOPHER; }
  std::string toString() const override { return "G" + std::to_string(age); }
  entity *next(simGrid &grid) override { return this; }
};

#include "lifeForms.h"
#include <iostream>
#include <vector>
class SimulationGrid {};

int main() {
  std::cout << "--- Testing Simplified Prey-Predator ---" << std::endl;

  std::vector<entity *> grid;

  grid.push_back(new empty(0, 0));
  grid.push_back(new plant(0, 1));
  grid.push_back(new fox(1, 0, 3));    // Fox, age 3
  grid.push_back(new gopher(1, 1, 2)); // Gopher, age 2

  for (entity *e : grid) {
    std::cout << "Entity Type: " << e->toString() << std::endl;
  }

  for (entity *e : grid) {
    delete e;
  }

  return 0;
}

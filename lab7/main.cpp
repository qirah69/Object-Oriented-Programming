#include "lifeForms.h"
#include <iostream>
#include <vector>

class simGrid {
private:
  int rows, cols;
  std::vector<std::vector<entity *>> grid;

public:
  // create grid and fill with empty cells
  simGrid(int r, int c) : rows(r), cols(c) {
    grid.resize(rows, std::vector<entity *>(cols));
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        grid[i][j] = new empty(i, j);
      }
    }
  }

  // delete all pointers to avoid memory leaks
  ~simGrid() {
    for (auto &rowVec : grid) {
      for (entity *e : rowVec)
        delete e;
    }
  }

  // replace a cell with a specific animal/plant
  void setEntity(int r, int c, entity *e) {
    if (r < rows && c < cols) {
      delete grid[r][c];
      grid[r][c] = e;
    }
  }

  // visit each cell and trigger its update logic
  void step() {
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        grid[i][j] = grid[i][j]->next(*this);
      }
    }
  }

  // print the grid as a matrix
  friend std::ostream &operator<<(std::ostream &os, const simGrid &sg) {
    for (int i = 0; i < sg.rows; ++i) {
      for (int j = 0; j < sg.cols; ++j) {
        os << *sg.grid[i][j] << "  ";
      }
      os << "\n";
    }
    return os;
  }
};

int main() {
  std::cout << "--- Prey-Predator Simulation: Simplified Version ---\n"
            << std::endl;

  simGrid sim(3, 3);

  // set up the starting positions
  sim.setEntity(0, 0, new fox(0, 0, 3));
  sim.setEntity(0, 1, new plant(0, 1));
  sim.setEntity(1, 1, new gopher(1, 1, 2));
  sim.setEntity(2, 2, new fox(2, 2, 1));

  std::cout << "Initial Grid:\n" << sim << std::endl;

  // get user input for simulation length
  int n;
  std::cout << "Enter number of cycles to simulate: ";
  if (!(std::cin >> n))
    n = 1;

  // run the update loop N times
  for (int i = 1; i <= n; ++i) {
    sim.step();
  }

  std::cout << "\nFinal Grid after " << n << " cycles:\n" << sim << std::endl;

  return 0;
}

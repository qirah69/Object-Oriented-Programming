#pragma once

#include <fstream>
#include <string>
#include <vector>

class Game {
private:
  std::string name;
  std::vector<std::string> genres;
  std::string execPath;
  unsigned int releaseYear;

public:
  Game() = default;
  Game(const std::string &name, std::vector<std::string> genres,
       const std::string &execPath, unsigned int releaseYear) {
    this->name = name;
    this->genres = genres;
    this->execPath = execPath;
    this->releaseYear = releaseYear;
  }
  std::string getName() const { return name; }
  std::vector<std::string> getGenres() const { return genres; }
  std::string getExecPath() const { return execPath; }
  unsigned int getReleaseYear() const { return releaseYear; }
};

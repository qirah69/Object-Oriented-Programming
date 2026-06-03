#include "../repo/GameRepo.h"
#include <cassert>
#include <iostream>

void testCSVAddGame() {
  CSVRepo repo("test_games.csv");
  repo.addGame(Game("Witcher 3", {"RPG", "Action"}, "/usr/bin/witcher3", 2015));
  assert(repo.getAllGames().size() == 1);
  assert(repo.getAllGames()[0].getName() == "Witcher 3");
  std::cout << "PASS: testCSVAddGame\n";
}

void testCSVRemoveGame() {
  CSVRepo repo("test_games.csv");
  repo.addGame(Game("Witcher 3", {"RPG"}, "/usr/bin/witcher3", 2015));
  repo.removeGame("Witcher 3");
  assert(repo.getAllGames().size() == 0);
  std::cout << "PASS: testCSVRemoveGame\n";
}

void testCSVUpdateGame() {
  CSVRepo repo("test_games.csv");
  repo.addGame(Game("Witcher 3", {"RPG"}, "/usr/bin/witcher3", 2015));
  repo.updateGame("Witcher 3",
                  Game("Witcher 4", {"RPG"}, "/usr/bin/witcher4", 2025));
  assert(repo.getAllGames()[0].getName() == "Witcher 4");
  assert(repo.getAllGames()[0].getReleaseYear() == 2025);
  std::cout << "PASS: testCSVUpdateGame\n";
}

void testCSVGetAllGames() {
  CSVRepo repo("test_games.csv");
  repo.addGame(Game("Game1", {"RPG"}, "/usr/bin/game1", 2020));
  repo.addGame(Game("Game2", {"Action"}, "/usr/bin/game2", 2021));
  repo.addGame(Game("Game3", {"Strategy"}, "/usr/bin/game3", 2022));
  assert(repo.getAllGames().size() == 3);
  std::cout << "PASS: testCSVGetAllGames\n";
}

void testCSVPersistence() {
  {
    CSVRepo repo("test_games.csv");
    repo.addGame(Game("Witcher 3", {"RPG"}, "/usr/bin/witcher3", 2015));
  }
  CSVRepo repo2("test_games.csv");
  assert(repo2.getAllGames().size() == 1);
  assert(repo2.getAllGames()[0].getName() == "Witcher 3");
  std::cout << "PASS: testCSVPersistence\n";
}

void testCSVRemoveNonExistent() {
  CSVRepo repo("test_games.csv");
  repo.addGame(Game("Witcher 3", {"RPG"}, "/usr/bin/witcher3", 2015));
  repo.removeGame("NonExistentGame");
  assert(repo.getAllGames().size() == 1);
  std::cout << "PASS: testCSVRemoveNonExistent\n";
}

void cleanupCSV() { std::remove("test_games.csv"); }

void runRepoTests() {
  std::cout << "=== Repo Tests ===\n";
  cleanupCSV();
  testCSVAddGame();
  cleanupCSV();
  testCSVRemoveGame();
  cleanupCSV();
  testCSVUpdateGame();
  cleanupCSV();
  testCSVGetAllGames();
  cleanupCSV();
  testCSVPersistence();
  cleanupCSV();
  testCSVRemoveNonExistent();
  cleanupCSV();
  std::cout << "=== All Repo Tests Passed ===\n\n";
}

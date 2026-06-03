#include "../controller/Controller.h"
#include "../repo/GameRepo.h"
#include <cassert>
#include <iostream>

void testControllerAddGame() {
  CSVRepo repo("test_controller.csv");
  Controller controller(repo);
  controller.AddGame(Game("Witcher 3", {"RPG"}, "/usr/bin/witcher3", 2015));
  assert(controller.GetAllGames().size() == 1);
  std::cout << "PASS: testControllerAddGame\n";
}

void testControllerRemoveGame() {
  CSVRepo repo("test_controller.csv");
  Controller controller(repo);
  controller.AddGame(Game("Witcher 3", {"RPG"}, "/usr/bin/witcher3", 2015));
  controller.RemoveGame("Witcher 3");
  assert(controller.GetAllGames().size() == 0);
  std::cout << "PASS: testControllerRemoveGame\n";
}

void testControllerUpdateGame() {
  CSVRepo repo("test_controller.csv");
  Controller controller(repo);
  controller.AddGame(Game("Witcher 3", {"RPG"}, "/usr/bin/witcher3", 2015));
  controller.UpdateGame("Witcher 3",
                        Game("Witcher 4", {"RPG"}, "/usr/bin/witcher4", 2025));
  assert(controller.GetAllGames()[0].getName() == "Witcher 4");
  std::cout << "PASS: testControllerUpdateGame\n";
}

void testControllerUndoAdd() {
  CSVRepo repo("test_controller.csv");
  Controller controller(repo);
  controller.AddGame(Game("Witcher 3", {"RPG"}, "/usr/bin/witcher3", 2015));
  assert(controller.GetAllGames().size() == 1);
  controller.Undo();
  assert(controller.GetAllGames().size() == 0);
  std::cout << "PASS: testControllerUndoAdd\n";
}

void testControllerUndoRemove() {
  CSVRepo repo("test_controller.csv");
  Controller controller(repo);
  controller.AddGame(Game("Witcher 3", {"RPG"}, "/usr/bin/witcher3", 2015));
  controller.RemoveGame("Witcher 3");
  controller.Undo();
  assert(controller.GetAllGames().size() == 1);
  assert(controller.GetAllGames()[0].getName() == "Witcher 3");
  std::cout << "PASS: testControllerUndoRemove\n";
}

void testControllerUndoUpdate() {
  CSVRepo repo("test_controller.csv");
  Controller controller(repo);
  controller.AddGame(Game("Witcher 3", {"RPG"}, "/usr/bin/witcher3", 2015));
  controller.UpdateGame("Witcher 3",
                        Game("Witcher 4", {"RPG"}, "/usr/bin/witcher4", 2025));
  controller.Undo();
  assert(controller.GetAllGames()[0].getName() == "Witcher 3");
  std::cout << "PASS: testControllerUndoUpdate\n";
}

void testControllerRedo() {
  CSVRepo repo("test_controller.csv");
  Controller controller(repo);
  controller.AddGame(Game("Witcher 3", {"RPG"}, "/usr/bin/witcher3", 2015));
  controller.Undo();
  assert(controller.GetAllGames().size() == 0);
  controller.Redo();
  assert(controller.GetAllGames().size() == 1);
  std::cout << "PASS: testControllerRedo\n";
}

void testControllerUndoEmptyStack() {
  CSVRepo repo("test_controller.csv");
  Controller controller(repo);
  controller.Undo(); // should not crash
  assert(controller.GetAllGames().size() == 0);
  std::cout << "PASS: testControllerUndoEmptyStack\n";
}

void testControllerFilterByGenre() {
  CSVRepo repo("test_controller.csv");
  Controller controller(repo);
  controller.AddGame(Game("Witcher 3", {"RPG"}, "/usr/bin/witcher3", 2015));
  controller.AddGame(Game("Doom", {"Action", "FPS"}, "/usr/bin/doom", 2016));
  controller.AddGame(Game("Civilization", {"Strategy"}, "/usr/bin/civ", 2016));
  GenreSpecification spec("RPG");
  auto filtered = controller.FilterGames(spec);
  assert(filtered.size() == 1);
  assert(filtered[0].getName() == "Witcher 3");
  std::cout << "PASS: testControllerFilterByGenre\n";
}

void testControllerFilterByYear() {
  CSVRepo repo("test_controller.csv");
  Controller controller(repo);
  controller.AddGame(Game("OldGame", {"RPG"}, "/usr/bin/old", 2010));
  controller.AddGame(Game("NewGame", {"Action"}, "/usr/bin/new", 2020));
  YearSpecification spec(2015, Comparison::GreaterThan);
  auto filtered = controller.FilterGames(spec);
  assert(filtered.size() == 1);
  assert(filtered[0].getName() == "NewGame");
  std::cout << "PASS: testControllerFilterByYear\n";
}

void testControllerFilterAndSpec() {
  CSVRepo repo("test_controller.csv");
  Controller controller(repo);
  controller.AddGame(Game("Witcher 3", {"RPG"}, "/usr/bin/witcher3", 2015));
  controller.AddGame(Game("OldRPG", {"RPG"}, "/usr/bin/oldrpg", 2005));
  controller.AddGame(Game("Doom", {"Action"}, "/usr/bin/doom", 2016));
  GenreSpecification genreSpec("RPG");
  YearSpecification yearSpec(2010, Comparison::GreaterThan);
  AndSpecification andSpec(genreSpec, yearSpec);
  auto filtered = controller.FilterGames(andSpec);
  assert(filtered.size() == 1);
  assert(filtered[0].getName() == "Witcher 3");
  std::cout << "PASS: testControllerFilterAndSpec\n";
}

void testControllerFilterOrSpec() {
  CSVRepo repo("test_controller.csv");
  Controller controller(repo);
  controller.AddGame(Game("Witcher 3", {"RPG"}, "/usr/bin/witcher3", 2015));
  controller.AddGame(Game("Doom", {"Action"}, "/usr/bin/doom", 2016));
  controller.AddGame(Game("Civilization", {"Strategy"}, "/usr/bin/civ", 2010));
  GenreSpecification genreSpec("RPG");
  GenreSpecification genreSpec2("Action");
  OrSpecification orSpec(genreSpec, genreSpec2);
  auto filtered = controller.FilterGames(orSpec);
  assert(filtered.size() == 2);
  std::cout << "PASS: testControllerFilterOrSpec\n";
}

void cleanupController() { std::remove("test_controller.csv"); }

void runControllerTests() {
  std::cout << "=== Controller Tests ===\n";
  cleanupController();
  testControllerAddGame();
  cleanupController();
  testControllerRemoveGame();
  cleanupController();
  testControllerUpdateGame();
  cleanupController();
  testControllerUndoAdd();
  cleanupController();
  testControllerUndoRemove();
  cleanupController();
  testControllerUndoUpdate();
  cleanupController();
  testControllerRedo();
  cleanupController();
  testControllerUndoEmptyStack();
  cleanupController();
  testControllerFilterByGenre();
  cleanupController();
  testControllerFilterByYear();
  cleanupController();
  testControllerFilterAndSpec();
  cleanupController();
  testControllerFilterOrSpec();
  cleanupController();
  std::cout << "=== All Controller Tests Passed ===\n";
}

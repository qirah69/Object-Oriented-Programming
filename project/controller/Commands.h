#pragma once

#include "../repo/GameRepo.h"

class Commands {
public:
  virtual void execute() = 0;
  virtual ~Commands() = default;
  virtual void undo() = 0;
};

class AddGameCommand : public Commands {
private:
  GameRepo &repo;
  Game game;

public:
  AddGameCommand(GameRepo &repo, const Game &game) : repo(repo), game(game) {}
  void execute() override { repo.addGame(game); }
  void undo() override { repo.removeGame(game.getName()); }
};

class RemoveGameCommand : public Commands {
private:
  GameRepo &repo;
  std::string gameName;
  Game removedGame;

public:
  RemoveGameCommand(GameRepo &repo, const std::string &gameName)
      : repo(repo), gameName(gameName) {}
  void execute() override {
    auto games = repo.getAllGames();
    for (const auto &game : games) {
      if (game.getName() == gameName) {
        removedGame = game;
        break;
      }
    }
    repo.removeGame(gameName);
  }
  void undo() override { repo.addGame(removedGame); }
};

class UpdateGameCommand : public Commands {
private:
  GameRepo &repo;
  std::string gameName;
  Game updatedGame;
  Game oldGame;

public:
  UpdateGameCommand(GameRepo &repo, const std::string &gameName,
                    const Game &updatedGame)
      : repo(repo), gameName(gameName), updatedGame(updatedGame) {}
  void execute() override {
    auto games = repo.getAllGames();
    for (const auto &game : games) {
      if (game.getName() == gameName) {
        oldGame = game;
        break;
      }
    }
    repo.updateGame(gameName, updatedGame);
  }
  void undo() override { repo.updateGame(updatedGame.getName(), oldGame); }
};

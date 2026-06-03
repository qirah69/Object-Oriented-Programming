#pragma once

#include "../repo/GameRepo.h"
#include "Commands.h"
#include "Filtering.h"
#include <memory>
#include <stack>

class Controller {
private:
  GameRepo &repo;
  std::stack<std::unique_ptr<Commands>> undoStack;
  std::stack<std::unique_ptr<Commands>> redoStack;

public:
  Controller(GameRepo &repo) : repo(repo) {}

  void AddGame(const Game &game) {
    auto cmd = std::make_unique<AddGameCommand>(repo, game);
    cmd->execute();
    undoStack.push(std::move(cmd));
    redoStack = {};
  }

  void RemoveGame(const std::string &gameName) {
    auto cmd = std::make_unique<RemoveGameCommand>(repo, gameName);
    cmd->execute();
    undoStack.push(std::move(cmd));
    redoStack = {};
  }

  void UpdateGame(const std::string &gameName, const Game &updatedGame) {
    auto cmd = std::make_unique<UpdateGameCommand>(repo, gameName, updatedGame);
    cmd->execute();
    undoStack.push(std::move(cmd));
    redoStack = {};
  }

  void Undo() {
    if (undoStack.empty())
      return;
    auto cmd = std::move(undoStack.top());
    undoStack.pop();
    cmd->undo();
    redoStack.push(std::move(cmd));
  }

  void Redo() {
    if (redoStack.empty())
      return;
    auto cmd = std::move(redoStack.top());
    redoStack.pop();
    cmd->execute();
    undoStack.push(std::move(cmd));
  }

  std::vector<Game> FilterGames(const Specification &spec) const {
    std::vector<Game> result;
    for (const auto &game : repo.getAllGames()) {
      if (spec.isSatisfiedBy(game)) {
        result.push_back(game);
      }
    }
    return result;
  }

  std::vector<Game> GetAllGames() const { return repo.getAllGames(); }
};

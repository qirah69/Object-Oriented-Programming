#pragma once

#include "../domain/Game.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

class GameRepo {
public:
  GameRepo() = default;
  virtual void addGame(const Game &game) = 0;
  virtual void removeGame(const std::string &name) = 0;
  virtual void updateGame(const std::string &name, const Game &updatedGame) = 0;
  virtual std::vector<Game> getAllGames() const = 0;
  virtual ~GameRepo() = default;
};

class CSVRepo : public GameRepo {
private:
  std::vector<Game> games;
  std::string fileName;

  void loadCSV() {
    std::ifstream inFile(fileName);
    while (inFile) {
      std::string name, genresStr, execPath;
      unsigned int releaseYear;
      if (!std::getline(inFile, name, ','))
        break;
      if (!std::getline(inFile, genresStr, ','))
        break;
      if (!std::getline(inFile, execPath, ','))
        break;
      if (!(inFile >> releaseYear))
        break;
      inFile.ignore();

      std::vector<std::string> genres;
      size_t pos = 0;
      while ((pos = genresStr.find('|')) != std::string::npos) {
        genres.push_back(genresStr.substr(0, pos));
        genresStr.erase(0, pos + 1);
      }
      if (!genresStr.empty())
        genres.push_back(genresStr);

      games.emplace_back(name, genres, execPath, releaseYear);
    }
  }

  void saveCSV() const {
    std::ofstream outFile(fileName);
    for (const auto &game : games) {
      outFile << game.getName() << ",";
      const auto &genres = game.getGenres();
      for (size_t i = 0; i < genres.size(); ++i) {
        outFile << genres[i];
        if (i < genres.size() - 1)
          outFile << "|";
      }
      outFile << "," << game.getExecPath() << "," << game.getReleaseYear()
              << "\n";
    }
  }

public:
  CSVRepo(const std::string &fileName = "games.csv") : fileName(fileName) {
    loadCSV();
  }

  void addGame(const Game &game) override {
    games.push_back(game);
    saveCSV();
  }
  void removeGame(const std::string &name) override {
    games.erase(std::remove_if(games.begin(), games.end(),
                               [&name](const Game &game) {
                                 return game.getName() == name;
                               }),
                games.end());
    saveCSV();
  }
  void updateGame(const std::string &name, const Game &updatedGame) override {
    for (auto &game : games) {
      if (game.getName() == name) {
        game = updatedGame;
        break;
      }
    }
    saveCSV();
  }
  std::vector<Game> getAllGames() const override { return games; }
};

class JSONRepo : public GameRepo {
private:
  std::vector<Game> games;
  std::string fileName;

  void loadJSON() {
    QFile inFile(QString::fromStdString(fileName));
    if (!inFile.open(QIODevice::ReadOnly))
      return;
    QJsonDocument doc = QJsonDocument::fromJson(inFile.readAll());
    QJsonArray gamesArray = doc.array();
    for (const auto &gameValue : gamesArray) {
      QJsonObject gameObj = gameValue.toObject();
      std::string name = gameObj["name"].toString().toStdString();
      std::vector<std::string> genres;
      QJsonArray genresArray = gameObj["genres"].toArray();
      for (const auto &genreValue : genresArray) {
        genres.push_back(genreValue.toString().toStdString());
      }
      std::string execPath = gameObj["execPath"].toString().toStdString();
      unsigned int releaseYear = gameObj["releaseYear"].toInt();
      games.emplace_back(name, genres, execPath, releaseYear);
    }
  }

  void saveJSON() const {
    QFile outFile(QString::fromStdString(fileName));
    QJsonArray gamesArray;
    for (const auto &game : games) {
      QJsonObject gameObj;
      gameObj["name"] = QString::fromStdString(game.getName());
      QJsonArray genresArray;
      for (const auto &genre : game.getGenres())
        genresArray.append(QString::fromStdString(genre));
      gameObj["genres"] = genresArray;
      gameObj["execPath"] = QString::fromStdString(game.getExecPath());
      gameObj["releaseYear"] = static_cast<int>(game.getReleaseYear());
      gamesArray.append(gameObj);
    }
    QJsonDocument doc(gamesArray);
    if (!outFile.open(QIODevice::WriteOnly))
      return;
    outFile.write(doc.toJson());
  }

public:
  JSONRepo(const std::string &fileName = "games.json") : fileName(fileName) {
    loadJSON();
  }

  void addGame(const Game &game) override {
    games.push_back(game);
    saveJSON();
  }
  void removeGame(const std::string &name) override {
    games.erase(std::remove_if(games.begin(), games.end(),
                               [&name](const Game &game) {
                                 return game.getName() == name;
                               }),
                games.end());
    saveJSON();
  }
  void updateGame(const std::string &name, const Game &updatedGame) override {
    for (auto &game : games) {
      if (game.getName() == name) {
        game = updatedGame;
        break;
      }
    }
    saveJSON();
  }
  std::vector<Game> getAllGames() const override { return games; }
};

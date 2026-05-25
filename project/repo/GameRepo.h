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

  void loadCSV() {
    std::ifstream inFile("games.csv");
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
      inFile.ignore(); // Ignore the newline after reading releaseYear

      std::vector<std::string> genres;
      size_t pos = 0;
      while ((pos = genresStr.find('|')) != std::string::npos) {
        genres.push_back(genresStr.substr(0, pos));
        genresStr.erase(0, pos + 1);
      }
      if (!genresStr.empty()) {
        genres.push_back(genresStr);
      }

      games.emplace_back(name, genres, execPath, releaseYear);
    }
  };

  void save() const {
    std::ofstream outFile("games.csv");
    for (const auto &game : games) {
      for (const auto &game : games) {
        outFile << game.getName() << ",";
        const auto &genres = game.getGenres();
        for (size_t i = 0; i < genres.size(); ++i) {
          outFile << genres[i];
          if (i < genres.size() - 1) {
            outFile << "|";
          }
        }
        outFile << "," << game.getExecPath() << "," << game.getReleaseYear()
                << "\n";
      }
    }
  };

public:
  CSVRepo() { loadCSV(); }
  void addGame(const Game &game) override { games.push_back(game); }
  void removeGame(const std::string &name) override {
    games.erase(std::remove_if(games.begin(), games.end(),
                               [&name](const Game &game) {
                                 return game.getName() == name;
                               }),
                games.end());
  }
  void updateGame(const std::string &name, const Game &updatedGame) override {
    for (auto &game : games) {
      if (game.getName() == name) {
        game = updatedGame;
        break;
      }
    }
  }
  std::vector<Game> getAllGames() const override { return games; }
};

class JSONRepo : public GameRepo {
private:
  std::vector<Game> games;

  void loadJSON() {
    QFile inFile("games.json");
    inFile.open(QIODevice::ReadOnly);
    QJSONDocument doc = QJSONDocument::fromJson(inFile.readAll());
    QJSONArray gamesArray = doc.array();
    for (const auto &gameValue : gamesArray) {
      QJSONObject gameObj = gameValue.toObject();
      std::string name = gameObj["name"].toString().toStdString();
      std::vector<std::string> genres;
      QJSONArray genresArray = gameObj["genres"].toArray();
      for (const auto &genreValue : genresArray) {
        genres.push_back(genreValue.toString().toStdString());
      }
      std::string execPath = gameObj["execPath"].toString().toStdString();
      unsigned int releaseYear = gameObj["releaseYear"].toInt();
      games.emplace_back(name, genres, execPath, releaseYear);
    }
  }

  void save() const {}
};

#include "song.h"
#include <cctype>
#include <string>
#include <vector>

Song::Song(std::string title, std::string artist, std::string lyrics) {
  this->title = title;
  this->artist = artist;
  std::string currWord = "";
  for (char c : lyrics) {
    if (std::isalpha(c)) {
      currWord += std::tolower(c);
    } else if (!currWord.empty()) {
      lyricsWords.push_back(currWord);
      currWord = "";
    }
  }
  if (!currWord.empty()) {
    lyricsWords.push_back(currWord);
  }
}

std::string Song::getArtist() const { return artist; }
std::string Song::getTitle() const { return title; }
const std::vector<std::string> &Song::getLyricsWords() const {
  return lyricsWords;
}

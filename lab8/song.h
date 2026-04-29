#pragma once
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

class Song {
protected:
  std::string title;
  std::string artist;

private:
  std::vector<std::string> lyricsWords;

public:
  Song(std::string title, std::string artist, std::string lyrics);
  std::string getArtist() const;
  std::string getTitle() const;
  const std::vector<std::string> &getLyricsWords() const;
};

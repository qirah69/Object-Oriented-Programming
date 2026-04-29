#pragma once
#include "song.h"
#include <map>
#include <set>
#include <string>
#include <vector>

class SongCollection {
private:
  std::vector<Song> songs;
  std::map<std::string, std::vector<Song>> wordIndex;

public:
  SongCollection(const std::string &filename);
  std::set<std::string> getUniqueArtists() const;
  std::vector<Song> getSongsByArtist(const std::string &artist) const;
  std::vector<Song> getSongsWithWord(const std::string &word) const;
  std::map<std::string, std::vector<Song>> rankingBySongs() const;
  std::vector<Song> sortByArtist() const;
  std::vector<Song> sortByTitle() const;
  std::vector<Song> sortByLyricsNumber() const;
};

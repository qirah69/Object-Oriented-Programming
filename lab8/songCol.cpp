#include "songCol.h"
#include "song.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

// Helper function to absolutely destroy invisible carriage returns and spaces
static std::string trimStr(const std::string &str) {
  size_t first = str.find_first_not_of(" \r\n\t");
  if (std::string::npos == first)
    return "";
  size_t last = str.find_last_not_of(" \r\n\t");
  return str.substr(first, (last - first + 1));
}

SongCollection::SongCollection(const std::string &filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::invalid_argument("Could not open file: " + filename);
  }

  std::string line;
  std::string currTitle = "", currArtist = "", currLyrics = "";
  bool readingLyrics = false;

  while (std::getline(file, line)) {
    // Clean the line of invisible Windows formatting ghosts
    std::string cleanLine = trimStr(line);

    if (line.find("__Artist:") != std::string::npos) {
      currArtist = trimStr(line.substr(line.find(":") + 1));
      readingLyrics = false;
    } else if (line.find("__Title:") != std::string::npos) {
      currTitle = trimStr(line.substr(line.find(":") + 1));
      readingLyrics = false;
    } else if (line.find("__Lyrics:") != std::string::npos) {
      readingLyrics = true;
    } else if (readingLyrics && !cleanLine.empty()) {
      currLyrics += cleanLine + "\n";
    } else if (readingLyrics && cleanLine.empty()) {
      songs.push_back(Song(currTitle, currArtist, currLyrics));
      // Reset variables so previous songs don't bleed into the next
      currTitle = "";
      currArtist = "";
      currLyrics = "";
      readingLyrics = false;
    }
  }

  if (!currArtist.empty() && !currTitle.empty()) {
    songs.push_back(Song(currTitle, currArtist, currLyrics));
  }

  for (const Song &song : songs) {
    std::vector<std::string> songWords = song.getLyricsWords();
    std::set<std::string> uniqueWords(songWords.begin(), songWords.end());
    for (const std::string &word : uniqueWords) {
      wordIndex[word].push_back(song);
    }
  }
}

std::set<std::string> SongCollection::getUniqueArtists() const {
  std::set<std::string> uniqueArtists;
  for (const Song &song : songs) {
    uniqueArtists.insert(song.getArtist());
  }
  return uniqueArtists;
}

std::vector<Song>
SongCollection::getSongsByArtist(const std::string &artist) const {
  std::vector<Song> songList;
  for (const Song &song : songs) {
    if (song.getArtist() == artist) {
      songList.push_back(song);
    }
  }
  return songList;
}

std::vector<Song>
SongCollection::getSongsWithWord(const std::string &word) const {
  std::string tempWord = "";
  for (char c : word) {
    if (std::isalpha(c)) {
      tempWord += std::tolower(c);
    }
  }

  auto it = wordIndex.find(tempWord);
  if (it != wordIndex.end()) {
    return it->second;
  }
  return {};
}

std::map<std::string, std::vector<Song>>
SongCollection::rankingBySongs() const {
  std::map<std::string, std::vector<Song>> ranking;
  for (const Song &song : songs) {
    ranking[song.getArtist()].push_back(song);
  }
  return ranking;
}

std::vector<Song> SongCollection::sortByArtist() const {
  std::vector<Song> sortedSongs = songs;
  std::sort(sortedSongs.begin(), sortedSongs.end(),
            [](const Song &a, const Song &b) {
              return a.getArtist() < b.getArtist();
            });
  return sortedSongs;
}

std::vector<Song> SongCollection::sortByTitle() const {
  std::vector<Song> sortedSongs = songs;
  std::sort(
      sortedSongs.begin(), sortedSongs.end(),
      [](const Song &a, const Song &b) { return a.getTitle() > b.getTitle(); });
  return sortedSongs;
}

std::vector<Song> SongCollection::sortByLyricsNumber() const {
  std::vector<Song> sortedSongs = songs;
  std::sort(sortedSongs.begin(), sortedSongs.end(),
            [](const Song &a, const Song &b) {
              return a.getLyricsWords().size() < b.getLyricsWords().size();
            });
  return sortedSongs;
}

#include <string>

class Song {
private:
  std::string title;
  std::string artist;
  std::string duration;
  std::string path;

public:
  Song(const std::string &t, const std::string &a, const std::string &d,
       const std::string &p) {
    title = t;
    artist = a;
    duration = d;
    path = p;
  }

  std::string getTitle() const { return title; }

  std::string getArtist() const { return artist; }

  std::string getDuration() const { return duration; }

  std::string getPath() const { return path; }
};

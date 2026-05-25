#include "song.h"
#include <QObject>
#include <QVector>

class SongController : public QObject {
  Q_OBJECT
private:
  QVector<Song> allSongs;
  QVector<Song> playlist;

public:
  SongController(QObject *parent = nullptr) : QObject(parent) {}

  void addSongToAll(const Song &song) { allSongs.append(song); }
  void addSongToPlaylist(const Song &song) { playlist.append(song); }
  void removeSong(const QString &title) {
    for (int i = 0; i < allSongs.size(); ++i) {
      if (allSongs[i].getTitle() == title.toStdString()) {
        allSongs.remove(i);
        break;
      }
    }
    for (int j = 0; j < playlist.size(); ++j) {
      if (playlist[j].getTitle() == title.toStdString()) {
        playlist.remove(j);
        break;
      }
    }
  }

  Song getSongByTitle(const QString &title) {
    for (const Song &song : allSongs) {
      if (song.getTitle() == title.toStdString()) {
        return song;
      }
    }
    for (const Song &song : playlist) {
      if (song.getTitle() == title.toStdString()) {
        return song;
      }
    }
    return Song("", "", "", "");
  }

  QVector<Song> getSongFromAllSongs() { return allSongs; }
  QVector<Song> getSongFromPlaylist() { return playlist; }
};

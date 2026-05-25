#pragma once
#include "songController.h"
#include <QAudioOutput>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMediaPlayer>
#include <QPushButton>
#include <QString>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>

class MainWindow : public QWidget {
  Q_OBJECT
private:
  QHBoxLayout *mainLayout;
  QWidget *leftWidget;
  QVBoxLayout *leftLayout;
  QPushButton *moveSongToPlaylistButton;
  QWidget *rightWidget;
  QVBoxLayout *rightLayout;
  QLabel *tableLabel;
  QTableWidget *songTable;
  QWidget *formWidget;
  QFormLayout *formLayout;
  QLabel *titleLabel;
  QLabel *artistLabel;
  QLabel *durationLabel;
  QLabel *pathLabel;
  QLineEdit *titleEdit;
  QLineEdit *artistEdit;
  QLineEdit *durationEdit;
  QLineEdit *pathEdit;
  QWidget *bottomButtonsWidget;
  QHBoxLayout *bottomButtonsLayout;
  QPushButton *addButton;
  QPushButton *deleteButton;
  QPushButton *updateButton;
  QPushButton *filterButton;
  QListWidget *playlistWidget;
  QLabel *playlistLabel;
  QPushButton *moveSongToAllSongsButton;
  QPushButton *playButton;
  QPushButton *nextButton;
  QMediaPlayer *mediaPlayer;
  QAudioOutput *audioOutput;
  SongController *controller;

public:
  MainWindow(QWidget *parent = nullptr);

private slots:
  void addSong();
  void deleteSong();
  void updateSong();
  void filterSongsByTitle();
  void moveToPlaylist();
  void playSong();
  void nextSong();
};

#include "mainWin.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  mainLayout = new QHBoxLayout();
  setLayout(mainLayout);
  leftWidget = new QWidget();
  leftLayout = new QVBoxLayout();
  moveSongToPlaylistButton = new QPushButton(">");
  rightWidget = new QWidget();
  rightLayout = new QVBoxLayout();
  // Table
  tableLabel = new QLabel("Available Songs:");
  songTable = new QTableWidget(0, 4);
  // Header of the table
  QStringList headers = {"Title", "Artist", "Duration", "Path"};
  songTable->setHorizontalHeaderLabels(headers);

  tableLabel->setBuddy(songTable);

  // Form
  formWidget = new QWidget();
  formLayout = new QFormLayout();

  titleLabel = new QLabel("&Title:");
  artistLabel = new QLabel("&Artist:");
  durationLabel = new QLabel("&Duration:");
  pathLabel = new QLabel("&Path:");

  titleEdit = new QLineEdit();
  artistEdit = new QLineEdit();
  durationEdit = new QLineEdit();
  pathEdit = new QLineEdit();

  titleLabel->setBuddy(titleEdit);
  artistLabel->setBuddy(artistEdit);
  durationLabel->setBuddy(durationEdit);
  pathLabel->setBuddy(pathEdit);

  formLayout->addRow(titleLabel, titleEdit);
  formLayout->addRow(artistLabel, artistEdit);
  formLayout->addRow(durationLabel, durationEdit);
  formLayout->addRow(pathLabel, pathEdit);
  formWidget->setLayout(formLayout);

  // Bottom Buttons
  bottomButtonsWidget = new QWidget();
  bottomButtonsLayout = new QHBoxLayout();

  addButton = new QPushButton("Add");
  deleteButton = new QPushButton("Delete");
  updateButton = new QPushButton("Update");
  filterButton = new QPushButton("Filter");

  bottomButtonsLayout->addWidget(addButton);
  bottomButtonsLayout->addWidget(deleteButton);
  bottomButtonsLayout->addWidget(updateButton);
  bottomButtonsLayout->addWidget(filterButton);

  // LEFT Layout elements
  leftLayout->addWidget(tableLabel);
  leftLayout->addWidget(songTable);
  leftLayout->addWidget(formWidget);
  bottomButtonsWidget->setLayout(bottomButtonsLayout);
  leftLayout->addWidget(bottomButtonsWidget);
  leftWidget->setLayout(leftLayout);

  controller = new SongController(this);
  connect(addButton, &QPushButton::clicked, this, &MainWindow::addSong);
  connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteSong);
  connect(updateButton, &QPushButton::clicked, this, &MainWindow::updateSong);
  connect(filterButton, &QPushButton::clicked, this,
          &MainWindow::filterSongsByTitle);
  /* ======================
   *    RIGHT SIDE OF APP
   * ======================
   */
  playlistLabel = new QLabel("Playlist:");
  playlistWidget = new QListWidget();
  playlistLabel->setBuddy(playlistWidget);
  playButton = new QPushButton("Play");
  nextButton = new QPushButton("Next");
  rightLayout->addWidget(playlistLabel);
  rightLayout->addWidget(playlistWidget);
  rightLayout->addWidget(playButton);
  rightLayout->addWidget(nextButton);
  rightWidget->setLayout(rightLayout);

  mainLayout->addWidget(leftWidget);
  mainLayout->addWidget(moveSongToPlaylistButton);
  mainLayout->addWidget(rightWidget);

  connect(playButton, &QPushButton::clicked, this, &MainWindow::playSong);
  connect(nextButton, &QPushButton::clicked, this, &MainWindow::nextSong);
  connect(moveSongToPlaylistButton, &QPushButton::clicked, this,
          &MainWindow::moveToPlaylist);

  // Media Players
  mediaPlayer = new QMediaPlayer(this);
  audioOutput = new QAudioOutput(this);
  audioOutput->setVolume(50);

  setWindowTitle("Playlist Qt");
  resize(800, 600);
}

void MainWindow::addSong() {
  if (titleEdit->text().isEmpty() || artistEdit->text().isEmpty() ||
      durationEdit->text().isEmpty() || pathEdit->text().isEmpty()) {
    return;
  }
  std::string path = pathEdit->text().toStdString();
  path.append("/" + titleEdit->text().toStdString() + ".mp3");

  Song newSong(titleEdit->text().toStdString(),
               artistEdit->text().toStdString(),
               durationEdit->text().toStdString(), path);
  controller->addSongToAll(newSong);
  int currentRow = songTable->rowCount();
  songTable->insertRow(currentRow);
  songTable->setItem(currentRow, 0, new QTableWidgetItem(titleEdit->text()));
  songTable->setItem(currentRow, 1, new QTableWidgetItem(artistEdit->text()));
  songTable->setItem(currentRow, 2, new QTableWidgetItem(durationEdit->text()));
  songTable->setItem(currentRow, 3,
                     new QTableWidgetItem(QString::fromStdString(path)));
  songTable->resizeColumnsToContents();

  titleEdit->clear();
  artistEdit->clear();
  durationEdit->clear();
  pathEdit->clear();
}

void MainWindow::deleteSong() {
  if (songTable->currentRow() < 0) {
    return;
  }
  controller->removeSong(songTable->item(songTable->currentRow(), 0)->text());
  songTable->removeRow(songTable->currentRow());
}

void MainWindow::updateSong() {
  if (songTable->currentRow() < 0) {
    return;
  }
  controller->removeSong(songTable->item(songTable->currentRow(), 0)->text());
  songTable->removeRow(songTable->currentRow());
  controller->addSongToAll(
      Song(titleEdit->text().toStdString(), artistEdit->text().toStdString(),
           durationEdit->text().toStdString(), pathEdit->text().toStdString()));
  addSong();
}

void MainWindow::filterSongsByTitle() {
  if (titleEdit->text().isEmpty()) {
    return;
  }
  if (controller->getSongByTitle(titleEdit->text()).getTitle().empty()) {
    return;
  }
  for (int i = 0; i < songTable->rowCount(); ++i) {
    if (songTable->item(i, 0)->text().contains(titleEdit->text(),
                                               Qt::CaseInsensitive)) {
      songTable->setRowHidden(i, false);
    } else {
      songTable->setRowHidden(i, true);
    }
  }
}

void MainWindow::moveToPlaylist() {
  if (songTable->currentRow() < 0) {
    return;
  }
  playlistWidget->addItem(songTable->item(songTable->currentRow(), 0)->text());
  songTable->removeRow(songTable->currentRow());
}

void MainWindow::playSong() {
  if (playlistWidget->currentRow() < 0) {
    return;
  }
  mediaPlayer->setAudioOutput(audioOutput);
  QString path = QString::fromStdString(
      controller->getSongByTitle(playlistWidget->currentItem()->text())
          .getPath());
  mediaPlayer->setSource(QUrl::fromLocalFile(path));
  mediaPlayer->play();
}

void MainWindow::nextSong() {
  if (playlistWidget->currentRow() < 0) {
    return;
  }
  if (playlistWidget->currentRow() == playlistWidget->count() - 1) {
    playlistWidget->setCurrentRow(0);
  } else {
    mediaPlayer->stop();
    playlistWidget->setCurrentRow(playlistWidget->currentRow() + 1);
    mediaPlayer->setSource(QUrl::fromLocalFile(QString::fromStdString(
        controller->getSongByTitle(playlistWidget->currentItem()->text())
            .getPath())));
    mediaPlayer->play();
  }
}

#include "mainWin.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QString>
#include <QTableWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  QHBoxLayout *mainLayout = new QHBoxLayout();
  setLayout(mainLayout);
  QWidget *leftWidget = new QWidget();
  QVBoxLayout *leftLayout = new QVBoxLayout();
  QPushButton *moveSongToPlaylistButton = new QPushButton(">");
  QWidget *rightWidget = new QWidget();
  QVBoxLayout *rightLayout = new QVBoxLayout();
  // Table
  QLabel *tableLabel = new QLabel("Available Songs:");
  QTableWidget *songTable = new QTableWidget(0, 3); // 5 rows, 3 columns
  // Header of the table
  QStringList headers = {"Title", "Artist", "Duration"};
  songTable->setHorizontalHeaderLabels(headers);

  tableLabel->setBuddy(songTable);

  // Form
  QWidget *formWidget = new QWidget();
  QFormLayout *formLayout = new QFormLayout();

  QLabel *titleLabel = new QLabel("&Title:");
  QLabel *artistLabel = new QLabel("&Artist:");
  QLabel *durationLabel = new QLabel("&Duration:");
  QLabel *pathLabel = new QLabel("&Path:");

  QLineEdit *titleEdit = new QLineEdit();
  QLineEdit *artistEdit = new QLineEdit();
  QLineEdit *durationEdit = new QLineEdit();
  QLineEdit *pathEdit = new QLineEdit();

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
  QWidget *bottomButtonsWidget = new QWidget();
  QHBoxLayout *bottomButtonsLayout = new QHBoxLayout();

  QPushButton *addButton = new QPushButton("Add");
  QPushButton *deleteButton = new QPushButton("Delete");
  QPushButton *updateButton = new QPushButton("Update");
  QPushButton *filterButton = new QPushButton("Filter");

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

  /* ======================
   *    RIGHT SIDE OF APP
   * ======================
   */

  QLabel *playlistLabel = new QLabel("Playlist:");
  QListWidget *playlistWidget = new QListWidget();
  playlistLabel->setBuddy(playlistWidget);
  QPushButton *playButton = new QPushButton("Play");
  QPushButton *nextButton = new QPushButton("Next");
  rightLayout->addWidget(playlistLabel);
  rightLayout->addWidget(playlistWidget);
  rightLayout->addWidget(playButton);
  rightLayout->addWidget(nextButton);
  rightWidget->setLayout(rightLayout);

  mainLayout->addWidget(leftWidget);
  mainLayout->addWidget(moveSongToPlaylistButton);
  mainLayout->addWidget(rightWidget);
  setWindowTitle("Playlist Qt");
  resize(800, 600);
}

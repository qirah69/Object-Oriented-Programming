#pragma once
#include "../controller/Controller.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

class MainWindow : public QWidget {
  Q_OBJECT
public:
  MainWindow(Controller *controller, QWidget *parent = nullptr);

private:
  // --- Controller ---
  Controller *controller;

  // --- Layouts ---
  QHBoxLayout *mainLayout;
  QVBoxLayout *leftLayout;
  QVBoxLayout *rightLayout;

  // --- Left Panel ---
  QWidget *leftWidget;
  QListWidget *gameList;

  // --- Form ---
  QWidget *formWidget;
  QFormLayout *formLayout;
  QLineEdit *nameEdit;
  QLineEdit *genreEdit;
  QLineEdit *yearEdit;
  QLineEdit *pathEdit;

  // --- Buttons ---
  QWidget *bottomButtonsWidget;
  QHBoxLayout *bottomButtonsLayout;
  QPushButton *addButton;
  QPushButton *deleteButton;
  QPushButton *updateButton;
  QPushButton *filterButton;
  QPushButton *playButton;
  QPushButton *undoButton;
  QPushButton *redoButton;

  // --- Right Panel ---
  QWidget *rightWidget;
  QLabel *nameLabel;
  QLabel *genreLabel;
  QLabel *yearLabel;

  // --- Setup ---
  void setupLeftPanel();
  void setupRightPanel();
  void connectSignals();

private slots:
  void addGame();
  void deleteGame();
  void updateGame();
  void filterGame();
  void playGame();
  void undoAction();
  void redoAction();
  void onGameSelected(const QString &gameName);
};

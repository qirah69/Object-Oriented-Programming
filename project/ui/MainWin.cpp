#include "MainWin.h"
#include <QProcess>
#include <algorithm>

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QWidget(parent) {
  this->controller = controller;
  mainLayout = new QHBoxLayout();
  setLayout(mainLayout);
  setupLeftPanel();
  setupRightPanel();
  connectSignals();
  for (const auto &game : controller->GetAllGames())
    gameList->addItem(QString::fromStdString(game.getName()));
  setWindowTitle("Game Launcher");
  resize(900, 600);
}

void MainWindow::setupLeftPanel() {
  leftWidget = new QWidget();
  leftLayout = new QVBoxLayout();

  // Game list
  QLabel *listLabel = new QLabel("My Games:");
  gameList = new QListWidget();

  // Form
  formWidget = new QWidget();
  formLayout = new QFormLayout();
  nameEdit = new QLineEdit();
  genreEdit = new QLineEdit();
  yearEdit = new QLineEdit();
  pathEdit = new QLineEdit();
  formLayout->addRow("Name:", nameEdit);
  formLayout->addRow("Genres (RPG|Action):", genreEdit);
  formLayout->addRow("Year:", yearEdit);
  formLayout->addRow("Executable Path:", pathEdit);
  formWidget->setLayout(formLayout);

  // Buttons
  bottomButtonsWidget = new QWidget();
  bottomButtonsLayout = new QHBoxLayout();
  addButton = new QPushButton("Add");
  deleteButton = new QPushButton("Delete");
  updateButton = new QPushButton("Update");
  filterButton = new QPushButton("Filter");
  undoButton = new QPushButton("Undo");
  redoButton = new QPushButton("Redo");
  bottomButtonsLayout->addWidget(addButton);
  bottomButtonsLayout->addWidget(deleteButton);
  bottomButtonsLayout->addWidget(updateButton);
  bottomButtonsLayout->addWidget(filterButton);
  bottomButtonsLayout->addWidget(undoButton);
  bottomButtonsLayout->addWidget(redoButton);
  bottomButtonsWidget->setLayout(bottomButtonsLayout);

  leftLayout->addWidget(listLabel);
  leftLayout->addWidget(gameList);
  leftLayout->addWidget(formWidget);
  leftLayout->addWidget(bottomButtonsWidget);
  leftWidget->setLayout(leftLayout);
  mainLayout->addWidget(leftWidget);
}

void MainWindow::setupRightPanel() {
  rightWidget = new QWidget();
  rightLayout = new QVBoxLayout();

  nameLabel = new QLabel("Name: -");
  genreLabel = new QLabel("Genres: -");
  yearLabel = new QLabel("Year: -");
  playButton = new QPushButton("Launch Game");

  rightLayout->addWidget(nameLabel);
  rightLayout->addWidget(genreLabel);
  rightLayout->addWidget(yearLabel);
  rightLayout->addStretch();
  rightLayout->addWidget(playButton);
  rightWidget->setLayout(rightLayout);
  mainLayout->addWidget(rightWidget);
}

void MainWindow::connectSignals() {
  connect(addButton, &QPushButton::clicked, this, &MainWindow::addGame);
  connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteGame);
  connect(updateButton, &QPushButton::clicked, this, &MainWindow::updateGame);
  connect(filterButton, &QPushButton::clicked, this, &MainWindow::filterGame);
  connect(playButton, &QPushButton::clicked, this, &MainWindow::playGame);
  connect(undoButton, &QPushButton::clicked, this, &MainWindow::undoAction);
  connect(redoButton, &QPushButton::clicked, this, &MainWindow::redoAction);
  connect(gameList, &QListWidget::currentTextChanged, this,
          &MainWindow::onGameSelected);
}

void MainWindow::addGame() {
  if (nameEdit->text().isEmpty() || pathEdit->text().isEmpty())
    return;

  std::string name = nameEdit->text().toStdString();
  std::string execPath = pathEdit->text().toStdString();
  unsigned int year = yearEdit->text().toUInt();

  std::vector<std::string> genres;
  std::string genresStr = genreEdit->text().toStdString();
  size_t pos = 0;
  while ((pos = genresStr.find('|')) != std::string::npos) {
    genres.push_back(genresStr.substr(0, pos));
    genresStr.erase(0, pos + 1);
  }
  if (!genresStr.empty())
    genres.push_back(genresStr);

  Game game(name, genres, execPath, year);
  controller->AddGame(game);
  gameList->addItem(nameEdit->text());

  nameEdit->clear();
  genreEdit->clear();
  yearEdit->clear();
  pathEdit->clear();
}

void MainWindow::deleteGame() {
  if (gameList->currentRow() < 0)
    return;
  controller->RemoveGame(gameList->currentItem()->text().toStdString());
  gameList->takeItem(gameList->currentRow());
  gameList->clearSelection();
}

void MainWindow::updateGame() {
  if (gameList->currentRow() < 0 || nameEdit->text().isEmpty())
    return;

  std::string oldName = gameList->currentItem()->text().toStdString();
  std::string newName = nameEdit->text().toStdString();
  std::string execPath = pathEdit->text().toStdString();
  unsigned int year = yearEdit->text().toUInt();

  std::vector<std::string> genres;
  std::string genresStr = genreEdit->text().toStdString();
  size_t pos = 0;
  while ((pos = genresStr.find('|')) != std::string::npos) {
    genres.push_back(genresStr.substr(0, pos));
    genresStr.erase(0, pos + 1);
  }
  if (!genresStr.empty())
    genres.push_back(genresStr);

  Game updatedGame(newName, genres, execPath, year);
  controller->UpdateGame(oldName, updatedGame);
  gameList->currentItem()->setText(nameEdit->text());
  controller->UpdateGame(oldName, updatedGame);
  gameList->currentItem()->setText(nameEdit->text());

  nameEdit->clear();
  genreEdit->clear();
  yearEdit->clear();
  pathEdit->clear();
  gameList->clearSelection();
}

void MainWindow::filterGame() {
  if (genreEdit->text().isEmpty() && yearEdit->text().isEmpty()) {
    // Show all games
    for (int i = 0; i < gameList->count(); ++i)
      gameList->item(i)->setHidden(false);
    return;
  }

  std::vector<Game> filtered;
  if (!genreEdit->text().isEmpty() && !yearEdit->text().isEmpty()) {
    GenreSpecification genreSpec(genreEdit->text().toStdString());
    YearSpecification yearSpec(yearEdit->text().toUInt(),
                               Comparison::GreaterThan);
    AndSpecification andSpec(genreSpec, yearSpec);
    filtered = controller->FilterGames(andSpec);
  } else if (!genreEdit->text().isEmpty()) {
    GenreSpecification spec(genreEdit->text().toStdString());
    filtered = controller->FilterGames(spec);
  } else {
    YearSpecification spec(yearEdit->text().toUInt(), Comparison::GreaterThan);
    filtered = controller->FilterGames(spec);
  }

  for (int i = 0; i < gameList->count(); ++i) {
    QString itemName = gameList->item(i)->text();
    bool found =
        std::any_of(filtered.begin(), filtered.end(), [&](const Game &g) {
          return QString::fromStdString(g.getName()) == itemName;
        });
    gameList->item(i)->setHidden(!found);
  }
}

void MainWindow::playGame() {
  if (gameList->currentRow() < 0)
    return;
  std::string name = gameList->currentItem()->text().toStdString();
  auto games = controller->GetAllGames();
  for (const auto &game : games) {
    if (game.getName() == name) {
      QProcess::startDetached(QString::fromStdString(game.getExecPath()));
      return;
    }
  }
}

void MainWindow::undoAction() {
  controller->Undo();
  gameList->clear();
  for (const auto &game : controller->GetAllGames())
    gameList->addItem(QString::fromStdString(game.getName()));
}

void MainWindow::redoAction() {
  controller->Redo();
  gameList->clear();
  for (const auto &game : controller->GetAllGames())
    gameList->addItem(QString::fromStdString(game.getName()));
}

void MainWindow::onGameSelected(const QString &gameName) {
  auto games = controller->GetAllGames();
  for (const auto &game : games) {
    if (QString::fromStdString(game.getName()) == gameName) {
      nameLabel->setText("Name: " + QString::fromStdString(game.getName()));
      const auto &genres = game.getGenres();
      QString genreStr;
      for (size_t i = 0; i < genres.size(); ++i) {
        genreStr += QString::fromStdString(genres[i]);
        if (i < genres.size() - 1)
          genreStr += "|";
      }
      genreLabel->setText("Genres: " + genreStr);
      yearLabel->setText("Year: " + QString::number(game.getReleaseYear()));

      nameEdit->setText(QString::fromStdString(game.getName()));
      genreEdit->setText(genreStr);
      yearEdit->setText(QString::number(game.getReleaseYear()));
      pathEdit->setText(QString::fromStdString(game.getExecPath()));
      return;
    }
  }
}

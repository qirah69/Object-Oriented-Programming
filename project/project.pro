QT += widgets multimedia core

HEADERS += repo/GameRepo.h \
           domain/Game.h \
           controller/Commands.h \
           controller/Controller.h \
           controller/Filtering.h

build_tests {
    SOURCES += tests/main.cpp
} else {
    HEADERS += ui/MainWin.h
    SOURCES += main.cpp \
               ui/MainWin.cpp
}

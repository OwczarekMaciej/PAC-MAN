QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/blinky.cpp \
    src/boost.cpp \
    src/clyde.cpp \
    src/dot.cpp \
    src/enemy.cpp \
    src/game_view.cpp \
    src/inky.cpp \
    src/mainwindow.cpp \
    src/maze.cpp \
    src/pacman.cpp \
    src/pinky.cpp


HEADERS += \
    src/blinky.h \
    src/boost.h \
    src/clyde.h \
    src/dot.h \
    src/enemy.h \
    src/game_view.h \
    src/entity.h \
    src/inky.h \
    src/item.h \
    src/mainwindow.h \
    src/maze.h \
    src/pacman.h \
    src/pinky.h

FORMS += \
    src/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imgresources.qrc

DISTFILES +=

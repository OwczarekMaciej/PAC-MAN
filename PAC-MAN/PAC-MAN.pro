QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/boost.cpp \
    src/dot.cpp \
    src/game_view.cpp \
    src/mainwindow.cpp \
    src/maze.cpp \
    src/pacman.cpp


HEADERS += \
    src/boost.h \
    src/dot.h \
    src/game_view.h \
    src/item.h \
    src/mainwindow.h \
    src/maze.h \
    src/pacman.h

FORMS += \
    src/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imgresources.qrc

DISTFILES +=

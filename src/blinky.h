#ifndef BLINKY_H
#define BLINKY_H

#include <QTimer>
#include <QObject>
#include <QString>
#include <cmath>
#include <QDebug>
#include "entity.h"
#include "enemy.h"
#include "maze.h"

class Blinky: public Enemy {
    Q_OBJECT
public:
    Blinky(Maze *maze_parent);
    QPoint chase_strategy();
    char ghost_char();

private:
    Maze *maze;
};

#endif // BLINKY_H

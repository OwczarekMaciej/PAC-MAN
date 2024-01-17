#ifndef PINKY_H
#define PINKY_H

#include <QTimer>
#include <QObject>
#include <QString>
#include <QDebug>
#include "entity.h"
#include "enemy.h"
#include "maze.h"

class Pinky: public Enemy {
    Q_OBJECT
public:
    Pinky(Maze *maze_parent);
    QPoint chase_strategy();
    char ghost_char();
    int enemy_base_time();

private:
    Maze *maze;
};


#endif // PINKY_H

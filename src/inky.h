#ifndef INKY_H
#define INKY_H

#include <QTimer>
#include <QObject>
#include <QString>
#include <QDebug>
#include "entity.h"
#include "enemy.h"
#include "maze.h"

class Inky: public Enemy {
    Q_OBJECT
public:
    Inky(Maze *maze_parent);
    QPoint chase_strategy();
    char ghost_char();
    int enemy_base_time();

private:
    Maze *maze;
};



#endif // INKY_H

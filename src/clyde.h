#ifndef CLYDE_H
#define CLYDE_H

#include <QTimer>
#include <QObject>
#include <QString>
#include <QDebug>
#include "entity.h"
#include "enemy.h"
#include "maze.h"

class Clyde: public Enemy {
    Q_OBJECT
public:
    Clyde(Maze *maze_parent);
    QPoint chase_strategy();
    char ghost_char();
    int enemy_base_time();


private:
    Maze *maze;
};



#endif // CLYDE_H

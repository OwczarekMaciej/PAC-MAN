#include "maze.h"
#include <QDebug>

Maze::Maze(QObject *parent)
    : QObject (parent)
{
    createMaze();
}

void Maze::createMaze() {
    map = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {3, 3, 3, 3, 3, 0, 1, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 1, 0, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 0, 1, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 1, 0, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 3, 3, 3, 3, 3},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0, 3, 3, 3, 3, 3, 3, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0, 3, 3, 3, 3, 3, 3, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {3, 3, 3, 3, 3, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 0, 1, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 1, 0, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 3, 3, 3, 3, 3},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 2, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 2, 0},
        {0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
}

QList <QPoint> Maze::dots()
{
    QList <QPoint> list;
    for(int i = 0; i < maze_hight; i++)
    {
        for(int j = 0; j < maze_width; j++)
        {
            if(map[i][j] == 1)
            {
                list.push_back(QPoint(i,j));
            }
        }
    }
    return list;
}

QList <QPoint> Maze::boosts()
{
    QList <QPoint> list;
    for(int i = 0; i < maze_hight; i++)
    {
        for(int j = 0; j < maze_width; j++)
        {
            if(map[i][j] == 2)
            {
                list.push_back(QPoint(i,j));
            }
        }
    }
    return list;
}

bool Maze::can_entity_move(QPointF pos, QPoint direction) {
    int x = int(pos.y() - 15) / 16;
    int y = int(pos.x()) / 16;
    //qDebug() << pos.y() << pos.x();
    //qDebug() << x << y;
    //qDebug() << map[x][y];


    if (x + direction.y() >= 0 && x + direction.y() < maze_hight && y + direction.x() >= 0 && y + direction.x() < maze_width) {
        if (map[x + direction.y()][y + direction.x()] != 0)
            return true;
        else
            return false;
    }
    else if (x == tunnel_level && y + direction.x() < 0)
        return true;
    else if (x == tunnel_level && y + direction.x() > maze_width - 1)
        return true;
    return false;

}

void Maze::check_for_items(QPointF pos, QPoint direction)
{
    int x = int(pos.y() - 15) / 16;
    int y = int(pos.x()) / 16;

    if (map[x][y] != 0 && map[x][y] != 3) {
        if (map[x][y] == 1) {
            emit dot_eaten(QPoint(x, y));
            map[x][y] = 3;
        } else if (map[x][y] == 2) {
            emit boost_ability();
            emit dot_eaten(QPoint(x, y));
            map[x][y] = 3;
        }
    }
    pacman_dir = direction;
}

void Maze::set_location(QPoint pos, char charcter) {
    switch (charcter) {
    case 'a':
        pacman = pos;
        break;
    case 'b':
        blinky = pos;
        break;
    case 'c':
        clyde = pos;
        break;
    }
}

void Maze::set_pacman_pos(QPointF pos) {

    pacman_pos = pos;
}


QPointF Maze::get_pacman_pos() {
    return pacman_pos;
}

void Maze::setPos(QPointF pos) {
    pacman_pos = pos;
}

QPoint Maze::get_pacman_loc(){
    return pacman;
}

QPoint Maze::get_pacman_dir() {
    return pacman_dir;
}

QPoint Maze::get_blinky_loc()
{
    return blinky;
}

QPoint Maze::get_clyde_loc()
{
    return clyde;
}


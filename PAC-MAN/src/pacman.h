#ifndef PACMAN_H
#define PACMAN_H

#include "entity.h"
#include "maze.h"

#include <QPixmap>
#include <QTimer>


class Pacman : public Entity
{
public:
    Pacman(Maze *maze_parent);
    //~Pacman() = default;

     void setDirection(QPoint dir);

public slots:
    void move();
    void switchAnimations();

private:
    void set_char_img();

    QTimer *timer;
    QPoint direction;
    QPoint tmp_direction;
    QPixmap images[3], dead_img[11];
    Maze *maze;

    bool is_dead;
    int img_index = 0;
    int change_img = 1;
};

#endif // PACMAN_H

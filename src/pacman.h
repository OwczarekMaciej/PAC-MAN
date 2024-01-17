#ifndef PACMAN_H
#define PACMAN_H

#include <QPixmap>
#include <QTimer>

#include "maze.h"
#include "entity.h"

class Pacman :  public Entity
{
    Q_OBJECT
public:
    Pacman(Maze *maze_parent);

     void set_direction(QPoint dir);
     void start();
     void die();

     const int pacman_start_pos_y = 23;
     const int pacman_start_pos_x = 13;

public slots:
    void move();
    void switch_animations();
    void dead_animations();

private:
    void set_char_img();
    void pacman_tunnel_swap();

    QTimer *timer, *dead_timer;
    QPoint direction;
    QPoint tmp_direction;
    QPixmap images[3], dead_img[11];
    Maze *maze;

    bool is_dead;
    int img_index = 0;
    int change_img = 1;
    int speed;

    const int left_boundary = -30;
    const int right_boundary = 478;

};


#endif // PACMAN_H

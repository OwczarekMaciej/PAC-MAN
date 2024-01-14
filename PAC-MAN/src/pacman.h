#ifndef PACMAN_H
#define PACMAN_H

#include <QPixmap>
#include <QTimer>

#include "entity.h"
#include "maze.h"

class Pacman :  public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Pacman(Maze *maze_parent);
    ~Pacman() {};

     void set_direction(QPoint dir);
     void start();

public slots:
    void move();
    void switchAnimations();

private:
    void set_char_img();
    void pacman_tunnel_swap();

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

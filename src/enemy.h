#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "maze.h"

#include <QObject>
#include <QTimer>
#include <QDebug>



class Enemy : public Entity
{
    Q_OBJECT
public:
    Enemy(Maze *maze);

    void move();
    void start();
    void die();

    void set_direction(QPoint dir);

    void set_each_images(QString ghost_name);

    virtual QPoint chase_strategy() = 0;
    virtual char ghost_char() = 0;

public slots:
    void switch_animations();


private:
    void set_char_img();

    void where_to_go();
    void choose_chase_direction();

    static qreal calc_distance(QPoint a, QPoint b);

    QTimer *animation_timer, *follow_timer;
    QPoint direction;
    QPoint tmp_direction;
    QPixmap images[4][2], dead_img[4], boost_img[2][2];
    Maze *maze;

    int img_index = 0;
    int change_img = 1;

    const int left_boundary = -30;
    const int right_boundary = 478;

    int image_index_i, image_index_j;
    QPoint target;


};

#endif // ENEMY_H

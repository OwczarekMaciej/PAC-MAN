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

    static qreal calc_distance(QPoint a, QPoint b);

    virtual QPoint chase_strategy() = 0;
    virtual char ghost_char() = 0;
    virtual int enemy_base_time() = 0;

    QTimer *base_mode_timer;
    QTimer* initial_start_timer;

public slots:
    void switch_animations();
    void boost_mode();
    void ghost_boost_beh();
    void shine_img();
    void leave_base();

signals:
    void enemy_dead();
    void game_over();


private:
    void set_char_img();
    void choose_chase_direction();
    void check_if_died();
    void go_back_to_base();


    QTimer *animation_timer, *boost_timer, *ghost_shine;
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
    QPointF base_point_cor = QPoint(12 * 16, 13 * 16 + 15);
    QPoint base_point = QPoint(14, 14);

    int mode;
    int boost_time;
    int speed;
    int tmp_mode;

    QPoint out_of_base_point = QPoint(13 * 16, 11 * 16 + 15);;

    enum Mode { BOOST, CHASE, BASE, DIED };

};

#endif // ENEMY_H

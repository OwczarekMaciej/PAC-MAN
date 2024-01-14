#include "pacman.h"
#include <QDebug>

Pacman::Pacman(Maze *maze_parent)
{
    setOffset(QPoint(-7,-7));
    direction = QPoint(0,0);
    tmp_direction = QPoint(0,0);

    set_char_img();

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(switchAnimations()));
    timer->setInterval(50);

    maze = maze_parent;
    //maze->set_location(QPoint(14, 16), 'a');

    is_dead = false;
}

void Pacman::set_char_img()
{
    for (int i = 0; i < 3; i ++) {
        images[i].load(":res/pacman" + QString::number(i+1) + ".png");
        images[i] = images[i].scaledToHeight(30);
    }
    setPixmap(images[0]);
    setTransformOriginPoint(boundingRect().width() / 2 - 7, boundingRect().height() / 2 - 7);

    for (int i = 0; i < 3; i ++) {
        dead_img[i].load(":res/dead/" + QString::number(i) + ".png");
        dead_img[i] = dead_img[i].scaledToHeight(30);
    }
}

void Pacman::switchAnimations() {
    if (!is_dead) {
        setPixmap(images[img_index]);
        img_index += change_img;
        if (img_index >= 2 || img_index <= 0)
            change_img = -change_img;
    }
    else {
        if (img_index < 11) {
            setPixmap(dead_img[img_index]);
            img_index += change_img;
        }
        else if (img_index >= 11) {
            timer->stop();
            is_dead = false;
            hide();
        }
    }
}

void Pacman::set_direction(QPoint dir)
{
    if (x() == 216. && y() == 383. && direction == QPoint(0, 0) && (dir == Dir::Left || dir == Dir::Right)) {
        direction = dir;
        if (direction == Dir::Left)
            setRotation(180);
        else if (direction == Dir::Right)
            setRotation(0);
    }
    tmp_direction = dir;
}

void Pacman::move()
{
    maze->set_pacman_pos(pos());
    if (y() == 239. && (x() < 0 || x() >= 448))
    {
        pacman_tunnel_swap();
    }
    else if (int(y() - 15) % 16 == 0 && int(x()) % 16 == 0) {
        if (tmp_direction != direction && maze->can_entity_move(pos(), tmp_direction))
        {
            direction = tmp_direction;
            if (direction == QPoint(0, -1))
                setRotation(270);
            else if (direction == QPoint(0, 1))
                setRotation(90);
            else if (direction == QPoint(-1, 0))
                setRotation(180);
            else if (direction == QPoint(1, 0))
                setRotation(0);
        }
        else if (maze->can_entity_move(pos(), direction))
        {
            setPos(pos() + direction * 2);
            timer->start();
        }
        else
        {
            timer->stop();
            setPixmap(images[1]);
        }
    }
    else
        setPos(pos() + direction * 2);
}

void Pacman::start() {
    timer->start();
}

void Pacman::pacman_tunnel_swap()
{
    if (tmp_direction == QPoint(-1, 0) || tmp_direction == QPoint(1, 0))
        direction = tmp_direction;
    if (direction == QPoint(-1, 0))
        setRotation(180);
    else if (direction == QPoint(1, 0))
        setRotation(0);
    setPos(pos() + direction * 2);

    if (x() < -30)
        setX(478);
    else if (x() > 478)
        setX(-30);
}

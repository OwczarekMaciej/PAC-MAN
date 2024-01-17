#include "pacman.h"
#include <QDebug>

Pacman::Pacman(Maze *maze_parent)
{
    setOffset(QPoint(-7,-7));
    direction = QPoint(0,0);
    tmp_direction = QPoint(0,0);

    set_char_img();

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(switch_animations()));
    timer->setInterval(50);

    dead_timer = new QTimer();
    connect(dead_timer, SIGNAL(timeout()), this, SLOT(dead_animations()));
    dead_timer->setInterval(100);

    maze = maze_parent;

    is_dead = false;
    speed = 2;
}

void Pacman::set_char_img()
{
    for (int i = 0; i < 3; i ++) {
        images[i].load(":res/pacman" + QString::number(i+1) + ".png");
        images[i] = images[i].scaledToHeight(30);
    }
    setPixmap(images[0]);
    setTransformOriginPoint(boundingRect().width() / 2 - 7, boundingRect().height() / 2 - 7);

    for (int i = 0; i < 11; i ++) {
        dead_img[i].load(":res/dead/" + QString::number(i) + ".png");
        dead_img[i] = dead_img[i].scaledToHeight(30);
    }
}

void Pacman::switch_animations() {
    if (!is_dead) {
        setPixmap(images[img_index]);
        img_index += change_img;
        if (img_index >= 2 || img_index <= 0)
            change_img = -change_img;
    }
}

void Pacman::dead_animations()
{
    if (img_index < 11) {
        setPixmap(dead_img[img_index]);
        img_index += 1;
    }
    else if (img_index >= 11) {
        //dead_timer->stop();
        hide();
    }
}

void Pacman::set_direction(QPoint dir)
{
    if (x() == pacman_start_pos_x * 16 + 8. && y() == pacman_start_pos_y * 16 + 15. && direction == QPoint(0, 0) && (dir == QPoint(-1, 0) || dir == QPoint(1, 0))) {
        direction = dir;
        if (direction == QPoint(-1, 0))
            setRotation(180);
        else if (direction == QPoint(1, 0))
            setRotation(0);
    }
    tmp_direction = dir;
}

void Pacman::move()
{
    //qDebug() << pos().y() << pos().x();
    maze->set_pacman_pos(pos());

    if (y() == 239. && (x() < 0 || x() >= 448))
    {
        pacman_tunnel_swap();
    }
    else if (int(y() - 15) % 16 == 0 && int(x()) % 16 == 0)
    {
        maze->set_location(QPoint(int(y() - 15) / 16, int(x()) / 16), 'a');
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
            maze->check_for_items(pos(), direction);
            setPos(pos() + direction * speed);
            timer->start();
        }
        else
        {
            maze->check_for_items(pos(), direction);
            timer->stop();
            setPixmap(images[1]);
        }
    }
    else
        setPos(pos() + direction * speed);
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

    if (x() < left_boundary)
        setX(right_boundary);
    else if (x() > right_boundary)
        setX(left_boundary);
}

void Pacman::die()
{
    if(!is_dead)
    {
        qDebug() << "die";
        timer->stop();
        dead_timer->start();
        img_index = 0;
        is_dead = true;
    }
}

#include "pacman.h"

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

    is_dead = false;
}

void Pacman::set_char_img()
{
    for (int i = 0; i < 3; i ++) {
        images[i].load(":res/pacman/" + QString::number(i) + ".png");
        images[i] = images[i].scaledToHeight(30);
    }
    setPixmap(images[0]);
    setTransformOriginPoint(boundingRect().width() / 2 - 7, boundingRect().height() / 2 - 7);

    for (int i = 0; i < 3; i ++) {
        dead_img[i].load(":res/pacman/" + QString::number(i) + ".png");
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


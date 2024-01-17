#include "enemy.h"

Enemy::Enemy(Maze *maze_parent): maze(maze_parent)
{
    setOffset(QPoint(-7,-7));
    direction = QPoint(0,0);
    tmp_direction = QPoint(-1,-1);


    animation_timer = new QTimer();
    connect(animation_timer, SIGNAL(timeout()), this, SLOT(switch_animations()));
    animation_timer->start(10);


    maze = maze_parent;
    set_char_img();

}

void Enemy::set_char_img()
{
    for (int i = 0; i < 2; i ++) {
        for (int j = 0; j < 2; j ++) {
            boost_img[i][j].load(":/res/ghost/boost/boost" + QString::number(i) + QString::number(j + 1) +".png");
            boost_img[i][j] = boost_img[i][j].scaledToHeight(30);
        }
    }

    for (int i = 0; i < 4; i ++) {
        dead_img[i].load(":/res/ghost/dead/" + QString::number(i) + ".png");
        dead_img[i] = dead_img[i].scaledToWidth(30);
    }
}

void Enemy::set_each_images(QString ghost_name)
{
    QString udlr = "udlr";
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 2; j ++) {
            images[i][j].load(":/res/ghost/" + ghost_name + "/" + udlr[i] + QString::number(j + 1) +".png");
            images[i][j] = images[i][j].scaledToHeight(30);
        }
    }

    setPixmap(images[0][0]);
}

void Enemy::switch_animations() {
    if (direction == QPoint(0, -1))
        image_index_i = 0;
    else if (direction == QPoint(0, 1))
        image_index_i = 1;
    else if (direction == QPoint(-1, 0))
        image_index_i = 2;
    else
        image_index_i = 3;


    image_index_j++;
    if (image_index_j >= 2)
        image_index_j = 0;
    setPixmap(images[image_index_i][image_index_j]);
}

void Enemy::start()
{
    animation_timer->start();
}

void Enemy::die()
{

}

void Enemy::move()
{

    //where_to_go();
    if(int(y() - 15) % 16 == 0 && int(x()) % 16 == 0 )
    {
        choose_chase_direction();
        maze->set_location(QPoint(int(y() - 15) / 16, int(x()) / 16), 'b');
        if (tmp_direction != QPoint(-1, -1))
        {
            if (maze->can_entity_move(pos(), tmp_direction)) {
                direction = tmp_direction;
                tmp_direction = QPoint(-1, -1);
            }
        }
        if (maze->can_entity_move(pos(), direction))
        {
            setPos(pos() + direction * 1);
        }

    }
    else {
        setPos(pos() + direction * 1);
    }
}

void Enemy::set_direction(QPoint dir)
{
    tmp_direction = dir;
}

void Enemy::where_to_go()
{
    QPoint choose_dir[2] = {QPoint(-1, 0), QPoint(1, 0)};
    QPoint choice;
    //QPoint target = chase_strategy();
    QPoint target = maze->get_pacman_loc();
    qreal length = std::numeric_limits<int>::max();
    for (int i = 0; i < 2; i ++) {
        if (calc_distance(target, QPoint(int(y() - 15) / 16, int(x()) / 16)) < length) {
            length = calc_distance(target, QPoint(int(y() - 15) / 16 + choose_dir[i].y(), int(x()) / 16 + choose_dir[i].x()));
            choice = choose_dir[i];
        }
        //qDebug() << length << choice;
    }
    direction = choice;
}

qreal Enemy::calc_distance(QPoint a, QPoint b)
{
    return sqrt(pow((b-a).x(), 2) + pow((b-a).y(), 2));
}

void Enemy::choose_chase_direction()
{
    QPoint choice;
    int enemy_pos_y = int(y() - 15) / 16;
    int enemy_pos_x = int(x()) / 16;
    //target = chase_strategy();
    target = maze->get_pacman_loc();
    if(maze->can_entity_move(pos(), direction))
    {
        QPoint choose_dir[4] = {QPoint(-1, 0), QPoint(1, 0), QPoint(0, -1), QPoint(0, 1) };
        qreal length = std::numeric_limits<int>::max();
        for(int i = 0; i < 4; i++)
        {
            if (choose_dir[i] + direction == QPoint(0, 0))
                continue;
            if(maze->can_entity_move(pos() + direction, choose_dir[i]))
            {
                qreal tmp_distance = calc_distance(target, QPoint(enemy_pos_y + direction.y() + choose_dir[i].y(), enemy_pos_x + direction.x() + choose_dir[i].x()));
                if (tmp_distance < length)
                {
                    length = tmp_distance;
                    choice = choose_dir[i];
                }
            }

        }
    }
    if (choice != QPoint(-1, -1)) {
        set_direction(choice);
    }
    qDebug() << target << choice;
}


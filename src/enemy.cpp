#include "enemy.h"

Enemy::Enemy(Maze *maze_parent): maze(maze_parent)
{
    setOffset(QPoint(-7,-7));
    direction = QPoint(0,0);
    tmp_direction = QPoint(-1,-1);
    mode = Mode::BASE;

    connect(maze, SIGNAL(boost_ability()), this, SLOT(boost_mode()));

    animation_timer = new QTimer();
    connect(animation_timer, SIGNAL(timeout()), this, SLOT(switch_animations()));
    animation_timer->start(10);

    boost_timer = new QTimer();
    connect(boost_timer, SIGNAL(timeout()), this, SLOT(ghost_boost_beh()));

    ghost_shine = new QTimer();
    connect(ghost_shine, SIGNAL(timeout()), this, SLOT(shine_img()));

    base_mode_timer = new QTimer();
    connect(base_mode_timer, SIGNAL(timeout()), this, SLOT(leave_base()));

    initial_start_timer = new QTimer();
    connect(initial_start_timer, SIGNAL(timeout()), this, SLOT(leave_base()));


    maze = maze_parent;
    set_char_img();

    image_index_i = 1;
    image_index_j = 0;
    speed = 1;
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
    if(mode != Mode::BOOST)
    {
        if (direction == QPoint(0, -1))
            image_index_i = 0;
        else if (direction == QPoint(0, 1))
            image_index_i = 1;
        else if (direction == QPoint(-1, 0))
            image_index_i = 2;
        else
            image_index_i = 3;

        if (mode == Mode::DIED)
            setPixmap(dead_img[image_index_i]);
        else
            setPixmap(images[image_index_i][image_index_j]);
    }
    else
        setPixmap(boost_img[image_index_i][image_index_j]);

    image_index_j++;
    if (image_index_j >= 2)
        image_index_j = 0;

}

void Enemy::start()
{
    initial_start_timer->start(enemy_base_time());
}

void Enemy::move()
{
    check_if_died();
    go_back_to_base();
    if (x() < 0 || x() >= right_boundary - 30)
    {
        //qDebug() << "out of boundaries";
        setPos(pos() + direction * 1);
        if (x() < left_boundary){
            setX(right_boundary);
        }
        else if (x() > right_boundary) {
            setX(left_boundary);
        }
    }
    else if(int(y() - 15) % 16 == 0 && int(x()) % 16 == 0 )
    {
        choose_chase_direction();
        maze->set_location(QPoint(int(y() - 15) / 16, int(x()) / 16), ghost_char());
        if (tmp_direction != QPoint(-1, -1))
        {
            if (maze->can_entity_move(pos(), tmp_direction)) {
                direction = tmp_direction;
                tmp_direction = QPoint(-1, -1);
            }
        }
        if (maze->can_entity_move(pos(), direction))
        {
            setPos(pos() + direction * speed);
        }
    }
    else {
        setPos(pos() + direction * speed);
    }
}

void Enemy::set_direction(QPoint dir)
{
    tmp_direction = dir;
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

    if(mode == Mode::CHASE)
        target = chase_strategy();
    else if(mode == Mode::BOOST)
        target = maze->get_pacman_loc();
    else if(mode == Mode::DIED)
        target = base_point;
    else if(mode == Mode::BASE)
        target = chase_strategy();


    if(maze->can_entity_move(pos(), direction))
    {
        QPoint choose_dir[4] = {QPoint(-1, 0), QPoint(1, 0), QPoint(0, -1), QPoint(0, 1) };
        qreal length = std::numeric_limits<int>::max();
        qreal min_length = 0;
        for(int i = 0; i < 4; i++)
        {
            if (choose_dir[i] + direction == QPoint(0, 0))
                continue;
            if(maze->can_entity_move(pos() + direction, choose_dir[i]))
            {
                qreal tmp_distance = calc_distance(target, QPoint(enemy_pos_y + direction.y() + choose_dir[i].y(), enemy_pos_x + direction.x() + choose_dir[i].x()));
                if(mode == Mode::BOOST)
                {
                    if(tmp_distance > min_length)
                    {
                        min_length = tmp_distance;
                        choice = choose_dir[i];
                    }
                }
                else if (tmp_distance < length)
                {
                    length = tmp_distance;
                    choice = choose_dir[i];
                }
            }
        }
    }
    set_direction(choice);
    //qDebug() << target << choice;
}

void Enemy::boost_mode()
{
    if(mode == Mode::BASE)
        return;
    else if( mode == Mode::DIED)
        return;
    tmp_mode = mode;
    mode = Mode::BOOST;
    image_index_i = 1;
    boost_time = 10;
    boost_timer->start(1000);
}

void Enemy::ghost_boost_beh()
{
    boost_time--;
    if(boost_time < 4 && boost_time > 0)
    {
        ghost_shine->start(100);
    }
    else if(boost_time <= 0)
    {
        //mode = Mode::CHASE;
        mode = tmp_mode;
        boost_timer->stop();
        ghost_shine->stop();
    }
}

void Enemy::shine_img()
{
    image_index_i ++;
    image_index_i %= 2;
    setPixmap(boost_img[image_index_i][image_index_i]);
}

void Enemy::check_if_died()
{
    if(mode != Mode::DIED)
    {
        QPointF origin = pos() + QPointF(boundingRect().width() / 2 - 7, boundingRect().height() / 2 - 7);
        QPointF player = maze->get_pacman_pos() - QPointF(7, 7) + QPointF(15, 15);

        if (int(origin.y()) / 16 == int(player.y()) / 16 && int(origin.x()) / 16 == int(player.x()) / 16) {
            if (mode == Mode::BOOST)
                die();
            else {
                emit game_over();
                qDebug() << "Game over";
            }
        }
    }
}

void Enemy::die()
{
    emit enemy_dead();
    speed = 2;
    mode = Mode::DIED;
    boost_timer->stop();
    boost_time = 0;
    ghost_shine->stop();
    setPos(int(x()) / 16 * 16, int(y() - 15) / 16 * 16 + 15);
}

void Enemy::go_back_to_base()
{
    if(mode == Mode::DIED && pos() == QPointF(14*15, 191))
    {
        direction = QPoint(0,1);
    }
    else if(mode == Mode::DIED && pos() == QPointF(14*15, 239))
    {
        mode = Mode::BASE;
        speed = 1;
        setPos(int(x()) / 16 * 16, int(y() - 15) / 16 * 16 + 15);
        target = chase_strategy();
        qDebug() << "base mode";
        base_mode_timer->start(3000);
    }
}

void Enemy::leave_base()
{
    setPos(out_of_base_point);
    qDebug() << "leaving base";
    base_mode_timer->stop();
    initial_start_timer->stop();
    mode = Mode::CHASE;
}


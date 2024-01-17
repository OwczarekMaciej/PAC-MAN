#include "game_view.h"
#include "dot.h"
#include "boost.h"

#include <QPixmap>
#include <QDebug>


Game_view::Game_view()
{
    setWindowTitle("PAC_MAN");
    setFixedSize(window_witdh+5, window_height);
    set_scene();

}

void Game_view::set_scene()
{
    my_scene = new QGraphicsScene(this);
    my_scene->setSceneRect(0,0, window_witdh, window_height - 50);
    my_scene->setBackgroundBrush(QPixmap(":/res/maze.png").scaledToWidth(window_witdh));

    setScene(my_scene);
    set_text();
    maze = new Maze(this);
    connect(maze, SIGNAL(dot_eaten(QPoint)), this, SLOT(collected_item(QPoint)));

    place_dots();
    place_pacman();
}

void Game_view::set_text()
{
    game_title = new QGraphicsTextItem();
    game_title->setPlainText("PACMAN");
    game_title->setDefaultTextColor(Qt::yellow);
    game_title->setFont(QFont(font_family, title_font_size));
    game_title->setPos(150,window_height - 70);
    my_scene->addItem(game_title);

    score_label = new QGraphicsTextItem();
    score_label->setPlainText("SCORE");
    score_label->setDefaultTextColor(Qt::white);
    score_label->setFont(QFont(font_family, score_font_size));
    score_label->setPos(0, -25);
    my_scene->addItem(score_label);

    score = new QGraphicsTextItem();
    score->setPlainText("0");
    score->setDefaultTextColor(Qt::yellow);
    score->setFont(QFont(font_family, score_font_size));
    score->setPos(115, -25);
    my_scene->addItem(score);

    winner_text1 = new QGraphicsTextItem();
    winner_text1->setPlainText("CONGRATULATIONS!");
    winner_text1->setDefaultTextColor(Qt::red);
    winner_text1->setFont(QFont(font_family, winner_font_size));
    winner_text1->setPos(window_witdh/2 - winner_text1->boundingRect().width()/2,
                        window_height/2 - winner_text1->boundingRect().height()/2 - 50);
    winner_text2 = new QGraphicsTextItem();
    winner_text2->setPlainText("YOU WON!");
    winner_text2->setDefaultTextColor(Qt::red);
    winner_text2->setFont(QFont(font_family, winner_font_size));
    winner_text2->setPos(window_witdh/2 - winner_text2->boundingRect().width()/2,
                        window_height/2 - winner_text2->boundingRect().height()/2);


    my_scene->addItem(winner_text1);
    my_scene->addItem(winner_text2);
    winner_text1->hide();
    winner_text2->hide();

}

void Game_view::place_dots()
{

    QList <QPoint> list = maze->dots();
    foreach(QPoint pos, list) {
        item[pos.x()][pos.y()] = new Dot(this);
        item[pos.x()][pos.y()]->setPos(16 * pos.y(), 15 + 16 * pos.x());
        my_scene->addItem(item[pos.x()][pos.y()]);
        connect(item[pos.x()][pos.y()], SIGNAL(dot_eaten()), this, SLOT(dot_collected()));
    }

    list = maze->boosts();
    foreach(QPoint pos, list) {
        item[pos.x()][pos.y()] = new Boost(this);
        item[pos.x()][pos.y()]->setPos(-6 + 16 * pos.y(), 8 + 16 * pos.x());
        my_scene->addItem(item[pos.x()][pos.y()]);
        connect(item[pos.x()][pos.y()], SIGNAL(boost_eaten()), this, SLOT(dot_collected()));

    }
}

void Game_view::place_pacman()
{
    pacman = new Pacman(maze);

    pacmanTimer = new QTimer(this);
    connect(pacmanTimer, SIGNAL(timeout()), pacman, SLOT(move()));
    pacmanTimer->start(10);
    pacman->start();

    pacman->setPos(pacman->pacman_start_pos_x * 16 + 8, pacman->pacman_start_pos_y * 16 + 15);
    qDebug() << window_witdh / 2 - pacman->boundingRect().width() / 2 << pacman->pos().x() << pacman->pos().y();

    my_scene->addItem(pacman);

    blinky = new Blinky(maze);
    ghostMove = new QTimer(this);
    connect(ghostMove, SIGNAL(timeout()), blinky, SLOT(move()));
    ghostMove->start(11);
    blinky->setPos(16 ,16+ 15);
    my_scene->addItem(blinky);

}

void Game_view::keyPressEvent(QKeyEvent *event) {

    if ((event->key() == Qt::Key_Up) || (event->key() == Qt::Key_W))
        pacman->set_direction(QPoint(0, -1));
    else if ((event->key() == Qt::Key_Down)|| (event->key() == Qt::Key_S))
        pacman->set_direction(QPoint(0, 1));
    else if ((event->key() == Qt::Key_Left) || (event->key() == Qt::Key_A))
        pacman->set_direction(QPoint(-1, 0));
    else if ((event->key() == Qt::Key_Right) || (event->key() == Qt::Key_D))
        pacman->set_direction(QPoint(1, 0));
}

void Game_view::collected_item(QPoint pos) {
    item[pos.x()][pos.y()]->eaten();
}

void Game_view::dot_collected()
{
    current_score += 10;
    score->setPlainText(QString::number(current_score));
    dots_left--;
    check_for_win();
}

void Game_view::check_for_win()
{
    if(dots_left == 0)
    {
        qDebug() << "WIN";
        winner_text1->show();
        winner_text2->show();
        pacmanTimer->stop();
    }
}

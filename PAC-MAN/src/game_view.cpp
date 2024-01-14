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
    connect(maze, SIGNAL(eat(QPoint)), this, SLOT(itemEat(QPoint)));

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

}

void Game_view::place_dots()
{

    QList <QPoint> list = maze->dots();
    foreach(QPoint pos, list) {
        item[pos.x()][pos.y()] = new Dot(this);
        item[pos.x()][pos.y()]->setPos(16 * pos.y(), 15 + 16 * pos.x());
        my_scene->addItem(item[pos.x()][pos.y()]);
        //connect(item[pos.x()][pos.y()], SIGNAL(dot_eaten()), this, SLOT(dotsAte()));
    }

    list = maze->boosts();
    foreach(QPoint pos, list) {
        item[pos.x()][pos.y()] = new Boost(this);
        item[pos.x()][pos.y()]->setPos(-6 + 16 * pos.y(), 8 + 16 * pos.x());
        my_scene->addItem(item[pos.x()][pos.y()]);
        //connect(item[pos.x()][pos.y()], SIGNAL(dot_eaten()), this, SLOT(dotsAte()));
        }
}

void Game_view::place_pacman()
{
    pacman = new Pacman(maze);

    pacmanTimer = new QTimer(this);
    connect(pacmanTimer, SIGNAL(timeout()), pacman, SLOT(move()));
    pacmanTimer->start(20);
    pacman->start();

    pacman->setPos(window_witdh / 2 - pacman->boundingRect().width() / 2 + 7 , 383);
    //qDebug() << window_witdh / 2 - pacman->boundingRect().width() / 2 << pacman->pos().x() << pacman->pos().y();

    my_scene->addItem(pacman);
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

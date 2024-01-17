#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

#include "maze.h"
#include "item.h"
#include "entity.h"
#include "pacman.h"
#include "blinky.h"


class Game_view : public QGraphicsView
{
    Q_OBJECT

public:
    Game_view();
    void keyPressEvent(QKeyEvent *event);

private:
    const int window_witdh = 448;
    const int window_height = 580;



    int title_font_size = 16;
    int score_font_size = 16;
    int winner_font_size = 20;
    const QString font_family = "Emulogic";

    int current_score = 0;
    int dots_left = 252;

    void set_scene();
    void set_text();

    void place_dots();
    void place_pacman();
    void check_for_win();

    QGraphicsScene *my_scene;
    QGraphicsTextItem *game_title;
    QGraphicsTextItem *score_label;
    QGraphicsTextItem *score;
    QGraphicsTextItem *winner_text1;
    QGraphicsTextItem *winner_text2;

    Item *item[31][28];
    Maze *maze;

    Pacman *pacman;
    Blinky *blinky;
    QTimer *pacmanTimer, *ghostMove;

public slots:
    void collected_item(QPoint pos);
    void dot_collected();

};


#endif // GAME_VIEW_H

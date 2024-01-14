#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>

#include "maze.h"
#include "item.h"


class Game_view : public QGraphicsView
{
    Q_OBJECT

public:
    Game_view();

private:
    const int window_witdh = 448;
    const int window_height = 580;

    int title_font_size = 16;
    int score_font_size = 16;
    const QString font_family = "Emulogic";

    void set_scene();
    void set_text();

    void place_dots();

    QGraphicsScene *my_scene;
    QGraphicsTextItem *game_title;
    QGraphicsTextItem *score_label;
    QGraphicsTextItem *score;

    Item *item[31][28];
    Maze *maze;

};


#endif // GAME_VIEW_H

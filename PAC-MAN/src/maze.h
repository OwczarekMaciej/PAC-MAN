#ifndef MAZE_H
#define MAZE_H

#include <QObject>
#include <QGraphicsItem>


class Maze : public QObject
{
    Q_OBJECT
public:
    Maze(QObject *parent = 0);

    void createMaze();

    QList <QPoint> dots();
    QList <QPoint> boosts();

    bool can_entity_move(QPointF pos, QPoint direction);

    void check_for_items(QPointF pos, QPoint direction);
    void set_location(QPoint pos, char charcter);

    void set_pacman_pos(QPointF pos);

signals:
    void eat(QPoint pos);
    void boost_ability();

private:
    const int maze_width = 28;
    const int maze_hight = 31;
    QList <QList<int>> map;
    QPoint player_dir;

    QPoint pacman;
    QPointF pacman_pos;
};

#endif // MAZE_H

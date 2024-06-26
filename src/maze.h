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
    void setPos(QPointF pos);

    void set_pacman_pos(QPointF pos);
    QPointF get_pacman_pos();

    QPoint get_pacman_loc();
    QPoint get_pacman_dir();

    QPoint get_blinky_loc();
    QPoint get_clyde_loc();

    QList <QList<int>> map;
signals:
    void dot_eaten(QPoint pos);
    void boost_ability();
    void fail();

private:
    const int maze_width = 28;
    const int maze_hight = 31;
    const int tunnel_level = 14;


    QPoint pacman_dir;

    QPoint pacman, blinky, clyde;
    QPointF pacman_pos;

    bool nerf;
};

#endif // MAZE_H

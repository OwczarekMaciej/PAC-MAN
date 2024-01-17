#ifndef DOT_H
#define DOT_H

#include <QObject>
#include <QGraphicsItem>

#include "item.h"
#include "game_view.h"

class Dot : public Item
{
    Q_OBJECT
public:
    Dot(Game_view *parent_p);

    void eaten();

signals:
    void dot_eaten();

private:
    Game_view *parent;
};


#endif // DOT_H

#ifndef BOOST_H
#define BOOST_H


#include <QObject>
#include <QGraphicsItem>

#include "item.h"
#include "game_view.h"

class Boost : public Item
{
    Q_OBJECT
public:
    Boost(Game_view *parent_p);

    void eaten();

signals:
    void boost_eaten();

private:
    Game_view *parent;
};


#endif // DOT_H

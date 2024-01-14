#include "boost.h"

Boost::Boost(Game_view *parent_p)
{
    parent = parent_p;
    setPixmap(QPixmap(":/res/boost.png").scaledToWidth(28));
}

void Boost::eaten()
{
    emit boost_eaten();
    delete this;
}

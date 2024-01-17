#include "dot.h"

Dot::Dot(Game_view *parent_p)
{
    parent = parent_p;
    setPixmap(QPixmap(":/res/dot.png").scaledToWidth(16));
}

void Dot::eaten()
{
    emit dot_eaten();
    delete this;
}

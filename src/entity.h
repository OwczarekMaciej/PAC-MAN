#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <cmath>
#include <limits>

class Entity : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    virtual void set_direction(QPoint dir) = 0;
    virtual void start() = 0;
    virtual void die() = 0;

public slots:
    virtual void move() = 0;
};


#endif // ENTITY_H

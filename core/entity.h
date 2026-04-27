#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QPointF>
#include <QRectF>

class Entity : public QObject
{
    Q_OBJECT
public:
    virtual ~Entity() = default;

    virtual QPointF position() const = 0;
    virtual void setPosition(const QPointF& pos) = 0;
    virtual bool passable() const = 0;
    virtual int id() const = 0;
    virtual QRectF hitbox() const = 0;
    virtual qreal height() const = 0;
    virtual qreal width() const = 0;

};

#endif // ENTITY_H

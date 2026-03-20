#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QPointF>

class Entity : public QObject
{
    Q_OBJECT
public:
    virtual ~Entity() = default;

    virtual QPointF position() const = 0;
    virtual void setPosition(const QPointF& pos) = 0;
    virtual bool passable() const = 0;
    virtual int id() const = 0;

};

#endif // ENTITY_H

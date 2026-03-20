#ifndef ENTITYALIVE_H
#define ENTITYALIVE_H

#include "entity.h"

class EntityAlive : public Entity
{
    Q_OBJECT
public:
    virtual ~EntityAlive() = default;

    virtual int health() const = 0;
    virtual int level() const = 0;
    virtual int maxHealth() const = 0;
    virtual float speed() const = 0;

    virtual void setHealth(int health) = 0;
    virtual void setPosition(const QPointF& pos) = 0;
    virtual int setLevel() = 0;

public slots:
    virtual void takeDamage(int damage) = 0;
    virtual void onDeath() = 0;
};

#endif // ENTITYALIVE_H

#ifndef ENTITYCREATOR_H
#define ENTITYCREATOR_H

#include "entity.h"
#include "enemy.h"
#include "player.h"
#include "environment.h"

class EntityCreator
{
public:
    virtual ~EntityCreator() = default;

    virtual Entity* create(QObject *parent = nullptr) const = 0;
};

class EnemyCreator : public EntityCreator
{
public:
    explicit EnemyCreator(QObject *parent = nullptr) {};
    Entity* create(QObject *parent = nullptr) const override {return new Enemy(parent); }
};

class PlayerCreator : public EntityCreator
{
public:
    explicit PlayerCreator(QObject *parent = nullptr) {};
    Entity* create(QObject *parent = nullptr) const override {return new Player(parent); }
};

class EnvCreator : public EntityCreator
{
public:
    explicit EnvCreator(QObject *parent = nullptr) {};
    Entity* create(QObject *parent = nullptr) const override {return new Environment(parent); }
};

#endif // ENTITYCREATOR_H

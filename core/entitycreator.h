#ifndef ENTITYCREATOR_H
#define ENTITYCREATOR_H

#include "entity.h"
#include "enemy.h"
#include "player.h"
#include "environment.h"
#include "weapon/firestaff.h"

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
    ~EnemyCreator() {};
    Entity* create(QObject *parent = nullptr) const override {return new Enemy(parent); }
};

class PlayerCreator : public EntityCreator
{
public:
    explicit PlayerCreator(QObject *parent = nullptr) {};
    ~PlayerCreator() {};
    Entity* create(QObject *parent = nullptr) const override {return new Player(parent); }
};

class EnvCreator : public EntityCreator
{
public:
    explicit EnvCreator(QObject *parent = nullptr) {};
    ~EnvCreator() {};
    Entity* create(QObject *parent = nullptr) const override {return new Environment(parent); }
};

class WeaponCreator : public EntityCreator
{
    WeaponEntity::WeaponType m_weapon;
    EnemyModel* m_enemyModel;
public:
    explicit WeaponCreator(EnemyModel* enemyModel, WeaponEntity::WeaponType weapon, QObject *parent = nullptr)
        : m_enemyModel(enemyModel), m_weapon(weapon) {};
    ~WeaponCreator() {};
    Entity* create(QObject *parent = nullptr) const override {
        switch (m_weapon) {
        case WeaponEntity::WeaponType::FireStaff:
            return new FireStaff(m_enemyModel, parent);
        case WeaponEntity::WeaponType::Sword:
            // return new Sword(parent);
        default:
            return nullptr;
        }
    }



};

#endif // ENTITYCREATOR_H

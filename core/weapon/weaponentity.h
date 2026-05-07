#ifndef WEAPONENTITY_H
#define WEAPONENTITY_H

#include "entity.h"
#include "enemymodel.h"

class WeaponEntity : public Entity
{
    Q_OBJECT
public:
    virtual ~WeaponEntity() = default;

    virtual int level() const = 0;
    virtual float attackSpeed() const = 0;
    virtual float damage() const = 0;

    enum class WeaponType {
        FireStaff,
        Sword
    };

protected slots:
    virtual void attack() = 0;

};

#endif // WEAPONENTITY_H

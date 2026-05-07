#ifndef FIRESTAFF_H
#define FIRESTAFF_H

#include "weaponentity.h"
#include "player.h"
#include "enemymodel.h"

class FireStaff : public WeaponEntity
{
    Q_OBJECT
public:
    explicit FireStaff(EnemyModel* enemyModel, QObject* parent = nullptr);
    ~FireStaff() {};

    //entity
    QPointF position() const override {return Player::getPosition(); }
    bool passable() const override {return m_passable; }
    int id() const override {return m_id; }
    QRectF hitbox() const override {return m_hitbox; }
    qreal width() const override {return m_width; }
    qreal height() const override {return m_height; }

    //weapon entity
    int level() const override {return Player::getLevel(); }
    float attackSpeed() const override {return m_attackSpeed; }
    float damage() const override {return m_damage; }

    void setPosition(const QPointF& pos) override;

private slots:
    void attack() override;

private:
    float m_attackSpeed = 1;
    float m_damage = 1;
    qreal m_height = 5;
    qreal m_width = 5;
    bool m_passable = true;
    int m_id = 11;
    QRectF m_hitbox = QRectF(Player::getPosition().x(), Player::getPosition().y(), width(), height());

    float m_projSpeed = 1;
    float m_attackRange = 200;
    QTimer* m_attackTimer;
    EnemyModel* m_enemyModel;
};

#endif // FIRESTAFF_H

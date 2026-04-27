#ifndef ENEMY_H
#define ENEMY_H

#include <QTimer>

#include "entityalive.h"

class Enemy : public EntityAlive
{
    Q_OBJECT
    Q_PROPERTY(int health READ health NOTIFY healthChanged)
    Q_PROPERTY(int maxHealth READ maxHealth NOTIFY levelChanged)
    Q_PROPERTY(qreal width READ width)
    Q_PROPERTY(qreal height READ height)
    Q_PROPERTY(QPointF position READ position WRITE setPosition NOTIFY enemyPositionChanged)
public:
    explicit Enemy(QObject *parent = nullptr);
    ~Enemy();

    //virtual
    int health() const override {return m_health; }
    QPointF position() const override {return m_position; }
    int level() const override {return m_level; }
    bool passable() const override {return m_passable; }
    int id() const override {return m_id; }
    int maxHealth() const override {return m_maxHealth; }
    float speed() const override {return m_speed; }
    qreal width() const override {return m_width; }
    qreal height() const override {return m_height; }
    QRectF hitbox() const override {return m_hitbox; }

    void setHealth(int health) override;
    void setPosition(const QPointF& pos) override;
    int setLevel() override;

public slots:
    void takeDamage(int damage) override;
    void onDeath() override;
    //virtual

private slots:
    void updatePosition();

signals:
    void healthChanged();
    void enemyPositionChanged();
    void died();
    void levelChanged();

private:
    void startFollowingPlayer();

private:
    int const m_id = 2;
    int const m_passable = 1;
    float const m_speed = 1;
    int m_health = 100;
    int m_maxHealth = 100;
    int m_level = 1;
    QTimer* m_movementTimer = nullptr;
    QPointF m_position = QPointF(0, 0);
    qreal m_height = 40;
    qreal m_width = 40;
    QRectF m_hitbox = QRectF(m_position.x(), m_position.y(), width(), height());
};

#endif // ENEMY_H

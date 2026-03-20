#ifndef PLAYER_H
#define PLAYER_H

#include "entityalive.h"

class Player : public EntityAlive
{
    Q_OBJECT
    Q_PROPERTY(int health READ health NOTIFY healthChanged)
    Q_PROPERTY(int maxHealth READ maxHealth NOTIFY levelChanged)
    Q_PROPERTY(QPointF position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(int level READ level NOTIFY levelChanged)
    Q_PROPERTY(int experience READ experience NOTIFY experienceChanged)
    Q_PROPERTY(float speed READ speed)
public:
    explicit Player(QObject *parent = nullptr);

    //virtual
    int health() const override {return m_health; }
    QPointF position() const override { return m_position; }
    int level() const override { return m_level; }
    bool passable() const override {return m_passable; }
    int id() const override {return m_id; }
    int maxHealth() const override { return m_maxHealth; }
    float speed() const override {return m_speed;}

    void setHealth(int health) override;
    void setPosition(const QPointF& pos) override;
    int setLevel() override;

public slots:
    void takeDamage(int damage) override;
    void onDeath() override;
    //virtual

public:
    int experience() const { return m_experience; }
    bool followingMouse() const {return m_followingMouse; }

public slots:
    void heal(int amount);
    void addExperience(int exp);
    void startFollowingMouse();
    void updateFollowPosition(int x, int y);
    void stopFollowingMouse();

signals:
    void healthChanged();
    void positionChanged();
    void levelChanged();
    void experienceChanged();
    void died();

private:
    int const m_id = 0;
    bool const m_passable = 1;
    float const m_speed = 15;
    int m_health = 100;
    int m_maxHealth = 100;
    int m_level = 1;
    int m_experience = 0;
    int m_expPerLvl = 10;
    QPointF m_position = QPointF(0, 0);
    bool m_followingMouse = false;
};

#endif // PLAYER_H

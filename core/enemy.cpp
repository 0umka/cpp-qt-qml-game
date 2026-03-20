#include "enemy.h"
#include "player.h"
#include <QDebug>

Enemy::Enemy(QObject *parent)
    : EntityAlive{}
{}

void Enemy::setHealth(int health)
{
    health = qBound(0, health, m_maxHealth);
    if (m_health != health) {
        m_health = health;
        emit healthChanged();

        if (m_health == 0) {
            emit died();
        }
    }
}

void Enemy::takeDamage(int damage)
{
    setHealth(m_health - damage);
    qDebug() << "Enemy took" << damage << "damage, health now:" << m_health;
}

void Enemy::onDeath()
{

}

void Enemy::updateFollowPosition(int x, int y)
{

}

void Enemy::setPosition(const QPointF &pos)
{
    if (m_position != pos) {
        m_position = pos;
        emit positionChanged();
    }
}

int Enemy::setLevel()
{
    return 1;
}

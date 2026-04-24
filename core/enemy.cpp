#include "enemy.h"
#include "player.h"

#include <QDebug>

Enemy::Enemy(QObject *parent)
    : EntityAlive{}
{
    m_movementTimer = new QTimer(this);
    m_movementTimer->setInterval(16);
    connect(m_movementTimer, &QTimer::timeout, this, &Enemy::updatePosition);
    startFollowingPlayer();
}

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

void Enemy::updatePosition()
{
    QPointF delta = Player::getPosition() - m_position;
    float distance = std::hypot(delta.x(), delta.y());

    if (distance > m_speed) {
        QPointF currentPos = delta / distance;
        setPosition(m_position + currentPos * m_speed);
    }
}

void Enemy::startFollowingPlayer()
{
    m_movementTimer->start();
}

void Enemy::setPosition(const QPointF &pos)
{
    if (m_position != pos) {
        m_position = pos;
        emit enemyPositionChanged();
    }
}

int Enemy::setLevel()
{
    return 1;
}
